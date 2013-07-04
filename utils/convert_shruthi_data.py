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

"""Tool for converting the Shruthi-1 patches into the Ambika FS format."""

import logging
import optparse
import os
import struct


SHRUTHI_MOD_SOURCE = [
  'MOD_SRC_LFO_1',
  'MOD_SRC_LFO_2',
  'MOD_SRC_SEQ',
  'MOD_SRC_SEQ_1',
  'MOD_SRC_SEQ_2',
  'MOD_SRC_STEP',
  'MOD_SRC_WHEEL',
  'MOD_SRC_AFTERTOUCH',
  'MOD_SRC_PITCH_BEND',
  'MOD_SRC_OFFSET',
  'MOD_SRC_CV_1',
  'MOD_SRC_CV_2',
  'MOD_SRC_CV_3',
  'MOD_SRC_CV_4',
  'MOD_SRC_CC_A',
  'MOD_SRC_CC_B',
  'MOD_SRC_CC_C',
  'MOD_SRC_CC_D',
  'MOD_SRC_NOISE',
  'MOD_SRC_ENV_1',
  'MOD_SRC_ENV_2',
  'MOD_SRC_VELOCITY',
  'MOD_SRC_RANDOM',
  'MOD_SRC_NOTE',
  'MOD_SRC_GATE',
  'MOD_SRC_AUDIO',
  'MOD_SRC_OP_1',
  'MOD_SRC_OP_2',
]

SHRUTHI_MOD_DESTINATION = [
  'MOD_DST_FILTER_CUTOFF',
  'MOD_DST_VCA',
  'MOD_DST_PARAMETER_1',
  'MOD_DST_PARAMETER_2',
  'MOD_DST_OSC_1',
  'MOD_DST_OSC_2',
  'MOD_DST_OSC_1_2_COARSE',
  'MOD_DST_OSC_1_2_FINE',
  'MOD_DST_MIX_BALANCE',
  'MOD_DST_MIX_NOISE',
  'MOD_DST_MIX_SUB_OSC',
  'MOD_DST_FILTER_RESONANCE',
  'MOD_DST_CV_1',
  'MOD_DST_CV_2',
  'MOD_DST_ATTACK',
  'MOD_DST_LFO_1',
  'MOD_DST_LFO_2',
]

SHRUTHI_OSCILLATOR_ALGORITHM = [
  'WAVEFORM_NONE',
  'WAVEFORM_SAW',
  'WAVEFORM_SQUARE',
  'WAVEFORM_TRIANGLE',
  'WAVEFORM_CZ_SAW',
  'WAVEFORM_CZ_RESO',
  'WAVEFORM_CZ_TRIANGLE',
  'WAVEFORM_CZ_PULSE',
  'WAVEFORM_CZ_SYNC',
  'WAVEFORM_QUAD_SAW_PAD',
  'WAVEFORM_FM',
  'WAVEFORM_WAVETABLE_WAVES',
  'WAVEFORM_WAVETABLE_TAMPURA',
  'WAVEFORM_WAVETABLE_DIGITAL',
  'WAVEFORM_WAVETABLE_METALLIC',
  'WAVEFORM_WAVETABLE_BOWED',
  'WAVEFORM_WAVETABLE_SLAP',
  'WAVEFORM_WAVETABLE_ORGAN',
  'WAVEFORM_WAVETABLE_MALE',
  'WAVEFORM_WAVETABLE_USER',
  'WAVEFORM_8BITLAND',
  'WAVEFORM_CRUSHED_SINE',
  'WAVEFORM_DIRTY_PWM',
  'WAVEFORM_FILTERED_NOISE',
  'WAVEFORM_VOWEL',
  'WAVEFORM_WAVETABLE_BELLISH',
  'WAVEFORM_WAVETABLE_POLATED',
  'WAVEFORM_WAVETABLE_CELLO',
  'WAVEFORM_WAVETABLE_CLIPSWEEP',
  'WAVEFORM_WAVETABLE_FEMALE',
  'WAVEFORM_WAVETABLE_FMNTVOC',
  'WAVEFORM_WAVETABLE_FORMANT2',
  'WAVEFORM_WAVETABLE_RES3HP',
  'WAVEFORM_WAVETABLE_ELECTP',
  'WAVEFORM_WAVETABLE_VIBES',
]

