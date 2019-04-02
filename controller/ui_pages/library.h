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
// Special UI page for loading/saving operations.

#ifndef CONTROLLER_UI_PAGES_LIBRARY_H_
#define CONTROLLER_UI_PAGES_LIBRARY_H_

#include "controller/controller.h"
#include "controller/storage.h"
#include "controller/ui_pages/ui_page.h"

namespace ambika {

enum LibraryAction {
  LIBRARY_ACTION_BROWSE,
  LIBRARY_ACTION_SAVE
};

class Library : public UiPage {
 public:
  Library() { }
  
  static void OnInit(PageInfo* info);
  static void SetActiveControl(ActiveControl active_control);

  static uint8_t OnIncrement(int8_t increment);
  static uint8_t OnClick();
  static uint8_t OnKey(uint8_t key);

  static void UpdateScreen();
  static void UpdateLeds();
  
  static const prog_EventHandlers event_handlers_;
  
  static void OnDialogClosed(uint8_t dialog_id, uint8_t return_value);
  static void SaveLocation() {
    loaded_objects_indices_[location_.index()] = location_.bank_slot();
  }
  static inline void set_name_dirty() {
    name_dirty_ = 1;
  }
  static StorageLocation* mutable_location() { return &location_; }
  static const StorageLocation& location() { return location_; }

  static void PrintActiveObjectName(char* buffer);
  static void UpdateLocation();

 private:
  static void Browse();
  static void ShowDiskErrorMessage();

  static uint8_t OnKeyBrowse(uint8_t key);
  static uint8_t OnKeySave(uint8_t key);
  
  static LibraryAction action_;
  static StorageLocation location_;
  static uint16_t loaded_objects_indices_[kNumVoices * 3 + 1];
  static char name_[16];
  static uint8_t is_edit_buffer_;
  static uint8_t more_;
  static uint8_t initialization_mode_;
  static uint8_t name_dirty_;
  
  DISALLOW_COPY_AND_ASSIGN(Library);
};

}  // namespace ambika

#endif  // CONTROLLER_UI_PAGES_LIBRARY_H_
