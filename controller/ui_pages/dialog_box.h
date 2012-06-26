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
// Generic dialog box.

#ifndef CONTROLLER_UI_PAGES_DIALOG_BOX_H_
#define CONTROLLER_UI_PAGES_DIALOG_BOX_H_

#include "controller/ui_pages/ui_page.h"

namespace ambika {

class DialogBox : public UiPage {
 public:
  DialogBox() { }
  
  static void OnInit(PageInfo* info);
  
  static uint8_t OnIncrement(int8_t increment);
  static uint8_t OnClick();
  static uint8_t OnPot(uint8_t index, uint8_t value);
  static uint8_t OnKey(uint8_t key);
  static uint8_t OnIdle();
  static inline void set_choice(uint8_t choice) {
    choice_ = choice;
  }

  static void UpdateScreen();
  static void UpdateLeds();
  
  static const prog_EventHandlers event_handlers_;
  
 protected:
  static uint8_t choice_;
  
  DISALLOW_COPY_AND_ASSIGN(DialogBox);
};

}  // namespace ambika

#endif  // CONTROLLER_UI_PAGES_DIALOG_BOX_H_
