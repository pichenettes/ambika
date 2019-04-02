// Copyright 2009 Emilie Gillet.
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
// LFO (cheap oscillator).
//
// Contrary to oscillators which are templatized "static singletons", to
// generate the fastest, most specialized code, LFOs are less
// performance-sensitive and are thus implemented as a traditional class.

#ifndef COMMON_LFO_H_
#define COMMON_LFO_H_

#include "avrlib/base.h"
#include "avrlib/op.h"
#include "avrlib/random.h"
#include "common/patch.h"

using avrlib::InterpolateSample;
using avrlib::Random;

namespace ambika {

extern const prog_uint8_t wav_res_lfo_waveforms[] PROGMEM;

class Lfo {
 public:
  Lfo() { }

  uint8_t Render(uint8_t shape) {
    phase_ += phase_increment_;
    looped_ = phase_ < phase_increment_;
    
    // Compute the LFO value.
    uint8_t value;
    switch (shape) {
      case LFO_WAVEFORM_RAMP:
        value = phase_ >> 8;
        break;
        
      case LFO_WAVEFORM_S_H:
        if (looped_) {
          value_ = Random::GetByte();
        }
        value = value_;
        break;

      case LFO_WAVEFORM_TRIANGLE:
        value = (phase_ & 0x8000) ?
            phase_ >> 7 :
            ~static_cast<uint8_t>(phase_ >> 7);
        break;

      case LFO_WAVEFORM_SQUARE:
        value = (phase_ & 0x8000) ? 255 : 0;
        break;

#ifndef DISABLE_WAVETABLE_LFOS
      default:
        {
          uint8_t shape_offset = shape - LFO_WAVEFORM_WAVE_1;
          uint16_t offset = static_cast<uint16_t>(shape_offset) << 8;
          offset += shape_offset;
          value = InterpolateSample(wav_res_lfo_waveforms + offset, phase_);
        }
        break;
#endif  // DISABLE_WAVETABLE_LFOS
    }
    return value;
  }

  void set_phase(uint16_t phase) {
    looped_ = phase <= phase_;
    phase_ = phase;
  }
  

  void set_phase_increment(uint16_t phase_increment) {
    phase_increment_ = phase_increment;
  }
  
  uint8_t looped() const { return looped_; }

 private:
  // Phase increment.
  uint16_t phase_increment_;

  // Current phase of the lfo.
  uint16_t phase_;
  uint8_t looped_;

  // Current value of S&H.
  uint8_t value_;
  uint8_t step_;
  
  DISALLOW_COPY_AND_ASSIGN(Lfo);
};

}  // namespace ambika

#endif  // COMMON_LFO_H_