SHRUTHI_MIX_OPERATOR = [
  'OP_SUM',
  'OP_SYNC',
  'OP_RING_MOD',
  'OP_XOR',
  'OP_FUZZ',
  'OP_CRUSH_4',
  'OP_CRUSH_8',
  'OP_FOLD',
  'OP_BITS',
  'OP_DUO',
  'OP_PING_PONG_2',
  'OP_PING_PONG_4',
  'OP_PING_PONG_8',
  'OP_PING_PONG_SEQ'
]

AMBIKA_OSCILLATOR_ALGORITHM = {
  'WAVEFORM_NONE': 0,
  'WAVEFORM_SAW': 1,
  'WAVEFORM_SQUARE': 2,
  'WAVEFORM_TRIANGLE': 3,
  'WAVEFORM_CRUSHED_SINE': 4,
  'WAVEFORM_CZ_SAW': 5,
  'WAVEFORM_CZ_SAW_LP': 6,
  'WAVEFORM_CZ_SAW_PK': 7,
  'WAVEFORM_CZ_SAW_BP': 8,
  'WAVEFORM_CZ_SAW_HP': 9,
  'WAVEFORM_CZ_PLS_LP': 10,
  'WAVEFORM_CZ_PLS_PK': 11,
  'WAVEFORM_CZ_PLS_BP': 12,
  'WAVEFORM_CZ_PLS_HP': 13,
  'WAVEFORM_CZ_TRI_LP': 14,
  'WAVEFORM_QUAD_SAW_PAD': 15,
  'WAVEFORM_FM': 16,
  'WAVEFORM_8BITLAND': 17,
  'WAVEFORM_DIRTY_PWM': 18,
  'WAVEFORM_FILTERED_NOISE': 19,
  'WAVEFORM_VOWEL': 20,
  'WAVEFORM_WAVETABLE_MALE': 21,
  'WAVEFORM_WAVETABLE_FEMALE': 22,
  'WAVEFORM_WAVETABLE_FMNTVOC': 23,
  'WAVEFORM_WAVETABLE_TAMPURA': 24,
  'WAVEFORM_WAVETABLE_BOWED': 25,
  'WAVEFORM_WAVETABLE_CELLO': 26,
  'WAVEFORM_WAVETABLE_VIBES': 27,
  'WAVEFORM_WAVETABLE_SLAP': 28,
  'WAVEFORM_WAVETABLE_ELECTP': 29,
  'WAVEFORM_WAVETABLE_ORGAN': 30,
  'WAVEFORM_WAVETABLE_WAVES': 31,
  'WAVEFORM_WAVETABLE_DIGITAL': 32,
  'WAVEFORM_WAVETABLE_POLATED': 33,
  'WAVEFORM_WAVETABLE_FORMANT2': 34,
  'WAVEFORM_WAVETABLE_CLIPSWEEP': 34,
  'WAVEFORM_WAVETABLE_METALLIC': 35,
  'WAVEFORM_WAVETABLE_BELLISH': 36,
  'WAVEFORM_WAVETABLE_WAVEQUENCE': 37,
  'WAVEFORM_WAVETABLE_USER': 31,
  'WAVEFORM_CZ_RESO': 6,
  'WAVEFORM_CZ_TRIANGLE': 14,
  'WAVEFORM_CZ_PULSE': 11,
  'WAVEFORM_CZ_SYNC': 12,
}

