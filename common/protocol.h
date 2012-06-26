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
// Voicecard protocol.
//
// 0x00 BULK size data...
// 0x10 noteH noteL velocity: triggers note
// 0x11 noteH noteL velocity: triggers note with legato
// 0x20 address value: write patch data
// 0x30 address value: write part data
// 0x40 address value: write entry in modulation matrix
// 0x5n value: write lfo n value
// 0x60 release
// 0x70 kill
// 0x8n retrigger envelope
// 0xf8 reset all controllers
// 0xf9 reset
// 0xfa lights out
// 0xfb trigger firmware update
// 0xfc get product ID
// 0xfd get version ID
// 0xfe ...
// 0xff sync/receive

#ifndef COMMON_PROTOCOL_H_
#define COMMON_PROTOCOL_H_

#include "avrlib/base.h"

namespace ambika {

enum ProtocolCommands {
  COMMAND_BULK_SEND = 0x00,
  
  COMMAND_NOTE_ON = 0x10,
  COMMAND_NOTE_ON_LEGATO = 0x11,
  
  COMMAND_WRITE_PATCH_DATA = 0x20,
  COMMAND_WRITE_PART_DATA = 0x30,
  COMMAND_WRITE_MOD_MATRIX = 0x40,
  COMMAND_WRITE_LFO = 0x50,
  
  COMMAND_RELEASE = 0x60,
  COMMAND_KILL = 0x70,
  
  COMMAND_RETRIGGER_ENVELOPE = 0x80,
  
  COMMAND_RESET_ALL_CONTROLLERS = 0xf8,
  COMMAND_RESET = 0xf9,

  COMMAND_LIGHTS_OUT = 0xfa,
  COMMAND_FIRMWARE_UPDATE_MODE = 0xfb,
  COMMAND_GET_SLAVE_ID = 0xfc,
  COMMAND_GET_VERSION_ID = 0xfd,
  COMMAND_SYNC = 0xff
};

enum SlaveId {
  SLAVE_ID_SOLO_VOICECARD = 0x01,
  SLAVE_ID_LAST
};

}  // namespace ambika

#endif  // COMMON_PROTOCOL_H_
