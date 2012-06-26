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
// Base UI page class.

#include "controller/ui_pages/ui_page.h"

#include "avrlib/string.h"

#include "controller/display.h"
#include "controller/leds.h"
#include "controller/parameter.h"
#include "controller/storage.h"
#include "controller/system_settings.h"

namespace ambika {

/* static */
int8_t UiPage::active_control_;

/* static */
EditMode UiPage::edit_mode_;

/* static */
PageInfo* UiPage::info_;

/* static */
const prog_EventHandlers UiPage::event_handlers_ PROGMEM = {
  OnInit,
  SetActiveControl,
  OnIncrement,
  OnClick,
  OnPot,
  OnKey,
  NULL,
  OnIdle,
  UpdateScreen,
  UpdateLeds,
  OnDialogClosed,
};

/* static */
void UiPage::OnInit(PageInfo* info) {
  info_ = info;
  edit_mode_ = EDIT_IDLE;
  active_control_ = 0;
}

/* static */
void UiPage::SetActiveControl(ActiveControl active_control) { }

/* static */
uint8_t UiPage::OnIncrement(int8_t increment) {
  return 1;
}

/* static */
uint8_t UiPage::OnClick() {
  if (edit_mode_ != EDIT_IDLE) {
    edit_mode_ = EDIT_IDLE;
  } else {
    edit_mode_ = EDIT_STARTED_BY_ENCODER;
  }
  return 1;
}

/* static */
uint8_t UiPage::OnPot(uint8_t index, uint8_t value) {
  return 1;
}

/* static */
uint8_t UiPage::OnKey(uint8_t key) {
  if (key >= SWITCH_SHIFT_1) {
    StorageLocation location = { STORAGE_OBJECT_PROGRAM, 0, 0 };
    location.part = ui.state().active_part;
    storage.InitFilesystem();
    switch (key) {
      case SWITCH_SHIFT_1:
        display.set_status('C');
        storage.Copy(location);
        break;
      case SWITCH_SHIFT_2:
        display.set_status('S');
        storage.Swap(location);
        break;
      case SWITCH_SHIFT_3:
        display.set_status('P');
        storage.Paste(location);
        break;
      case SWITCH_SHIFT_7:
        display.set_status('*');
        storage.Snapshot(location);
        break;
    }
    return 1;
  }
  
  if (info_->index == PAGE_SYSTEM_SETTINGS) {
    system_settings.Save();
  }
  
  return 0;
}

/* static */
uint8_t UiPage::OnIdle() {
  if (edit_mode_ == EDIT_STARTED_BY_POT) {
    edit_mode_ = EDIT_IDLE;
  }
  return 1;
}

/* static */
void UiPage::UpdateScreen() { }

/* static */
void UiPage::OnDialogClosed(uint8_t dialog_id, uint8_t return_value) { }

/* static */
void UiPage::UpdateLeds() {
  leds.set_pixel(info_->group, info_->led_pattern);
}

}  // namespace ambika
