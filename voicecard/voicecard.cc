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

#include "voicecard/voicecard.h"

#include "avrlib/boot.h"
#include "avrlib/gpio.h"
#include "avrlib/parallel_io.h"
#include "avrlib/timer.h"

#include "voicecard/audio_out.h"
#include "voicecard/leds.h"
#include "voicecard/resources.h"
#include "voicecard/voice.h"
#include "voicecard/voicecard_rx.h"

using namespace avrlib;
using namespace ambika;

static const uint8_t kPinVcaOut = 3;
static const uint8_t kPinVcfResonanceOut = 5;
static const uint8_t kPinVcfCutoffOut = 6;

PwmOutput<kPinVcfCutoffOut> vcf_cutoff_out;
PwmOutput<kPinVcfResonanceOut> vcf_resonance_out;
PwmOutput<kPinVcaOut> vca_out;

ParallelPort<PortC, PARALLEL_TRIPLE_LOW> vcf_mode;

Gpio<PortB, 0> log_vca;
Gpio<PortB, 1> inverted_resonance;

UartSpiMaster<UartSpiPort0, Gpio<PortD, 2>, 2> dac_interface;

static uint8_t update_vca;
static const uint8_t dac_scale = 16;

ISR(TIMER2_OVF_vect) {
  static uint8_t sample_counter = 0;
  static Word vca_12bits;
  
  if (update_vca) {
    dac_interface.Strobe();
    update_vca = 0;
    dac_interface.Overwrite(vca_12bits.bytes[1]);
    dac_interface.Overwrite(vca_12bits.bytes[0]);
    dac_interface.Wait();
    uint16_t next_vca_value;
    if (log_vca.is_low()) {
      next_vca_value = ambika::ResourcesManager::Lookup<uint16_t, uint8_t>(
          lut_res_vca_linearization,
          voice.vca());
    } else {
      next_vca_value = voice.vca() * dac_scale;
    }
    vca_12bits.value = next_vca_value | 0x1000;
  }
  
  uint8_t sample = audio_buffer.ImmediateRead();
  if (++sample_counter >= voice.crush()) {
    dac_interface.Strobe();
    sample_counter = 0;
    Word sample_12bits;
    sample_12bits.value = (sample * dac_scale) | 0x9000;
    dac_interface.Overwrite(sample_12bits.bytes[1]);
    dac_interface.Overwrite(sample_12bits.bytes[0]);
  }
  voicecard_rx.Receive();
}

Gpio<PortD, 7> timing_signal;

inline void Init() {
  sei();
  UCSR0B = 0;
  ResetWatchdog();
  
  dac_interface.Init();

  rx_led.set_mode(DIGITAL_OUTPUT);
  note_led.set_mode(DIGITAL_OUTPUT);
  
  vcf_cutoff_out.Init();
  vcf_resonance_out.Init();
  vca_out.Init();
  vcf_mode.set_mode(DIGITAL_OUTPUT);

  voicecard_rx.Init();
  timing_signal.set_mode(DIGITAL_OUTPUT);
  voice.Init();
  
  log_vca.set_mode(DIGITAL_INPUT);
  log_vca.High();
  inverted_resonance.set_mode(DIGITAL_INPUT);
  inverted_resonance.High();
  
  dac_interface.Strobe();
  dac_interface.Overwrite(0x10 | 0x0f);
  dac_interface.Overwrite(0xff);
  
  // Successful boot!
  if (eeprom_read_byte(kFirmwareUpdateFlagPtr) != FIRMWARE_UPDATE_DONE) {
    eeprom_write_byte(kFirmwareUpdateFlagPtr, FIRMWARE_UPDATE_DONE);
  }
  
  // Initialize all the PWM outputs to 39kHz, phase correct mode.
  Timer<0>::set_prescaler(1);
  Timer<0>::set_mode(TIMER_PWM_PHASE_CORRECT);
  Timer<1>::set_prescaler(1);
  Timer<1>::set_mode(TIMER_PWM_PHASE_CORRECT);
  Timer<2>::set_prescaler(1);
  Timer<2>::set_mode(TIMER_PWM_PHASE_CORRECT);
  Timer<2>::Start();
}

static uint8_t filter_mode_bytes[] = { 0, 1, 2, 3 };
static uint8_t leds_timeout = 0;

int main(void) {
  Init();
  // For testing only...
  // voice.Trigger(60 * 128, 100, 0);
  while (1) {
    // Check if there's a block of samples to fill.
    if (audio_buffer.writable() >= kAudioBlockSize) {
      voicecard_rx.TickRxLed();
      timing_signal.Low();
      voice.ProcessBlock();
      vcf_cutoff_out.Write(voice.cutoff());
      if (inverted_resonance.is_low()) {
        vcf_resonance_out.Write(~voice.resonance());
      } else {
        vcf_resonance_out.Write(voice.resonance());
      }
      vcf_mode.Write(filter_mode_bytes[voice.patch().filter[0].mode]);
      timing_signal.High();
      update_vca = 1;
    }
    voicecard_rx.Process();
  }
}
