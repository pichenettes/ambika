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
// "Part" is the dumb data structure storing the part settings.
// "PartManager" is responsible for handling a bunch of voicecards assigned
// to the same logical part.

#ifndef CONTROLLER_PART_H_
#define CONTROLLER_PART_H_

#include "avrlib/base.h"

#include "common/lfo.h"
#include "common/patch.h"

#include "controller/controller.h"
#include "controller/note_stack.h"
#include "controller/voice_allocator.h"

namespace ambika {
  
enum InitializationMode {
  INITIALIZATION_DEFAULT,
  INITIALIZATION_RANDOM
};

enum ArpeggiatorDirection {
  ARPEGGIO_DIRECTION_UP = 0,
  ARPEGGIO_DIRECTION_DOWN,
  ARPEGGIO_DIRECTION_UP_DOWN,
  ARPEGGIO_DIRECTION_AS_PLAYED,
  ARPEGGIO_DIRECTION_RANDOM,
  ARPEGGIO_DIRECTION_CHORD,
  ARPEGGIO_DIRECTION_LAST
};

enum ArpSequencerMode {
  ARP_SEQUENCER_MODE_STEP,
  ARP_SEQUENCER_MODE_ARPEGGIATOR,
  ARP_SEQUENCER_MODE_NOTE,
  ARP_SEQUENCER_MODE_LAST
};

enum PolyphonyMode {
  MONO,
  POLY,
  UNISON_2X,
  CYCLIC,
  CHAIN,
  POLYPHONY_MODE_LAST
};

enum PartFlags {
  FLAG_HAS_CHANGE = 1,
  FLAG_HAS_USER_CHANGE = 2,
};

static const uint8_t kNumSequences = 3;

struct NoteStep {
  uint8_t note;
  uint8_t velocity;
  uint8_t legato;
  uint8_t gate;
};

struct PartData {
  // Offset: 0
  uint8_t volume;

  // Offset: 1-5
  int8_t octave;
  int8_t tuning;
  uint8_t spread;
  uint8_t raga;

  // Offset: 5-8
  uint8_t legato;
  uint8_t portamento_time;
  uint8_t arp_sequencer_mode;

  // Offset: 8-12
  uint8_t arp_direction;
  uint8_t arp_octave;
  uint8_t arp_pattern;
  uint8_t arp_divider;

  // Offset: 12..16
  uint8_t sequence_length[kNumSequences];
  uint8_t polyphony_mode;

  // Offset: 16-80
  //  0..15: step sequence 1
  // 16..31: step sequence 2
  // 32..63: (note value | 0x80 if gate), (note velocity | 0x80 if legato)
  uint8_t sequence_data[64];
  
  // Offset: 80-84
  uint8_t padding[4];
  
  uint8_t step_value(uint8_t sequence, uint8_t step) const {
    return sequence_data[(step + (sequence << 4)) & 0x1f];
  }
  
  void set_step_value(uint8_t sequence, uint8_t step, uint8_t value) {
    sequence_data[(step + (sequence << 4)) & 0x1f] = value;
  }
  
  uint8_t note(uint8_t step) const {
    uint8_t offset = (32 + (step << 1)) & 0x3f;
    return sequence_data[offset] & 0x7f;
  }
  
  void set_note(uint8_t step, uint8_t note) {
    uint8_t offset = (32 + (step << 1)) & 0x3f;
    sequence_data[offset] &= 0x80;
    sequence_data[offset] |= note;
  }
  
  uint16_t ordered_gate_velocity(uint8_t step) const {
    uint8_t offset = (32 + (step << 1)) & 0x3f;
    if (!(sequence_data[offset] & 0x80)) {
      return 0;
    } else {
      uint8_t o = sequence_data[offset + 1] + 128;
      return static_cast<uint16_t>(o) + 1;
    }
  }
  
  void set_ordered_gate_velocity(uint8_t step, uint16_t value) {
    uint8_t offset = (32 + (step << 1)) & 0x3f;
    if (!value) {
      sequence_data[offset] &= 0x7f;
      sequence_data[offset + 1] = 0;
    } else {
      sequence_data[offset] |= 0x80;
      sequence_data[offset + 1] = (value - 1) + 128;
    }
  }
  
  void set_velocity(uint8_t step, uint8_t velocity) {
    uint8_t offset = (32 + (step << 1)) & 0x3f;
    sequence_data[offset + 1] &= 0x80;
    sequence_data[offset + 1] |= velocity;
  }
  
  NoteStep note_step(uint8_t step) const {
    NoteStep n;
    uint8_t offset = (32 + (step << 1)) & 0x3f;
    n.note = sequence_data[offset];
    n.velocity = sequence_data[offset + 1];
    n.gate = n.note & 0x80;
    n.legato = n.velocity & 0x80;
    n.note &= 0x7f;
    n.velocity &= 0x7f;
    return n;
  }
};

typedef PartData PROGMEM prog_PartData;

enum PartParameter {
  PRM_PART_VOLUME = sizeof(Patch),
  PRM_PART_OCTAVE,
  PRM_PART_TUNING,
  PRM_PART_TUNING_SPREAD,
  PRM_PART_RAGA,
  PRM_PART_LEGATO,
  PRM_PART_PORTAMENTO_TIME,
  PRM_PART_ARP_MODE,
  PRM_PART_ARP_DIRECTION,
  PRM_PART_ARP_OCTAVE,
  PRM_PART_ARP_PATTERN,
  PRM_PART_ARP_RESOLUTION,
  PRM_PART_SEQUENCE_LENGTH_1,
  PRM_PART_SEQUENCE_LENGTH_2,
  PRM_PART_SEQUENCE_LENGTH_3,
  PRM_PART_POLYPHONY_MODE
};

class Part {
 public:
  Part() { }
  void Init();

