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
// A page which allows up to 8 user-selected parameters to be tweaked.

#include "controller/ui_pages/performance_page.h"

#include "avrlib/string.h"

#include "controller/display.h"
#include "controller/leds.h"
#include "controller/multi.h"
#include "controller/ui_pages/parameter_editor.h"

namespace ambika {

/* static */
const prog_EventHandlers PerformancePage::event_handlers_ PROGMEM = {
  ParameterEditor::OnInit,
  ParameterEditor::SetActiveControl,
  OnIncrement,
  OnClick,
  ParameterEditor::OnPot,
  OnKey,
  NULL,
  ParameterEditor::OnIdle,
  ParameterEditor::UpdateScreen,
  UpdateLeds,
  OnDialogClosed,
};

/* static */
uint8_t PerformancePage::note_ = 60;

/* static */
uint8_t PerformancePage::note_active_ = 0;

/* static */
uint8_t PerformancePage::OnIncrement(int8_t increment) {
  if (note_active_) {
    if ((note_ < 0x7f && increment > 0) ||
        (note_ > 0 && increment < 0)) {
      multi.StartNote(note_ + increment);
      multi.StopNote(note_);
      note_ += increment;
    }
    return 1;
  }
}

/* static */
uint8_t PerformancePage::OnClick() {
  if (!note_active_) {
    multi.StartNote(note_);
    note_active_ = 1;
  } else {
    multi.StopNote(note_);
    note_active_ = 0;
  }
  return 1;
}

/* static */
uint8_t PerformancePage::OnKey(uint8_t key) {
  return ParameterEditor::OnKey(key);
}

/* static */
void PerformancePage::UpdateLeds() {
  leds.set_pixel(LED_7, 0xf0);
  if (multi.running()) {
    if (multi.step() >= 0x8) {
      leds.set_pixel(LED_STATUS, 0x0f);
    }
    leds.set_pixel(LED_1 + (multi.step() & 0x07), 0x03);
  }
}

}  // namespace ambika
