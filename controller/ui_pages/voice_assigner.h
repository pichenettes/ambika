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

#ifndef CONTROLLER_UI_PAGES_VOICE_ASSIGNER_H_
#define CONTROLLER_UI_PAGES_VOICE_ASSIGNER_H_

#include "controller/ui_pages/parameter_editor.h"

namespace ambika {

class VoiceAssigner : public ParameterEditor {
 public:
  VoiceAssigner() { }
  
  static void OnInit(PageInfo* info);
  static void SetActiveControl(ActiveControl active_control);

  static uint8_t OnIncrement(int8_t increment);
  static uint8_t OnClick();
  static uint8_t OnPot(uint8_t index, uint8_t value);
  static uint8_t OnNote(uint8_t note, uint8_t velocity);

  static void UpdateScreen();
  
  static const prog_EventHandlers event_handlers_;
  
 private:
  static uint8_t available_voices();
   
  DISALLOW_COPY_AND_ASSIGN(VoiceAssigner);
};

}  // namespace ambika

#endif  // CONTROLLER_UI_PAGES_VOICE_ASSIGNER_H_
