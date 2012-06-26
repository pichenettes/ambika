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
// Parameter definitions.

#ifndef CONTROLLER_PARAMETER_DEFINITIONS_H_
#define CONTROLLER_PARAMETER_DEFINITIONS_H_

#include "avrlib/base.h"

#include "controller/resources.h"
#include "controller/controller.h"

namespace ambika {

enum Unit {
  UNIT_RAW_UINT8,
  UNIT_UINT8,
  UNIT_INDEX,
  UNIT_INT8,
  UNIT_BOOLEAN,
  UNIT_OSCILLATOR_WAVEFORM,
  UNIT_MIX_OPERATOR,
  UNIT_SUB_OSC_WAVEFORM,
  UNIT_FILTER_MODE,
  UNIT_LFO_SYNC_MODE,
  UNIT_LFO_RATE,
  UNIT_LFO_SHAPE,
  UNIT_MODULATION_SOURCE,
  UNIT_MODULATION_DESTINATION,
  UNIT_MODIFIER,
  UNIT_RAGA,
  UNIT_ARP_MODE,
  UNIT_ARP_DIRECTION,
  UNIT_POLYPHONY_MODE,
  UNIT_NOTE,
  UNIT_TEMPO,
  UNIT_CLOCK_RESOLUTION,
  UNIT_GROOVE_TEMPLATE,
  UNIT_MIDI_IN_MASK,
  UNIT_MIDI_OUT_MODE,
  UNIT_MIDI_CHANNEL,
  UNIT_LAST
};

enum ParameterLevel {
  PARAMETER_LEVEL_PATCH,
  PARAMETER_LEVEL_PART,
  PARAMETER_LEVEL_MULTI,
  PARAMETER_LEVEL_SYSTEM,
  PARAMETER_LEVEL_UI
};

struct Parameter {
  // Whether this parameter belongs to a patch, a part, or the global level.
  uint8_t level;
  
  // At which offset in the datastructure this parameter resides
  uint8_t offset;
  
  // Unit of this parameter. This is used to invoke a specific format function
  // for displaying the parameter value on screen.
  uint8_t unit;
  
  // Minimum and maximum value of this parameter.
  uint8_t min_value;
  uint8_t max_value;
  
  // For parameters grouped into banks (eg: modulation matrix):
  // - number of instances of this parameter.
  // - bytes the offset must be increased to jump to the next instance.
  // - which UI variable control the currently active parameter.
  uint8_t num_instances;
  uint8_t stride;
  uint8_t indexed_by;
  uint8_t midi_cc;
  
  // Resource id of the short and long name of the parameter
  ResourceId short_name;
  ResourceId long_name;
  ResourceId object;
  
  uint8_t Scale(uint8_t value_7bits) const;
  uint8_t Clamp(uint8_t value) const;
  uint8_t Increment(uint8_t current_value, int8_t increment) const;
  uint8_t RandomValue() const;
  
  uint8_t is_snapped(uint8_t current_value, uint8_t value_7bits) const;

  void PrintValue(uint8_t value, char* buffer, uint8_t width) const;
  void PrintName(char* buffer, uint8_t width) const;
  void PrintObject(
      uint8_t part,
      uint8_t instance,
      char* buffer,
      uint8_t width) const;
  void Print(
      uint8_t value,
      char* buffer,
      uint8_t name_width,
      uint8_t value_width) const;
  
  static void PrintNote(uint8_t note, char* buffer);
};

const uint8_t kNumParameters = 72;
typedef Parameter PROGMEM prog_Parameter;

// The parameter manager is the class who knows how to apply a parameter change
// for each specific object type.
class ParameterManager {
 public:
  ParameterManager() { }

  static void Init();
  
  static const Parameter& parameter(uint8_t index);
  
  static uint8_t ControlChangeToParameterId(uint8_t cc);
  static uint8_t AddressToParameterId(uint8_t address);
  
  static void SetValue(
      const Parameter& parameter,
      uint8_t part,
      uint8_t instance_index,
      uint8_t value,
      uint8_t user_initiated);

  static uint8_t GetValue(
      const Parameter& parameter,
      uint8_t part,
      uint8_t instance_index);

  static void Increment(
      const Parameter& parameter,
      uint8_t part,
      uint8_t instance_index,
      int8_t increment) {
    uint8_t value = GetValue(parameter, part, instance_index);
    value = parameter.Increment(value, increment);
    SetValue(parameter, part, instance_index, value, 1);
  }
  
  static void Increment(
      uint8_t parameter_index,
      uint8_t part,
      uint8_t instance_index,
      int8_t increment) {
    const Parameter& p = parameter(parameter_index);
    Increment(p, part, instance_index, increment);
  }
  
  static void Scale(
      const Parameter& parameter,
      uint8_t part,
      uint8_t instance_index,
      uint8_t value) {
    SetValue(parameter, part, instance_index, parameter.Scale(value), 1);
  }

  static void Scale(
      uint8_t parameter_index,
      uint8_t part,
      uint8_t instance_index,
      uint8_t value) {
    const Parameter& p = parameter(parameter_index);
    Scale(p, part, instance_index, value);
  }
  
  static uint8_t is_snapped(
      const Parameter& parameter,
      uint8_t part,
      uint8_t instance_index,
      uint8_t value) {
    uint8_t current_value = GetValue(parameter, part, instance_index);
    return parameter.is_snapped(current_value, value);
  }

  static uint8_t is_snapped(
      uint8_t parameter_index,
      uint8_t part,
      uint8_t instance_index,
      uint8_t value) {
    const Parameter& p = parameter(parameter_index);
    return is_snapped(p, part, instance_index, value);
  }
  
 private:
  static Parameter dummy_parameter_;
  static Parameter cached_definition_;
  static uint8_t cached_index_;
  
  DISALLOW_COPY_AND_ASSIGN(ParameterManager);
};

extern ParameterManager parameter_manager;

}  // namespace ambika

#endif  // CONTROLLER_PARAMETER_DEFINITIONS_H_
