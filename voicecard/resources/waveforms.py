#!/usr/bin/python2.5
#
# Copyright 2011 Emilie Gillet.
#
# Author: Emilie Gillet (emilie.o.gillet@gmail.com)
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
#
# -----------------------------------------------------------------------------
#
# Waveform definitions.

import numpy


"""----------------------------------------------------------------------------
Waveforms for vowel synthesis
----------------------------------------------------------------------------"""

SAMPLE_RATE = 20000000 / 510.0

waveforms = []
# Create amplitude modulated sine/square tables for formants.
sine_samples = []
square_samples = []
sine = numpy.sin(numpy.arange(16.0) / 16.0 * 2 * numpy.pi)
for i, x in enumerate(sine):
  gains = numpy.exp(0.184 * numpy.arange(16.0))
  gains[0] = 0
  values = gains * x * 4
  values = numpy.round(values).astype(int)
  amps = numpy.round(gains)
  if (i >= 8):
    amps = -amps
  square_samples.extend(amps.astype(int))
  sine_samples.extend(values)

waveforms.extend([
    ('formant_sine', sine_samples),
    ('formant_square', square_samples)
])


"""----------------------------------------------------------------------------
Band-limited waveforms
----------------------------------------------------------------------------"""

WAVETABLE_SIZE = 256

# The Juno-6 / Juno-60 waveforms have a brighter harmonic content, which can be
# recreated by adding to the signal a 1-pole high-pass filtered version of
# itself.
JUNINESS = 1.0


def Dither(x, order=0, type=numpy.uint8):
  for i in xrange(order):
    x = numpy.hstack((numpy.zeros(1,), numpy.cumsum(x)))
  x = numpy.round(x)
  for i in xrange(order):
    x = numpy.diff(x)
  if any(x < numpy.iinfo(type).min) or any(x > numpy.iinfo(type).max):
    print 'Clipping occurred!'
  x[x < numpy.iinfo(type).min] = numpy.iinfo(type).min
  x[x > numpy.iinfo(type).max] = numpy.iinfo(type).max
  return x.astype(type)


def Scale(array, min=1, max=254, center=True, dither=2):
  if center:
    array -= array.mean()
  mx = numpy.abs(array).max()
  array = (array + mx) / (2 * mx)
  array = array * (max - min) + min
  return Dither(array, order=dither)


# Sine wave.
sine = -numpy.sin(numpy.arange(WAVETABLE_SIZE + 1) / float(WAVETABLE_SIZE) * 2 * numpy.pi) * 127.5 + 127.5

# Band limited waveforms.
num_zones = (107 - 24) / 16 + 2
bl_pulse_tables = []
bl_square_tables = []
bl_saw_tables = []
bl_tri_tables = []

wrap = numpy.fmod(numpy.arange(WAVETABLE_SIZE + 1) + WAVETABLE_SIZE / 2, WAVETABLE_SIZE)
quadrature = numpy.fmod(numpy.arange(WAVETABLE_SIZE + 1) + WAVETABLE_SIZE / 4, WAVETABLE_SIZE)
fill = numpy.fmod(numpy.arange(WAVETABLE_SIZE + 1), WAVETABLE_SIZE)

waveforms.append(('sine', Scale(sine[quadrature])))
# waveforms.append(('sine_no_dither', Scale(sine[quadrature], dither=0)))

for zone in range(num_zones):
  f0 = 440.0 * 2.0 ** ((18 + 16 * zone - 69) / 12.0)
  period = SAMPLE_RATE / f0
  m = 2 * numpy.floor(period / 2) + 1.0
  i = numpy.arange(-WAVETABLE_SIZE / 2, WAVETABLE_SIZE / 2) / float(WAVETABLE_SIZE)
  pulse = numpy.sin(numpy.pi * i * m) / (m * numpy.sin(numpy.pi * i) + 1e-9)
  pulse[WAVETABLE_SIZE / 2] = 1.0
  pulse = pulse[fill]

  square = numpy.cumsum(pulse - pulse[wrap])
  triangle = -numpy.cumsum(square[::-1] - square.mean()) / WAVETABLE_SIZE

  square -= JUNINESS * triangle
  if zone == num_zones - 1:
    square = sine
  bl_square_tables.append(('bandlimited_square_%d' % zone,
                          Scale(square[quadrature])))

  triangle = triangle[quadrature]
  if zone == num_zones - 1:
    triangle = sine
  bl_tri_tables.append(('bandlimited_triangle_%d' % zone,
                        Scale(triangle[quadrature])))

  saw = -numpy.cumsum(pulse[wrap] - pulse.mean())
  saw -= JUNINESS * numpy.cumsum(saw - saw.mean()) / WAVETABLE_SIZE
  if zone == num_zones - 1:
    saw = sine
  bl_saw_tables.append(('bandlimited_saw_%d' % zone,
                       Scale(saw[quadrature])))


