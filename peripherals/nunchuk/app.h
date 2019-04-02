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
// Base class for each Nunchuk parsing-"app".

#ifndef PERIPHERALS_NUNCHUK_APP_H_
#define PERIPHERALS_NUNCHUK_APP_H_

#include <avr/pgmspace.h>

#include "avrlib/base.h"

namespace nunchuk {

struct AppInfo {
  void (*OnInit)();
  void (*OnPress)();
  void (*OnRelease)();
  void (*UpdateJoystick)(uint8_t x, uint8_t y);
  void (*UpdateJoystickIntegrated)(int32_t x, int32_t y);
  void (*UpdateJoystickPolar)(uint8_t radius, uint8_t octant);
  void (*UpdateAccelerometer)(uint8_t x, uint8_t y, uint8_t z);
  void (*OnShake)();
  void (*PlayLogotone)();
};

typedef AppInfo PROGMEM prog_AppInfo;

class App {
 public:
  App() { }
  
  static void Init();
  
  static void NextMidiChannel();
  static void NextApp();
  static void ResetIntegration();
  static void ProcessNunchuk(
      uint8_t x,
      uint8_t y,
      uint8_t acc_x,
      uint8_t acc_y,
      uint8_t acc_z,
      uint8_t c_pressed,
      uint8_t z_pressed);

 private:
  static void Launch(uint8_t app_index);
  
  static uint8_t current_app_index_;
  static uint8_t inhibit_app_change_;
  static int32_t integrated_x_;
  static int32_t integrated_y_;
  
  static uint8_t c_status_;
  static uint8_t z_status_;
  static AppInfo app_info_;
  
  DISALLOW_COPY_AND_ASSIGN(App);
};

extern App app;

}  // namespace nunchuk

#endif  // PERIPHERALS_NUNCHUK_APP_H_
