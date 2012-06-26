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

#include "controller/ui_pages/card_info_page.h"

#include "avrlib/string.h"

#include "controller/display.h"
#include "controller/leds.h"
#include "controller/multi.h"

#include "controller/storage.h"

namespace ambika {

/* static */
uint32_t CardInfoPage::free_space_;

/* static */
uint8_t CardInfoPage::card_type_;

/* static */
uint8_t CardInfoPage::fs_type_;

/* static */
const prog_EventHandlers CardInfoPage::event_handlers_ PROGMEM = {
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
void CardInfoPage::OnInit(PageInfo* info) {
  storage.InitFilesystem();
  free_space_ = storage.GetFreeSpace();
  uint16_t type = storage.GetType();
  fs_type_ = type & 0xff;
  card_type_ = type >> 8;
}

/* static */
uint8_t CardInfoPage::OnKey(uint8_t key) {
  switch(key) {
    case SWITCH_7:
      {
        Dialog d;
        d.dialog_type = DIALOG_CONFIRM;
        d.text = PSTR("format SD card?");
        d.user_text = NULL;
        ui.ShowDialogBox(0, d, 0);
        break;
      }
      break;
    case SWITCH_8:
      ui.ShowPage(PAGE_SYSTEM_SETTINGS);
      break;
  }
  
  return 1;
}

static const prog_char si_prefix[] PROGMEM = " kMGT";

/* static */
void CardInfoPage::UpdateScreen() {
  char* buffer = display.line_buffer(0) + 1;
  
  buffer[0] = 'S'; buffer[1] = 'D';
  if ((card_type_ & CT_SD2) && !(card_type_ & CT_BLOCK)) {
    buffer[2] = '2';
  } else if ((card_type_ & CT_SD2) && (card_type_ & CT_BLOCK)) {
    buffer[2] = 'H'; buffer[3] = 'C';
  }
  
  buffer[5] = 'f'; buffer[6] = 'a'; buffer[7] = 't';
  if (fs_type_ == 0) {
    buffer[8] = '1'; buffer[9] = '2';
  } else if (fs_type_ == 1) {
    buffer[8] = '1'; buffer[9] = '6';
  } else if (fs_type_ == 1) {
    buffer[8] = '3'; buffer[9] = '2';
  }
  uint8_t prefix = 0;
  uint32_t space = free_space_;
  while (space >= 32768) {
    space >>= 10;
    ++prefix;
  }
  UnsafeItoa<int16_t>(space, 5, &buffer[11]);
  AlignRight(&buffer[11], 5);
  
  buffer[16] = ResourcesManager::Lookup<char, uint8_t>(si_prefix, prefix);
  strncpy_P(&buffer[17], PSTR("bytes free"), 10);
  
  buffer = display.line_buffer(1) + 1;
  strncpy_P(&buffer[28], PSTR("format|exit"), 11);
  buffer[34] = kDelimiter;
}

/* static */
void CardInfoPage::UpdateLeds() {
  leds.set_pixel(LED_8, 0xf0);
  leds.set_pixel(LED_7, 0x0f);
}

/* static */
void CardInfoPage::OnDialogClosed(uint8_t dialog_id, uint8_t return_value) {
  if (return_value) {
    storage.Mkfs();
    OnInit(NULL);
  }
}

}  // namespace ambika
