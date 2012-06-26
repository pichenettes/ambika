// Copyright 2009 Olivier Gillet.
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
// Global system settings.

#include "controller/resources.h"
#include "controller/storage.h"
#include "controller/system_settings.h"

#include <avr/eeprom.h>

namespace ambika {

/* static */
SystemSettingsData SystemSettings::data_;

static const prog_SystemSettingsData init_settings PROGMEM = {
  0, 0, 1, 0, 1, 1
};

/* static */
void SystemSettings::Save() {
  data_.checksum = Storage::Checksum(&data_, sizeof(SystemSettingsData) - 1);
  eeprom_write_block(
      &data_,
      (void*)(E2END - sizeof(SystemSettingsData)),
      sizeof(SystemSettingsData));
}

/* static */
void SystemSettings::Init(bool force_reset) {
  eeprom_read_block(
      &data_,
      (void*)(E2END - sizeof(SystemSettingsData)),
      sizeof(SystemSettingsData));
  if (data_.checksum != Storage::Checksum(
          &data_, sizeof(SystemSettingsData) - 1) || force_reset) {
    ResourcesManager::Load(&init_settings, 0, &data_);
  }
}

/* extern */
SystemSettings system_settings;

}  // namespace ambika
