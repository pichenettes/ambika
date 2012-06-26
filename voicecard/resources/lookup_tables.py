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
# Lookup table definitions.

import numpy

"""----------------------------------------------------------------------------
LFO and envelope increments.
----------------------------------------------------------------------------"""

lookup_tables = []

sample_rate = 20000000 / 510.0
control_rate = sample_rate / 40.0
min_frequency = 1.0 / 16.0  # Hertz
max_frequency = 100.0  # Hertz

excursion = 65536
num_values = 128
min_increment = excursion * min_frequency / control_rate
max_increment = excursion * max_frequency / control_rate

rates = numpy.linspace(numpy.log(min_increment),
                       numpy.log(max_increment), num_values)

lookup_tables.append(
    ('lfo_increments', numpy.exp(rates).astype(int))
)


# Create lookup table for envelope times (x^0.25).
max_time = 12.0  # seconds
min_time = 3.0 / control_rate  # seconds
excursion = 65535.0
gamma = 0.175
min_increment = excursion / (max_time * control_rate)
max_increment = excursion / (min_time * control_rate)

rates = numpy.linspace(numpy.power(max_increment, -gamma),
                       numpy.power(min_increment, -gamma), num_values)

values = numpy.power(rates, -1/gamma).astype(int)
slow_values = numpy.arange(num_values + 2, 2, -1) / 2
i = num_values - 1
while slow_values[i] != values[i]:
  values[i] = slow_values[i]
  i -= 1
values[0] = 65535
lookup_tables.append(
    ('env_portamento_increments', values)
)

# Create table for pitch.
a4_midi = 69
a4_pitch = 440.0
excursion = 65536.0
notes = numpy.arange(116 * 128.0, 128 * 128.0, 2)
pitches = a4_pitch * 2 ** ((notes - a4_midi * 128) / (128 * 12))
increments = excursion / sample_rate * pitches

lookup_tables.append(
    ('oscillator_increments', increments.astype(int))
)


"""----------------------------------------------------------------------------
Table with FM modulation frequency ratios. This is taken from the
DX21 manual (http://www.maths.abdn.ac.uk/~bensondj/dx7/manuals/dx21-man.pdf),
with less details in the highest frequencies. Added: slight variations in
pitch to create phasing/detune effects, low octaves, and 7/4, 9/4 that I really
like.
----------------------------------------------------------------------------"""

fm_frequency_ratios = numpy.array(
[ 0.125,
  0.25,
  0.5,
  0.5 * 2 ** (16 / 1200.0),
  numpy.sqrt(2) / 2,
  numpy.pi / 4,
  1.0,
  1.0 * 2 ** (8 / 1200.0),
  numpy.sqrt(2),
  numpy.pi / 2,
  7.0 / 4,
  2,
  2 * 2 ** (8 / 1200.0),
  9.0 / 4,
  11.0 / 4,
  2 * numpy.sqrt(2),
  3,
  numpy.pi,
  numpy.sqrt(3) * 2,
  4,
  numpy.sqrt(2) * 3,
  numpy.pi * 3 / 2,
  5,
  numpy.sqrt(2) * 4,
  8]
)

lookup_tables.append(
    ('fm_frequency_ratios', (fm_frequency_ratios * 256).astype(int))
)

"""----------------------------------------------------------------------------
SSM2164 pseudo-linearization.

Log-VCAs suck, but they are cheap to do if you have a spare cell on a
SSM2164, which happens to be the case with the SVF which uses 3-cells.

If you don't need more than 8-bits of resolution on the envelope CV, the
linearization can be done in software.

Vdac = 2.048 * 2 * v_12bits / 4096 (Assuming the 4822 is in double gain mode)
VCAgain = 10 ** (-1.5 * Vdac)
----------------------------------------------------------------------------"""

# Change this to get a more logarithmey-response.
skew = 0.5

g = numpy.linspace(9e-5, 0.99, 256)
v = 4096 / 4.096 * -(2.0 + skew) / 3.0 * numpy.log10(g)
vca_linearization_table = numpy.maximum(numpy.minimum(numpy.round(v), 4095), 0)

v_dac = 2.048 * 2 * (vca_linearization_table / 4096.0)
vca_gain = 10 ** (-1.5 * v_dac)

# import pylab
# pylab.plot(vca_gain)
# pylab.savefig('curve.pdf')
# pylab.show()

lookup_tables.append(
    ('vca_linearization', vca_linearization_table.astype(int))
)

lookup_tables.append(
    ('cz_phase_reset', [0, 32768, 16384, 32768])
)
