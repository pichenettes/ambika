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
// System settings data structure.

#ifndef CONTROLLER_SYSTEM_SETTINGS_H_
#define CONTROLLER_SYSTEM_SETTINGS_H_

#include "avrlib/base.h"

#include <avr/pgmspace.h>

namespace ambika {

enum MidiOutMode {
  MIDI_OUT_THRU,
  MIDI_OUT_SEQUENCER,
  MIDI_OUT_CONTROLLER,
  MIDI_OUT_CHAIN,
  MIDI_OUT_FULL
};

struct SystemSettingsData {
  uint8_t midi_in_mask;
  uint8_t midi_out_mode;
  uint8_t show_help;
  uint8_t snap;
  uint8_t autobackup;
  uint8_t voicecard_leds;
  uint8_t swap_leds_colors;
  uint8_t padding[8];
  uint8_t checksum;
};

typedef SystemSettingsData PROGMEM prog_SystemSettingsData;

class SystemSettings {
 public:
  SystemSettings() { }
  
  static void Save();
  static void Init(bool force_reset);
  
  static inline SystemSettingsData* mutable_data() { return &data_; }
  static inline const SystemSettingsData& data() { return data_; }
  
  static inline uint8_t rx_sysex() {
    return !(data_.midi_in_mask & 1);
  }
  static inline uint8_t rx_program_change() {
    return !(data_.midi_in_mask & 2);
  }
  static inline uint8_t rx_nrpn() {
    return !(data_.midi_in_mask & 4);
  }
  static inline uint8_t rx_cc() {
    return !(data_.midi_in_mask & 8);
  }
  
 private:
  static SystemSettingsData data_;
 
  DISALLOW_COPY_AND_ASSIGN(SystemSettings);
};

enum SystemParameter {
  PRM_SYSTEM_MIDI_IN_MASK,
  PRM_SYSTEM_MIDI_OUT_MODE,
  PRM_SYSTEM_SHOW_HELP,
  PRM_SYSTEM_SNAP,
  PRM_SYSTEM_AUTOBACKUP,
  PRM_SYSTEM_VOICECARD_LEDS,
  PRM_SYSTEM_VOICECARD_SWAP_LEDS_COLORS
};

extern SystemSettings system_settings;

}  // namespace ambika

#endif  // CONTROLLER_SYSTEM_SETTINGS_H_
