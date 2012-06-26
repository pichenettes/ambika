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

#include "avrlib/op.h"
#include "avrlib/time.h"

#include "controller/voicecard_tx.h"

#include <string.h>

namespace ambika {

/* extern */
VoicecardProtocolTx voicecard_tx;

/* <static> */
SpiMaster<SpiSS, MSB_FIRST, 8> VoicecardProtocolTx::spi_;
AddressBus VoicecardProtocolTx::voicecard_address_;
uint8_t VoicecardProtocolTx::voice_status_[kNumVoices];
uint8_t VoicecardProtocolTx::sd_card_busy_;
RingBuffer<OddOutputBufferSpecs> VoicecardProtocolTx::odd_buffer_;
RingBuffer<EvenOutputBufferSpecs> VoicecardProtocolTx::even_buffer_;
/* </static> */

/* static */
void VoicecardProtocolTx::Init() {
  voicecard_address_.set_mode(DIGITAL_OUTPUT);
  spi_.Init();
  memset(voice_status_, 0, sizeof(voice_status_));
}

/* static */
void VoicecardProtocolTx::PrepareForBlockWrite(uint8_t voice_id) {
  Write(voice_id, COMMAND_BULK_SEND);
}

/* static */
void VoicecardProtocolTx::WriteBlock(
    uint8_t voice_id,
    const uint8_t* data,
    uint8_t size) {
  FlushBuffers();
  voicecard_address_.Write(voice_id);
  spi_.Write(size);
  while (size) {
    // Block until we can write more.
    spi_.Write(*data++);
    --size;
  }
}

/* static */
void VoicecardProtocolTx::SyncAllVoices() {
  for (uint8_t i = 0; i < kNumVoices; ++i) {
    Sync(i);
  }
}

/* static */
void VoicecardProtocolTx::LightsOut() {
  for (uint8_t i = 0; i < kNumVoices; ++i) {
    BlockingTransaction(i, COMMAND_LIGHTS_OUT);
  }
}

/* static */
void VoicecardProtocolTx::Sync(uint8_t voice_id) {
  for (uint8_t i = 0; i < 4; ++i) {
    BlockingTransaction(voice_id, COMMAND_SYNC);
  }
}

/* static */
void VoicecardProtocolTx::Trigger(
    uint8_t voice_id,
    uint16_t note,
    uint8_t velocity,
    uint8_t legato) {
  voice_status_[voice_id] = velocity;
  Write(voice_id, COMMAND_NOTE_ON + legato);
  Write(voice_id, note >> 8);
  Write(voice_id, note & 0xff);
  Write(voice_id, velocity << 1);
}

/* static */
void VoicecardProtocolTx::WriteData(
    uint8_t voice_id,
    uint8_t data_type,
    uint8_t address,
    uint8_t value) {
  Write(voice_id, data_type);
  Write(voice_id, address);
  Write(voice_id, value);
}
    
/* static */
void VoicecardProtocolTx::WriteLfo(
    uint8_t voice_id,
    uint8_t address,
    uint8_t value) {
  Write(voice_id, COMMAND_WRITE_LFO | address);
  Write(voice_id, value);
}

/* static */
Word VoicecardProtocolTx::GetVersion(uint8_t voice_id) {
  Word result;
  Sync(voice_id);
  BlockingTransaction(voice_id, COMMAND_GET_SLAVE_ID);
  ConstantDelay(5);
  result.bytes[0] = BlockingTransaction(voice_id, 0xff);
  BlockingTransaction(voice_id, COMMAND_GET_VERSION_ID);
  ConstantDelay(5);
  result.bytes[1] = BlockingTransaction(voice_id, 0xff);
  return result;
}

/* static */
uint8_t VoicecardProtocolTx::WriteAsNibbles(uint8_t voice_id, uint8_t value) {
  voicecard_address_.Write(voice_id);
  spi_.Write(value & 0x0f);
  spi_.Write(U8Swap4(value) & 0x0f);
  return spi_.ImmediateRead();
}

/* static */
void VoicecardProtocolTx::FlushBuffers() {
  while (even_buffer_.readable() || odd_buffer_.readable());
}

/* static */
uint8_t VoicecardProtocolTx::BlockingTransaction(
    uint8_t voice_id,
    uint8_t value) {
  FlushBuffers();
  ConstantDelay(1);
  voicecard_address_.Write(voice_id);
  spi_.Write(value);
  return spi_.ImmediateRead();
}

/* static */
void VoicecardProtocolTx::Write(uint8_t voice_id, uint8_t value) {
  Word w;
  w.bytes[0] = voice_id;
  w.bytes[1] = value;
  if (voice_id & 1) {
    odd_buffer_.Write(w.value);
  } else {
    even_buffer_.Write(w.value);
  }
}

}  // namespace ambika
