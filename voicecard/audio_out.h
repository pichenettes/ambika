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
// Instance of the audio out class.

#ifndef VOICECARD_AUDIO_OUT_H_
#define VOICECARD_AUDIO_OUT_H_

#include "avrlib/base.h"
#include "avrlib/gpio.h"
#include "avrlib/ring_buffer.h"
#include "voicecard/voicecard.h"

namespace ambika {

struct AudioBufferSpecs {
  typedef uint8_t Value;
  enum {
    buffer_size = 128,
    data_size = 8,
  };
};

extern avrlib::RingBuffer<AudioBufferSpecs> audio_buffer;

}  // namespace ambika

#endif  // VOICECARD_AUDIO_OUT_H_
