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

#ifndef VOICECARD_VOICECARD_RX_H_
#define VOICECARD_VOICECARD_RX_H_

#include <avr/eeprom.h>

#include "avrlib/ring_buffer.h"
#include "avrlib/spi.h"
#include "avrlib/timer.h"
#include "avrlib/watchdog_timer.h"

#include "common/protocol.h"

#include "voicecard/voice.h"
#include "voicecard/voicecard.h"
#include "voicecard/leds.h"

namespace ambika {

using avrlib::RingBuffer;

enum State {
  EXPECTING_COMMAND,
  EXPECTING_ARGUMENTS,
};

struct InputBufferSpecs {
  typedef uint8_t Value;
  enum {
    buffer_size = 256,
    data_size = 8,
  };
};

class VoicecardProtocolRx {
 public:
  VoicecardProtocolRx() { }
  
  static void Init() {
    spi_.Init();
    state_ = EXPECTING_COMMAND;
    lights_out_ = 0;
  }
  
  static inline void Receive() {
    if (spi_.readable()) {
      rx_led_counter_ = 255;
      uint8_t byte = spi_.ImmediateRead();
      buffer_.Overwrite(byte);
      spi_.Reply(0xff);
    }
  }
  
  static void TickRxLed() {
    if (rx_led_counter_) {
      --rx_led_counter_;
      if (!lights_out_) {
        rx_led.High();
      }
    } else {
      rx_led.Low();
    }
  }
  
  static void DoLongCommand() {
    switch (command_ & 0xf0) {
      case COMMAND_NOTE_ON:
        voice.Trigger(
            (arguments_[0] << 8) | arguments_[1],
            arguments_[2],
            command_ & 1);
        if (!lights_out_) {
          note_led.High();
        }
        break;
      case COMMAND_WRITE_PATCH_DATA:
        voice.set_patch_data(arguments_[0], arguments_[1]);
        break;
      case COMMAND_WRITE_PART_DATA:
        voice.set_part_data(arguments_[0], arguments_[1]);
        break;
      case COMMAND_WRITE_MOD_MATRIX:
        voice.set_modulation_source(arguments_[0], arguments_[1]);
        break;
      case COMMAND_WRITE_LFO:
        voice.set_modulation_source(
            MOD_SRC_LFO_1 + (command_ & 0x0f),
            arguments_[0]);
        break;
    }
  }
  
  static void DoShortCommand() {
    switch (command_) {
      case COMMAND_RELEASE:
        voice.Release();
        note_led.Low();
        break;
      case COMMAND_KILL:
        voice.Kill();
        note_led.Low();
        break;
      case COMMAND_RETRIGGER_ENVELOPE:
      case COMMAND_RETRIGGER_ENVELOPE + 1:
      case COMMAND_RETRIGGER_ENVELOPE + 2:
        voice.TriggerEnvelope(command_ & 0x0f, ATTACK);
        break;
      case COMMAND_RESET_ALL_CONTROLLERS:
        voice.ResetAllControllers();
        break;
      case COMMAND_RESET:
        voice.Init();
        note_led.Low();
        break;
      case COMMAND_LIGHTS_OUT:
        lights_out_ = 1;
        rx_led.Low();
        note_led.Low();
        break;
      case COMMAND_BULK_SEND:
        {
          // Stop doing anything else
          Timer<2>::Stop();
          uint8_t size = spi_.Read();
          uint8_t* data = data_ptr_ = voice.mutable_patch_data();
          while (size--) {
            *data++ = spi_.Read();
          }
          Timer<2>::Start();
        }
        break;
      case COMMAND_FIRMWARE_UPDATE_MODE:
        eeprom_write_byte(kFirmwareUpdateFlagPtr, FIRMWARE_UPDATE_REQUESTED);
        SystemReset(0);
        while (1) { }
        break;
      // This prepares SPDR for the next transfer.
      case COMMAND_GET_SLAVE_ID:
        SPDR = SLAVE_ID_SOLO_VOICECARD;
        break;
      case COMMAND_GET_VERSION_ID:  
        SPDR = kSystemVersion;
        break;
    }
  }
  
  static void Process() {
    while (buffer_.readable()) {
      uint8_t byte = buffer_.ImmediateRead();
      if (state_ == EXPECTING_COMMAND) {
        command_ = byte;
        data_ptr_ = arguments_;
        state_ = EXPECTING_ARGUMENTS;
        if (command_ >= COMMAND_NOTE_ON &&
            command_ < COMMAND_WRITE_PATCH_DATA) {
          data_size_ = 3;
        } else if (command_ >= COMMAND_WRITE_PATCH_DATA
                   && command_ < COMMAND_WRITE_LFO) {
          data_size_ = 2;
        } else if ((command_ & 0xf0) == COMMAND_WRITE_LFO) {
          data_size_ = 1;
        } else {
          DoShortCommand();
          state_ = EXPECTING_COMMAND;
        }
      } else {
        *data_ptr_++ = byte;
        if (--data_size_ == 0) {
          DoLongCommand();
          state_ = EXPECTING_COMMAND;
        }
      }
    }
  }
  
  static inline uint8_t writable() { return buffer_.writable(); }

 private:
  static SpiSlave<MSB_FIRST, false> spi_;

  static RingBuffer<InputBufferSpecs> buffer_;
  static uint8_t command_;
  static uint8_t state_;
  static uint8_t data_size_;
  static uint8_t* data_ptr_;
  static uint8_t arguments_[3];
  static uint8_t rx_led_counter_;
  static uint8_t lights_out_;
   
  DISALLOW_COPY_AND_ASSIGN(VoicecardProtocolRx);
};

extern VoicecardProtocolRx voicecard_rx;

}  // namespace ambika

#endif  // VOICECARD_VOICECARD_RX_H_