AMBIKA_MODULATION_SOURCE = {
  'MOD_SRC_ENV_1': 1,
  'MOD_SRC_ENV_2': 2,
  'MOD_SRC_ENV_3': 0,

  'MOD_SRC_LFO_1': 3,
  'MOD_SRC_LFO_2': 4,
  'MOD_SRC_LFO_3': 5,
  'MOD_SRC_LFO_4': 6,

  'MOD_SRC_OP_1': 7,
  'MOD_SRC_OP_2': 8,
  'MOD_SRC_OP_3': 9,
  'MOD_SRC_OP_4': 10,

  'MOD_SRC_SEQ_1': 11,
  'MOD_SRC_SEQ_2': 12,
  'MOD_SRC_ARP_STEP': 13,

  'MOD_SRC_VELOCITY': 14,
  'MOD_SRC_AFTERTOUCH': 15,
  'MOD_SRC_PITCH_BEND': 16,
  'MOD_SRC_WHEEL': 17,
  'MOD_SRC_WHEEL_2': 18,
  'MOD_SRC_EXPRESSION': 19,

  'MOD_SRC_NOTE': 20,
  'MOD_SRC_GATE': 21,
  'MOD_SRC_NOISE': 22,
  'MOD_SRC_RANDOM': 23,
  'MOD_SRC_CONSTANT_256': 24,
  'MOD_SRC_CONSTANT_128': 25,
  'MOD_SRC_CONSTANT_64': 26,
  'MOD_SRC_CONSTANT_32': 27,
  'MOD_SRC_CONSTANT_16': 28,
  'MOD_SRC_CONSTANT_8': 29,
  'MOD_SRC_CONSTANT_4': 30,
  
  'MOD_SRC_SEQ': 11,
  'MOD_SRC_STEP': 13,
  'MOD_SRC_AUDIO': 29,
  'MOD_SRC_OFFSET': 24
}

AMBIKA_MODULATION_DESTINATION = {
  'MOD_DST_PARAMETER_1': 0,
  'MOD_DST_PARAMETER_2': 1,
  'MOD_DST_OSC_1': 2,
  'MOD_DST_OSC_2': 3,
  'MOD_DST_OSC_1_2_COARSE': 4,
  'MOD_DST_OSC_1_2_FINE': 5,

  'MOD_DST_MIX_BALANCE': 6,
  'MOD_DST_MIX_PARAM': 7,
  'MOD_DST_MIX_NOISE': 8,
  'MOD_DST_MIX_SUB_OSC': 9,
  'MOD_DST_MIX_FUZZ': 10,
  'MOD_DST_MIX_CRUSH': 11,

  'MOD_DST_FILTER_CUTOFF': 12,
  'MOD_DST_FILTER_RESONANCE': 13,

  'MOD_DST_ATTACK': 14,
  'MOD_DST_DECAY': 15,
  'MOD_DST_RELEASE': 16,
  'MOD_DST_LFO_4': 17,

  'MOD_DST_LFO_1': 17,
  'MOD_DST_LFO_2': 17,
  
  'MOD_DST_VCA': 18,
}

DEFAULT_AMBIKA_PART_DATA = [
  120,
  0, 0, 0, 0,
  0, 0, 0,
  0, 1, 0, 10,
  16,
  16,
  16,
  1,
  0xff, 0xff, 0x80, 0x80, 0xcc, 0xcc, 0x20, 0x20,
  0x00, 0x20, 0x40, 0x60, 0x80, 0xa0, 0xc0, 0xff,
  0x00, 0x10, 0x20, 0x40, 0x80, 0xff, 0x80, 0x40,
  0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x80, 0x40,
  60 | 0x80, 100,
  60, 100,
  48 | 0x80, 100,
  48, 100,
  60 | 0x80, 100,
  60, 100,
  48 | 0x80, 100,
  48, 100,
  60 | 0x80, 100,
  60, 100,
  48 | 0x80, 100,
  48 | 0x80, 100 | 0x80,
  60 | 0x80, 100,
  60, 100,
  48 | 0x80, 100,
  48, 100,
  0,
  0,
  0,
  0,
]

