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

#include "controller/ui_pages/os_info_page.h"

#include <avr/eeprom.h>

#include "avrlib/string.h"
#include "avrlib/watchdog_timer.h"

#include "controller/display.h"
#include "controller/leds.h"
#include "controller/multi.h"
#include "controller/storage.h"

namespace ambika {

/* static */
const prog_EventHandlers OsInfoPage::event_handlers_ PROGMEM = {
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
uint8_t OsInfoPage::found_firmware_files_;

/* static */
void OsInfoPage::OnInit(PageInfo* info) {
  active_control_ = 0;
  FindFirmwareFiles();
}

/* static */
void OsInfoPage::FindFirmwareFiles() {
  found_firmware_files_ = 0;
  if (storage.FileExists(PSTR("/AMBIKA.BIN"))) {
    found_firmware_files_ |= 1;
  }
  
  if (storage.FileExists(PSTR("/VOICE$.BIN"), '1' + active_control_)) {
    found_firmware_files_ |= 2;
  }
}

/* static */
uint8_t OsInfoPage::OnIncrement(int8_t increment) {
  active_control_ = Clip(active_control_ + increment, 0, kNumVoices);
  FindFirmwareFiles();
}

/* static */
uint8_t OsInfoPage::OnKey(uint8_t key) {
  switch(key) {
    case SWITCH_1:
      {
        if (found_firmware_files_ & 1) {
          // Force a reset into the SD card loader.
          eeprom_write_byte(kFirmwareUpdateFlagPtr, 1);
          SystemReset(0);
          while (1) { }
        }
      }
      break;
      
    case SWITCH_4:
      {
        if (found_firmware_files_ & 2) {
          // Resets the voicecard into its bootloader.
          voicecard_tx.EnterFirmwareUpdateMode(active_control_);
          // Wait while the voicecard reboots.
          ConstantDelay(100);
          uint8_t page_size_nibbles = 0;
          for (uint8_t i = 0; i < 250; ++i) {
            // Confirms the reset to the bootloader.
            page_size_nibbles = \
                voicecard_tx.EnterFirmwareUpdateMode(active_control_);
          }
          if (page_size_nibbles) {
            // Sends the firmware data in nibblized format.
            storage.SpiCopy(
                active_control_,
                PSTR("/VOICE$.BIN"),
                '1' + active_control_,
                page_size_nibbles);
            voicecard_tx.EnterFirmwareUpdateMode(active_control_);
          }
        }
      }
      break;
      
    case SWITCH_8:
      ui.ShowPreviousPage();
      break;
  }
  return 1;
}

/* static */
void OsInfoPage::PrintVersionNumber(char* buffer, uint8_t number) {
  *buffer++ = 'v';
  *buffer++ = '0' + U8ShiftRight4(number);
  *buffer++ = '.';
  *buffer++ = '0' + (number & 0x0f);
}

/* static */
void OsInfoPage::UpdateScreen() {
  char* buffer = display.line_buffer(0) + 1;
  memcpy_P(&buffer[0], PSTR("ambika"), 6);
  PrintVersionNumber(&buffer[10], kSystemVersion);

  memcpy_P(&buffer[15], PSTR("port 1 device ?"), 15);
  Word version_number = voicecard_tx.GetVersion(active_control_);
  buffer[20] = '1' + active_control_;
  uint8_t valid_device = 0;
  if (version_number.bytes[0] < SLAVE_ID_LAST && version_number.bytes[0] > 0) {
    buffer[29] = '0' + version_number.bytes[0];
    PrintVersionNumber(&buffer[35], version_number.bytes[1]);
    valid_device = 1;
  }
  buffer[14] = kDelimiter;
  buffer = display.line_buffer(1) + 1;
  if (found_firmware_files_ & 1) {
    strncpy_P(&buffer[0], PSTR("upgrade"), 7);
  }
  buffer[14] = kDelimiter;
  if (found_firmware_files_ & 2) {
    if (valid_device) {
      strncpy_P(&buffer[15], PSTR("upgrade"), 7);
    } else {
      strncpy_P(&buffer[15], PSTR("install"), 7);
    }
  }
  strncpy_P(&buffer[35], PSTR("exit"), 4);
}

/* static */
void OsInfoPage::UpdateLeds() {
  leds.set_pixel(LED_8, 0xf0);
  if (found_firmware_files_ & 1) {
    leds.set_pixel(LED_1, 0x0f);
  }
  if (found_firmware_files_ & 2) {
    leds.set_pixel(LED_4, 0x0f);
  }
}

}  // namespace ambika
