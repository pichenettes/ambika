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
// MIDI output.

#include "peripherals/nunchuk/midi_output.h"

#include "avrlib/op.h"

namespace nunchuk {

using namespace avrlib;

/* static */
MidiSerialPort MidiOutput::serial_port_;

/* static */
RingBuffer<MidiOutput> MidiOutput::buffer_;

/* static */
uint8_t MidiOutput::use_serial_;

/* static */
uint8_t MidiOutput::channel_;

/* static */
uint8_t MidiOutput::previous_pitch_bend_msb_;

/* static */
uint8_t MidiOutput::previous_modulation_msb_;

/* static */
uint8_t MidiOutput::previous_breath_msb_;

/* static */
uint8_t MidiOutput::previous_cutoff_;

/* static */
uint8_t MidiOutput::smoothed_cutoff_;

/* static */
void MidiOutput::Init() {
  serial_port_.Init();
  use_serial_ = 1;
  // TODO(pichenettes): load from eeprom
  channel_ = 0;
  previous_pitch_bend_msb_ = 0;
  previous_modulation_msb_ = 0;
  previous_breath_msb_ = 0;
}

/* static */
void MidiOutput::set_channel(uint8_t c) {
  c = c & 0xf;
  if (c != channel_) {
    AllSoundsOff();
    channel_ = c;
    // TODO(pichenettes): save to eeprom
  }
}

/* static */
void MidiOutput::Process() {
  if (use_serial_) {
    if (buffer_.readable() && serial_port_.writable()) {
      serial_port_.Overwrite(buffer_.ImmediateRead());
    }
  } else {
    // SPI read and response.
  }
}

/* static */
void MidiOutput::AllSoundsOff() {
  buffer_.Write(0xb0 | channel_);
  buffer_.Write(0x78);
  buffer_.Write(0);
}

/* static */
void MidiOutput::NoteOn(uint8_t note, uint8_t velocity) {
  buffer_.Write(0x90 | channel_);
  buffer_.Write(note);
  buffer_.Write(velocity);
}

/* static */
void MidiOutput::NoteOff(uint8_t note) {
  buffer_.Write(0x80 | channel_);
  buffer_.Write(note);
  buffer_.Write(0);
}

/* static */
void MidiOutput::Cc(uint8_t cc, uint8_t value) {
  buffer_.Write(0xb0 | channel_);
  buffer_.Write(cc);
  buffer_.Write(value);
}

/* static */
void MidiOutput::PitchBend(uint8_t msb) {
  if (msb != previous_pitch_bend_msb_) {
    buffer_.Write(0xe0 | channel_);
    buffer_.Write(0);
    buffer_.Write(msb);
  }
  previous_pitch_bend_msb_ = msb;
}

/* static */
void MidiOutput::Modulation(uint8_t msb) {
  if (msb != previous_modulation_msb_) {
    buffer_.Write(0xb0 | channel_);
    buffer_.Write(0x01);
    buffer_.Write(msb);
  }
  previous_modulation_msb_ = msb;
}

/* static */
void MidiOutput::Breath(uint8_t msb) {
  if (msb != previous_breath_msb_) {
    buffer_.Write(0xb0 | channel_);
    buffer_.Write(0x02);
    buffer_.Write(msb);
  }
  previous_breath_msb_ = msb;
}

/* static */
void MidiOutput::Cutoff(uint8_t value) {
  if (value != previous_cutoff_) {
    buffer_.Write(0xb0 | channel_);
    buffer_.Write(0x4a);
    buffer_.Write(value);
  }
  previous_cutoff_ = value;
}

/* static */
void MidiOutput::SmoothCutoff(uint8_t value) {
  smoothed_cutoff_ = U8Mix(smoothed_cutoff_, value, 240, 15);
  Cutoff(smoothed_cutoff_);
}



/* extern */
MidiOutput midi_output;

}  // namespace nunchuk
