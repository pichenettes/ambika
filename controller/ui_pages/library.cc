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
// Special UI page for loading/saving operations.

#include "controller/ui_pages/library.h"

#include "avrlib/string.h"

#include "controller/display.h"
#include "controller/leds.h"
#include "controller/midi_dispatcher.h"
#include "controller/multi.h"

namespace ambika {

const prog_char blank_patch_name[] PROGMEM = "(empty)       \0";

/* static */
const prog_EventHandlers Library::event_handlers_ PROGMEM = {
  OnInit,
  UiPage::SetActiveControl,
  OnIncrement,
  OnClick,
  UiPage::OnPot,
  OnKey,
  NULL,
  OnIdle,
  UpdateScreen,
  UpdateLeds,
  OnDialogClosed,
};

/* <static> */
LibraryAction Library::action_;
StorageLocation Library::location_ = { STORAGE_OBJECT_PROGRAM, 0, 0 };
char Library::name_[16];
uint8_t Library::is_edit_buffer_;
uint8_t Library::more_;
uint8_t Library::initialization_mode_;
uint16_t Library::loaded_objects_indices_[kNumVoices * 3 + 1] = {
  0, 0, 0,
  0, 0, 0,
  0, 0, 0,
  0, 0, 0,
  0, 0, 0,
  0, 0, 0,
  0,
};
uint8_t Library::name_dirty_ = 0;
/* </static> */


/* static */
void Library::OnInit(PageInfo* info) {
  more_ = 0;
  location_.part = ui.state().active_part;
  if (storage.InitFilesystem() != FS_OK) {
    ShowDiskErrorMessage();
  }
  Browse();
  name_dirty_ = 0;
  initialization_mode_ = 1;
}

/* static */
void Library::Browse() {
  action_ = LIBRARY_ACTION_BROWSE;
  location_.bank = loaded_objects_indices_[location_.index()] >> 8;
  location_.slot = loaded_objects_indices_[location_.index()] & 0xff;
  location_.name = name_;
  edit_mode_ = EDIT_IDLE;
  active_control_ = 1;
  is_edit_buffer_ = 1;
  if (storage.LoadName(location_) != FS_OK) {
    memcpy_P(name_, blank_patch_name, sizeof(name_));
  }
}

/* static */
uint8_t Library::OnIncrement(int8_t increment) {
  if (action_ == LIBRARY_ACTION_BROWSE ||
      edit_mode_ == EDIT_STARTED_BY_ENCODER) {
    if (active_control_ == 0) {
      int8_t bank = location_.bank;
      location_.bank = Clip(bank + increment, 0, 25);
    } else if (active_control_ == 1){
      int16_t slot = location_.slot;
      location_.slot = Clip(location_.slot + increment, 0, 127);
    } else {
      char character = name_[active_control_ - 2];
      character = Clip(character + increment, 32, 127);
      name_[active_control_ - 2] = character;
    }
  }
  if (action_ == LIBRARY_ACTION_SAVE && edit_mode_ == EDIT_IDLE) {
    int8_t control = active_control_;
    control = Clip(control + increment, 0, 16);
    active_control_ = control;
  }
  
  if (action_ == LIBRARY_ACTION_BROWSE) {
    if (location_.bank_slot() != loaded_objects_indices_[location_.index()]) {
      // Send program change.
      if (location_.object == STORAGE_OBJECT_PROGRAM) {
        midi_dispatcher.OnProgramLoaded(
            multi.data().part_mapping_[location_.part].tx_channel(),
            location_.bank,
            location_.slot);
      }
      
      if (storage.Load(location_) != FS_OK) {
        is_edit_buffer_ = 1;
        memcpy_P(name_, blank_patch_name, sizeof(name_));
      } else {
        is_edit_buffer_ = 0;
      }
      SaveLocation();
    }
  }
  
  return 1;
}

/* static */
uint8_t Library::OnClick() {
  if (action_ == LIBRARY_ACTION_BROWSE) {
    active_control_ = (active_control_ + 1) & 1;
  } else {
    UiPage::OnClick();
  }
  return 1;
}

/* static */
uint8_t Library::OnKey(uint8_t key) {
  if (action_ == LIBRARY_ACTION_BROWSE) {
    return OnKeyBrowse(key);
  } else {
    return OnKeySave(key);
  }
}

/* static */
uint8_t Library::OnKeyBrowse(uint8_t key) {
  if (more_ == 0) {
    switch (key) {
      case SWITCH_1:
        {
          if (location_.object == STORAGE_OBJECT_MULTI) {
            location_.object = STORAGE_OBJECT_PATCH;
          } else {
            location_.object = static_cast<StorageObject>(location_.object + 1);
          }
          location_.bank = loaded_objects_indices_[location_.index()] >> 8;
          location_.slot = loaded_objects_indices_[location_.index()] & 0xff;
          Browse();
        }
        break;

      case SWITCH_2:
        {
          PrintActiveObjectName(&name_[0]);
          Dialog d;
          d.dialog_type = DIALOG_SELECT;
          d.num_choices = 2;
          d.first_choice = STR_RES_RANDOMIZE;
          d.text = 0;
          d.user_text = name_;
          ui.ShowDialogBox(1, d, initialization_mode_);
        }
        break;

      case SWITCH_3:
        storage.SysExSend(location_);
        break;

      case SWITCH_4:
        {
          action_ = LIBRARY_ACTION_SAVE;
          active_control_ = 2;
          edit_mode_ = EDIT_STARTED_BY_ENCODER;
          // We are writing to an empty location. Let's be nice with the user
          // and clear the patch name area.
          if (!memcmp_P(name_, blank_patch_name, sizeof(name_) - 1)) {
            memset(name_, ' ', sizeof(name_) - 1);
          }
        }
        break;

      case SWITCH_5:
        ui.ShowPage(PAGE_VERSION_MANAGER);
        break;

      case SWITCH_7:
        more_ ^= 1;
        break;

      case SWITCH_8:
        ui.ShowPreviousPage();
        break;
    }
  } else {
    switch (key) {
      case SWITCH_1:
        ui.ShowPage(PAGE_SYSTEM_SETTINGS);
        break;
        
      case SWITCH_2:
        {
          Dialog d;
          d.dialog_type = DIALOG_CONFIRM;
          d.text = PSTR("use current multi as default?");
          d.user_text = NULL;
          ui.ShowDialogBox(3, d, 0);
        }
        break;
        
      case SWITCH_3:
        ui.ShowPage(PAGE_OS_INFO);
        break;
        
      case SWITCH_7:
        more_ ^= 1;
        break;
        
      case SWITCH_8:
        ui.ShowPreviousPage();
        break;
    }
  }

  return 1;
}

/* static */
uint8_t Library::OnKeySave(uint8_t key) {
  switch (key) {
    case 6:
      {
        if (storage.Save(location_) == FS_OK) {
          SaveLocation();
          Browse();
        } else {
          ShowDiskErrorMessage();
        }
      }
      break;
      
    case 7:
      Browse();
      break;
  }   
  return 1;
}

/* static */
void Library::PrintActiveObjectName(char* buffer) {
  if (location_.object == STORAGE_OBJECT_MULTI) {
    strcpy_P(&buffer[0], PSTR("multi"));
  } else {
    ResourcesManager::LoadStringResource(
        STR_RES_PT_X_PATCH + location_.object, &buffer[0], 14);
    buffer[3] = '1' + location_.part; 
  }
}

/* static */
void Library::UpdateLocation() {
  if (location_.part != ui.state().active_part || name_dirty_) {
    location_.part = ui.state().active_part;
    name_dirty_ = 0;
    Browse();
  }
}

/* static */
void Library::UpdateScreen() {
  UpdateLocation();
  
  // First line: File browser
  char* buffer = display.line_buffer(0) + 1;
  
  PrintActiveObjectName(&buffer[0]);
  AlignLeft(&buffer[0], 15);

  if (is_edit_buffer_ && action_ == LIBRARY_ACTION_BROWSE) {
    buffer[14] = 0xa5;  // square dot.
  }
  buffer[15] = 'A' + location_.bank;
  UnsafeItoa<int16_t>(location_.slot, 3, &buffer[16]);
  PadRight(&buffer[16], 3, '0');
  memcpy(&buffer[20], name_, sizeof(name_) - 1);
  AlignLeft(&buffer[20], sizeof(name_) - 1);

  // Second line: buttons
  if (action_ == LIBRARY_ACTION_BROWSE) {
    buffer = display.line_buffer(1) + 1;
    if (more_) {
      strncpy_P(&buffer[0], PSTR("pref|~ini|about               more|exit"), 39);
      buffer[4] = kDelimiter;
    } else {
      strncpy_P(&buffer[0], PSTR(" |   init|send|save|versions  more|exit"), 39);
      buffer[9] = kDelimiter;
      buffer[14] = kDelimiter;
      buffer[19] = kDelimiter;
    }
    buffer[34] = kDelimiter;
  } else {
    buffer = display.line_buffer(1) + 1;
    strncpy_P(&buffer[28], PSTR("save|cancel"), 11);
    buffer[32] = kDelimiter;
  }
  
  // And now the cursor.
  if (action_ == LIBRARY_ACTION_SAVE) {
    display.set_cursor_character(edit_mode_ == EDIT_IDLE ? 0xff : '_');
  } else {
    display.set_cursor_character(' ');
  }
  
  if (active_control_ == 0) {
    display.set_cursor_position(16);
  } else if (active_control_ == 1) {
    display.set_cursor_position(
        action_ == LIBRARY_ACTION_SAVE ? 19 : kLcdNoCursor);
  } else {
    display.set_cursor_position(19 + active_control_);
  }
}

/* static */
void Library::UpdateLeds() {
  leds.set_pixel(LED_8, 0xf0);
  leds.set_pixel(LED_7, 0x0f);
  if (action_ == LIBRARY_ACTION_BROWSE) {
    for (uint8_t i = 0; i < (more_ ? 3 : 5); ++i) {
      leds.set_pixel(LED_1 + i, 0x0f);
    }
  }
}

/* static */
void Library::ShowDiskErrorMessage() {
  Dialog d;
  d.dialog_type = DIALOG_ERROR;
  d.text = PSTR("SD card I/O error");
  d.user_text = NULL;
  ui.ShowDialogBox(2, d, 0);
}

/* static */
void Library::OnDialogClosed(uint8_t dialog_id, uint8_t return_value) {
  switch (dialog_id) {
    // Handler for the init dialog box.
    case 1:
      if (return_value) {
        initialization_mode_ = return_value - 1;
        InitializationMode mode = return_value == 1
            ? INITIALIZATION_RANDOM
            : INITIALIZATION_DEFAULT;
        storage.Snapshot(location_);
        if (location_.object == STORAGE_OBJECT_MULTI) {
          multi.InitSettings(mode);
        } else {
          switch (location_.object) {
            case STORAGE_OBJECT_PATCH:
              multi.mutable_part(location_.part)->InitPatch(mode);
              break;

            case STORAGE_OBJECT_SEQUENCE:
              multi.mutable_part(location_.part)->InitSequence(mode);
              break;

            case STORAGE_OBJECT_PROGRAM:
              multi.mutable_part(location_.part)->InitSettings(mode);
              break;
          }
        }
      }
      Browse();
      break;
    
    // Handler for the save multi dialog box.
    case 3:
      if (return_value) {
        display.set_status('>');
        Storage::WriteMultiToEeprom();
      }
      break;
  }
}

}  // namespace ambika
