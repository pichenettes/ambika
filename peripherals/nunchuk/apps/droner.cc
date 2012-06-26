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

#include "peripherals/nunchuk/apps/droner.h"

#include "avrlib/op.h"
#include "avrlib/random.h"

#include "peripherals/nunchuk/midi_output.h"
#include "peripherals/nunchuk/ui.h"

namespace nunchuk { namespace apps {

using namespace avrlib;

/* static */
uint8_t Droner::note_list_[16];

/* static */
uint8_t Droner::num_notes_;

/* static */
uint8_t Droner::recording_mode_;

/* static */
uint8_t Droner::root_note_;

/* static */
uint8_t Droner::note_changed_;

/* static */
uint8_t Droner::inhibit_;

/* static */
const prog_AppInfo Droner::app_info_ PROGMEM = {
  &OnInit, // void (*OnInit)();
  &OnPress, // void (*OnPress)();
  &OnRelease, // void (*OnRelease)();
  &UpdateJoystick, // void (*UpdateJoystick)(uint8_t x, uint8_t y);
  &UpdateJoystickIntegrated, // void (*UpdateJoystickIntegrated)(int32_t x, int32_t y);
  NULL, // void (*UpdateJoystickPolar)(uint8_t radius, uint8_t octant);
  &UpdateAccelerometer, // void (*UpdateAccelerometer)(uint8_t, uint8_t, uint8_t);
  NULL, // void (*OnShake)();
  &PlayLogotone // void (*PlayLogotone)();
};

/* static */
void Droner::OnInit() {
  root_note_ = 60;
}

/* static */
void Droner::OnPress() {
  recording_mode_ = 1;
  app.ResetIntegration();
  note_changed_ = 0;
}

/* static */
void Droner::OnRelease() {
  recording_mode_ = 0;
  if (!note_changed_) {
    for (uint8_t i = 0; i < num_notes_; ++i) {
      midi_output.NoteOff(note_list_[i]);
    }
    num_notes_ = 0;
    note_list_[0] = 0;
    root_note_ = 60;
  } else {
    root_note_ = note_list_[num_notes_];
    num_notes_ = (num_notes_ + 1) & 0xf;
    note_list_[num_notes_] = root_note_ + 7;
  }
  inhibit_ = 0;
}

/* static */
void Droner::UpdateJoystick(uint8_t x, uint8_t y) {
  if (!recording_mode_) {
    midi_output.PitchBend(x >> 1);
    if (y > 128) {
      midi_output.Modulation(y - 128);
    } else {
      midi_output.Breath(128 - y);
    }
  }
}

/* static */
void Droner::UpdateJoystickIntegrated(int32_t x, int32_t y) {
  if (recording_mode_) {
    uint8_t note = Clip(root_note_ + (y >> 12) + (x >> 14), 0, 127);
    if (note != note_list_[num_notes_]) {
      uint8_t note_available = 1;
      for (uint8_t i = 0; i < num_notes_; ++i) {
        if (note_list_[i] == note) {
          note_available = 0;
          break;
        }
      }
      if (note_available) {
        note_changed_ = 1;
        midi_output.NoteOff(note_list_[num_notes_]);
        note_list_[num_notes_] = note;
        midi_output.NoteOn(note_list_[num_notes_], 100);
      }
    }
  }
}

/* static */
void Droner::UpdateAccelerometer(uint8_t x, uint8_t y, uint8_t z) {
  if (y > 250 && !inhibit_ && num_notes_) {
    uint8_t num_notes_played = 0;
    while (!num_notes_played) {
      for (uint8_t i = 0; i < num_notes_; ++i) {
        midi_output.NoteOff(note_list_[i]);
        if (Random::GetByte() & 0x80) {
          midi_output.NoteOn(note_list_[i], 50 + ((Random::GetByte()) >> 2));
          ++num_notes_played;
        }
        inhibit_ = 50;
      }
    }
  }
  if (inhibit_) {
    --inhibit_;
  }
  if (z > 192) {
    midi_output.SmoothCutoff(127);
  } else if (z > 64) {
    midi_output.SmoothCutoff(z - 64);
  } else {
    midi_output.SmoothCutoff(0);
  }
}

/* static */
void Droner::PlayLogotone() {
  midi_output.NoteOn(48, 100);
  midi_output.NoteOn(55, 100);
  midi_output.NoteOn(60, 100);
  ConstantDelay(1000);
  midi_output.NoteOff(48);
  midi_output.NoteOff(55);
  midi_output.NoteOff(60);
}

} }  // namespace nunchuk::apps
