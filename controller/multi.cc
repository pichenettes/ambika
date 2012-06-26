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

#include "controller/midi_dispatcher.h"
#include "controller/multi.h"

#include "controller/resources.h"

namespace ambika {

/* extern */
Multi multi;

/* <static> */
MultiData Multi::data_;
Part Multi::parts_[kNumParts];
uint16_t Multi::clock_counter_ = 0;
uint16_t Multi::lfo_refresh_counter_ = 0;
uint8_t Multi::lfo_refresh_cycle_ = 0;
volatile uint8_t Multi::num_clock_events_;
uint16_t Multi::tick_duration_;
uint8_t Multi::tick_count_;
uint8_t Multi::step_count_;
uint8_t Multi::running_;
uint8_t Multi::idle_ticks_;
uint16_t Multi::tick_duration_table_[kNumStepsInGroovePattern];
uint8_t Multi::flags_;
/* </static> */

static const prog_MultiData init_settings PROGMEM = {
  // Parts mappings.
  1, 0, 127, 0x15,
  2, 0, 127, 0x2a,
  3, 0, 127, 0,
  4, 0, 127, 0,
  5, 0, 127, 0,
  6, 0, 127, 0,
  
  // Clock.
  120, 0, 0, 4,
  
  // Performance page assignments.
  0, 1, 0,
  0, 16, 0,
  1, 1, 0,
  1, 16, 0,
  0, 22, 0,
  0, 42, 0,
  1, 22, 0,
  1, 42, 0,
  
  // Padding.
  0, 0, 0, 0,
};

/* static */
void Multi::Init(bool force_reset) {
  for (uint8_t i = 0; i < kNumParts; ++i) {
    parts_[i].Init();
  }
  // Force a reset to factory settings.
  if (force_reset) {
    InitSettings(INITIALIZATION_DEFAULT);
    Storage::WriteMultiToEeprom();
  } else {
    if (!Storage::LoadMultiFromEeprom()) {
      InitSettings(INITIALIZATION_DEFAULT);
      Storage::WriteMultiToEeprom();
    } else {
      Touch();
    }
  }
  running_ = 0;
}

/* static */
void Multi::InitSettings(InitializationMode mode) {
  ResourcesManager::Load(&init_settings, 0, &data_);
  for (uint8_t i = 0; i < kNumParts; ++i) {
    parts_[i].InitSettings(mode);
  }
  Touch();
}

/* static */
uint8_t Multi::SolveAllocationConflicts(uint8_t constraint) {
  uint8_t available_voices = 0xff;
  for (uint8_t i = 0; i < kNumParts; ++i) {
    if (i != constraint) {
      data_.part_mapping_[i].voice_allocation &= available_voices;
      available_voices &= ~data_.part_mapping_[i].voice_allocation;
    }
  }
  return available_voices;
}

/* static */
void Multi::AssignVoicesToParts() {
  for (uint8_t i = 0; i < kNumParts; ++i) {
    parts_[i].AssignVoices(data_.part_mapping_[i].voice_allocation);
  }
}

/* static */
void Multi::Touch() {
  ComputeInternalClockOverflowsTable();
  SolveAllocationConflicts(-1);
  AssignVoicesToParts();
  flags_ = FLAG_HAS_CHANGE;
}

const int32_t kTempoFactor = (4 * kSampleRateNum * 60L / 24L / kSampleRateDen);

/* static */
void Multi::ComputeInternalClockOverflowsTable() {
  STATIC_ASSERT(kTempoFactor == 392156L);

  int32_t rounding = 2 * static_cast<int32_t>(data_.clock_bpm);
  int32_t denominator = 4 * static_cast<int32_t>(data_.clock_bpm);
  int16_t base_tick_duration = (kTempoFactor + rounding) / denominator;
  for (uint8_t i = 0; i < kNumStepsInGroovePattern; ++i) {
    int32_t swing_direction = ResourcesManager::Lookup<int16_t, uint8_t>(
        LUT_RES_GROOVE_SWING + data_.clock_groove_template, i);
    swing_direction *= base_tick_duration;
    swing_direction *= data_.clock_groove_amount;
    int16_t swing = swing_direction >> 16;
    tick_duration_table_[i] = base_tick_duration + swing;
  }
  tick_duration_ = tick_duration_table_[0];
}

/* static */
void Multi::Clock() {
  // This is used by the internal clock, and to get a global pulse for the 
  // incoming clock.
  ++tick_count_;
  if (tick_count_ == kNumTicksPerStep) {
    tick_count_ = 0;
    ++step_count_;
    if (step_count_ == kNumStepsInGroovePattern) {
      step_count_ = 0;
    }
    tick_duration_ = tick_duration_table_[step_count_];
  }
  
  if (running_)  {
    // Advance the clock of all parts, and check if some of them are idle.
    midi_dispatcher.OnClock();
    uint8_t idle = 1;
    for (uint8_t i = 0; i < kNumParts; ++i) {
      parts_[i].Clock();
      if (parts_[i].num_pressed_keys() > 0) {
        idle = 0;
      }
    }
    // No key is being pressed on any part. It looks like we are counting beats
    // for nothing...
    if (internal_clock()) {
      if (idle) {
        ++idle_ticks_;
      } else {
        idle_ticks_ = 0;
      }
      if (idle_ticks_ > U8U8Mul(data_.clock_release, 24)) {
        Stop();
      }
    }
  }
}

/* static */
void Multi::Start() {
  midi_dispatcher.OnStart();
  tick_count_ = 0;
  step_count_ = 0;
  idle_ticks_ = 0;
  for (uint8_t i = 0; i < kNumParts; ++i) {
    parts_[i].Start();
  }
  tick_duration_ = tick_duration_table_[0];
  running_ = 1;
}

/* static */
void Multi::Stop() {
  midi_dispatcher.OnStop();
  for (uint8_t i = 0; i < kNumParts; ++i) {
    parts_[i].Stop();
  }
  running_ = 0;
}

/* static */
void Multi::UpdateClocks() {
  while (lfo_refresh_counter_ >= kControlRate) {
    ++lfo_refresh_cycle_;
    lfo_refresh_counter_ -= kControlRate;
    for (uint8_t i = 0; i < kNumParts; ++i) {
      parts_[i].UpdateLfos(lfo_refresh_cycle_ & 1);
    }
  }
  
  // Process ticks generated by the ISR-based clock.
  if (internal_clock()) {
    while (num_clock_events_) {
      Clock();
      --num_clock_events_;
    }
  } else {
    num_clock_events_ = 0;
  }
}

/* static */
void Multi::SetValue(uint8_t address, uint8_t value) {
  uint8_t* bytes = static_cast<uint8_t*>(static_cast<void*>(&data_));
  if (bytes[address] != value) {
    bytes[address] = value;
    flags_ |= FLAG_HAS_USER_CHANGE;
    if (address < PRM_MULTI_CLOCK_BPM) {
      if ((address & 3) == 3) {
        Touch();
      }
    } else if (address <= PRM_MULTI_CLOCK_GROOVE_AMOUNT) {
      ComputeInternalClockOverflowsTable();
    }
  }
}

}  // namespace ambika
