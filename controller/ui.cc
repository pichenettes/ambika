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
// User interface.

#include "controller/ui.h"

#include "avrlib/string.h"

#include "controller/display.h"
#include "controller/leds.h"
#include "controller/multi.h"
#include "controller/resources.h"
#include "controller/system_settings.h"

#include "controller/ui_pages/card_info_page.h"
#include "controller/ui_pages/dialog_box.h"
#include "controller/ui_pages/knob_assigner.h"
#include "controller/ui_pages/library.h"
#include "controller/ui_pages/os_info_page.h"
#include "controller/ui_pages/parameter_editor.h"
#include "controller/ui_pages/performance_page.h"
#include "controller/ui_pages/sequence_editor.h"
#include "controller/ui_pages/version_manager.h"
#include "controller/ui_pages/voice_assigner.h"
#include "controller/voicecard_tx.h"

namespace ambika {
  
const prog_PageInfo page_registry[] PROGMEM = {
  { PAGE_OSCILLATORS,
    &ParameterEditor::event_handlers_,
    { 0, 1, 2, 3, 4, 5, 6, 7 },
    PAGE_MIXER, 0, 0xf0,
  },
  
  { PAGE_MIXER,
    &ParameterEditor::event_handlers_,
    { 8, 13, 12, 11, 9, 10, 14, 15 },
    PAGE_OSCILLATORS, 0, 0x0f,
  },
  
  { PAGE_FILTER,
    &ParameterEditor::event_handlers_,
    { 16, 17, 0xff, 18, 22, 23, 0xff, 0xff },
    PAGE_FILTER, 1, 0xf0,
  },
  
  { PAGE_ENV_LFO,
    &ParameterEditor::event_handlers_,
    { 24, 30, 31, 29, 25, 26, 27, 28 },
    PAGE_VOICE_LFO, 2, 0xf0,
  },
  
  { PAGE_VOICE_LFO,
    &ParameterEditor::event_handlers_,
    { 0xff, 32, 33, 0xff, 0xff, 0xff, 0xff, 0xff },
    PAGE_ENV_LFO, 2, 0x0f,
  },
  
  { PAGE_MODULATIONS,
    &ParameterEditor::event_handlers_,
    { 34, 35, 36, 37, 38, 39, 40, 41 },
    PAGE_MODULATIONS, 3, 0xf0,
  },
  
  { PAGE_PART,
    &ParameterEditor::event_handlers_,
    { 42, 57, 47, 48, 43, 44, 45, 46 },
    PAGE_PART_ARPEGGIATOR, 4, 0xf0,
  },
  
  { PAGE_PART_ARPEGGIATOR,
    &ParameterEditor::event_handlers_,
    { 49, 50, 51, 52, 53, 54, 55, 56 },
    PAGE_PART_SEQUENCER, 4, 0x0f,
  },
  
  { PAGE_PART_SEQUENCER,
    &SequenceEditor::event_handlers_,
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    PAGE_PART, 4, 0xff,
  },
  
  { PAGE_MULTI,
    &VoiceAssigner::event_handlers_,
    { 58, 59, 60, 61, 0xff, 0xff, 0xff, 0xff },
    PAGE_MULTI_CLOCK, 5, 0xf0,
  },
  
  { PAGE_MULTI_CLOCK,
    &ParameterEditor::event_handlers_,
    { 62, 63, 64, 65, 0xff, 0xff, 0xff, 0xff, },
    PAGE_MULTI, 5, 0x0f,
  },
  
  { PAGE_PERFORMANCE,
    &PerformancePage::event_handlers_,
    { 0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, },
    PAGE_KNOB_ASSIGN, 6, 0xf0,
  },
  
  { PAGE_KNOB_ASSIGN,
    &KnobAssigner::event_handlers_,
    { 0, 0, 0, 0, 0, 0, 0, 0, },
    PAGE_PERFORMANCE, 6, 0x0f,
  },

  { PAGE_LIBRARY,
    &Library::event_handlers_,
    { 0, 0, 0, 0, 0, 0, 0, 0, },
    PAGE_LIBRARY, 7, 0xf0,
  },

  { PAGE_VERSION_MANAGER,
    &VersionManager::event_handlers_,
    { 0, 0, 0, 0, 0, 0, 0, 0, },
    PAGE_LIBRARY, 8, 0xf0,
  },

  { PAGE_SYSTEM_SETTINGS,
    &ParameterEditor::event_handlers_,
    { 66, 67, 71, 72, 68, 69, 0xff, 70, },
    PAGE_SYSTEM_SETTINGS, 8, 0xf0,
  },

  { PAGE_OS_INFO,
    &OsInfoPage::event_handlers_,
    { 0, 0, 0, 0, 0, 0, 0, 0, },
    PAGE_OS_INFO, 8, 0xf0,
  },
};

static const prog_uint8_t default_most_recent_page_in_group[9] PROGMEM = {
  PAGE_OSCILLATORS,
  PAGE_FILTER,
  PAGE_ENV_LFO,
  PAGE_MODULATIONS,
  PAGE_PART,
  PAGE_MULTI,
  PAGE_PERFORMANCE,
  PAGE_LIBRARY,
  PAGE_SYSTEM_SETTINGS
};

/* <static> */
UiPageNumber Ui::active_page_;
UiPageNumber Ui::most_recent_non_system_page_;
uint8_t Ui::cycle_;
uint8_t Ui::inhibit_switch_;
Encoder Ui::encoder_;
Switches Ui::switches_;
Pots Ui::pots_;

UiState Ui::state_;
EventQueue<8> Ui::queue_;
uint8_t Ui::pot_value_[8];
UiPageNumber Ui::most_recent_page_in_group_[9];

PageInfo Ui::page_info_;
EventHandlers Ui::event_handlers_;
/* </static> */

/* extern */
Ui ui;

static char line[41];

/* static */
void Ui::Init() {
  memset(&state_, 0, sizeof(UiState));
  memcpy_P(most_recent_page_in_group_, default_most_recent_page_in_group, 8);

  encoder_.Init();
  switches_.Init();
  pots_.Init();
  lcd.Init();
  display.Init();
  leds.Init();
  lcd.SetCustomCharMapRes(character_table[0], 7, 1);
  
  ShowPage(PAGE_FILTER);
  
  memset(line, ' ', 41);
  line[40] = '\0';
  inhibit_switch_ = 0;
}

/* static */
void Ui::Poll() {
  ++cycle_;
  // I
  int8_t increment = encoder_.Read();
  if (increment != 0) {
    uint8_t control_id = 0;
    if (switches_.low(0)) {
      increment *= 8;
      inhibit_switch_ = 0x01;
    }
    if (switches_.low(7)) {
      ++control_id;
      inhibit_switch_ = 0x80;
    }
    queue_.AddEvent(CONTROL_ENCODER, control_id, increment);
  }
  if (encoder_.clicked()) {
    queue_.AddEvent(CONTROL_ENCODER_CLICK, 0, 1);
  }
  
  if (!(cycle_ & 31)) {
    switches_.Read();
    uint8_t mask = 1;
    for (uint8_t i = 0; i < 8; ++i) {
      if (switches_.raised(i)) {
        if ((inhibit_switch_ & mask)) {
          inhibit_switch_ ^= mask;
        } else {
          uint8_t control = SWITCH_8;
          if (switches_.low(0)) {
            control = SWITCH_SHIFT_8;
            inhibit_switch_ = 0x01;
          }
          control -= i;
          queue_.AddEvent(CONTROL_SWITCH, control, 1);
        }
      }
      mask <<= 1;
    }
  }
  
  pots_.Read();
  uint8_t index = pots_.last_read();
  uint16_t value = pots_.value(index);
  if (value != pot_value_[index]) {
    pot_value_[index] = value;
    // Software correction for the neat (but incorrect) hardware layout.
    if (index < 4) {
      index = 3 - index;
    }
    queue_.AddEvent(CONTROL_POT, index, value);
  }
  
  if (voicecard_tx.sd_card_busy()) {
    display.ForceStatus(0xdb);
    leds.set_direct_pixel(LED_STATUS, 0x0f);
  }

  // O
  leds.Write();
  lcd.Tick();
}

/* static */
void Ui::ShowPageRelative(int8_t increment) {
  // Disable page scrolling for the system pages.
  if (page_info_.index >= PAGE_LIBRARY) {
    return; 
  }
  
  int8_t current_page = page_info_.index;
  current_page += increment;
  if (current_page < 0) {
    current_page = PAGE_PERFORMANCE;
  }
  if (current_page > PAGE_PERFORMANCE) {
    current_page = 0;
  }
  ShowPage(static_cast<UiPageNumber>(current_page));
  // Jump to the last control when scrolling backwards.
  if (increment >= 0) {
    (*event_handlers_.SetActiveControl)(ACTIVE_CONTROL_FIRST);
  } else {
    (*event_handlers_.SetActiveControl)(ACTIVE_CONTROL_LAST);
  }
}

const prog_uint8_t part_leds_remap[] PROGMEM = { 0, 3, 1, 4, 2, 5 };

/* static */
void Ui::DoEvents() {
  display.Tick();
  
  uint8_t redraw = 0;
  while (queue_.available()) {
    Event e = queue_.PullEvent();
    queue_.Touch();
    switch (e.control_type) {
      case CONTROL_ENCODER_CLICK:
        (*event_handlers_.OnClick)();
        break;
        
      case CONTROL_ENCODER:
        if (e.control_id == 0) {
          (*event_handlers_.OnIncrement)(e.value);
        } else {
          int8_t new_part = state_.active_part + e.value;
          new_part = Clip(new_part, 0, kNumParts - 1);
          state_.active_part = new_part;
        }
        break;
        
      case CONTROL_SWITCH:
        if (!(*event_handlers_.OnKey)(e.control_id)) {
          // Cycle through the next page in the group.
          if (page_info_.group == e.control_id) {
            ShowPage(page_info_.next_page);
          } else {
            // Jump to the most recently visited page in the group.
            ShowPage(most_recent_page_in_group_[e.control_id]);
          }
        }
        break;
        
      case CONTROL_POT:
        (*event_handlers_.OnPot)(e.control_id, e.value);
        break;
    }
    redraw = 1;
  }
  
  if (queue_.idle_time_ms() > 800) {
    queue_.Touch();
    if ((*event_handlers_.OnIdle)()) {
      redraw = 1;
    }
  }
  
  if (multi.flags() & FLAG_HAS_CHANGE) {
    redraw = 1;
    multi.ClearFlag(FLAG_HAS_CHANGE);
  }
  
  if (redraw) {
    display.Clear();
    // The status icon is displayed when there is blank space at the left/right
    // of the page. We don't want the icon to display the icon to show up on the
    // right side of the page, so we fill the last character of the first line
    // with an invisible, non-space character.
    display.line_buffer(0)[39] = '\xfe';
    
    display.set_cursor_position(kLcdNoCursor);
    (*event_handlers_.UpdateScreen)();
  }
  
  leds.Clear();
  leds.set_pixel(
      LED_PART_1 + pgm_read_byte(part_leds_remap + state_.active_part), 0xf0);
  for (uint8_t i = 0; i < kNumVoices; ++i) {
    uint8_t led_index = pgm_read_byte(part_leds_remap + i);
    uint8_t velocity = voicecard_tx.voice_status(i) >> 3;
    leds.set_pixel(
        LED_PART_1 + led_index,
        velocity | leds.pixel(LED_PART_1 + led_index));
  }
  (*event_handlers_.UpdateLeds)();
  if (system_settings.data().swap_leds_colors) {
    for (uint8_t i = 0; i < 15; ++i) {
      leds.set_pixel(i, U8Swap4(leds.pixel(i)));
    }
  }
  leds.Sync();
}

/* static */
void Ui::ShowPage(UiPageNumber page, uint8_t initialize) {
  // Flush the event queue.
  queue_.Flush();
  queue_.Touch();
  pots_.Lock(16);
  
  if (page <= PAGE_KNOB_ASSIGN) {
    most_recent_non_system_page_ = page;
  }
  active_page_ = page;

  // Load the page info structure in RAM.
  ResourcesManager::Load(page_registry, page, &page_info_);

  // Load the event handlers structure in RAM.
  ResourcesManager::Load(page_info_.event_handlers, 0, &event_handlers_);
  most_recent_page_in_group_[page_info_.group] = page;
  if (initialize) {
    (*event_handlers_.OnInit)(&page_info_);
  }
  (*event_handlers_.UpdateScreen)();
}

/* static */
void Ui::ShowDialogBox(uint8_t dialog_id, Dialog dialog, uint8_t choice) {
  // Flush the event queue.
  queue_.Flush();
  queue_.Touch();
  
  // Replace the current page by the dialog box handler.
  ResourcesManager::Load(&DialogBox::event_handlers_, 0, &event_handlers_);
  page_info_.dialog = dialog;
  page_info_.index = dialog_id;
  (*event_handlers_.OnInit)(&page_info_);
  DialogBox::set_choice(choice);
  (*event_handlers_.UpdateScreen)();
}

/* static */
void Ui::CloseDialogBox(uint8_t return_value) {
  // Return to the page that was active when the dialog was shown.
  uint8_t returning_from = page_info_.index;
  ShowPage(active_page_, 0);
  (*event_handlers_.OnDialogClosed)(returning_from, return_value);
}

}  // namespace ambika
