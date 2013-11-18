// Copyright 2009 Olivier Gillet.
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
// Parameter definitions.

#include "controller/parameter.h"

#include <avr/pgmspace.h>

#include "avrlib/string.h"

#include "common/patch.h"
#include "controller/multi.h"
#include "controller/part.h"
#include "controller/system_settings.h"
#include "controller/ui.h"

namespace ambika {

static const prog_uint16_t units_definitions[UNIT_LAST] PROGMEM = {
  0,                  // UNIT_RAW_UINT8
  0,                  // UNIT_UINT8
  0,                  // UNIT_INDEX
  0,                  // UNIT_INT8
  STR_RES_OFF,        // UNIT_BOOLEAN
  STR_RES_NONE,       // UNIT_OSCILLATOR_WAVEFORM,
  STR_RES___OFF,      // UNIT_MIX_OPERATOR
  STR_RES_SQU1,       // UNIT_SUB_OSC_WAVEFORM
  STR_RES_LP,         // UNIT_FILTER_MODE
  STR_RES_FREE,       // UNIT_LFO_SYNC_MODE
  STR_RES_1_1,        // UNIT_LFO_RATE
  STR_RES_TRI,        // UNIT_LFO_SHAPE
  STR_RES_ENV1,       // UNIT_MODULATION_SOURCE
  STR_RES_PRM1,       // UNIT_MODULATION_DESTINATION
  STR_RES__OFF,       // UNIT_MODIFIER
  STR_RES_EQUAL,      // UNIT_RAGA
  STR_RES_STEP_SEQ,   // UNIT_ARP_MODE
  STR_RES_UP,         // UNIT_ARP_DIRECTION
  STR_RES_MONO,       // UNIT_POLYPHONY_MODE
  0,                  // UNIT_NOTE
  0,                  // UNIT_TEMPO
  STR_RES_1_1,        // UNIT_CLOCK_RESOLUTION
  STR_RES_SWING,      // UNIT_GROOVE_TEMPLATE
  STR_RES_____,       // UNIT_MIDI_IN_MASK
  STR_RES_THRU,       // UNIT_MIDI_OUT_MODE
};

static const prog_char note_names[] PROGMEM = " CC# DD# E FF# GG# AA# B";
static const prog_char octaves[] PROGMEM = "-0123456789";


uint8_t Parameter::Scale(uint8_t value_7bits) const {
  uint8_t scaled_value;
  if (unit == UNIT_RAW_UINT8) {
    scaled_value = value_7bits;
  } else {
    uint8_t range = max_value - min_value + 1;
    scaled_value = U8U8MulShift8(range, value_7bits << 1);
    scaled_value += min_value;
    if (unit == UNIT_TEMPO) {
      if (scaled_value >= 239) {
        scaled_value = 240;
      }
      scaled_value &= 0xfe;
    }
  }
  return scaled_value;
}

uint8_t Parameter::is_snapped(
    uint8_t current_value,
    uint8_t value_7bits) const {
  uint8_t scaled_value = Scale(value_7bits);
  int16_t delta;
  if (unit == UNIT_INT8) {
    delta = static_cast<int16_t>(static_cast<int8_t>(current_value)) - \
        static_cast<int8_t>(scaled_value);
  } else {
    delta = static_cast<int16_t>(static_cast<uint8_t>(current_value)) - \
        static_cast<uint8_t>(scaled_value);
  }
  if (delta < 0) {
    delta = -delta;
  }
  return delta <= static_cast<uint8_t>(max_value - min_value) >> 5;
}

uint8_t Parameter::Clamp(uint8_t value) const {
  if (unit == UNIT_INT8) {
    int8_t signed_value = static_cast<int8_t>(value);
    if (signed_value < static_cast<int8_t>(min_value)) {
      value = min_value;
    } else if (signed_value > static_cast<int8_t>(max_value)) {
      value = max_value;
    }
  } else {
    if (value < min_value) {
      value = min_value;
    } else if (value > max_value) {
      value = max_value;
    }
  }
  return value;
}

uint8_t Parameter::Increment(
    uint8_t current_value,
    int8_t increment) const {
  int16_t value = current_value;
  uint8_t new_value = current_value;
  if (unit == UNIT_INT8) {
    value = static_cast<int16_t>(static_cast<int8_t>(value));
    value += increment;
    if (value >= static_cast<int8_t>(min_value) &&
        value <= static_cast<int8_t>(max_value)) {
      new_value = static_cast<uint8_t>(value);
    }
  } else {
    value += increment;
    if (value >= min_value && value <= max_value) {
      new_value = static_cast<uint8_t>(value);
    }
  }
  return new_value;
}

uint8_t Parameter::RandomValue() const {
  uint8_t range = max_value - min_value + 1;
  uint8_t value = Random::GetByte();
  // Handle two special cases: min = max ; and range = 256.
  if (range == 0) {
    if (max_value == min_value) {
      return min_value;
    } else {
      return value;
    }
  }
  while (value >= range) {
    value -= range;
  }
  return value + min_value;
}

/* static */
void Parameter::PrintNote(uint8_t note, char* buffer) {
  uint8_t octave = 0;
  while (note >= 12) {
    ++octave;
    note -= 12;
  }
  *buffer++ = ResourcesManager::Lookup<char, uint8_t>(
      note_names, note << 1);
  *buffer++ = ResourcesManager::Lookup<char, uint8_t>(
      note_names, 1 + (note << 1));
  *buffer++ = ResourcesManager::Lookup<char, uint8_t>(
      octaves, octave);
  *buffer = '\0';
}

void Parameter::PrintValue(uint8_t value, char* buffer, uint8_t width) const {
  ResourceId text = ResourcesManager::Lookup<uint16_t, uint8_t>(
      units_definitions,
      unit);
  switch (unit) {
    case UNIT_INDEX:
      ++value;
      break;

    case UNIT_LFO_RATE:
      if (value >= kNumSyncedLfoRates) {
        text = 0;
        value -= kNumSyncedLfoRates;
      }
      break;

    case UNIT_MODULATION_SOURCE:
      if (width > 5) {
        text = STR_RES_ENV_1;
      }
      break;

    case UNIT_MODULATION_DESTINATION:
      if (width > 5) {
        text = STR_RES_PARAM_1;
      }
      break;
      
    case UNIT_TEMPO:
      if (value < 40) {
        text = STR_RES_EXT;
        value = 0;
      }
      break;
      
    case UNIT_NOTE:
      PrintNote(value, buffer);
      break;
      
    case UNIT_MIDI_CHANNEL:
      if (value == 0) {
        text = STR_RES_OMNI;
      }
  }
  
  if (text) {
    ResourcesManager::LoadStringResource(text + value, buffer, width);
  } else if (unit != UNIT_NOTE) {
    int16_t v = (unit == UNIT_INT8) ? static_cast<int8_t>(value) : value;
    UnsafeItoa<int16_t>(v, width, buffer);
  }
  AlignRight(buffer, width);
}

void Parameter::PrintName(char* buffer, uint8_t width) const {
  ResourceId caption = (width <= 6) ? short_name : long_name;
  ResourcesManager::LoadStringResource(caption, buffer, width);
  AlignLeft(buffer, width);
}

void Parameter::PrintObject(
    uint8_t part,
    uint8_t instance,
    char* buffer,
    uint8_t width) const {
  // Print a part number.
  if (part != 0xff) {
    *buffer++ = 'p';
    *buffer++ = 't';
    *buffer++ = ' ';
    *buffer++ = '1' + part;
    *buffer++ = ' ';
    width -= 5;
  }
  ResourcesManager::LoadStringResource(object, buffer, width);
  if (indexed_by != 0xff) {
    char digits[4];
    digits[0] = ' ';
    digits[3] = '\0';
    UnsafeItoa<int16_t>(instance + 1, 2, &digits[1]);
    strcat(buffer, digits);
  }
  AlignLeft(buffer, width);
}

void Parameter::Print(
    uint8_t value,
    char* buffer,
    uint8_t name_width,
    uint8_t value_width) const {
  PrintName(buffer, name_width);
  uint8_t start = name_width - 1;
  while (buffer[start] == ' ') {
    --start;
    ++value_width;
  }
  buffer[++start] = ' ';
  PrintValue(value, buffer + start + 1, value_width);
}


static const prog_char midi_cc_map[128] PROGMEM = {
   // 0-15
   255, 255, 255,  22, 255,  48, 255,  42,
   255,  23, 255, 255,  14,  15,   2,   3,
   // 16-31
     0,   1,   4,   5,   6,   7,   8,   9,
    10,  11,  12,  13,  18,  19,  20,  21,
   // 32-47
   255, 255, 255, 255, 255, 255, 255, 255,
   255, 255, 255, 255,  29,  30,  31,  32,
   // 48-63
    33, 255, 255, 255,  29,  30,  31, 255,
   255, 255, 255, 255,  29,  30,  31, 255,
   // 64-79
   255, 255, 255, 255,  47, 255,  27,  17,
    28,  25,  16,  26, 255, 255,  27, 255,
   // 80-95
    28,  25, 255,  26, 255, 255,  27, 255,
    28,  25, 255,  26, 255, 255,  44,  45,
   // 96-111
   255, 255, 255, 255, 255, 255,  49,  50,
    51,  52,  53,  57, 255, 255, 255, 255,
   // 112-127
   255, 255, 255, 255, 255, 255, 255, 255,
   255, 255, 255, 255, 255, 255, 255, 255
};

static const prog_char midi_nrpn_map[256] PROGMEM = {
   // 0-15
     0,   1,   2,   3,   4,   5,   6,   7,
     8,   9,  10,  11,  12,  13,  14,  15,
   // 16-31
    16,  17,  18,  19,  20,  21,  22,  23,
    25,  26,  27,  28,  31,  30, 255,  29,
   // 32-47
    25,  26,  27,  28,  31,  30, 255,  29,
    25,  26,  27,  28,  31,  30, 255,  29,
   // 48-63
    33,  32,  35,  36,  37,  35,  36,  37,
    35,  36,  37,  35,  36,  37,  35,  36,
   // 64-79
    37,  35,  36,  37,  35,  36,  37,  35,
    36,  37,  35,  36,  37,  35,  36,  37,
   // 80-95
    35,  36,  37,  35,  36,  37,  35,  36,
    37,  35,  36,  37,  39,  40,  41,  39,
   // 96-111
    40,  41,  39,  40,  41,  39,  40,  41,
   255, 255, 255, 255, 255, 255, 255, 255,
   // 112-127
   42,  43,  44,  45,  46,  47,  48,  49,
   50,  51,  52,  53,  54,  55,  56,  57,
   // 128-143
   254, 254, 254, 254, 254, 254, 254, 254,
   254, 254, 254, 254, 254, 254, 254, 254,
   // 144-159
   254, 254, 254, 254, 254, 254, 254, 254,
   254, 254, 254, 254, 254, 254, 254, 254,
   // 160-175
   254, 254, 254, 254, 254, 254, 254, 254,
   254, 254, 254, 254, 254, 254, 254, 254,
   // 176-191
   254, 254, 254, 254, 254, 254, 254, 254,
   254, 254, 254, 254, 254, 254, 254, 254,
   // 192-207
   255, 255, 255, 255, 255, 255, 255, 255,
   255, 255, 255, 255, 255, 255, 255, 255,
   // 208-223
   255, 255, 255, 255, 255, 255, 255, 255,
   255, 255, 255, 255, 255, 255, 255, 255,
   // 224-255
   255, 255, 255, 255, 255, 255, 255, 255,
   255, 255, 255, 255, 255, 255, 255, 255
};



static const prog_Parameter parameters[kNumParameters] PROGMEM = {
  // Parameters for patch editor.
  
  // Oscillators
  // 0
  { PARAMETER_LEVEL_PATCH,
    PRM_PATCH_OSC1_SHAPE,
    UNIT_OSCILLATOR_WAVEFORM, WAVEFORM_NONE, WAVEFORM_LAST - 1,
    1, 0, 0xff, 16,
    STR_RES_WAVEFORM, STR_RES_WAVEFORM, STR_RES_OSCILLATOR_1 },
  
  // 1
  { PARAMETER_LEVEL_PATCH,
    PRM_PATCH_OSC1_PWM,
    UNIT_RAW_UINT8, 0, 127,
    1, 0, 0xff, 17,
    STR_RES_PARAMETER, STR_RES_PARAMETER, STR_RES_OSCILLATOR_1 },
  
  // 2
  { PARAMETER_LEVEL_PATCH,
    PRM_PATCH_OSC1_RANGE,
    UNIT_INT8, -24, 24,
    1, 0, 0xff, 14,
    STR_RES_RANGE, STR_RES_RANGE, STR_RES_OSCILLATOR_1 },

  // 3
  { PARAMETER_LEVEL_PATCH,
    PRM_PATCH_OSC1_DETUNE,
    UNIT_INT8, -64, 64,
    1, 0, 0xff, 15,
    STR_RES_TUNE, STR_RES_TUNE, STR_RES_OSCILLATOR_1 },
  
  // 4
  { PARAMETER_LEVEL_PATCH,
    PRM_PATCH_OSC2_SHAPE,
    UNIT_OSCILLATOR_WAVEFORM, WAVEFORM_NONE, WAVEFORM_LAST - 1,
    1, 0, 0xff, 18,
    STR_RES_WAVEFORM, STR_RES_WAVEFORM, STR_RES_OSCILLATOR_2 },
  
  // 5
  { PARAMETER_LEVEL_PATCH,
    PRM_PATCH_OSC2_PWM,
    UNIT_RAW_UINT8, 0, 127,
    1, 0, 0xff, 19,
    STR_RES_PARAMETER, STR_RES_PARAMETER, STR_RES_OSCILLATOR_2 },
  
  // 6
  { PARAMETER_LEVEL_PATCH,
    PRM_PATCH_OSC2_RANGE,
    UNIT_INT8, -24, 24,
    1, 0, 0xff, 20,
    STR_RES_RANGE, STR_RES_RANGE, STR_RES_OSCILLATOR_2 },

  // 7
  { PARAMETER_LEVEL_PATCH,
    PRM_PATCH_OSC2_DETUNE,
    UNIT_INT8, -64, 64,
    1, 0, 0xff, 21,
    STR_RES_TUNE, STR_RES_TUNE, STR_RES_OSCILLATOR_2 },
  
  // Mixer
  // 8
  { PARAMETER_LEVEL_PATCH,
    PRM_PATCH_MIX_BALANCE,
    UNIT_UINT8, 0, 63,
    1, 0, 0xff, 22,
    STR_RES_MIX, STR_RES_OSC_MIX, STR_RES_MIXER },
  
  // 9
  { PARAMETER_LEVEL_PATCH,
    PRM_PATCH_MIX_OPERATOR,
    UNIT_MIX_OPERATOR, 0, OP_LAST - 1,
    1, 0, 0xff, 23,
    STR_RES_XMOD, STR_RES_CROSSMOD_, STR_RES_MIXER },
  
  // 10
  { PARAMETER_LEVEL_PATCH,
    PRM_PATCH_MIX_PARAMETER,
    UNIT_UINT8, 0, 63,
    1, 0, 0xff, 24,
    STR_RES_AMNT, STR_RES_AMOUNT, STR_RES_MIXER },
  
  // 11
  { PARAMETER_LEVEL_PATCH,
    PRM_PATCH_MIX_SUB_SHAPE,
    UNIT_SUB_OSC_WAVEFORM, WAVEFORM_SUB_OSC_SQUARE_1, WAVEFORM_SUB_OSC_LAST - 1,
    1, 0, 0xff, 25,
    STR_RES_WAVEFORM, STR_RES_WAVEFORM, STR_RES_MIXER },
  
  // 12
  { PARAMETER_LEVEL_PATCH,
    PRM_PATCH_MIX_SUB_LEVEL,
    UNIT_UINT8, 0, 63,
    1, 0, 0xff, 26,
    STR_RES_SUB_OSC_, STR_RES_SUB_OSC_, STR_RES_MIXER },
  
  // 13
  { PARAMETER_LEVEL_PATCH,
    PRM_PATCH_MIX_NOISE_LEVEL,
    UNIT_UINT8, 0, 63,
    1, 0, 0xff, 27,
    STR_RES_NOISE, STR_RES_NOISE, STR_RES_MIXER },
  
  // 14
  { PARAMETER_LEVEL_PATCH,
    PRM_PATCH_MIX_FUZZ,
    UNIT_UINT8, 0, 63,
    1, 0, 0xff, 12,
    STR_RES_FUZZ, STR_RES_FUZZ, STR_RES_MIXER },
  
  // 15
  { PARAMETER_LEVEL_PATCH,
    PRM_PATCH_MIX_CRUSH,
    UNIT_UINT8, 0, 31,
    1, 0, 0xff, 13,
    STR_RES_CRSH, STR_RES_CRUSH, STR_RES_MIXER },
  
  // 16
  { PARAMETER_LEVEL_PATCH,
    PRM_PATCH_FILTER1_CUTOFF,
    UNIT_RAW_UINT8, 0, 127,
    1, 0, 0xff, 74,
    STR_RES_FREQUENCY, STR_RES_FREQUENCY, STR_RES_FILTER_1 },
  
  // 17
  { PARAMETER_LEVEL_PATCH,
    PRM_PATCH_FILTER1_RESONANCE,
    UNIT_UINT8, 0, 63,
    1, 0, 0xff, 71,
    STR_RES_RESONANCE, STR_RES_RESONANCE, STR_RES_FILTER_1 },
  
  // 18
  { PARAMETER_LEVEL_PATCH,
    PRM_PATCH_FILTER1_MODE,
    UNIT_FILTER_MODE, FILTER_MODE_LP, FILTER_MODE_HP,
    1, 0, 0xff, 28,
    STR_RES_MODE, STR_RES_MODE, STR_RES_FILTER_1 },

  // 19
  { PARAMETER_LEVEL_PATCH,
    PRM_PATCH_FILTER2_CUTOFF,
    UNIT_RAW_UINT8, 0, 127,
    1, 0, 0xff, 29,
    STR_RES_FREQUENCY, STR_RES_FREQUENCY, STR_RES_FILTER_2 },
  
  // 20
  { PARAMETER_LEVEL_PATCH,
    PRM_PATCH_FILTER2_RESONANCE,
    UNIT_UINT8, 0, 63,
    1, 0, 0xff, 30,
    STR_RES_RESONANCE, STR_RES_RESONANCE, STR_RES_FILTER_2 },
  
  // 21
  { PARAMETER_LEVEL_PATCH,
    PRM_PATCH_FILTER2_MODE,
    UNIT_FILTER_MODE, FILTER_MODE_LP, FILTER_MODE_HP,
    1, 0, 0xff, 31,
    STR_RES_MODE, STR_RES_MODE, STR_RES_FILTER_2 },
  
  // 22
  { PARAMETER_LEVEL_PATCH,
    PRM_PATCH_FILTER1_ENV,
    UNIT_UINT8, 0, 63,
    1, 0, 0xff, 3,
    STR_RES_ENV2TVCF, STR_RES_ENV2TVCF, STR_RES_FILTER_1 },
  
  // 23
  { PARAMETER_LEVEL_PATCH,
    PRM_PATCH_FILTER1_LFO,
    UNIT_UINT8, 0, 63,
    1, 0, 0xff, 9,
    STR_RES_LFO2TVCF, STR_RES_LFO2TVCF, STR_RES_FILTER_1 },
  
  // 24
  { PARAMETER_LEVEL_UI,
    PRM_UI_ACTIVE_ENV_LFO,
    UNIT_INDEX, 0, 2,
    1, 0, 0xff, 0xff,
    STR_RES_LFO_EG, STR_RES_LFO_EG, 0 },
  
  // 25
  { PARAMETER_LEVEL_PATCH,
    PRM_PATCH_ENV_ATTACK,
    UNIT_RAW_UINT8, 0, 127,
    3, 8, PRM_UI_ACTIVE_ENV_LFO, 73,
    STR_RES_ATTK, STR_RES_ATTACK, STR_RES_ENVELOPE },
  
  // 26
  { PARAMETER_LEVEL_PATCH,
    PRM_PATCH_ENV_DECAY,
    UNIT_RAW_UINT8, 0, 127,
    3, 8, PRM_UI_ACTIVE_ENV_LFO, 75,
    STR_RES_DECAY, STR_RES_DECAY, STR_RES_ENVELOPE },

  // 27
  { PARAMETER_LEVEL_PATCH,
    PRM_PATCH_ENV_SUSTAIN,
    UNIT_RAW_UINT8, 0, 127,
    3, 8, PRM_UI_ACTIVE_ENV_LFO, 70,
    STR_RES_SUSTAIN, STR_RES_SUSTAIN, STR_RES_ENVELOPE },
  
  // 28
  { PARAMETER_LEVEL_PATCH,
    PRM_PATCH_ENV_RELEASE,
    UNIT_RAW_UINT8, 0, 127,
    3, 8, PRM_UI_ACTIVE_ENV_LFO, 72,
    STR_RES_RELEASE, STR_RES_RELEASE, STR_RES_ENVELOPE },
  
  // 29
  { PARAMETER_LEVEL_PATCH,
    PRM_PATCH_LFO_SYNC,
    UNIT_LFO_SYNC_MODE, 0, LFO_SYNC_MODE_LAST - 1,
    3, 8, PRM_UI_ACTIVE_ENV_LFO, 44,
    STR_RES_TRIGGER, STR_RES_TRIGGER, STR_RES_LFO },
  
  // 30
  { PARAMETER_LEVEL_PATCH,
    PRM_PATCH_LFO_RATE,
    UNIT_LFO_RATE, 0, kNumSyncedLfoRates + 127,
    3, 8, PRM_UI_ACTIVE_ENV_LFO, 45,
    STR_RES_RATE, STR_RES_RATE, STR_RES_LFO },
  
  // 31
  { PARAMETER_LEVEL_PATCH,
    PRM_PATCH_LFO_SHAPE,
    UNIT_LFO_SHAPE, 0, LFO_WAVEFORM_LAST - 1,
    3, 8, PRM_UI_ACTIVE_ENV_LFO, 46,
    STR_RES_WAVEFORM, STR_RES_WAVEFORM, STR_RES_LFO },
  
  // 32
  { PARAMETER_LEVEL_PATCH,
    PRM_PATCH_VOICE_LFO_RATE,
    UNIT_RAW_UINT8, 0, 127,
    1, 0, 0xff, 47,
    STR_RES_RATE, STR_RES_RATE, STR_RES_VOICE_LFO },

  // 33
  { PARAMETER_LEVEL_PATCH,
    PRM_PATCH_VOICE_LFO_SHAPE,
    UNIT_LFO_SHAPE, 0, LFO_WAVEFORM_RAMP,
    1, 0, 0xff, 48,
    STR_RES_WAVEFORM, STR_RES_WAVEFORM, STR_RES_VOICE_LFO },

  // 34
  { PARAMETER_LEVEL_UI,
    PRM_UI_ACTIVE_MODULATION,
    UNIT_INDEX, 0, 13,
    1, 0, 0xff, 0xff,
    STR_RES_MODUL_, STR_RES_MODULATION, 0 },

  // 35
  { PARAMETER_LEVEL_PATCH,
    PRM_PATCH_MOD_SOURCE,
    UNIT_MODULATION_SOURCE, 0, MOD_SRC_CONSTANT_256,
    14, 3, PRM_UI_ACTIVE_MODULATION, 0xff,
    STR_RES_SRCE, STR_RES_SOURCE, STR_RES_MODULATION },
  
  // 36
  { PARAMETER_LEVEL_PATCH,
    PRM_PATCH_MOD_DESTINATION,
    UNIT_MODULATION_DESTINATION, 0, MOD_DST_LAST - 1,
    14, 3, PRM_UI_ACTIVE_MODULATION, 0xff,
    STR_RES_DESTINATION, STR_RES_DESTINATION, STR_RES_MODULATION },
  
  // 37
  { PARAMETER_LEVEL_PATCH,
    PRM_PATCH_MOD_AMOUNT,
    UNIT_INT8, -63, 63,
    14, 3, PRM_UI_ACTIVE_MODULATION, 0xff,
    STR_RES_AMNT, STR_RES_AMOUNT, STR_RES_MODULATION },
  
  // 38
  { PARAMETER_LEVEL_UI,
    PRM_UI_ACTIVE_MODIFIER,
    UNIT_INDEX, 0, 3,
    1, 0, 0xff, 0xff,
    STR_RES_MODIF_, STR_RES_MODIFIER, 0 },
  
  // 39
  { PARAMETER_LEVEL_PATCH,
    PRM_PATCH_MOD_OPERAND1,
    UNIT_MODULATION_SOURCE, 0, MOD_SRC_LAST - 1,
    4, 3, PRM_UI_ACTIVE_MODIFIER, 0xff,
    STR_RES_IN1, STR_RES_IN1, STR_RES_MODIFIER },

  // 40
  { PARAMETER_LEVEL_PATCH,
    PRM_PATCH_MOD_OPERAND2,
    UNIT_MODULATION_SOURCE, 0, MOD_SRC_LAST - 1,
    4, 3, PRM_UI_ACTIVE_MODIFIER, 0xff,
    STR_RES_IN2, STR_RES_IN2, STR_RES_MODIFIER },
  
  // 41
  { PARAMETER_LEVEL_PATCH,
    PRM_PATCH_MOD_OPERATOR,
    UNIT_MODIFIER, 0, MODIFIER_LAST - 1,
    4, 3, PRM_UI_ACTIVE_MODIFIER, 0xff,
    STR_RES_OPERATOR, STR_RES_OPERATOR, STR_RES_MODIFIER },
  
  // Parameters for part editor
  // 42
  { PARAMETER_LEVEL_PART,
    PRM_PART_VOLUME,
    UNIT_RAW_UINT8, 0, 127,
    1, 0, 0xff, 7,
    STR_RES_VOLUME, STR_RES_VOLUME, STR_RES_PART },
  
  // 43
  { PARAMETER_LEVEL_PART,
    PRM_PART_OCTAVE,
    UNIT_INT8, -2, 2,
    1, 0, 0xff, 0xff,
    STR_RES_OCTV, STR_RES_OCTAVE, STR_RES_PART },
  
  // 44
  { PARAMETER_LEVEL_PART,
    PRM_PART_TUNING,
    UNIT_INT8, -127, 127,
    1, 0, 0xff, 94,
    STR_RES_TUNE, STR_RES_TUNE, STR_RES_PART },
  
  // 45
  { PARAMETER_LEVEL_PART,
    PRM_PART_TUNING_SPREAD,
    UNIT_UINT8, 0, 40,
    1, 0, 0xff, 95,
    STR_RES_SPRD, STR_RES_SPREAD, STR_RES_PART },
  
  // 46
  { PARAMETER_LEVEL_PART,
    PRM_PART_RAGA,
    UNIT_RAGA, 0, 31,
    1, 0, 0xff, 0xff,
    STR_RES_RAGA, STR_RES_RAGA, STR_RES_PART },
  
  // 47
  { PARAMETER_LEVEL_PART,
    PRM_PART_LEGATO,
    UNIT_BOOLEAN, 0, 1,
    1, 0, 0xff, 68,
    STR_RES_LEGATO, STR_RES_LEGATO, STR_RES_PART },
  
  // 48
  { PARAMETER_LEVEL_PART,
    PRM_PART_PORTAMENTO_TIME,
    UNIT_UINT8, 0, 63,
    1, 0, 0xff, 5,
    STR_RES_PORTAMENTO, STR_RES_PORTAMENTO, STR_RES_PART },
  
  // 49
  { PARAMETER_LEVEL_PART,
    PRM_PART_ARP_MODE,
    UNIT_ARP_MODE, 0, ARP_SEQUENCER_MODE_LAST - 1,
    1, 0, 0xff, 102,
    STR_RES_A_SQ, STR_RES_ARP_SEQ, STR_RES_PART },
  
  // 50
  { PARAMETER_LEVEL_PART,
    PRM_PART_ARP_DIRECTION,
    UNIT_ARP_DIRECTION, ARPEGGIO_DIRECTION_UP, ARPEGGIO_DIRECTION_LAST - 1,
    1, 0, 0xff, 103,
    STR_RES_DIRECTION, STR_RES_DIRECTION, STR_RES_ARPEGGIO },
  
  // 51
  { PARAMETER_LEVEL_PART,
    PRM_PART_ARP_OCTAVE,
    UNIT_INT8, 1, 4,
    1, 0, 0xff, 104,
    STR_RES_RANGE, STR_RES_RANGE, STR_RES_ARPEGGIO },
  
  // 52
  { PARAMETER_LEVEL_PART,
    PRM_PART_ARP_PATTERN,
    UNIT_INDEX, 0, kNumArpeggiatorPatterns - 1,
    1, 0, 0xff, 105,
    STR_RES_PATTERN, STR_RES_PATTERN, STR_RES_ARPEGGIO },
  
  // 53
  { PARAMETER_LEVEL_PART,
    PRM_PART_ARP_RESOLUTION,
    UNIT_CLOCK_RESOLUTION, 0, 14,
    1, 0, 0xff, 106,
    STR_RES_GRID, STR_RES_GRID, STR_RES_ARPEGGIO },
    
  // 54
  { PARAMETER_LEVEL_PART,
    PRM_PART_SEQUENCE_LENGTH_1,
    UNIT_UINT8, 1, 32,
    1, 0, 0xff, 0xff,
    STR_RES_LEN1, STR_RES_SEQ1_LEN, STR_RES_SEQUENCER },

  // 55
  { PARAMETER_LEVEL_PART,
    PRM_PART_SEQUENCE_LENGTH_2,
    UNIT_UINT8, 1, 32,
    1, 0, 0xff, 0xff,
    STR_RES_LEN2, STR_RES_SEQ2_LEN, STR_RES_SEQUENCER },

  // 56
  { PARAMETER_LEVEL_PART,
    PRM_PART_SEQUENCE_LENGTH_3,
    UNIT_UINT8, 1, 32,
    1, 0, 0xff, 0xff,
    STR_RES_LENP, STR_RES_PATT_LEN, STR_RES_SEQUENCER },
  
  // 57
  { PARAMETER_LEVEL_PART,
    PRM_PART_POLYPHONY_MODE,
    UNIT_POLYPHONY_MODE, 0, 3,
    1, 0, 0xff, 107,
    STR_RES_MODE, STR_RES_MODE, STR_RES_PART },
  
  // 58
  { PARAMETER_LEVEL_UI,
    PRM_UI_ACTIVE_PART,
    UNIT_INDEX, 0, 5,
    1, 0, 0xff, 0xff,
    STR_RES_PART, STR_RES_PART, 0 },
  
  // 59
  { PARAMETER_LEVEL_MULTI,
    PRM_MULTI_MIDI_CHANNEL,
    UNIT_MIDI_CHANNEL, 0, 16,
    6, 4, PRM_UI_ACTIVE_PART, 0xff,
    STR_RES_CHANNEL, STR_RES_CHANNEL, STR_RES_PART },
  
  // 60
  { PARAMETER_LEVEL_MULTI,
    PRM_MULTI_KEYRANGE_LOW,
    UNIT_NOTE, 0, 127,
    6, 4, PRM_UI_ACTIVE_PART, 0xff,
    STR_RES_LOW, STR_RES_LOW, STR_RES_PART },
  
  // 61
  { PARAMETER_LEVEL_MULTI,
    PRM_MULTI_KEYRANGE_HIGH,
    UNIT_NOTE, 0, 127,
    6, 4, PRM_UI_ACTIVE_PART, 0xff,
    STR_RES_HIGH, STR_RES_HIGH, STR_RES_PART },
  
  // 62
  { PARAMETER_LEVEL_MULTI,
    PRM_MULTI_CLOCK_BPM,
    UNIT_TEMPO, 39, 240,
    1, 0, 0xff, 0xff,
    STR_RES_BPM, STR_RES_BPM, STR_RES_CLOCK },
  
  // 63
  { PARAMETER_LEVEL_MULTI,
    PRM_MULTI_CLOCK_GROOVE_TEMPLATE,
    UNIT_GROOVE_TEMPLATE, 0, STR_RES_MONKEY - STR_RES_SWING,
    1, 0, 0xff, 0xff,
    STR_RES_GROOVE, STR_RES_GROOVE, STR_RES_CLOCK },
  
  // 64
  { PARAMETER_LEVEL_MULTI,
    PRM_MULTI_CLOCK_GROOVE_AMOUNT,
    UNIT_RAW_UINT8, 0, 127,
    1, 0, 0xff, 0xff,
    STR_RES_AMNT, STR_RES_AMOUNT, STR_RES_CLOCK },

  // 65
  { PARAMETER_LEVEL_MULTI,
    PRM_MULTI_CLOCK_LATCH,
    UNIT_UINT8, 0, 8,
    1, 0, 0xff, 0xff,
    STR_RES_LTCH, STR_RES_LATCH, STR_RES_CLOCK },

  // 66
  { PARAMETER_LEVEL_SYSTEM,
    PRM_SYSTEM_MIDI_IN_MASK,
    UNIT_MIDI_IN_MASK, 0, 15,
    1, 0, 0xff, 0xff,
    STR_RES_INPT_FILTER, STR_RES_INPT_FILTER, STR_RES_MIDI },
  
  // 67
  { PARAMETER_LEVEL_SYSTEM,
    PRM_SYSTEM_MIDI_OUT_MODE,
    UNIT_MIDI_OUT_MODE, MIDI_OUT_THRU, MIDI_OUT_FULL,
    1, 0, 0xff, 0xff,
    STR_RES_OUTP_MODE, STR_RES_OUTP_MODE, STR_RES_MIDI },
  
  // 68
  { PARAMETER_LEVEL_SYSTEM,
    PRM_SYSTEM_SHOW_HELP,
    UNIT_BOOLEAN, 0, 1,
    1, 0, 0xff, 0xff,
    STR_RES_HELP, STR_RES_HELP, STR_RES_SYSTEM },
  
  // 69
  { PARAMETER_LEVEL_SYSTEM,
    PRM_SYSTEM_SNAP,
    UNIT_BOOLEAN, 0, 1,
    1, 0, 0xff, 0xff,
    STR_RES_SNAP, STR_RES_SNAP, STR_RES_SYSTEM },
    
  // 70
  { PARAMETER_LEVEL_SYSTEM,
    PRM_SYSTEM_AUTOBACKUP,
    UNIT_BOOLEAN, 0, 1,
    1, 0, 0xff, 0xff,
    STR_RES_AUTO_BACKUP, STR_RES_AUTO_BACKUP, STR_RES_SYSTEM },
  
  // 71  
  { PARAMETER_LEVEL_SYSTEM,
    PRM_SYSTEM_VOICECARD_LEDS,
    UNIT_BOOLEAN, 0, 1,
    1, 0, 0xff, 0xff,
    STR_RES_LEDS, STR_RES_CARD_LEDS, STR_RES_SYSTEM },
  
  // 71 2
  { PARAMETER_LEVEL_SYSTEM,
    PRM_SYSTEM_VOICECARD_SWAP_LEDS_COLORS,
    UNIT_BOOLEAN, 0, 1,
    1, 0, 0xff, 0xff,
    STR_RES_SWAP_COLORS, STR_RES_SWAP_COLORS, STR_RES_SYSTEM },
};

/* static */
Parameter ParameterManager::cached_definition_;

/* static */
Parameter ParameterManager::dummy_parameter_ = {
  PARAMETER_LEVEL_PART, 0, UNIT_UINT8, 0, 255, 0, 0, 0, 0, 0, 0, 0
};

/* static */
uint8_t ParameterManager::cached_index_ = 0xff;

/* static */
void ParameterManager::Init() {
}

/* static */
const Parameter& ParameterManager::parameter(
    uint8_t index) {
  if (index == 0xfe) {
    return dummy_parameter_;
  }
  if (index != cached_index_) {
    ResourcesManager::Load(
        parameters,
        index,
        &cached_definition_);
    cached_index_ = index;
  }
  return cached_definition_;
}

/* static */
uint8_t ParameterManager::ControlChangeToParameterId(uint8_t cc) {
  return ResourcesManager::Lookup<uint8_t, uint8_t>(midi_cc_map, cc);
}

/* static */
uint8_t ParameterManager::AddressToParameterId(uint8_t address) {
  return ResourcesManager::Lookup<uint8_t, uint8_t>(midi_nrpn_map, address);
}

/* static */
void ParameterManager::SetValue(
    const Parameter& parameter,
    uint8_t part,
    uint8_t instance_index,
    uint8_t value,
    uint8_t user_initiated) {
  uint8_t address = parameter.offset + parameter.stride * instance_index;
  if (parameter.level <= PARAMETER_LEVEL_PART) {
    multi.mutable_part(part)->SetValue(address, value, user_initiated);
  } else if (parameter.level == PARAMETER_LEVEL_MULTI) {
    multi.SetValue(address, value);
  } else if (parameter.level == PARAMETER_LEVEL_SYSTEM) {
    uint8_t* bytes = static_cast<uint8_t*>(
        static_cast<void*>(system_settings.mutable_data()));
    bytes[address] = value;
  } else {
    uint8_t* bytes = static_cast<uint8_t*>(
        static_cast<void*>(ui.mutable_state()));
    bytes[address] = value;
  }
}

/* static */
uint8_t ParameterManager::GetValue(
    const Parameter& parameter,
    uint8_t part,
    uint8_t instance_index) {
  uint8_t address = parameter.offset + parameter.stride * instance_index;
  uint8_t value = 0;
  if (parameter.level <= PARAMETER_LEVEL_PART) {
    value = multi.part(part).GetValue(address);
  } else if (parameter.level == PARAMETER_LEVEL_MULTI) {
    value = multi.GetValue(address);
  } else if (parameter.level == PARAMETER_LEVEL_SYSTEM) {
    uint8_t* bytes = static_cast<uint8_t*>(
        static_cast<void*>(system_settings.mutable_data()));
    value = bytes[address];
  } else {
    return ui.GetValue(address);
  }
  return value;
}

/* extern */
ParameterManager parameter_manager;

}  // namespace ambika
