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
//
// -----------------------------------------------------------------------------
//
// Instance of the LedArray class, configured for the mother board.

#ifndef CONTROLLER_LEDS_H_
#define CONTROLLER_LEDS_H_

#include "avrlib/devices/bicolor_led_array.h"

#include "controller/hardware_config.h"

namespace ambika {
  
enum LedNumber {
  LED_1,
  LED_2,
  LED_3,
  LED_4,
  LED_5,
  LED_6,
  LED_7,
  LED_8,
  LED_PART_1,
  LED_PART_2,
  LED_PART_3,
  LED_PART_4,
  LED_PART_5,
  LED_PART_6,
  LED_STATUS
};
  
using avrlib::BicolorLedArray;

typedef BicolorLedArray<IOEnableLine, IOClockLine, IOOutputLine, 2> Leds;
extern Leds leds;

}  // namespace ambika

#endif  // CONTROLLER_LEDS_H_
