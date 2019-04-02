// Copyright 2011 Emilie Gillet.
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

#include "avrlib/devices/wii_nunchuk.h"
#include "avrlib/gpio.h"
#include "avrlib/time.h"
#include "avrlib/watchdog_timer.h"

#include "peripherals/nunchuk/app.h"
#include "peripherals/nunchuk/ui.h"
#include "peripherals/nunchuk/midi_output.h"

using namespace avrlib;
using namespace nunchuk;

WiiNunchuk nunchuk_reader;
Gpio<PortD, 1> test_pin;

volatile uint8_t onboard_switch_released = 0;

ISR(TIMER1_OVF_vect) {
  static uint8_t count = 0;
  midi_output.Process();
  if ((++count & 7) == 0) {
    program_switch.Read();
    if (program_switch.raised()) {
      onboard_switch_released = 1;
    }
  }
}

void Init() {
  sei();
  UCSR0B = 0;
  note_led.set_mode(DIGITAL_OUTPUT);
  connection_led.set_mode(DIGITAL_OUTPUT);
  test_pin.set_mode(DIGITAL_OUTPUT);

  midi_output.Init();
  program_switch.Init();
  nunchuk_reader.Init();
  app.Init();
  Timer<1>::set_prescaler(2);
  Timer<1>::set_mode(TIMER_PWM_PHASE_CORRECT);
  Timer<1>::Start();
}

int main(void) {
  ResetWatchdog();
  cli();
  Init();
  
  while (1) {
    if (nunchuk_reader.Poll()) {
      connection_led.High();
      if (!nunchuk_reader.alive()) {
        nunchuk_reader.Init();
      } else {
        app.ProcessNunchuk(
            nunchuk_reader.joystick_x(),
            nunchuk_reader.joystick_y(),
            nunchuk_reader.acc_x(),
            nunchuk_reader.acc_y(),
            nunchuk_reader.acc_z(),
            nunchuk_reader.c_pressed(),
            nunchuk_reader.z_pressed());
      }
    } else {
      connection_led.Low();
    }
    if (onboard_switch_released) {
      app.NextApp();
      onboard_switch_released = 0;
    }
    ConstantDelay(1);
  }
}
