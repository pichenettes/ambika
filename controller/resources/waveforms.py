#!/usr/bin/python2.5
#
# Copyright 2011 Olivier Gillet.
#
# Author: Olivier Gillet (ol.gillet@gmail.com)
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
# Custom LFO waveshapes.

import numpy


def convolve(curve, impulse):
  return numpy.fft.irfft(numpy.fft.rfft(curve) * numpy.fft.rfft(impulse))


def scale(x, min=1, max=254, center=True, dithering=0):
  mx = x.max()
  mn = x.min()
  x = (x - mn) / (mx - mn)
  x = numpy.round(x * (max - min) + min)
  target_type = numpy.uint8
  x[x < numpy.iinfo(target_type).min] = numpy.iinfo(target_type).min
  x[x > numpy.iinfo(target_type).max] = numpy.iinfo(target_type).max
  return x.astype(target_type)


custom_lfos = []

t = numpy.arange(0, 256) / 256.0
ramp = t
triangle = 2 * t * (t < 0.5) + (2.0 - 2 * t) * (t >= 0.5)
square = (t < 0.5)
bipolar_triangle = 2 * triangle - 1.0
sine = numpy.sin(2 * numpy.pi * t)

# Sine and harmonics (4)
sine_2 = numpy.sin(2 * numpy.pi * t) + 0.7 * numpy.sin(4 * numpy.pi * t)
sine_3 = numpy.sin(2 * numpy.pi * t) + 0.7 * numpy.sin(6 * numpy.pi * t)
sine_5 = numpy.sin(2 * numpy.pi * t) + 0.7 * numpy.sin(10 * numpy.pi * t)
custom_lfos.append(sine)
custom_lfos.append(sine_2)
custom_lfos.append(sine_3)
custom_lfos.append(sine_5)
# Gurgles (2)
window = (1.0 - numpy.cos(4 * numpy.pi * t)) / 2.0
custom_lfos.append(numpy.maximum(sine_2, 0.0) * window)
custom_lfos.append(numpy.maximum(sine_3, 0.0) * window)

# Bat (2)
for fold_amount in [0.5, 1.0]:
  fold = (1 + fold_amount) * bipolar_triangle
  fold[fold > 1.0] = 2.0 - fold[fold > 1.0]
  fold[fold < -1.0] = -2.0 - fold[fold < -1.0]
  custom_lfos.append(fold)

# Spiky (2)
spike = 2 ** (4 * triangle) - 1
bipolar_spike = numpy.sign(bipolar_triangle) * (
    2 ** (4 * numpy.abs(bipolar_triangle)) - 1)
custom_lfos.append(spike)
custom_lfos.append(bipolar_spike)

# Low-pass filtered ramp and square (2)
smooth = numpy.exp(-10 * t)
custom_lfos.append(convolve(ramp, smooth))
custom_lfos.append(convolve(square, smooth))

# Low-pass filtered ramp and square with resonance (2)
bouncy = numpy.exp(-10 * t) * numpy.sin(16 * numpy.pi * t)
custom_lfos.append(convolve(ramp, bouncy))
custom_lfos.append(convolve(square, bouncy))

# Steps (2)
custom_lfos.append(numpy.round(triangle * 3))
custom_lfos.append(numpy.round(triangle * 15))

lfo_waveforms = numpy.zeros((257 * len(custom_lfos),), dtype=numpy.uint8)
for i, values in enumerate(custom_lfos):
  values = scale(values)
  lfo_waveforms[i * 257: i * 257 + 256] = values
  lfo_waveforms[i * 257 + 256] = values[0]

waveforms = [('lfo_waveforms', lfo_waveforms)]
