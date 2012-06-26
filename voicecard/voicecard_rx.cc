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

#include "voicecard/voicecard_rx.h"

namespace ambika {

/* static */
RingBuffer<InputBufferSpecs> VoicecardProtocolRx::buffer_;

/* static */
uint8_t VoicecardProtocolRx::command_;

/* static */
uint8_t VoicecardProtocolRx::state_;

/* static */
uint8_t VoicecardProtocolRx::data_size_;

/* static */
uint8_t* VoicecardProtocolRx::data_ptr_;

/* static */
uint8_t VoicecardProtocolRx::rx_led_counter_;

/* static */
uint8_t VoicecardProtocolRx::arguments_[3];

/* static */
uint8_t VoicecardProtocolRx::lights_out_;

/* extern */
VoicecardProtocolRx voicecard_rx;

}  // namespace ambika
