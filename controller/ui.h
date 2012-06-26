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

#ifndef CONTROLLER_UI_H_
#define CONTROLLER_UI_H_

#include "avrlib/base.h"

#include "avrlib/devices/pot_scanner.h"
#include "avrlib/devices/rotary_encoder.h"
#include "avrlib/devices/switch.h"
#include "avrlib/ui/event_queue.h"

#include "controller/hardware_config.h"
#include "controller/resources.h"

namespace ambika {

using namespace avrlib;

struct UiState {
  uint8_t active_env_lfo;
  uint8_t active_modulation;
  uint8_t active_modifier;
  uint8_t active_part;
};

enum UIStateParameter {
  PRM_UI_ACTIVE_ENV_LFO,
  PRM_UI_ACTIVE_MODULATION,
  PRM_UI_ACTIVE_MODIFIER,
  PRM_UI_ACTIVE_PART
};

enum SwitchNumber {
  SWITCH_1,
  SWITCH_2,
  SWITCH_3,
  SWITCH_4,
  SWITCH_5,
  SWITCH_6,
  SWITCH_7,
  SWITCH_8,
  
  SWITCH_SHIFT_1,
  SWITCH_SHIFT_2,
  SWITCH_SHIFT_3,
  SWITCH_SHIFT_4,
  SWITCH_SHIFT_5,
  SWITCH_SHIFT_6,
  SWITCH_SHIFT_7,
  SWITCH_SHIFT_8
};

enum ActiveControl {
  ACTIVE_CONTROL_FIRST,
  ACTIVE_CONTROL_LAST,
};

enum UiPageNumber {
  PAGE_OSCILLATORS,
  PAGE_MIXER,
  
  PAGE_FILTER,
  
  PAGE_ENV_LFO,
  PAGE_VOICE_LFO,
  
  PAGE_MODULATIONS,
  
  PAGE_PART,
  PAGE_PART_ARPEGGIATOR,
  PAGE_PART_SEQUENCER,
  
  PAGE_MULTI,
  PAGE_MULTI_CLOCK,
  
  PAGE_PERFORMANCE,
  PAGE_KNOB_ASSIGN,
  
  PAGE_LIBRARY,
  PAGE_VERSION_MANAGER,
  PAGE_SYSTEM_SETTINGS,  
  PAGE_OS_INFO,
};

typedef RotaryEncoder<EncoderALine, EncoderBLine, EncoderClickLine> Encoder;
typedef DebouncedSwitches<IOEnableLine, IOClockLine, IOInputLine, 8> Switches;
typedef HysteresisPotScanner<8, 0, 8, 7> Pots;

struct PageInfo;

struct EventHandlers {
  void (*OnInit)(PageInfo* info);
  void (*SetActiveControl)(ActiveControl);
  uint8_t (*OnIncrement)(int8_t);
  uint8_t (*OnClick)();
  uint8_t (*OnPot)(uint8_t, uint8_t);
  uint8_t (*OnKey)(uint8_t);
  uint8_t (*OnNote)(uint8_t, uint8_t);
  uint8_t (*OnIdle)();
  void (*UpdateScreen)();
  void (*UpdateLeds)();
  void (*OnDialogClosed)(uint8_t, uint8_t);
};

typedef EventHandlers PROGMEM prog_EventHandlers;

enum DialogType {
  DIALOG_ERROR,
  DIALOG_INFO,
  DIALOG_CONFIRM,
  DIALOG_SELECT,
};

struct Dialog {
  DialogType dialog_type;
  uint8_t num_choices;
  ResourceId first_choice;
  const prog_char* text;
  char* user_text;
};

struct PageInfo {
  uint8_t index;
  
  const prog_EventHandlers* event_handlers;
  // For a standard parameter editing page, indices of the parameters to edit ;
  // or 0xf0 -- x0f7 for the 8 assignable knobs.
  union {
    uint8_t data[8];
    Dialog dialog;
  };

  UiPageNumber next_page;
  uint8_t group;
  uint8_t led_pattern;
};

typedef PageInfo PROGMEM prog_PageInfo;

class Ui {
 public:
  Ui() { }
  
  static void Init();
  static void Poll();
  static void DoEvents();
  static void FlushEvents() {
    queue_.Flush();
  }
  
  static uint8_t has_events() {
    return queue_.available();
  }
  
  static void ShowPageRelative(int8_t increment);
  static void ShowPage(UiPageNumber page, uint8_t initialize);
  static void ShowPage(UiPageNumber page) {
    ShowPage(page, 1);
  }
  static void ShowPreviousPage() {
    ShowPage(most_recent_non_system_page_);
  };

  static void ShowDialogBox(uint8_t dialog_id, Dialog dialog, uint8_t choice);
  static void CloseDialogBox(uint8_t return_value);
  
  static UiState* mutable_state() { return &state_; }
  static const UiState& state() { return state_; }
  
  static uint8_t GetValue(uint8_t address) {
    return static_cast<uint8_t*>(
        static_cast<void*>(&state_))[address];
  }
  
  static uint8_t OnNote(uint8_t note, uint8_t velocity) {
    if (event_handlers_.OnNote && \
          (*event_handlers_.OnNote)(note, velocity)) {
      queue_.AddEvent(CONTROL_REFRESH, 0, 0);
      return 1;
    }
    return 0;
  }
  
  static uint8_t shifted() { return switches_.low(7); }
  
 private:
  static UiPageNumber active_page_;
  static UiPageNumber most_recent_non_system_page_;
   
  static uint8_t cycle_;
  static Encoder encoder_;
  static Switches switches_;
  static uint8_t inhibit_switch_;
  static Pots pots_;
  static UiState state_;
  static EventQueue<8> queue_;
  static uint8_t pot_value_[8];
  
  static uint8_t active_group_;
  static UiPageNumber most_recent_page_in_group_[9];
  static EventHandlers event_handlers_;
  static PageInfo page_info_;

  DISALLOW_COPY_AND_ASSIGN(Ui);
};

extern Ui ui;

}  // namespace ambika

#endif  // CONTROLLER_UI_H_
