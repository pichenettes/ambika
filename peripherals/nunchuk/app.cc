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

#include "peripherals/nunchuk/app.h"

#include "avrlib/op.h"
#include "avrlib/time.h"

#include "peripherals/nunchuk/apps/cyclo_sequencer.h"
#include "peripherals/nunchuk/apps/droner.h"
#include "peripherals/nunchuk/apps/drummer.h"

#include "peripherals/nunchuk/midi_output.h"
#include "peripherals/nunchuk/ui.h"

namespace nunchuk {

using namespace avrlib;

/* static */
AppInfo App::app_info_;

/* static */
uint8_t App::current_app_index_;

/* static */
uint8_t App::inhibit_app_change_;

/* static */
uint8_t App::c_status_;

/* static */
uint8_t App::z_status_;

/* static */
int32_t App::integrated_x_;

/* static */
int32_t App::integrated_y_;


const AppInfo* registry[] = {
  &apps::Drummer::app_info_,
  &apps::CycloSequencer::app_info_,
  &apps::Droner::app_info_,
};

const uint8_t kNumApps = sizeof(registry) / sizeof(const AppInfo*);

/* static */
void App::Init() {
  // TODO(pichenettes): load from eeprom.
  Launch(0);
}

/* static */
void App::NextApp() {
  Launch(current_app_index_ + 1);
}

/* static */
void App::Launch(uint8_t app_index) {
  if (app_index >= kNumApps) {
    app_index = 0;
  }
  if (current_app_index_ != app_index) {
    current_app_index_ = app_index;
    // TODO(pichenettes): save to eeprom.
  }
  memcpy_P(&app_info_, registry[current_app_index_], sizeof(AppInfo));
  if (app_info_.OnInit) {
    (*app_info_.OnInit)();
  }
  midi_output.AllSoundsOff();
  // TODO(pichenettes): send an all notes off message.
  if (app_info_.PlayLogotone) {
    (*app_info_.PlayLogotone)();
  }
  ResetIntegration();
}

/* static */
void App::ResetIntegration() {
  integrated_x_ = 0;
  integrated_y_ = 0;
}

/* static */
void App::NextMidiChannel() {
  uint8_t c = midi_output.channel();
  c = (c + 1) & 0xf;
  midi_output.set_channel(c);
  note_led.Low();
  connection_led.Low();
  for (uint8_t i = 0; i < ((c & 0x07) + 1) * 2; ++i) {
    if (c & 0x8) {
      note_led.Toggle();
    } else {
      connection_led.Toggle();
    }
    ConstantDelay(150);
  }
}

/* static */
void App::ProcessNunchuk(
    uint8_t x,
    uint8_t y,
    uint8_t acc_x,
    uint8_t acc_y,
    uint8_t acc_z,
    uint8_t c_pressed,
    uint8_t z_pressed) {

  // Send events for joystick.
  if (app_info_.UpdateJoystick) {
    (*app_info_.UpdateJoystick)(x, y);
  }
  int8_t dx = static_cast<int8_t>(x) - 128;
  int8_t dy = static_cast<int8_t>(y) - 128;
  if (app_info_.UpdateJoystickPolar) {
    uint8_t octant = 0;
    uint8_t r = S8S8MulShift8(dx, dx) + S8S8MulShift8(dy, dy);
    if (dx >= 0) {
      if (dy >= 0) {
        if (dy >= dx) {
          octant = 0;
        } else {
          octant = 1;
        }
      } else {
        if (-dy >= dx) {
          octant = 3;
        } else {
          octant = 2;
        }
      }
    } else {
      if (dy >= 0) {
        if (dy >= -dx) {
          octant = 7;
        } else {
          octant = 6;
        }
      } else {
        if (-dy >= -dx) {
          octant = 4;
        } else {
          octant = 5;
        }
      }
    }
    (*app_info_.UpdateJoystickPolar)(r, octant);
  }
  if (dx > 16 || dx < -16) {
    integrated_x_ += dx;
  }
  if (dy > 16 || dy < -16) {
    integrated_y_ += dy;
  }
  if (app_info_.UpdateJoystickIntegrated) {
    (*app_info_.UpdateJoystickIntegrated)(integrated_x_, integrated_y_);
  }

  // Send events for accelerometer
  if (app_info_.UpdateAccelerometer) {
    (*app_info_.UpdateAccelerometer)(acc_x, acc_y, acc_z);
  }
  if (app_info_.OnShake) {
    if (0) {
      (*app_info_.OnShake)();
    }
  }
  
  if (c_status_) {
    // C has been released
    if (!c_pressed && !inhibit_app_change_) {
      NextApp();
    }
    if (z_status_ && !z_pressed) {
      NextMidiChannel();
      inhibit_app_change_ = 1;
    }
  } else {
    inhibit_app_change_ = 0;
    // Send events for the Z button
    if (z_status_ && !z_pressed) {
      if (app_info_.OnRelease) {
        (*app_info_.OnRelease)();
      }
    } else {
      if (!z_status_ && z_pressed) {
        if (app_info_.OnPress) {
          (*app_info_.OnPress)();
        }
      }
    }
  }
  z_status_ = z_pressed;
  c_status_ = c_pressed;
}

/* extern */
App app;

}  // namespace nunchuk
