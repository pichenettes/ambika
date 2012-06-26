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

#ifndef VOICECARD_VOICE_H_
#define VOICECARD_VOICE_H_

#include "voicecard/voicecard.h"

#include "common/lfo.h"
#include "common/patch.h"

#include "voicecard/envelope.h"

namespace ambika {

// Used for MIDI -> oscillator increment conversion.
static const int16_t kLowestNote = 0 * 128;
static const int16_t kHighestNote = 120 * 128;
static const int16_t kOctave = 12 * 128;
static const int16_t kPitchTableStart = 116 * 128;

// This mirrors the beginning of the Part data structure in the controller.
struct Part {
  uint8_t volume;
  uint8_t padding[4];
  uint8_t legato;
  uint8_t portamento_time;
};

class Voice {
 public:
  Voice() { }
  static void Init();

  // Called whenever a new note is played, manually or through the arpeggiator.
  static void Trigger(uint16_t note, uint8_t velocity, uint8_t legato);

  // Move this voice to the release stage.
  static void Release();

  // Move this voice to the release stage.
  static void Kill() { TriggerEnvelope(DEAD); }

  static void ProcessBlock();

  // Called whenever a write to the CV analog outputs has to be made.
  static inline uint8_t cutoff()  {
    return modulation_destinations_[MOD_DST_FILTER_CUTOFF];
  }
  static inline uint8_t vca()  {
    return modulation_destinations_[MOD_DST_VCA];
  }
  static inline uint8_t crush()  {
    return modulation_destinations_[MOD_DST_MIX_CRUSH];
  }
  static inline uint8_t resonance()  {
    return modulation_destinations_[MOD_DST_FILTER_RESONANCE];
  }
  static inline uint8_t modulation_source(uint8_t i) {
    return modulation_sources_[i];
  }
  static uint8_t modulation_destination(uint8_t i) {
    return modulation_destinations_[i];
  }
  
  static inline void set_modulation_source(uint8_t i, uint8_t value) {
    modulation_sources_[i] = value;
  }
  
  static void set_patch_data(uint8_t address, uint8_t value);
  static void set_part_data(uint8_t address, uint8_t value) {
    part_data_[address + 1] = value;
  }
  
  static uint8_t* mutable_patch_data() {
    return &patch_data_[1];
  }
  
  static const Patch& patch() { return patch_; }

  static Envelope* mutable_envelope(uint8_t i) { return &envelope_[i]; }
  static void TriggerEnvelope(uint8_t stage);
  static void TriggerEnvelope(uint8_t index, uint8_t stage);
  
  static void ResetAllControllers();

 private:
  static inline void LoadSources() __attribute__((always_inline));
  static inline void ProcessModulationMatrix() __attribute__((always_inline));
  static inline void UpdateDestinations() __attribute__((always_inline));
  static inline void RenderOscillators() __attribute__((always_inline));

  static uint8_t patch_data_[1];
  static Patch patch_;
  static uint8_t part_data_[1];
  static Part part_;
  
  // Envelope generators.
  static Envelope envelope_[kNumEnvelopes];
  static uint8_t gate_;
  static Lfo voice_lfo_;
  static uint8_t modulation_sources_[kNumModulationSources];
  static int8_t modulation_destinations_[kNumModulationDestinations];
  static int16_t dst_[kNumModulationDestinations];

  // Counters/phases for the pitch envelope generator (portamento).
  // Pitches are stored on 14 bits, the 7 highest bits are the MIDI note value,
  // the 7 lowest bits are used for fine-tuning.
  static int16_t pitch_increment_;
  static int16_t pitch_target_;
  static int16_t pitch_value_;
  
  static uint8_t buffer_[kAudioBlockSize];
  static uint8_t osc2_buffer_[kAudioBlockSize];
  static uint8_t sync_state_[kAudioBlockSize];
  static uint8_t no_sync_[kAudioBlockSize];
  static uint8_t dummy_sync_state_[kAudioBlockSize];

  DISALLOW_COPY_AND_ASSIGN(Voice);
};

extern Voice voice;

}  // namespace ambika

#endif  // VOICECARD_VOICE_H_
