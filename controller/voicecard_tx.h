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


#ifndef CONTROLLER_VOICECARD_TX_H_
#define CONTROLLER_VOICECARD_TX_H_

#include "avrlib/base.h"
#include "avrlib/parallel_io.h"
#include "avrlib/spi.h"

#include "common/protocol.h"

#include "controller/controller.h"
#include "controller/hardware_config.h"

namespace ambika {
  
using namespace avrlib;

enum VoicecardDataType {
  VOICECARD_DATA_PATCH = COMMAND_WRITE_PATCH_DATA,
  VOICECARD_DATA_PART = COMMAND_WRITE_PART_DATA,
  VOICECARD_DATA_MODULATION = COMMAND_WRITE_MOD_MATRIX,
};

struct OddOutputBufferSpecs {
  typedef uint16_t Value;
  enum {
    buffer_size = 32,
    data_size = 16,
  };
};

struct EvenOutputBufferSpecs {
  typedef uint16_t Value;
  enum {
    buffer_size = 32,
    data_size = 16,
  };
};

class VoicecardProtocolTx {
 public:
  VoicecardProtocolTx() { }
  static void Init();
  static void Trigger(
      uint8_t voice_id,
      uint16_t note,
      uint8_t velocity,
      uint8_t legato);
      
  static void WriteData(
      uint8_t voice_id,
      uint8_t data_type,
      uint8_t address,
      uint8_t value);

  static void WriteLfo(
      uint8_t voice_id,
      uint8_t address,
      uint8_t value);

  static void Sync(uint8_t voice_id);
  static void SyncAllVoices();
  static void LightsOut();

  static void PrepareForBlockWrite(uint8_t voice_id);
  static void WriteBlock(uint8_t voice_id, const uint8_t* data, uint8_t size);

  static inline void Release(uint8_t voice_id) {
    voice_status_[voice_id] = 0;
    Write(voice_id, COMMAND_RELEASE);
  }
  
  static inline void Kill(uint8_t voice_id) {
    voice_status_[voice_id] = 0;
    Write(voice_id, COMMAND_KILL);
  }
  
  static inline void RetriggerEnvelope(uint8_t voice_id, uint8_t envelope_id) {
    Write(voice_id, COMMAND_RETRIGGER_ENVELOPE | envelope_id);
  }
  
  static inline void ResetAllControllers(uint8_t voice_id) {
    Write(voice_id, COMMAND_RESET_ALL_CONTROLLERS);
  }
  
  static inline void Reset(uint8_t voice_id) {
    voice_status_[voice_id] = 0;
    Write(voice_id, COMMAND_RESET);
  }
  
  static Word GetVersion(uint8_t voice_id);

  static inline uint8_t voice_status(uint8_t voice_id) {
    return voice_status_[voice_id];
  }
  
  static inline uint8_t sd_card_busy() {
    return sd_card_busy_;
  }
  
  static inline uint8_t EnterFirmwareUpdateMode(uint8_t voice_id) {
    return BlockingTransaction(voice_id, COMMAND_FIRMWARE_UPDATE_MODE);
  }
  
  static inline void BeginSdCard() {
    FlushBuffers();
    voicecard_address_.Write(SPI_SLAVE_SD_CARD);
    SpiMISO::High();
    SPCR = 0x50;
    SPSR = 0x01;
    sd_card_busy_ = 1;
  }
  
  static inline void EndSdCard() {
    SpiMISO::Low();
    spi_.Init();
    sd_card_busy_ = 0;
  }
  
  static uint8_t WriteAsNibbles(uint8_t voice_id, uint8_t value);
  
  // Wait until the odd and even buffer are empty. This can take up to 1ms.
  static void FlushBuffers();
  
  static inline void SendBytes() {
    static uint8_t flop;
    flop ^= 1;
    if (even_buffer_.readable() && flop) {
      Word w;
      w.value = even_buffer_.ImmediateRead();
      voicecard_address_.Write(w.bytes[0]);
      spi_.Write(w.bytes[1]);
    }
    if (odd_buffer_.readable() && !flop) {
      Word w;
      w.value = odd_buffer_.ImmediateRead();
      voicecard_address_.Write(w.bytes[0]);
      // TODO(pichenettes): there's an optimization here... we do not need to
      // wait for the end of the write and we can leave early. But then we
      // might end up with a dangling SS set to low and we don't want that,
      // hell no!
      spi_.Write(w.bytes[1]);
    }
  }
  
 private:
  // Flush the buffer and do a write/read transaction.
  static uint8_t BlockingTransaction(uint8_t voice_id, uint8_t value);
  static void Write(uint8_t voice_id, uint8_t value);

  static SpiMaster<SpiSS, MSB_FIRST, 8> spi_;
  static AddressBus voicecard_address_;
  
  static uint8_t voice_status_[kNumVoices];
  static uint8_t sd_card_busy_;
  
  static RingBuffer<OddOutputBufferSpecs> odd_buffer_;
  static RingBuffer<EvenOutputBufferSpecs> even_buffer_;
  
  DISALLOW_COPY_AND_ASSIGN(VoicecardProtocolTx);
};

extern VoicecardProtocolTx voicecard_tx;

struct SdCardSession {
  static void Begin() { voicecard_tx.BeginSdCard(); }
  static void End() { voicecard_tx.EndSdCard(); }
};

}  // namespace ambika

#endif  // CONTROLLER_VOICECARD_TX_H_
