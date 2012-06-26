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

#ifndef CONTROLLER_UI_PAGES_UI_PAGE_H_
#define CONTROLLER_UI_PAGES_UI_PAGE_H_

#include "controller/ui.h"

namespace ambika {

enum EditMode {
  EDIT_IDLE,
  EDIT_STARTED_BY_ENCODER,
  EDIT_STARTED_BY_POT,
};

class UiPage {
 public:
  UiPage() { }
  
  static void OnInit(PageInfo* info);
  static void SetActiveControl(ActiveControl active_control);

  static uint8_t OnIncrement(int8_t increment);
  static uint8_t OnClick();
  static uint8_t OnPot(uint8_t index, uint8_t value);
  static uint8_t OnKey(uint8_t key);
  static uint8_t OnIdle();
  static void OnDialogClosed(uint8_t dialog_id, uint8_t return_value);

  static void UpdateScreen();
  static void UpdateLeds();
  
  static const prog_EventHandlers event_handlers_;
  
 protected:
  static EditMode edit_mode_;
  static int8_t active_control_;
  static PageInfo* info_;
  
  DISALLOW_COPY_AND_ASSIGN(UiPage);
};

}  // namespace ambika

#endif  // CONTROLLER_UI_PAGES_PARAMETER_EDITOR_H_
