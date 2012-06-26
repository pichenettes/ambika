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
// Cyclo-sequencer app.

#include "peripherals/nunchuk/apps/cyclo_sequencer.h"

#include <string.h>

#include "avrlib/op.h"
#include "avrlib/random.h"

#include "peripherals/nunchuk/midi_output.h"
#include "peripherals/nunchuk/ui.h"

namespace nunchuk { namespace apps {

using namespace avrlib;

/* static */
uint8_t CycloSequencer::notes_[8];

/* static */
uint8_t CycloSequencer::active_step_;

/* static */
uint8_t CycloSequencer::recording_mode_;

/* static */
uint8_t CycloSequencer::root_note_;

/* static */
uint8_t CycloSequencer::inhibit_;

/* static */
uint8_t CycloSequencer::retrigger_;

/* static */
uint8_t CycloSequencer::center_cut_enabled_;

/* static */
const prog_AppInfo CycloSequencer::app_info_ PROGMEM = {
  &OnInit, // void (*OnInit)();
  &OnPress, // void (*OnPress)();
  &OnRelease, // void (*OnRelease)();
  NULL, // void (*UpdateJoystick)(uint8_t x, uint8_t y);
  &UpdateJoystickIntegrated, // void (*UpdateJoystickIntegrated)(int32_t x, int32_t y);
  &UpdateJoystickPolar, // void (*UpdateJoystickPolar)(uint8_t, uint8_t);
  &UpdateAccelerometer, // void (*UpdateAccelerometer)(uint8_t, uint8_t, uint8_t);
  NULL, // void (*OnShake)();
  &PlayLogotone // void (*PlayLogotone)();
};

/* static */
void CycloSequencer::OnInit() {
  for (uint8_t i = 0; i < 8; i += 2) {
    notes_[i] = 48;
    notes_[i + 1] = 60;
  }
  notes_[7] = 43;
  active_step_ = 0;
  root_note_ = 0;
}

/* static */
void CycloSequencer::OnPress() {
  recording_mode_ = 1;
  midi_output.NoteOff(notes_[active_step_]);
  root_note_ = notes_[active_step_];
  app.ResetIntegration();
}

/* static */
void CycloSequencer::OnRelease() {
  recording_mode_ = 0;
  inhibit_ = 0;
}

/* static */
void CycloSequencer::UpdateJoystickPolar(uint8_t r, uint8_t octant) {
  if (!recording_mode_) {
    if (r > 56) {
      SetActiveStep(octant);
      center_cut_enabled_ = 1;
    } else if (r < 16) {
      if (center_cut_enabled_) {
        midi_output.NoteOff(notes_[active_step_]);
      }
      retrigger_ = 1;
      center_cut_enabled_ = 0;
    }
  }
}

/* static */
void CycloSequencer::UpdateJoystickIntegrated(int32_t x, int32_t y) {
  if (recording_mode_) {
    uint8_t note = Clip(root_note_ + (y >> 12) + (x >> 14), 0, 127);
    if (note != notes_[active_step_]) {
      midi_output.NoteOff(notes_[active_step_]);
      notes_[active_step_] = note;
      midi_output.NoteOn(note, 100);
    }
  }
}

/* static */
void CycloSequencer::SetActiveStep(uint8_t step) {
  if (step != active_step_) {
    midi_output.NoteOff(notes_[active_step_]);
    active_step_ = step;
    midi_output.NoteOn(notes_[active_step_], 100);
  } else {
    if (retrigger_) {
      retrigger_ = 0;
      midi_output.NoteOn(notes_[active_step_], 100);
    }
  }
}


/* static */
void CycloSequencer::UpdateAccelerometer(uint8_t x, uint8_t y, uint8_t z) {
  if (y > 224 && !inhibit_) {
    SetActiveStep((active_step_ + 1) & 0x7);
    inhibit_ = 50;
  }
  if (inhibit_) {
    --inhibit_;
  }
}

/* static */
void CycloSequencer::PlayLogotone() {
  for (uint8_t i = 24; i <= 60; i += 12) {
    midi_output.NoteOn(i, 100);
    ConstantDelay(100);
    midi_output.NoteOff(i);
  }
}

} }  // namespace nunchuk::apps
