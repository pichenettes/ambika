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
// Simple SPI update bootloader.
//
// Blink patterns:
// 
// R&G blink together on incoming SPI data: firmware update requested, waiting
// for confirmation.
// 
// G on, O blink: confirmation received, recording firmware data into flash.
// 
// R&G blink together very fast for 1.2s: update successful!

#include <avr/boot.h>
#include <avr/pgmspace.h>

#include "avrlib/op.h"
#include "avrlib/spi.h"
#include "avrlib/time.h"
#include "avrlib/watchdog_timer.h"

#include "common/protocol.h"

#include "voicecard/leds.h"
#include "voicecard/voicecard.h"

using namespace avrlib;
using namespace ambika;

SpiSlave<MSB_FIRST, true> spi;

static uint8_t rx_buffer[SPM_PAGESIZE];

int main(void) __attribute__ ((naked)) __attribute__ ((section (".init9")));

int main(void) {
  ResetWatchdog();
  cli();
  SP = RAMEND;
  asm volatile ("clr __zero_reg__");
  rx_led.set_mode(DIGITAL_OUTPUT);
  note_led.set_mode(DIGITAL_OUTPUT);
  
  uint8_t update_flag = eeprom_read_byte(kFirmwareUpdateFlagPtr);
  // Voicecard did not boot successfully!
  if (update_flag >= 2) {
    for (uint8_t i = 0; i < 12; ++i) {
      note_led.Toggle();
      rx_led.Toggle();
      ConstantDelay(120);
    }
  }
  if (update_flag != FIRMWARE_UPDATE_DONE) {
    spi.Init();
    
    // Sync phase: wait for a sequence of at least 240 reset commands.
    uint8_t reset_command_counter = 0;
    while (1) {
      note_led.Low();
      rx_led.Low();
      spi.Reply(SPM_PAGESIZE >> 4);
      uint8_t byte = spi.Read();
      note_led.High();
      rx_led.High();
      
      if (byte == COMMAND_FIRMWARE_UPDATE_MODE) {
        ++reset_command_counter;
      } else {
        if (reset_command_counter >= 240) {
          rx_buffer[0] = byte & 0x0f;
          spi.Reply(0);
          rx_buffer[0] |= U8Swap4(spi.Read() & 0x0f);
          break;
        } else {
          reset_command_counter = 0;
        }
      }
    }
    
    // Update phase: record incoming nibbles to flash until reset command is
    // seen in the stream.
    uint8_t total_read = 0;
    uint16_t read = 1;
    uint8_t done = 0;
    uint16_t page = 0;
    note_led.High();
    while (!done) {
      // Blink the LED.
      rx_led.Low();
      uint8_t byte = spi.Read();
      rx_led.High();
      
      // Oops, we have found a stop byte.
      if (byte == COMMAND_FIRMWARE_UPDATE_MODE) {
        // If there is a pending block, pad it.
        if (read) {
          read = SPM_PAGESIZE;
        }
        done = 1;
      } else {
        // Write a pair of nibbles.
        rx_buffer[read] = byte & 0x0f;
        ++total_read;
        spi.Reply(total_read);
        rx_led.Low();
        rx_buffer[read++] |= U8Swap4(spi.Read() & 0x0f);
        rx_led.High();
      }
      // A page is full (or has been padded).
      if (read == SPM_PAGESIZE) {
        uint16_t i;
        const uint8_t* p = rx_buffer;
        eeprom_busy_wait();

        boot_page_erase(page);
        boot_spm_busy_wait();

        for (i = 0; i < SPM_PAGESIZE; i += 2) {
          Word w;
          w.bytes[0] = *p++;
          w.bytes[1] = *p++;
          boot_page_fill(page + i, w.value);
        }

        boot_page_write(page);
        boot_spm_busy_wait();
        boot_rww_enable();

        page += SPM_PAGESIZE;
        read = 0;
      }
    }
    rx_led.Low();
    // A little dance to say that we are good.
    for (uint8_t i = 0; i < 16; ++i) {
      note_led.Toggle();
      rx_led.Toggle();
      ConstantDelay(75);
    }
  }
  if (update_flag != FIRMWARE_UPDATE_PROBING_BOOT) {
    eeprom_write_byte(kFirmwareUpdateFlagPtr, FIRMWARE_UPDATE_PROBING_BOOT);
  }
  void (*main_entry_point)(void) = 0x0000;
  main_entry_point();
}
