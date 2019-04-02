// Copyright 2011 Emilie Gillet.
//
// Author: Emilie Gillet (emilie.o.gillet@gmail.com)
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
// Sequence editor UI page.

#include "controller/ui_pages/sequence_editor.h"

#include "avrlib/string.h"

#include "controller/display.h"
#include "controller/leds.h"
#include "controller/multi.h"
#include "controller/parameter.h"
#include "controller/part.h"

namespace ambika {

/* static */
uint8_t SequenceEditor::step_ = 0;


/* static */
const prog_EventHandlers SequenceEditor::event_handlers_ PROGMEM = {
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
inline PartData* SequenceEditor::mutable_part_data() {
  return multi.mutable_part(ui.state().active_part)->mutable_data();
}

/* static */
inline const PartData& SequenceEditor::part_data() {
  return multi.part(ui.state().active_part).data();
}

/* static */
void SequenceEditor::OnInit(PageInfo* info) {
  UiPage::OnInit(info);
  active_control_ = 4;
  OnIncrement(0);
}

/* static */
void SequenceEditor::SetActiveControl(ActiveControl active_control) {
  if (active_control == ACTIVE_CONTROL_FIRST) {
    step_ = 0;
  } else {
    step_ = 127;
    OnIncrement(-1);
  }
}

/* static */
uint8_t SequenceEditor::OnNote(uint8_t note, uint8_t velocity) {
  if (edit_mode_ != EDIT_IDLE) {
    int8_t step = step_ - 1;
    if (active_control_ >= 4) {
      ++step;
    }
    if (step < 0) {
      return 0;
    }
    step = actual_step(step, 2);
    mutable_part_data()->set_note(step, note);
    mutable_part_data()->set_velocity(step, velocity);
    step_ = actual_step(step + 1, 2);
    return 1;
  } else {
    return 0;
  }
}


/* static */
uint8_t SequenceEditor::OnIncrement(int8_t increment) {
  if (edit_mode_ == EDIT_IDLE) {
    int8_t step = step_;
    step += increment;
    if (step < 0) {
      ui.ShowPageRelative(-1);
      return 1;
    }
    uint8_t max_num_steps = 0x00;
    for (uint8_t i = 0; i < 3; ++i) {
      uint8_t l = part_data().sequence_length[i];
      if (l > max_num_steps) {
        max_num_steps = l;
      }
    }
    if (step >= max_num_steps) {
      if (increment > 0) {
        ui.ShowPageRelative(1);
        return 1;
      } else {
        step = max_num_steps - 1;
      }
    }
    step_ = step;
  } else {
    edit_mode_ = EDIT_STARTED_BY_ENCODER;
    uint8_t index = active_control_;
    int8_t step = step_ - 1;
    if (index >= 4) {
      ++step;
      index -= 4;
    }
    if (step < 0) {
      return 1;
    }
    switch (index) {
      case 0:
        {
          step = actual_step(step, 2);
          uint8_t note = part_data().note(step) + increment;
          if (note >= 0 && note <= 127) {
            mutable_part_data()->set_note(step, note);
          }
        }
        break;
      case 1:
        {
          step = actual_step(step, 2);
          int16_t velocity = part_data().ordered_gate_velocity(step);
          velocity += increment;
          if (velocity >= 0 && velocity <= 0x100) {
            mutable_part_data()->set_ordered_gate_velocity(step, velocity);
          }
        }
        break;
      case 2:
      case 3:
        {
          step = actual_step(step, index - 2);
          int16_t value = part_data().step_value(index - 2, step);
          value += increment;
          if (value >= 0 && value <= 255) {
            mutable_part_data()->set_step_value(index - 2, step, value);
          }
        }
        break;
    }
  }
  return 1;
}

/* static */
uint8_t SequenceEditor::OnClick() {
  if (edit_mode_ != EDIT_IDLE) {
    edit_mode_ = EDIT_IDLE;
    active_control_ = 4;
  } else {
    edit_mode_ = EDIT_STARTED_BY_ENCODER;
  }
  return 1;
}

/* static */
uint8_t SequenceEditor::OnPot(uint8_t index, uint8_t value) {
  int8_t step = step_ - 1;
  active_control_ = index;
  if (index >= 4) {
    ++step;
    index -= 4;
  }
  if (step < 0) {
    return 1;
  }
  switch (index) {
    case 0:
      step = actual_step(step, 2);
      mutable_part_data()->set_note(step, 24 + (value >> 1));
      break;
    case 1:
      step = actual_step(step, 2);
      mutable_part_data()->set_ordered_gate_velocity(step, value << 1);
      break;
    case 2:
    case 3:
      step = actual_step(step, index - 2);
      mutable_part_data()->set_step_value(index - 2, step, value << 1);
      break;
  }
  return 1;
}

/* static */
uint8_t SequenceEditor::actual_step(uint8_t index, uint8_t sequence) {
  uint8_t l = part_data().sequence_length[sequence];
  if (l == 0) {
    return 0;
  } else {
    while (index >= l) {
      index -= l;
    }
    return index;
  }
}

/* static */
void SequenceEditor::UpdateScreen() {
  for (uint8_t i = 0; i < 2; ++i) {
    char* buffer = display.line_buffer(i);
    int8_t step = step_ - 1 + i;
    memset(buffer, ' ', kLcdWidth);
    if (step >= 0) {
      // Quick and dirty %02d
      buffer[1] = '0';
      uint8_t c = step + 1;
      while (c >= 10) {
        c -= 10;
        ++buffer[1];
      }
      buffer[2] = '0' + c;
      uint8_t step_index = actual_step(step, 2);
      buffer[3] = kDelimiter;
      buffer[10] = kDelimiter;
      if (step_index == 0) {
        buffer[4] = buffer[11] = '\xa5';
      }
      NoteStep n = part_data().note_step(step_index);
      Parameter::PrintNote(n.note, &buffer[5]);
      buffer[8] = ' ';
      if (n.gate) {
        buffer[15] = n.legato ? '\x04' : '\x01';
        UnsafeItoa<int16_t>(n.velocity, 3, &buffer[16]);
        AlignRight(&buffer[16], 3);
      } else {
        buffer[15] = '\x05';
      }
      uint8_t column = 20;
      for (uint8_t j = 0; j < 2; ++j) {
        step_index = actual_step(step, j);
        uint8_t step_value = part_data().step_value(j, step_index);
        if (step_index == 0) {
          buffer[column + 1] = '\xa5';
        }
        UnsafeItoa<int16_t>(step_value, 3, &buffer[column + 6]);
        AlignRight(&buffer[column + 6], 3);
        buffer[column] = kDelimiter;
        column += 10;
      }
    } else {
      memcpy_P(
          &buffer[3],
          PSTR("\x07 note \x07velocity \x07stepseq 1\x07stepseq 2"),
          37);
    }
  }
  display.set_cursor_character(edit_mode_ == EDIT_IDLE ? 0xff : '_');
  if (edit_mode_ == EDIT_IDLE) {
    display.set_cursor_position(kLcdNoCursor);
  } else {
    uint8_t index = active_control_;
    uint8_t position = 0;
    if (index >= 4) {
      index -= 4;
      position += kLcdWidth;
    }
    position += index * 10 + 4 + (index >> 1);
    display.set_cursor_position(position);
  }
}

}  // namespace ambika
