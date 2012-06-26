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
// Special UI page for displaying SD card information.

#ifndef CONTROLLER_UI_PAGES_CARD_INFO_PAGE_H_
#define CONTROLLER_UI_PAGES_CARD_INFO_PAGE_H_

#include "controller/ui_pages/ui_page.h"

namespace ambika {

class CardInfoPage : public UiPage {
 public:
  CardInfoPage() { }
  
  static void OnInit(PageInfo* info);
  
  static uint8_t OnKey(uint8_t key);
  static void UpdateScreen();
  static void UpdateLeds();

  static void OnDialogClosed(uint8_t dialog_id, uint8_t return_value);

  static const prog_EventHandlers event_handlers_;

 private:
  static uint32_t free_space_;
  static uint8_t card_type_;
  static uint8_t fs_type_;

  DISALLOW_COPY_AND_ASSIGN(CardInfoPage);
};

}  // namespace ambika

#endif  // CONTROLLER_UI_PAGES_CARD_INFO_PAGE_H_
