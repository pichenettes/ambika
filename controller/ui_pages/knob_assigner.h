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
// UI page to assign functions to knobs.

#ifndef CONTROLLER_UI_PAGES_KNOB_ASSIGNER_H_
#define CONTROLLER_UI_PAGES_KNOB_ASSIGNER_H_

#include "controller/ui_pages/ui_page.h"

namespace ambika {

class KnobAssigner : public UiPage {
 public:
  KnobAssigner() { }
  
  static void OnInit(PageInfo* info);
  static uint8_t OnIncrement(int8_t increment);
  static uint8_t OnPot(uint8_t index, uint8_t value);

  static void UpdateScreen();
  
  static const prog_EventHandlers event_handlers_;
  
 private:
  static uint8_t active_knob_;
  static uint8_t num_parameters_;
  
  DISALLOW_COPY_AND_ASSIGN(KnobAssigner);
};

}  // namespace ambika

#endif  // CONTROLLER_UI_PAGES_KNOB_ASSIGNER_H_
