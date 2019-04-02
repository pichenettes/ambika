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
// Cyclo-sequencer app.

#ifndef PERIPHERALS_NUNCHUK_APPS_CYCLO_SEQUENCER_H_
#define PERIPHERALS_NUNCHUK_APPS_CYCLO_SEQUENCER_H_

#include "peripherals/nunchuk/app.h"

namespace nunchuk { namespace apps {

class CycloSequencer {
 public:
  CycloSequencer() { }
  
  static void OnInit();
  static void OnPress();
  static void OnRelease();
  static void UpdateJoystickPolar(uint8_t radius, uint8_t octant);
  static void UpdateJoystickIntegrated(int32_t x, int32_t y);
  static void UpdateAccelerometer(uint8_t x, uint8_t y, uint8_t z);
  static void PlayLogotone();

  static const prog_AppInfo app_info_;
  
 private:
  static void SetActiveStep(uint8_t step);
  
  static uint8_t notes_[8];
  static uint8_t recording_mode_;
  static uint8_t active_step_;
  static uint8_t root_note_;
  static uint8_t retrigger_;
  static uint8_t center_cut_enabled_;
  static uint8_t inhibit_;
  
  DISALLOW_COPY_AND_ASSIGN(CycloSequencer);
};

} }  // namespace midipal::apps

#endif // PERIPHERALS_NUNCHUK_APPS_CYCLO_SEQUENCER_H_