class ShruthiPatch(object):
  
  def __init__(self, bytes):
    self.oscillators = []
    self.env = []
    self.lfo = []
    self.modulations = []
    for i in xrange(2):
      self.oscillators.append(
        {'shape': SHRUTHI_OSCILLATOR_ALGORITHM[bytes[i * 4 + 0]],
         'parameter': bytes[i * 4 + 1],
         'range': bytes[i * 4 + 2],
         'option': bytes[i * 4 + 3]})
    self.oscillators[0]['option'] = SHRUTHI_MIX_OPERATOR[
        self.oscillators[0]['option']]
    self.mix_balance = bytes[8]
    self.mix_sub_osc = bytes[9]
    self.mix_noise = bytes[10]
    self.mix_sub_osc_shape = bytes[11]
    self.filter_cutoff = bytes[12]
    self.filter_resonance = bytes[13]
    self.filter_env = bytes[14]
    self.filter_lfo = bytes[15]
    for i in xrange(2):
      self.env.append(
        {'attack': bytes[i * 4 + 16],
         'decay': bytes[i * 4 + 17],
         'sustain': bytes[i * 4 + 18],
         'release': bytes[i * 4 + 19]})
    for i in xrange(2):
      rate = bytes[i * 4 + 25]
      if rate <= 15:
        rate = 48
      self.lfo.append(
        {'waveform': bytes[i * 4 + 24],
         'rate': rate,
         'attack': bytes[i * 4 + 26],
         'retrigger_mode': bytes[i * 4 + 27]})
    for i in xrange(12):
      self.modulations.append(
        {'source': SHRUTHI_MOD_SOURCE[bytes[i * 3 + 32]],
         'destination': SHRUTHI_MOD_DESTINATION[bytes[i * 3 + 33]],
         'amount': bytes[i * 3 + 34]})
    self.name = ''.join(map(chr, bytes[68:76]))
    self.op_data = bytes[87:91]
    assert bytes[91] == ord('!')


def BuildAmbikaPatch(p):
  patch = [0] * 112
  # Oscillators
  patch[0] = AMBIKA_OSCILLATOR_ALGORITHM[p.oscillators[0]['shape']]
  patch[1] = p.oscillators[0]['parameter']
  patch[2] = p.oscillators[0]['range']
  patch[3] = 0

  patch[4] = AMBIKA_OSCILLATOR_ALGORITHM[p.oscillators[1]['shape']]
  patch[5] = p.oscillators[1]['parameter']
  patch[6] = p.oscillators[1]['range']
  patch[7] = p.oscillators[1]['option']
  
  op = p.oscillators[0]['option']
  if op == 'OP_SUM':
    patch[8] = p.mix_balance
    patch[9] = 0
    patch[10] = 0
    patch[14] = 0
    patch[15] = 0
  elif op == 'OP_SYNC':
    patch[8] = p.mix_balance
    patch[9] = 1
    patch[10] = 0
    patch[14] = 0
    patch[15] = 0
  elif op == 'OP_RING_MOD':
    patch[8] = 0
    patch[9] = 2
    patch[10] = p.mix_balance
    patch[14] = 0
    patch[15] = 0
  elif op == 'OP_XOR':
    patch[8] = 31
    patch[9] = 3
    patch[10] = 63
    patch[14] = 0
    patch[15] = 0
  elif op == 'OP_FUZZ':
    patch[8] = 31
    patch[9] = 0
    patch[10] = 0
    patch[14] = p.mix_balance
    patch[15] = 0
  elif op == 'OP_CRUSH_4':
    patch[8] = p.mix_balance
    patch[9] = 0
    patch[10] = 0
    patch[14] = 0
    patch[15] = 4
  elif op == 'OP_CRUSH_8':
    patch[8] = p.mix_balance
    patch[9] = 0
    patch[10] = 0
    patch[14] = 0
    patch[15] = 8
  elif op == 'OP_FOLD':
    patch[8] = 31
    patch[9] = 4
    patch[10] = p.mix_balance
    patch[14] = 0
    patch[15] = 0
  elif op == 'OP_BITS':
    patch[8] = 31
    patch[9] = 5
    patch[10] = p.mix_balance
    patch[14] = 0
    patch[15] = 0
  elif op == 'OP_PING_PONG_2':
    patch[8] = p.mix_balance
    patch[9] = 0
    patch[10] = 0
    patch[14] = 0
    patch[15] = 0

  patch[11] = p.mix_sub_osc_shape
  patch[12] = p.mix_sub_osc
  patch[13] = p.mix_noise
  patch[16] = p.filter_cutoff
  patch[17] = p.filter_resonance
  patch[18] = 0
  patch[19] = 0
  patch[20] = 0
  patch[21] = 0
  patch[22] = p.filter_env
  patch[23] = p.filter_lfo
  
  patch[24] = 0
  patch[25] = 40
  patch[26] = 80
  patch[27] = 40
  patch[28] = p.lfo[0]['waveform']
  patch[29] = p.lfo[0]['rate']
  patch[30] = p.lfo[0]['attack']
  patch[31] = p.lfo[0]['retrigger_mode']

  patch[32] = p.env[0]['attack']
  patch[33] = p.env[0]['decay']
  patch[34] = p.env[0]['sustain']
  patch[35] = p.env[0]['release']
  patch[36] = p.lfo[1]['waveform']
  patch[37] = p.lfo[1]['rate']
  patch[38] = p.lfo[1]['attack']
  patch[39] = p.lfo[1]['retrigger_mode']

  patch[40] = p.env[1]['attack']
  patch[41] = p.env[1]['decay']
  patch[42] = p.env[1]['sustain']
  patch[43] = p.env[1]['release']
  patch[44] = 0
  patch[45] = 63
  patch[46] = 0
  patch[47] = 0
  
  patch[48] = 0
  patch[49] = p.lfo[0]['rate']
  
  for i in xrange(14):
    modulation = {
        'source': 'MOD_SRC_LFO_1',
        'destination': 'MOD_DST_FILTER_CUTOFF',
        'amount': 0}
    if i < 6:
      modulation = p.modulations[i]
    if i >= 8:
      modulation = p.modulations[i - 2]
    
    if modulation['source'] not in AMBIKA_MODULATION_SOURCE:
      modulation['source'] = 'MOD_SRC_LFO_1'
      modulation['amount'] = 0
    
    patch[50 + i * 3] = AMBIKA_MODULATION_SOURCE[modulation['source']]
    patch[51 + i * 3] = AMBIKA_MODULATION_DESTINATION[modulation['destination']]
    patch[52 + i * 3] = modulation['amount']
  patch[92] = 3
  patch[93] = 4
  patch[94] = 0

  patch[95] = 4
  patch[96] = 5
  patch[97] = 0

  patch[98] = 5
  patch[99] = 6
  patch[100] = 0

  patch[101] = 6
  patch[102] = 7
  patch[103] = 0
  
  return patch


