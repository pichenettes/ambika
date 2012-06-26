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
// Special UI page for triggering OS updates.

#ifndef CONTROLLER_UI_PAGES_OS_INFO_PAGE_H_
#define CONTROLLER_UI_PAGES_OS_INFO_PAGE_H_

#include "controller/ui_pages/ui_page.h"

namespace ambika {

class OsInfoPage : public UiPage {
 public:
  OsInfoPage() { }
  
  static void OnInit(PageInfo* info);
  
  static uint8_t OnKey(uint8_t key);
  static uint8_t OnIncrement(int8_t increment);
  static void UpdateScreen();
  static void UpdateLeds();

  static const prog_EventHandlers event_handlers_;

 private:
  static void PrintVersionNumber(char* buffer, uint8_t number);
  static void ReadVoicecardVersion();
  static void FindFirmwareFiles();
  
  static uint8_t voicecard_version_;
  static uint8_t active_port_;
  static uint8_t found_firmware_files_;
  
  DISALLOW_COPY_AND_ASSIGN(OsInfoPage);
};

}  // namespace ambika

#endif  // CONTROLLER_UI_PAGES_OS_INFO_PAGE_H_
