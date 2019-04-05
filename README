#Ambika
## A hybrid MIDI polysynth and voicecard host.

Ambika consists of a compact motherboard serving as a "host" for up to 6 sound synthesis voicecard. While this design is primarily intended to be a flexible hybrid polysynth, it could also be used as a drum module/drum machine.

The motherboard comprises 6 audio outputs, each one connected to a voicecard ; a global mono output ; a pair of MIDI input/output ; a SD card slot ; a 5V/8V/-8V power supply capable of delivering 150mA on the 8V rails and 350mA on the 5V rail ; the master MCU and the user interface elements. The voicecards (a pair of each being attached to the 3 voicecard ports) are SPI slaves, they receive note and modulation data from the motherboard ; and output monophonic audio, ideally 1V pp.

3 designs of voicecards implementing a refined version of the Shruthi-1 engine are provided. Each of those use a different filter (4-Pole with LM13700, 4-Pole with SSM2164, 2-Pole SVF with SSM2164).

Original developer: Emilie Gillet (emilie.o.gillet@gmail.com)

The firmware is released under a GPL3.0 license. It includes a variant of the formant synthesis algorithm used in Peter Knight's Cantarino speech synthesizer.

The PCB layouts and schematics, documentation, analyses, simulations and 3D models are released under a Creative Commons cc-by-sa 3.0 license.

# BUILD

You'll need:
- make
- gcc-avr
- avr-libc
- avrdude
- python

On Ubuntu:
```
    sudo apt-get install gcc-avr make avr-libc
```

Next, you'll need to grab the projects this repo depends on.
```
    git submodule update --init
```

Once you've got that all settled, you'll need to change the path to `avr-gcc` in avrlib/makefile.mk.

```
    #remeber the path given by this command
    which avr-gcc

    <your editor of choice> avrlib/makefile.mk
    replace the old path in the line 'AVRLIB_TOOLS_PATH ?= <oldpath>' with the output from "which avr-gcc" you got above
```

Finally, run `make`