def ParseHexDump(data, name):
  byte_string = [chr(int(data[i:i+2], 16)) for i in xrange(0, len(data), 2)]
  byte_string = ''.join(byte_string)
  byte_string = byte_string.replace('$NAME___', (name.strip() + (' ' * 8))[:8])
  return map(ord, byte_string)


def SaveAmbikaProgram(f, patch_data, part_data, name):
  f.write('RIFF')
  assert len(patch_data) == 112
  assert len(part_data) == 84
  payload_size = 4 + 24 + len(patch_data) + 12 + len(part_data) + 12
  f.write(struct.pack('<L', payload_size))
  f.write('MBKS')
  
  f.write('name')
  f.write(struct.pack('<L', 16))
  f.write(name + ' ' * (15 - len(name)))
  f.write('\x00')
  
  f.write('obj ')
  f.write(struct.pack('<L', 4 + len(patch_data)))
  f.write(struct.pack('<L', 1))
  f.write(''.join(map(chr, patch_data)))

  f.write('obj ')
  f.write(struct.pack('<L', 4 + len(part_data)))
  f.write(struct.pack('<L', 5))
  f.write(''.join(map(chr, part_data)))


def main(options, args):
  program_number = 0
  for line in file(args[0]):
    tokens = line.strip().split('\t')
    if not tokens or not tokens[0] or tokens[0].startswith('#'):
      continue
    kind = tokens[0]
    
    if kind != 'patch':
      continue

    name = tokens[1]
    data = ParseHexDump('\t'.join(tokens[2:]), name)
    
    patch = BuildAmbikaPatch(ShruthiPatch(data))
    SaveAmbikaProgram(
        file('controller/data/programs2/%03d.PRO' % program_number, 'wb'),
        patch,
        DEFAULT_AMBIKA_PART_DATA,
        name)
    program_number += 1


if __name__ == '__main__':
  parser = optparse.OptionParser()
  options, args = parser.parse_args()
  if len(args) != 1:
    logging.fatal('Specify a source file')
  else:
    main(options, args)
