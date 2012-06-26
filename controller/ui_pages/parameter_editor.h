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
// A page which allows up to 8 parameters to be tweaked.

#ifndef CONTROLLER_UI_PAGES_PARAMETER_EDITOR_H_
#define CONTROLLER_UI_PAGES_PARAMETER_EDITOR_H_

#include "controller/ui_pages/ui_page.h"

namespace ambika {

const static uint8_t kNumParametersPerPage = 8;

class ParameterEditor : public UiPage {
 public:
  typedef DataTypeForSize<kNumParametersPerPage>::Type SnapMask;

  ParameterEditor() { }
  
  static void OnInit(PageInfo* info);
  static void SetActiveControl(ActiveControl active_control);

  static uint8_t OnIncrement(int8_t increment);
  static uint8_t OnPot(uint8_t index, uint8_t value);
  
  static void UpdateScreen();
  static void UpdateLeds();
  
  // Return the parameter, part and instance indices for a given control. This
  // adds a level of indirection allowing remappable knobs.
  static uint8_t parameter_index(uint8_t control_id);
  static uint8_t part_index(uint8_t control_id);
  static uint8_t instance_index(uint8_t control_id);
  
  static const prog_EventHandlers event_handlers_;
  
 private:
  static SnapMask snapped_;

  DISALLOW_COPY_AND_ASSIGN(ParameterEditor);
};

}  // namespace ambika

#endif  // CONTROLLER_UI_PAGES_PARAMETER_EDITOR_H_
