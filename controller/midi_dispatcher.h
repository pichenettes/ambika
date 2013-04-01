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

#ifndef CONTROLLER_MIDI_DISPATCHER_H_
#define CONTROLLER_MIDI_DISPATCHER_H_

#include "avrlib/base.h"
#include "avrlib/ring_buffer.h"

#include "controller/display.h"
#include "controller/multi.h"
#include "controller/storage.h"
#include "controller/system_settings.h"
#include "controller/ui_pages/library.h"
#include "controller/ui.h"

#include "midi/midi.h"

namespace ambika {

const uint8_t kDataEntryResendRate = 32;

struct LowPriorityBufferSpecs {
  enum {
    buffer_size = 128,
    data_size = 8,
  };
  typedef avrlib::DataTypeForSize<data_size>::Type Value;
};

struct HighPriorityBufferSpecs {
  enum {
    buffer_size = 8,
    data_size = 8,
  };
  typedef avrlib::DataTypeForSize<data_size>::Type Value;
};

class MidiDispatcher : public midi::MidiDevice {
 public:
  typedef avrlib::RingBuffer<LowPriorityBufferSpecs> OutputBufferLowPriority;
  typedef avrlib::RingBuffer<HighPriorityBufferSpecs> OutputBufferHighPriority;

  MidiDispatcher() { }

  // ------ MIDI in handling ---------------------------------------------------

  // Forwarded to the controller.
  static inline void NoteOn(uint8_t channel, uint8_t note, uint8_t velocity) {
    display.set_status('\x01');
    if (!ui.OnNote(note, velocity)) {
      multi.NoteOn(channel, note, velocity);
    }
  }
  static inline void NoteOff(uint8_t channel, uint8_t note, uint8_t velocity) {
    multi.NoteOff(channel, note, velocity);
  }

  // Handled.
  static inline void ControlChange(
      uint8_t channel,
      uint8_t controller,
      uint8_t value) {
    if (controller == midi::kBankMsb) {
      current_bank_ = value;
    } else {
      display.set_status('\x03');
      multi.ControlChange(channel, controller, value);
    }
  }
  static inline void PitchBend(uint8_t channel, uint16_t pitch_bend) {
    display.set_status('\x02');
    multi.PitchBend(channel, pitch_bend);
  }
  static void Aftertouch(uint8_t channel, uint8_t note, uint8_t velocity) {
    multi.Aftertouch(channel, note, velocity);
  }
  static void Aftertouch(uint8_t channel, uint8_t velocity) {
    multi.Aftertouch(channel, velocity);
  }
  static void AllSoundOff(uint8_t channel) {
    multi.AllSoundOff(channel);
  }
  static void ResetAllControllers(uint8_t channel) {
    multi.ResetAllControllers(channel);
  }
  static void AllNotesOff(uint8_t channel) {
    multi.AllNotesOff(channel);
  }
  static void OmniModeOff(uint8_t channel) {
    multi.OmniModeOff(channel);
  }
  static void OmniModeOn(uint8_t channel) {
    multi.OmniModeOn(channel);
  }
  
  static void ProgramChange(uint8_t channel, uint8_t program) {
    if (system_settings.rx_program_change()) {
      for (uint8_t retry = 0; retry < 2; ++retry) {
        bool error = false;
        if (current_bank_ < 26) {
          for (uint8_t i = 0; i < kNumParts; ++i) {
            if (multi.data().part_mapping_[i].receive_channel(channel)) {
              StorageLocation* location = Library::mutable_location();
              location->object = STORAGE_OBJECT_PROGRAM;
              location->name = NULL;  // We don't want to load the name.
              location->part = i;
              location->bank = current_bank_;
              location->slot = program;
              if (!error) {
                error = error | (storage.Load(*location) != FS_OK);
                if (!error) {
                  Library::SaveLocation();
                }
              }
            }
          }
        } else {
          StorageLocation* location = Library::mutable_location();
          location->object = STORAGE_OBJECT_MULTI;
          location->name = NULL;  // We don't want to load the name.
          location->part = 0;
          location->bank = current_bank_ - 26;
          location->slot = program;
          error = error | (storage.Load(*location) != FS_OK);
          if (!error) {
            Library::SaveLocation();
          }
        }
        if (!error) {
          Library::set_name_dirty();
          break;
        }
        Storage::InitFilesystem();
      }
    }
  }
  
  static void Reset() { multi.Reset(); }
  static void Clock() { 
    if (!multi.internal_clock()) {
      multi.Clock();
    }
  }
  static void Start() { multi.Start(); }
  static void Stop() { multi.Stop(); }
  static void Continue() { multi.Continue(); }
  
