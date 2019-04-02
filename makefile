# Copyright 2011 Emilie Gillet.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

include voicecard/makefile

VOICECARD_FIRMWARE = build/ambika_voicecard/ambika_voicecard.hex
VOICECARD_BOOTLOADER = build/ambika_voicecard_boot/ambika_voicecard_boot.hex
VOICECARD_EEPROM = data/voicecard_eeprom_golden.hex

CONTROLLER_FIRMWARE = build/ambika_controller/ambika_controller.hex
CONTROLLER_BOOTLOADER = build/ambika_controller_boot/ambika_controller_boot.hex

bootstrap_voicecard:
		make -f voicecard/makefile
		make -f voicecard/bootloader/makefile
		make -f voicecard/bootloader/makefile fuses
		$(AVRDUDE) -B 1 $(AVRDUDE_COM_OPTS) $(AVRDUDE_ISP_OPTS) \
		  -U eeprom:w:$(VOICECARD_EEPROM):i \
			-U flash:w:$(VOICECARD_FIRMWARE):i \
			-U flash:w:$(VOICECARD_BOOTLOADER):i \
			-U lock:w:0x2f:m

bootstrap_controller:
		make -f controller/makefile
		make -f controller/bootloader/makefile
		make -f controller/bootloader/makefile fuses
		$(AVRDUDE) -B 1 -V -p m644p $(AVRDUDE_ISP_OPTS) \
			-U flash:w:$(CONTROLLER_FIRMWARE):i \
			-U flash:w:$(CONTROLLER_BOOTLOADER):i \
			-U lock:w:0x2f:m
