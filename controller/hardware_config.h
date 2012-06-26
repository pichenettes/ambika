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

#ifndef CONTROLLER_HARDWARE_CONFIG_H_
#define CONTROLLER_HARDWARE_CONFIG_H_

#include "avrlib/base.h"
#include "avrlib/gpio.h"
#include "avrlib/parallel_io.h"
#include "avrlib/serial.h"

namespace ambika {

using avrlib::Gpio;
using avrlib::PARALLEL_NIBBLE_HIGH;
using avrlib::PARALLEL_TRIPLE_LOW;
using avrlib::ParallelPort;
using avrlib::PortB;
using avrlib::PortC;
using avrlib::PortD;
using avrlib::RingBuffer;
using avrlib::SerialInput;
using avrlib::SerialPort0;

// Encoder
typedef Gpio<PortC, 3> EncoderALine;
typedef Gpio<PortC, 2> EncoderBLine;
typedef Gpio<PortC, 1> EncoderClickLine;

// MIDI
typedef avrlib::Serial<
    SerialPort0,
    31250,
    avrlib::POLLED,
    avrlib::POLLED> MidiIO;
typedef RingBuffer<SerialInput<SerialPort0> > MidiBuffer;

// LCD
static const uint8_t kLcdWidth = 40;
static const uint8_t kLcdHeight = 2;
typedef Gpio<PortD, 3> LcdRsLine;
typedef Gpio<PortD, 2> LcdEnableLine;
typedef ParallelPort<PortD, PARALLEL_NIBBLE_HIGH> LcdDataBus;

// IO
typedef Gpio<PortC, 7> IOClockLine;
typedef Gpio<PortC, 6> IOInputLine;
typedef Gpio<PortC, 5> IOOutputLine;
typedef Gpio<PortC, 4> IOEnableLine;

// Address
typedef ParallelPort<PortB, PARALLEL_TRIPLE_LOW> AddressBus;

enum SpiSlaves {
  SPI_SLAVE_VOICECARD_0,
  SPI_SLAVE_VOICECARD_1,
  SPI_SLAVE_VOICECARD_2,
  SPI_SLAVE_VOICECARD_3,
  SPI_SLAVE_VOICECARD_4,
  SPI_SLAVE_VOICECARD_5,
  SPI_SLAVE_EXPANSION_PORT,
  SPI_SLAVE_SD_CARD
};

static uint8_t* kFirmwareUpdateFlagPtr = (uint8_t*)(E2END);

}  // namespace ambika

#endif  // CONTROLLER_HARDWARE_CONFIG_H_