# Save some bytes by using a slightly aliased triangle in the mid-octaves.
triangle_lowest_octave = bl_tri_tables[0]
for i in xrange(1, 3):
 bl_tri_tables[i] = triangle_lowest_octave


def LoadWavetable(x):
  # Load the data and split/pad single cycle waveforms.
  array = numpy.array(map(ord, list(file(x).read())))
  cycle = 128
  num_cycles = len(array) / cycle
  assert num_cycles == 16
  wavetable = numpy.zeros((num_cycles, cycle + 1))
  for i in xrange(num_cycles):
    for j in xrange(cycle):
      wavetable[i, j] = array[i * cycle + j]
    wavetable[i, cycle] = wavetable[i, 0]
  
  return wavetable.ravel()


waveforms.extend(bl_pulse_tables)
waveforms.extend(bl_square_tables)
waveforms.extend(bl_saw_tables)
waveforms.extend(bl_tri_tables)


"""----------------------------------------------------------------------------
Vowel data (formant amplitudes)
-----------------------------------------------------------------------------"""

vowel_data = [
    27, 40,  89, 15, 13, 1, 0,
    18, 51,  62, 13, 12, 6, 0,
    15, 69,  93, 14, 12, 7, 0,
    10, 84, 110, 13, 10, 8, 0,
    23, 44,  87, 15, 12, 1, 0,
    13, 29,  80, 13, 8,  0, 0,
     6, 46,  81, 12, 3,  0, 0,
     9, 51,  95, 15, 3,  0,  3,
     6, 73,  99, 7,  3,  14, 9]

waveforms.append(('vowel_data', vowel_data))


"""----------------------------------------------------------------------------
Waveshaper/distorsion
-----------------------------------------------------------------------------"""

signal_range = ((numpy.arange(0, 256) / 128.0 - 1.0))
fuzz = numpy.tanh(6.0 * signal_range) * 128.0 + 128.0

waveforms.append(('distortion', Scale(fuzz, dither=0)))


"""----------------------------------------------------------------------------
Dummy LFO waveshape table (not used, can be empty)
-----------------------------------------------------------------------------"""

waveforms.append(('lfo_waveforms', Scale(numpy.array([0.0, 1.0]), dither=0)))


"""----------------------------------------------------------------------------
Envelope curves
-----------------------------------------------------------------------------"""

env_linear = numpy.arange(0, 257.0) / 256.0
env_linear[-1] = env_linear[-2]
env_quartic = 1.0 - (1.0 - env_linear) ** 4.0
env_expo = 1.0 - numpy.exp(-4 * env_linear)

# waveforms.append(('env_quartic', env_quartic / env_quartic.max() * 255))
waveforms.append(('env_expo', env_expo / env_expo.max() * 255))

# import pylab
# pylab.plot(env_expo / env_expo.max() * 255)
# pylab.savefig('foo.pdf')


"""----------------------------------------------------------------------------
Wavetables
-----------------------------------------------------------------------------"""


waveforms.append(('waves', map(ord, file('data/waves.bin', 'rb').read())))

wavetables = [
# Male
16, 57, 52, 59, 53, 54, 55, 56, 57, 58, 62, 69, 59, 61, 60, 61, 62, 62,
# Female
16, 59, 52, 59, 71, 52, 70, 52, 56, 71, 14, 69, 71, 70, 71, 71, 71, 71,
# Choir
1, 70, 71, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
# Tampura
8, 14, 15, 15, 15, 16, 17, 17, 18, 18, 0, 0, 0, 0, 0, 0, 0, 0,
# Bowed
8, 34, 35, 36, 36, 37, 38, 39, 40, 40, 0, 0, 0, 0, 0, 0, 0, 0,
# Cello
1, 69, 57, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
# Vibes
8, 74, 75, 76, 77, 78, 79, 79, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0,
# Slap
8, 41, 42, 43, 43, 44, 44, 44, 44, 44, 0, 0, 0, 0, 0, 0, 0, 0,
# Epiano
8, 73, 73, 69, 72, 72, 72, 72, 72, 72, 0, 0, 0, 0, 0, 0, 0, 0,
# Organ
16, 3, 45, 45, 72, 46, 46, 46, 47, 48, 48, 49, 50, 50, 46, 51, 51, 51,
# Waves
16, 13, 0, 1, 2, 3, 4, 4, 5, 6, 7, 8, 9, 10, 11, 11, 12, 12,
# Digital
16, 3, 34, 19, 20, 21, 21, 66, 66, 22, 22, 23, 23, 24, 24, 25, 26, 26,
# Drone 1
8, 66, 68, 66, 72, 65, 65, 66, 66, 66, 0, 0, 0, 0, 0, 0, 0, 0,
# Drone 2
4, 67, 67, 68, 69, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
# Metallic
8, 27, 28, 29, 30, 31, 31, 32, 33, 33, 0, 0, 0, 0, 0, 0, 0, 0,
# Bell
4, 63, 63, 63, 64, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
]

waveforms.append(('wavetables', wavetables))