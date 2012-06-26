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

#include "controller/ui_pages/dialog_box.h"

#include "avrlib/string.h"

#include "controller/display.h"
#include "controller/leds.h"

namespace ambika {

/* static */
uint8_t DialogBox::choice_;

/* static */
const prog_EventHandlers DialogBox::event_handlers_ PROGMEM = {
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
void DialogBox::OnInit(PageInfo* info) {
  choice_ = 0;
}


/* static */
uint8_t DialogBox::OnIncrement(int8_t increment) {
  if (info_->dialog.dialog_type == DIALOG_SELECT) {
    choice_ = Clip(choice_ + increment, 0, info_->dialog.num_choices - 1);
  }
  return 1;
}

/* static */
uint8_t DialogBox::OnPot(uint8_t index, uint8_t value) {
  if (info_->dialog.dialog_type == DIALOG_SELECT) {
    choice_ = U8U8MulShift8(info_->dialog.num_choices, value << 1);
  }
}

/* static */
uint8_t DialogBox::OnKey(uint8_t key) {
  if (key == SWITCH_7 && info_->dialog.dialog_type >= DIALOG_CONFIRM) {
    ui.CloseDialogBox(1 + choice_);
  } else if (key == SWITCH_8) {
    ui.CloseDialogBox(info_->dialog.dialog_type < DIALOG_CONFIRM);
  }
  return 1;
}

/* static */
uint8_t DialogBox::OnClick() {
  ui.CloseDialogBox(1 + choice_);
  return 1;
}

/* static */
uint8_t DialogBox::OnIdle() {
  if (info_->dialog.dialog_type == DIALOG_INFO) {
    ui.CloseDialogBox(1);
  }
  return 1;
}

/* static */
void DialogBox::UpdateScreen() {
  char* buffer = display.line_buffer(0) + 1;
  uint8_t text_width = 35;
  
  // Draw the icon.
  switch (info_->dialog.dialog_type) {
    case DIALOG_ERROR:
      buffer[kLcdWidth + 36] = 'o';
      buffer[kLcdWidth + 37] = 'k';
      *buffer++ = '/';
      *buffer++ = '!';
      *buffer++ = '\x06';
      buffer++;
      break;
      
    case DIALOG_INFO:
      *buffer++ = '[';
      *buffer++ = 'i';
      *buffer++ = ']';
      buffer++;
      break;
    
    case DIALOG_CONFIRM:
      *buffer++ = '(';
      *buffer++ = '?';
      *buffer++ = ')';
      buffer++;
      break;
      
    case DIALOG_SELECT:
      text_width = 25;
      break;
  }
  
  // Draw the pre-defined text.
  if (info_->dialog.text) {
    strncpy_P(buffer, info_->dialog.text, text_width);
    AlignLeft(buffer, text_width);
  } else {
    *buffer = '@';
  }
  if (info_->dialog.user_text) {
    uint8_t len = strlen(info_->dialog.user_text);
    for (; buffer[text_width - len + 1] != '@'; --text_width) {
      buffer[text_width] = buffer[text_width - len + 1];
    }
    memcpy(&buffer[text_width - len + 1], info_->dialog.user_text, len);
  }
  
  // Draw the select box.
  if (info_->dialog.dialog_type == DIALOG_SELECT) {
    buffer[25] = '[';
    ResourcesManager::LoadStringResource(
        info_->dialog.first_choice + choice_,
        &buffer[27],
        10);
    AlignRight(&buffer[27], 10);
    buffer[38] = ']';
  }
  
  // Draw the buttons
  buffer = display.line_buffer(1) + 1;
  if (info_->dialog.dialog_type >= DIALOG_CONFIRM) {
    strncpy_P(&buffer[30], PSTR("yes | no"), 8);
    buffer[34] = kDelimiter;
  }
}

/* static */
void DialogBox::UpdateLeds() {
  uint8_t block_color;
  if (info_->dialog.dialog_type <= DIALOG_INFO) {
    leds.set_pixel(LED_8, 0xf0);
    block_color = 0xf0;
  } else {
    leds.set_pixel(LED_7, 0xf0);
    leds.set_pixel(LED_8, 0x0f);
    block_color = 0x0f;
  }
  for (uint8_t i = 0; i < kNumParts; ++i) {
    leds.set_pixel(LED_PART_1 + i, block_color);
  }
}

}  // namespace ambika
