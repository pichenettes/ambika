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
// Special UI element on the voice assignment page.

#include "controller/ui_pages/knob_assigner.h"

#include "avrlib/string.h"

#include "controller/display.h"
#include "controller/leds.h"
#include "controller/multi.h"
#include "controller/parameter.h"

namespace ambika {

enum Controls {
  CONTROL_KNOB,
  CONTROL_PART,
  CONTROL_PARAMETER,
};

/* static */
uint8_t KnobAssigner::active_knob_;

/* static */
uint8_t KnobAssigner::num_parameters_;

/* static */
const prog_EventHandlers KnobAssigner::event_handlers_ PROGMEM = {
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
void KnobAssigner::OnInit(PageInfo* info) {
  UiPage::OnInit(info);
  num_parameters_ = 0;
  for (uint8_t i = 0; i < kNumParameters; ++i) {
    const Parameter& parameter = parameter_manager.parameter(i);
    if (parameter.level >= PARAMETER_LEVEL_MULTI) {
      continue;
    }
    num_parameters_ += parameter.num_instances;
  }
}

/* static */
uint8_t KnobAssigner::OnIncrement(int8_t increment) {
  // Disabled fast increment / decrement.
  increment = increment > 0 ? 1 : -1;
  
  KnobAssignment* a = &multi.mutable_data()->knob_assignment[active_knob_];
  const Parameter& p = parameter_manager.parameter(a->parameter);
  int8_t instance = a->instance + increment;
  if (instance >= 0 && instance < p.num_instances) {
    a->instance = instance;
  } else {
    int8_t parameter = a->parameter;
    parameter += increment;
    while (parameter >= 0 && parameter < kNumParameters) {
      const Parameter& p = parameter_manager.parameter(parameter);
      if (p.level < PARAMETER_LEVEL_MULTI) {
        a->parameter = parameter;
        if (increment > 0) {
          a->instance = 0;
        } else {
          a->instance = p.num_instances - 1;
        }
        break;
      }
      parameter += increment;
    }
  }
  return 1;
}

/* static */
uint8_t KnobAssigner::OnPot(uint8_t index, uint8_t value) {
  active_control_ = index;
  edit_mode_ = EDIT_STARTED_BY_POT;
  KnobAssignment* a = &multi.mutable_data()->knob_assignment[active_knob_];
  switch (index) {
    case 0:
    case 4:
      active_knob_ = U8ShiftRight4(value);
      break;
    case 1:
    case 5:
      a->part = U8U8MulShift8(value << 1, 6);
      break;
    case 2:
    case 3:
    case 6:
    case 7:
      {
        uint8_t number = U8U8MulShift8(value << 1, num_parameters_);
        for (uint8_t i = 0; i < kNumParameters; ++i) {
          const Parameter& parameter = parameter_manager.parameter(i);
          if (parameter.level >= PARAMETER_LEVEL_MULTI) {
            continue;
          }
          a->parameter = i;
          if (number < parameter.num_instances) {
            a->instance = number;
            break;
          } else {
            number -= parameter.num_instances;
          }
        }
        break;
      }
  }
  return 1;
}

/* static */
void KnobAssigner::UpdateScreen() {
  char* buffer;
  const KnobAssignment& a = multi.data().knob_assignment[active_knob_];
  const Parameter& parameter = parameter_manager.parameter(a.parameter);

  buffer = display.line_buffer(0);
  strncpy_P(&buffer[1], PSTR("performance page customization"), 39);
  AlignLeft(&buffer[1], 39);

  buffer = display.line_buffer(1);
  strncpy_P(&buffer[1], PSTR("knob x|part z|"), 39);
  buffer[6] = '1' + active_knob_;
  buffer[7] = kDelimiter;
  buffer[13] = '1' + a.part;
  buffer[14] = kDelimiter;
  parameter.PrintObject(0xff, a.instance, &buffer[15], 25);
  uint8_t position = 39;
  while (buffer[position - 2] == ' ') {
    --position;
  }
  parameter.PrintName(&buffer[position], 40 - position);
}

}  // namespace ambika
