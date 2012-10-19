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
// Special UI element on the voice assignment page.

#include "controller/ui_pages/voice_assigner.h"

#include "avrlib/string.h"

#include "controller/display.h"
#include "controller/leds.h"
#include "controller/multi.h"

namespace ambika {

/* static */
const prog_EventHandlers VoiceAssigner::event_handlers_ PROGMEM = {
  OnInit,
  SetActiveControl,
  OnIncrement,
  OnClick,
  OnPot,
  OnKey,
  OnNote,
  OnIdle,
  UpdateScreen,
  UpdateLeds,
  OnDialogClosed,
};

/* static */
void VoiceAssigner::OnInit(PageInfo* info) {
  ParameterEditor::OnInit(info);
  SetActiveControl(ACTIVE_CONTROL_FIRST);
}

/* static */
void VoiceAssigner::SetActiveControl(ActiveControl active_control) {
  if (active_control == ACTIVE_CONTROL_FIRST) {
    active_control_ = 0xff;
    OnIncrement(1);
  } else {
    active_control_ = 3 + kNumVoices;
  }
}

/* static */
uint8_t VoiceAssigner::OnIncrement(int8_t increment) {
  if (edit_mode_ != EDIT_IDLE && active_control_ < 4) {
    return ParameterEditor::OnIncrement(increment);
  } else {
    int8_t new_control = active_control_ + increment;
    if (new_control < 0) {
      ui.ShowPageRelative(-1);
    } else if (new_control > 3 + kNumVoices) {
      ui.ShowPageRelative(1);
    } else {
      active_control_ = new_control;
    }
    return 1;
  }
}

/* static */
uint8_t VoiceAssigner::OnClick() {
  if (active_control_ < 4) {
    return ParameterEditor::OnClick();
  } else {
    uint8_t bit = 1 << (active_control_ - 4);
    uint8_t part = ui.state().active_part;
    uint8_t allocation = multi.data().part_mapping_[part].voice_allocation;
      // Remove this voice from any other part that used it.
    if (!(allocation & bit)) {
      for (uint8_t i = 0; i < kNumParts; ++i) {
        multi.mutable_data()->part_mapping_[i].voice_allocation &= ~bit;
      }
    }
    allocation ^= bit;
    if (multi.mutable_data()->part_mapping_[part].voice_allocation != \
        allocation) {
      multi.mutable_data()->part_mapping_[part].voice_allocation = allocation;
      multi.SolveAllocationConflicts(-1);
      multi.AssignVoicesToParts();
    }
    return 1;
  }
}

/* static */
uint8_t VoiceAssigner::OnNote(uint8_t note, uint8_t velocity) {
  if (edit_mode_ != EDIT_IDLE &&
      (active_control_ == 2 || active_control_ == 3)) {
    ParameterEditor::OnPot(active_control_, note);
    edit_mode_ = EDIT_IDLE;
    return 1;
  } else {
    return 0;
  }
}

/* static */
uint8_t VoiceAssigner::OnPot(uint8_t index, uint8_t value) {
  if (index <= 4) {
    uint8_t previous_active_control = active_control_;
    ParameterEditor::OnPot(index, value);
    if (index == 0) {
      active_control_ = previous_active_control;
      edit_mode_ = EDIT_IDLE;
    }
    return 1;
  } else {
    value >>= 5;
    uint8_t shift = 2 * (index - 5);
    uint8_t mask = 3 << shift;
    uint8_t part = ui.state().active_part;
    uint8_t allocation = multi.data().part_mapping_[part].voice_allocation;
    allocation = (allocation & ~mask) | (value << shift);
    allocation &= multi.SolveAllocationConflicts(part);
    if (multi.mutable_data()->part_mapping_[part].voice_allocation != \
        allocation) {
      multi.mutable_data()->part_mapping_[part].voice_allocation = allocation;
      multi.AssignVoicesToParts();
    }
    return 1;
  }
}

/* static */
void VoiceAssigner::UpdateScreen() {
  ParameterEditor::UpdateScreen();
  display.set_cursor_character(' ');
  display.set_cursor_position(
    active_control_ < 4 ? kLcdNoCursor : 53 + 5 * (active_control_ - 4));
  
  uint8_t part = ui.state().active_part;
  uint8_t allocation = multi.data().part_mapping_[part].voice_allocation;
  
  char* buffer = display.line_buffer(1);
  memset(buffer, ' ', kLcdWidth);
  strncpy_P(&buffer[1], PSTR("voicecard"), 9);
  buffer[10] = kDelimiter;
  
  uint8_t mask = 1;  
  for (uint8_t i = 0; i < kNumVoices; ++i) {
    uint8_t position = i * 5;
    if (allocation & mask) {
      buffer[position + 12] = '[';
      buffer[position + 14] = ']';
    }
    buffer[position + 13] = '1' + i;
    mask <<= 1;
  }
}

}  // namespace ambika