  static void SysExStart() {
    ProcessSysEx(0xf0);
  }
  static void SysExByte(uint8_t sysex_byte) {
    ProcessSysEx(sysex_byte);
  }
  static void SysExEnd() {
    ProcessSysEx(0xf7);
    if (Storage::sysex_rx_state() == RECEPTION_OK) {
      display.set_status('+');
    } else {
      display.set_status('#');
    }
  }
  
  static uint8_t CheckChannel(uint8_t channel) {
    return 1;
  }
  
  static void RawMidiData(
      uint8_t status,
      uint8_t* data,
      uint8_t data_size,
      uint8_t accepted_channel) {
    if (mode() == MIDI_OUT_FULL) {
      Send(status, data, data_size);
    }
  }
  
  static void RawByte(uint8_t byte) {
    if (mode() == MIDI_OUT_THRU) {
      OutputBufferLowPriority::Overwrite(byte);
    }
  }
  
  static uint8_t readable_high_priority() {
    return OutputBufferHighPriority::readable();
  }
  
  static uint8_t readable_low_priority() {
    return OutputBufferLowPriority::readable();
  }

  static uint8_t ImmediateReadHighPriority() {
    return OutputBufferHighPriority::ImmediateRead();
  }
  
  static uint8_t ImmediateReadLowPriority() {
    return OutputBufferLowPriority::ImmediateRead();
  }
  
  
  // ------ Generation of MIDI out messages ------------------------------------
  static inline void OnInternalNoteOff(Part* part, uint8_t note) {
    uint8_t channel = multi.part_channel(part);
    if (mode() == MIDI_OUT_SEQUENCER) {
      Send3(0x90 | channel, note, 0);
    }
  }
  
  static inline void OnInternalNoteOn(
      Part* part,
      uint8_t note,
      uint8_t velocity) {
    uint8_t channel = multi.part_channel(part);
    if (mode() == MIDI_OUT_SEQUENCER) {
      Send3(0x90 | channel, note, velocity);
    }
  }
  
  static inline void OnStart() {
    if (mode() == MIDI_OUT_SEQUENCER) {
      SendNow(0xfa);
    }
  }

  static inline void OnStop() {
    if (mode() == MIDI_OUT_SEQUENCER) {
      SendNow(0xfc);
    }
  }
  
  static inline void OnClock() {
    if (mode() == MIDI_OUT_SEQUENCER) {
      SendNow(0xf8);
    }
  }
  
  static inline void OnProgramLoaded(
      uint8_t channel,
      uint8_t bank,
      uint8_t program) {
    if (mode() == MIDI_OUT_FULL) {
      Send3(0xb0 | channel, 0x20, bank & 0x7f);
      // We send a program change + an active sensing message that does
      // strictly nothing. This way, we can use the already unrolled
      // Send3 function.
      Send3(0xc0 | channel, program & 0x7f, 0xfe);
    }
  }
  
  static inline void OnEdit(Part* part, uint8_t address, uint8_t value) {
    if (mode() < MIDI_OUT_CONTROLLER) {
      return;
    }
    uint8_t channel = multi.part_channel(part);
    ++data_entry_counter_;
    if (current_parameter_address_ != address || data_entry_counter_ >= 32) {
      Send3(0xb0 | channel, midi::kNrpnMsb, (address & 0x80) ? 1 : 0);
      Send3(0xb0 | channel, midi::kNrpnLsb, address & 0x7f);
      current_parameter_address_ = address;
      data_entry_counter_ = 0;
    }
    Send3(0xb0 | channel, midi::kDataEntryMsb, 1);
    Send3(0xb0 | channel, midi::kDataEntryLsb, value & 0x7f);
  }
  
  static void Send3(uint8_t status, uint8_t a, uint8_t b);
  static void SendBlocking(uint8_t byte);
  
  static void Flush() {
    while (OutputBufferLowPriority::readable());
  }

 private:
  static void Send(uint8_t status, uint8_t* data, uint8_t size);
  static void SendNow(uint8_t byte);
  static uint8_t mode() { return system_settings.data().midi_out_mode; }
  static void ProcessSysEx(uint8_t byte) {
    if (mode() == MIDI_OUT_FULL) {
      Send(byte, NULL, 0);
    }
    Storage::SysExReceive(byte);
  }
  
  static uint8_t current_bank_;
  static uint8_t data_entry_counter_;
  static uint8_t current_parameter_address_;
  
  DISALLOW_COPY_AND_ASSIGN(MidiDispatcher);
};

extern MidiDispatcher midi_dispatcher;

}  // namespace ambika

#endif  // CONTROLLER_MIDI_DISPATCHER_H_
