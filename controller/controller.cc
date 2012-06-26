// Copyright 2011 Olivier Gillet.
//
// Author: Olivier Gillet (ol.gillet@gmail.com)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.


#include <avr/interrupt.h>

#include "avrlib/boot.h"
#include "avrlib/serial.h"
#include "avrlib/watchdog_timer.h"

#include "controller/midi_dispatcher.h"
#include "controller/multi.h"
#include "controller/resources.h"
#include "controller/storage.h"
#include "controller/system_settings.h"
#include "controller/ui.h"
#include "controller/voicecard_tx.h"

#include "midi/midi.h"

using namespace ambika;
using namespace avrlib;
using namespace midi;

// Midi input.
MidiIO midi_io;
MidiBuffer midi_in_buffer;
MidiStreamParser<MidiDispatcher> midi_parser;

inline void FlushMidiOut() {
  // Try to flush the high priority buffer first.
  if (midi_dispatcher.readable_high_priority()) {
    if (midi_io.writable()) {
      midi_io.Overwrite(midi_dispatcher.ImmediateReadHighPriority());
    }
  } else {
    if (midi_dispatcher.readable_low_priority()) {
      if (midi_io.writable()) {
        midi_io.Overwrite(midi_dispatcher.ImmediateReadLowPriority());
      }
    }
  }
}

inline void PollMidiIn() {
  if (midi_io.readable()) {
    midi_in_buffer.NonBlockingWrite(midi_io.ImmediateRead());
  }
}

// This timer is responsible for:
// - Flushing the MIDI out data, at a rate of 4.882kHz
// - Debouncing the switches and refreshing the LCD at 4.882kHz
// - Ticking the ms sys clock at 4.882kHz / 4 = 1.221 kHz
ISR(TIMER1_OVF_vect, ISR_NOBLOCK) {
  static uint8_t cycle = 0;
  PollMidiIn();
  FlushMidiOut();
  ui.Poll();
  if ((cycle & 3) == 0) {
    TickSystemClock();
  }
  ++cycle;
  if (cycle == 48) {
    cycle = 0;
    storage.Tick();
  }
}

// This timer is responsible for keeping track of time for the internal clock,
// and for sending data to the voicecards.
ISR(TIMER2_OVF_vect) {
  multi.Tick();
  voicecard_tx.SendBytes();
}

void Init() {
  sei();
  UCSR0B = 0;
  UCSR1B = 0;
  ResetWatchdog();
  Gpio<PortC, 0>::set_mode(DIGITAL_OUTPUT);
  system_settings.Init(false);
  midi_io.Init();
  
  Timer<1>::set_prescaler(2);
  Timer<1>::set_mode(TIMER_PWM_PHASE_CORRECT);
  Timer<2>::set_prescaler(1);
  Timer<2>::set_mode(TIMER_PWM_PHASE_CORRECT);
  Timer<2>::Start();
  
  ui.Init();
  Timer<1>::Start();

  voicecard_tx.Init();
  voicecard_tx.SyncAllVoices();
  if (!system_settings.data().voicecard_leds) {
    voicecard_tx.LightsOut();
  }
  if (ui.shifted()) {
    system_settings.Init(true);
  }
  multi.Init(ui.shifted());

  storage.Init();
}

int main(void) {
  Init();
  ui.FlushEvents();
  while (1) {
    // Do some MIDI.
    while (midi_in_buffer.readable()) {
      midi_parser.PushByte(midi_in_buffer.ImmediateRead());
    }
    // Do some LFOs and clocks.
    multi.UpdateClocks();
    // Do some display.
    ui.DoEvents();
  }
}
