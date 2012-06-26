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
// Drummer app.

#include "peripherals/nunchuk/apps/drummer.h"

#include "peripherals/nunchuk/midi_output.h"
#include "peripherals/nunchuk/ui.h"

namespace nunchuk { namespace apps {

using namespace avrlib;

/* stattic */
uint8_t Drummer::pressed_;

/* stattic */
uint8_t Drummer::inhibit_;

/* stattic */
uint8_t Drummer::active_instrument_;

/* static */
const prog_AppInfo Drummer::app_info_ PROGMEM = {
  &OnInit, // void (*OnInit)();
  &OnPress, // void (*OnPress)();
  &OnRelease, // void (*OnRelease)();
  NULL, // void (*UpdateJoystick)(uint8_t x, uint8_t y);
  NULL, // void (*UpdateJoystickIntegrated)(int32_t x, int32_t y);
  &UpdateJoystickPolar, // void (*UpdateJoystickPolar)(uint8_t radius, uint8_t octant);
  &UpdateAccelerometer, // void (*UpdateAccelerometer)(uint8_t, uint8_t, uint8_t);
  NULL, // void (*OnShake)();
  &PlayLogotone // void (*PlayLogotone)();
};

/* static */
void Drummer::OnInit() {
  pressed_ = 0;
  active_instrument_ = 0;
  inhibit_ = 0;
}

/* static */
void Drummer::OnPress() {
  pressed_ = 1;
}

/* static */
void Drummer::OnRelease() {
  pressed_ = 0;
}

/* static */
void Drummer::UpdateJoystickPolar(uint8_t r, uint8_t octant) {
  if (r > 56) {
    active_instrument_ = octant << 1;
  }
}

static const prog_char octant_to_note[] PROGMEM = {
  36, 38,  // Kick, snare
  43, 61,  // Tom 2, Bongo
  45, 60,  // Tom 3, Bongo
  47, 64,  // Tom 4, Conga
  48, 63,  // Tom 5, Conga
  51, 75,  // Cowbell, clave
  68, 67,  // Agogo
  66, 65,  // Timbales
};

/* static */
void Drummer::UpdateAccelerometer(uint8_t x, uint8_t y, uint8_t z) {
  if (y > 192 && !inhibit_) {
    uint8_t note = pgm_read_byte(octant_to_note + \
        active_instrument_ + pressed_);
    midi_output.NoteOn(note, (y - 192) + 64);
    midi_output.NoteOff(note);
    inhibit_ = 1;
  }
  if (y < 160) {
    inhibit_ = 0;
  }
}

/* static */
void Drummer::PlayLogotone() {
  midi_output.NoteOn(36, 100);
  midi_output.NoteOff(36);
  ConstantDelay(250);
  midi_output.NoteOn(36, 100);
  midi_output.NoteOff(36);
  ConstantDelay(250);
  midi_output.NoteOn(38, 100);
  midi_output.NoteOff(38);
}

} }  // namespace nunchuk::apps
