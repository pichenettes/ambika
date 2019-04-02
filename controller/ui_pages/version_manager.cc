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
// Special UI page for displaying versioning information.

#include "controller/ui_pages/version_manager.h"

#include "avrlib/string.h"

#include "controller/display.h"
#include "controller/leds.h"
#include "controller/multi.h"
#include "controller/ui_pages/library.h"

#include "controller/storage.h"

namespace ambika {

/* static */
const prog_EventHandlers VersionManager::event_handlers_ PROGMEM = {
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
void VersionManager::OnInit(PageInfo* info) {
  storage.InitFilesystem();
  storage.Snapshot(Library::location());
  storage.PreviousVersion(Library::location());
}

/* static */
uint8_t VersionManager::OnKey(uint8_t key) {
  switch(key) {
    case SWITCH_1:
      storage.Copy(Library::location());
      ui.ShowPreviousPage();
      break;
      
    case SWITCH_2:
      storage.Swap(Library::location());
      ui.ShowPreviousPage();
      break;
    
    case SWITCH_3:
      storage.Paste(Library::location());
      ui.ShowPreviousPage();
      break;
    
    case SWITCH_5:
      storage.PreviousVersion(Library::location());
      break;
    
    case SWITCH_6:
      storage.NextVersion(Library::location());
      break;

    case SWITCH_7:
      storage.Snapshot(Library::location());
      // Fall through

    case SWITCH_8:
      ui.ShowPreviousPage();
      break;
  }
  
  return 1;
}

/* static */
void VersionManager::UpdateScreen() {
  Library::UpdateLocation();
  
  char* buffer = display.line_buffer(0) + 1;
  Library::PrintActiveObjectName(&buffer[0]);
  AlignLeft(&buffer[0], 15);
  
  
  strncpy_P(&buffer[21], PSTR("version"), 7);
  UnsafeItoa<int16_t>(storage.version(Library::location()), 3, &buffer[29]);
  AlignRight(&buffer[29], 3);
  
  
  buffer = display.line_buffer(1) + 1;
  strncpy_P(&buffer[0], PSTR("copy|swap|paste      << | >> |keep|exit"), 39);
  buffer[4] = kDelimiter;
  buffer[9] = kDelimiter;
  buffer[24] = kDelimiter;
  buffer[29] = kDelimiter;
  buffer[34] = kDelimiter;
}

/* static */
void VersionManager::UpdateLeds() {
  leds.set_pixel(LED_8, 0xf0);
  for (uint8_t i = 0; i < 7; ++i) {
    leds.set_pixel(LED_1 + i, 0x0f);
  }
  leds.set_pixel(LED_4, 0x00);
}

}  // namespace ambika