  void InitPatch(InitializationMode mode);
  void InitSettings(InitializationMode mode);
  void InitSequence(InitializationMode mode);
  
  void NoteOn(uint8_t note, uint8_t velocity);
  void NoteOff(uint8_t note);
  void ControlChange(uint8_t controller, uint8_t value);
  void PitchBend(uint16_t pitch_bend);
  void Aftertouch(uint8_t note, uint8_t velocity);
  void Aftertouch(uint8_t velocity);
  void AllSoundOff();
  void ResetAllControllers();
  void AllNotesOff();
  void MonoModeOn(uint8_t num_channels);
  void PolyModeOn();
  void Reset();
  void Clock();
  void Start();
  void Stop();
  
  uint8_t num_pressed_keys() const { return pressed_keys_.size(); }
  
  void SetValue(uint8_t address, uint8_t value, uint8_t user_initiated);
  
  inline uint8_t GetValue(uint8_t address) const {
    const uint8_t* bytes;
    bytes = static_cast<const uint8_t*>(static_cast<const void*>(&patch_));
    return bytes[address];
  }

  PartData* mutable_data() { return &data_; }
  const PartData& data() const { return data_; }
  
  const uint8_t* raw_sequence_data() const { 
    return static_cast<const uint8_t*>(static_cast<const void*>(&data_)) + 8;
  }
  const uint8_t* raw_data() const { 
    return static_cast<const uint8_t*>(static_cast<const void*>(&data_));
  }
  const uint8_t* raw_patch_data() const { 
    return static_cast<const uint8_t*>(static_cast<const void*>(&patch_));
  }
  
  uint8_t* mutable_raw_sequence_data() {
    return static_cast<uint8_t*>(static_cast<void*>(&data_)) + 8;
  }
  uint8_t* mutable_raw_data() {
    return static_cast<uint8_t*>(static_cast<void*>(&data_));
  }
  uint8_t* mutable_raw_patch_data() {
    return static_cast<uint8_t*>(static_cast<void*>(&patch_));
  }
  
  uint8_t lfo_value(uint8_t index) const { return lfo_previous_values_[index]; }
  uint8_t step(uint8_t index) const { return sequencer_step_[index]; }

  void Touch();
  void TouchPatch();
  void UpdateLfos(uint8_t refresh_cycle);
  
  void AssignVoices(uint8_t allocation);
  inline uint8_t flags() const { return flags_; }
  inline void ClearFlag(uint8_t flag) { flags_ &= ~flag; }
  

 private:
  void RandomizeRange(uint8_t start, uint8_t size);
  void InitializeAllocators();
  void TouchVoiceAllocation();
  void TouchClock();
  void TouchLfos();
  
  void RetriggerLfos();
  
  // Called on each "tick" of the arpeggiator and sequencer clock.
  void ClockSequencer();
  void ClockArpeggiator();
  
  // Called whenever a new arpeggiator note has to be triggered.
  void StartArpeggio();
  void StepArpeggio();
  
  void WriteToAllVoices(uint8_t data_type, uint8_t address, uint8_t value);
   
  // Check whether a note should be played by this part. A note can be rejected
  // if it is outside of the split region, or if it is outside of the selected
  // scale/raga.
  uint8_t AcceptNote(uint8_t note) const;
  uint16_t TuneNote(uint8_t midi_note) const;

  void InternalNoteOn(uint8_t note, uint8_t velocity);
  void InternalNoteOff(uint8_t note);
  
  uint8_t GetNextVoice(uint8_t voice_index) const;
  
  Patch patch_;
  PartData data_;
  
  uint8_t allocated_voices_[kNumVoices];
  uint8_t num_allocated_voices_;
  
  Lfo lfo_[kNumLfos];
  uint8_t lfo_step_[kNumLfos];
  uint8_t lfo_cycle_length_[kNumLfos];
  uint8_t lfo_previous_values_[kNumLfos];
  uint8_t lfo_refresh_cycle_;
  // This variable is used to get an estimate of the MIDI clock tick duration
  // expressed in 1/976 seconds (LFO refresh rate).
  uint16_t midi_clock_tick_duration_;
  
  uint8_t midi_clock_prescaler_;
  uint8_t midi_clock_counter_;

  // A part will ignore all incoming note off messages if the sustain pedal
  // is held.
  uint8_t ignore_note_off_messages_;
  NoteStack<12> pressed_keys_;
  NoteStack<7> mono_allocator_;
  VoiceAllocator poly_allocator_;
  
  uint8_t data_entry_msb_;
  uint8_t nrpn_msb_;
  uint8_t nrpn_;
  
  // Sequencer state.
  uint8_t sequencer_step_[kNumSequences];
  
  // Arpeggiator state.
  uint8_t previous_generated_note_;
  uint16_t arp_pattern_mask_;
  int8_t arp_direction_;
  int8_t arp_step_;
  int8_t arp_octave_;
  
  // Whether some settings have been changed by code.
  uint8_t flags_;
  
  // Backup copy of the "polyphony mode" parameter to reinitialize if necessary
  // all allocators when a new program is loaded.
  uint8_t polyphony_mode_;
  
  DISALLOW_COPY_AND_ASSIGN(Part);
};

}  // namespace ambika

#endif  // CONTROLLER_PART_H_
