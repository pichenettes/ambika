// Copyright 2011 Emilie Gillet.
//
// Author: Emilie Gillet (emilie.o.gillet@gmail.com)
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
//
// -----------------------------------------------------------------------------
//
// MIDI output.

#ifndef PERIPHERALS_NUNCHUK_MIDI_OUTPUT_H_
#define PERIPHERALS_NUNCHUK_MIDI_OUTPUT_H_

#include "avrlib/base.h"
#include "avrlib/serial.h"
#include "avrlib/ring_buffer.h"

typedef avrlib::Serial<
    avrlib::SerialPort0,
    31250,
    avrlib::DISABLED,
    avrlib::POLLED> MidiSerialPort;

namespace nunchuk {

class MidiOutput {
 public:
  MidiOutput() { }
  
  static void Init();
  static void Process();

  static void AllSoundsOff();
  static void NoteOn(uint8_t note, uint8_t velocity);
  static void NoteOff(uint8_t note);
  static void Cc(uint8_t cc, uint8_t value);
  static void PitchBend(uint8_t msb);
  static void Modulation(uint8_t msb);
  static void Breath(uint8_t msb);
  static void SmoothCutoff(uint8_t value);
  static void Cutoff(uint8_t value);

  static uint8_t channel() {
    return channel_;
  }
  
  static void set_channel(uint8_t c);
  
  typedef uint8_t Value;
  enum {
    buffer_size = 128,
    data_size = 8,
  };
  
 private:
  static MidiSerialPort serial_port_;
  static avrlib::RingBuffer<MidiOutput> buffer_;
  static uint8_t use_serial_;
  static uint8_t channel_;
  static uint8_t previous_pitch_bend_msb_;
  static uint8_t previous_modulation_msb_;
  static uint8_t previous_breath_msb_;
  static uint8_t previous_cutoff_;
  static uint8_t smoothed_cutoff_;
  
  DISALLOW_COPY_AND_ASSIGN(MidiOutput);
};

extern MidiOutput midi_output;

}  // namespace nunchuk

#endif  // PERIPHERALS_NUNCHUK_MIDI_OUTPUT_H_
