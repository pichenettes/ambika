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
//
// -----------------------------------------------------------------------------
//
// Main definitions.

#ifndef VOICECARD_VOICECARD_H_
#define VOICECARD_VOICECARD_H_

#include "avrlib/base.h"

#include <avr/pgmspace.h>

namespace ambika {

// One control signal sample is generated for each 40 audio sample.
static const uint8_t kControlRate = 40;

// The latency is 1ms, with a buffer storing 4ms of audio.
static const uint8_t kAudioBlockSize = kControlRate;

const uint8_t kSystemVersion = 0x10;

static uint8_t* kFirmwareUpdateFlagPtr = (uint8_t*)(E2END);

enum VoicecardFirmwareUpdateStatus {
  FIRMWARE_UPDATE_DONE = 0,
  FIRMWARE_UPDATE_REQUESTED = 1,
  FIRMWARE_UPDATE_PROBING_BOOT = 2,
};

}  // namespace ambika

#endif  // VOICECARD_VOICECARD_H_
