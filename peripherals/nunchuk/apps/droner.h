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
// Droner app.

#ifndef PERIPHERALS_NUNCHUK_APPS_DRONER_H_
#define PERIPHERALS_NUNCHUK_APPS_DRONER_H_

#include "peripherals/nunchuk/app.h"

namespace nunchuk { namespace apps {

class Droner {
 public:
  Droner() { }
  
  static void OnInit();
  static void OnPress();
  static void OnRelease();
  static void UpdateJoystick(uint8_t x, uint8_t y);
  static void UpdateJoystickIntegrated(int32_t x, int32_t y);
  static void UpdateAccelerometer(uint8_t x, uint8_t y, uint8_t z);
  static void PlayLogotone();

  static const prog_AppInfo app_info_;
  
 private:
  static uint8_t note_list_[16];
  static uint8_t num_notes_;
  static uint8_t recording_mode_;
  static uint8_t root_note_;
  static uint8_t note_changed_;
  static uint8_t inhibit_;
  
  DISALLOW_COPY_AND_ASSIGN(Droner);
};

} }  // namespace midipal::apps

#endif // PERIPHERALS_NUNCHUK_APPS_DRONER_H_
