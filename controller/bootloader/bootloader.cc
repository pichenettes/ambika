// Copyright 2011 Olivier Gillet.
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
// Bootloader supporting MIDI SysEx update.

#include <avr/boot.h>
#include <avr/pgmspace.h>
#include <avr/delay.h>

#include "avrlib/devices/sd_card.h"
#include "avrlib/devices/shift_register.h"
#include "avrlib/filesystem/fat_file_reader.h"
#include "avrlib/spi.h"
#include "avrlib/string.h"
#include "avrlib/watchdog_timer.h"

#include "controller/hardware_config.h"
#include "controller/display.h"

using namespace avrlib;
using namespace ambika;

Lcd ambika::lcd;

ShiftRegisterInput<
  IOEnableLine,
  IOClockLine,
  IOInputLine, 8, LSB_FIRST> switches;

ShiftRegisterOutput<
  IOEnableLine,
  IOClockLine,
  IOOutputLine, 16, MSB_FIRST> leds;

Serial<SerialPort0, 31250, POLLED, DISABLED> midi;

typedef SdCard<SpiMaster<SpiSS, MSB_FIRST, 4> > SdCardInterface;
FATFileReader<SdCardInterface> reader;
AddressBus address;

void (*main_entry_point)(void) = 0x0000;

uint16_t page = 0;
uint8_t rx_buffer[2 * (SPM_PAGESIZE + 1)];

void Print(uint8_t position, const char* message) {
  lcd.MoveCursor(position, 0);
  lcd.Write(message);
  lcd.Flush();
}

void LedsError() {
  leds.Write(0x40ff);
}

void LedsOk() {
  leds.Write(0xbf00);
}

void WriteBufferToFlash() {
  uint16_t i;
  const uint8_t* p = rx_buffer;
  eeprom_busy_wait();

  boot_page_erase(page);
  boot_spm_busy_wait();

  for (i = 0; i < SPM_PAGESIZE; i += 2) {
    uint16_t w = *p++;
    w |= (*p++) << 8;
    boot_page_fill(page + i, w);
  }

  boot_page_write(page);
  boot_spm_busy_wait();
  boot_rww_enable();
  
  page += SPM_PAGESIZE;
  char buffer[6];
  UnsafeItoa(page, 6, buffer);
  Print(1, buffer);
}

char msg_sd_update[]   = "SD update... ";
char msg_sd_error[]    = "SD error";
char msg_midi_update[] = "Syx update...";
char msg_done[]        = "Done         ";

inline void SdCardUpdater() {
  // Select the SD card.
  address.set_mode(DIGITAL_OUTPUT);
  address.Write(SPI_SLAVE_SD_CARD);
  FsHandle h;
  if (reader.Init() == FFR_OK &&
      reader.Open("AMBIKA  BIN", &h) == FFR_OK) {
    Print(0, msg_sd_update);
    while (reader.Read(&h, SPM_PAGESIZE, rx_buffer)) {
      WriteBufferToFlash();
    }
    if (h.eof()) {
      Print(0, msg_done);
      ConstantDelay(1000);
      return;
    }
  }
  LedsError();
  Print(0, msg_sd_error);
  ConstantDelay(2000);
  return;
}

static const uint8_t sysex_header[] = {
  0xf0,  // <SysEx>
  0x00, 0x21, 0x02,  // Mutable instruments manufacturer id.
  0x00, 0x04,  // Product ID for Ambika.
};

enum SysExReceptionState {
  MATCHING_HEADER = 0,
  READING_COMMAND = 1,
  READING_DATA = 2,
};

inline void MidiUpdater() {
  uint8_t byte;
  uint16_t bytes_read = 0;
  uint16_t rx_buffer_index;
  uint8_t state = MATCHING_HEADER;
  uint8_t checksum;
  uint8_t sysex_commands[2];
  uint8_t status = 0;

  Print(0, msg_midi_update);
  midi.Init();
  
  while (1) {
    byte = midi.Read();
    // In case we see a realtime message in the stream, safely ignore it.
    if (byte > 0xf0 && byte != 0xf7) {
      continue;
    }
    switch (state) {
      case MATCHING_HEADER:
        if (byte == sysex_header[bytes_read]) {
          LedsOk();
          ++bytes_read;
          if (bytes_read == sizeof(sysex_header)) {
            bytes_read = 0;
            state = READING_COMMAND;
          }
        } else {
          LedsError();
          bytes_read = 0;
        }
        break;

      case READING_COMMAND:
        if (byte < 0x80) {
          sysex_commands[bytes_read++] = byte;
          if (bytes_read == 2) {
            bytes_read = 0;
            rx_buffer_index = 0;
            checksum = 0;
            state = READING_DATA;
          }
        } else {
          state = MATCHING_HEADER;
          status = 0;
          bytes_read = 0;
        }
        break;

      case READING_DATA:
        if (byte < 0x80) {
          if (bytes_read & 1) {
            rx_buffer[rx_buffer_index] |= byte & 0xf;
            if (rx_buffer_index < SPM_PAGESIZE) {
              checksum += rx_buffer[rx_buffer_index];
            }
            ++rx_buffer_index;
          } else {
            rx_buffer[rx_buffer_index] = (byte << 4);
          }
          ++bytes_read;
        } else if (byte == 0xf7) {
          if (sysex_commands[0] == 0x7f &&
              sysex_commands[1] == 0x00 &&
              bytes_read == 0) {
            // Reset.
            Print(0, msg_done);
            ConstantDelay(1000);
            return;
          } else if (rx_buffer_index == SPM_PAGESIZE + 1 &&
                     sysex_commands[0] == 0x7e &&
                     sysex_commands[1] == 0x00 &&
                     rx_buffer[rx_buffer_index - 1] == checksum) {
            // Block write.
            WriteBufferToFlash();
          } else {
            LedsError();
          }
          state = MATCHING_HEADER;
          bytes_read = 0;
        }
        break;
    }
  }
}

int main(void) {
  ResetWatchdog();
  
  cli();
  switches.Init();
  leds.Init();
  uint8_t switches_state = switches.Read();
  uint8_t update_requested = eeprom_read_byte(kFirmwareUpdateFlagPtr);
  if (update_requested) {
    eeprom_write_byte(kFirmwareUpdateFlagPtr, 0);
  }
  if (switches_state != 0xff || update_requested) {
    LedsOk();
    lcd.Init();
  }
  if (!(switches_state & 0x80) || update_requested) {
    SdCardUpdater();
  } else if (!(switches_state & 0x40)) {
    MidiUpdater();
  }
  main_entry_point();
}
