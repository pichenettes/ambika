// Copyright 2009 Olivier Gillet.
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
// Resources definitions.
//
// Automatically generated with:
// make resources


#ifndef CONTROLLER_RESOURCES_H_
#define CONTROLLER_RESOURCES_H_


#include "avrlib/base.h"

#include <avr/pgmspace.h>


#include "avrlib/resources_manager.h"

namespace ambika {

typedef uint16_t ResourceId;

extern const prog_char* string_table[];

extern const prog_uint16_t* lookup_table_table[];

extern const prog_uint8_t* character_table[];

extern const prog_uint8_t* waveform_table[];

extern const prog_uint16_t lut_res_lfo_increments[] PROGMEM;
extern const prog_uint16_t lut_res_scale_just[] PROGMEM;
extern const prog_uint16_t lut_res_scale_pythagorean[] PROGMEM;
extern const prog_uint16_t lut_res_scale_1_4_eb[] PROGMEM;
extern const prog_uint16_t lut_res_scale_1_4_e[] PROGMEM;
extern const prog_uint16_t lut_res_scale_1_4_ea[] PROGMEM;
extern const prog_uint16_t lut_res_scale_bhairav[] PROGMEM;
extern const prog_uint16_t lut_res_scale_gunakri[] PROGMEM;
extern const prog_uint16_t lut_res_scale_marwa[] PROGMEM;
extern const prog_uint16_t lut_res_scale_shree[] PROGMEM;
extern const prog_uint16_t lut_res_scale_purvi[] PROGMEM;
extern const prog_uint16_t lut_res_scale_bilawal[] PROGMEM;
extern const prog_uint16_t lut_res_scale_yaman[] PROGMEM;
extern const prog_uint16_t lut_res_scale_kafi[] PROGMEM;
extern const prog_uint16_t lut_res_scale_bhimpalasree[] PROGMEM;
extern const prog_uint16_t lut_res_scale_darbari[] PROGMEM;
extern const prog_uint16_t lut_res_scale_rageshree[] PROGMEM;
extern const prog_uint16_t lut_res_scale_khamaj[] PROGMEM;
extern const prog_uint16_t lut_res_scale_mimal[] PROGMEM;
extern const prog_uint16_t lut_res_scale_parameshwari[] PROGMEM;
extern const prog_uint16_t lut_res_scale_rangeshwari[] PROGMEM;
extern const prog_uint16_t lut_res_scale_gangeshwari[] PROGMEM;
extern const prog_uint16_t lut_res_scale_kameshwari[] PROGMEM;
extern const prog_uint16_t lut_res_scale_pa__kafi[] PROGMEM;
extern const prog_uint16_t lut_res_scale_natbhairav[] PROGMEM;
extern const prog_uint16_t lut_res_scale_m_kauns[] PROGMEM;
extern const prog_uint16_t lut_res_scale_bairagi[] PROGMEM;
extern const prog_uint16_t lut_res_scale_b_todi[] PROGMEM;
extern const prog_uint16_t lut_res_scale_chandradeep[] PROGMEM;
extern const prog_uint16_t lut_res_scale_kaushik_todi[] PROGMEM;
extern const prog_uint16_t lut_res_scale_jogeshwari[] PROGMEM;
extern const prog_uint16_t lut_res_arpeggiator_patterns[] PROGMEM;
extern const prog_uint16_t lut_res_groove_swing[] PROGMEM;
extern const prog_uint16_t lut_res_groove_shuffle[] PROGMEM;
extern const prog_uint16_t lut_res_groove_push[] PROGMEM;
extern const prog_uint16_t lut_res_groove_lag[] PROGMEM;
extern const prog_uint16_t lut_res_groove_human[] PROGMEM;
extern const prog_uint16_t lut_res_groove_monkey[] PROGMEM;
extern const prog_uint8_t chr_res_special_characters[] PROGMEM;
extern const prog_uint8_t wav_res_lfo_waveforms[] PROGMEM;
#define STR_RES_WAVEFORM 0  // waveform
#define STR_RES_PARAMETER 1  // parameter
#define STR_RES_RANGE 2  // range
#define STR_RES_TUNE 3  // tune
#define STR_RES_OSC_MIX 4  // osc mix
#define STR_RES_SUB_OSC_ 5  // sub osc.
#define STR_RES_CROSSMOD_ 6  // crossmod.
#define STR_RES_OPERATOR 7  // operator
#define STR_RES_AMOUNT 8  // amount
#define STR_RES_RESONANCE 9  // resonance
#define STR_RES_MODE 10  // mode
#define STR_RES_ENV2TVCF 11  // env2~vcf
#define STR_RES_LFO2TVCF 12  // lfo2~vcf
#define STR_RES_ATTACK 13  // attack
#define STR_RES_DECAY 14  // decay
#define STR_RES_SUSTAIN 15  // sustain
#define STR_RES_RELEASE 16  // release
#define STR_RES_TRIGGER 17  // trigger
#define STR_RES_RATE 18  // rate
#define STR_RES_LFO_EG 19  // lfo/eg
#define STR_RES_VOICE_LFO 20  // voice lfo
#define STR_RES_SOURCE 21  // source
#define STR_RES_DESTINATION 22  // destination
#define STR_RES_IN1 23  // in1
#define STR_RES_IN2 24  // in2
#define STR_RES_MODULATION 25  // modulation
#define STR_RES_MODUL_ 26  // modul.
#define STR_RES__MODULATION 27  // modulation
#define STR_RES_MODIFIER 28  // modifier
#define STR_RES_MODIF_ 29  // modif.
#define STR_RES_VOLUME 30  // volume
#define STR_RES_OCTAVE 31  // octave
#define STR_RES_SPREAD 32  // spread
#define STR_RES_LEGATO 33  // legato
#define STR_RES_PORTAMENTO 34  // portamento
#define STR_RES_ARP_SEQ 35  // arp/seq
#define STR_RES_RAGA 36  // raga
#define STR_RES_DIRECTION 37  // direction
#define STR_RES_PATTERN 38  // pattern
#define STR_RES_CHANNEL 39  // channel
#define STR_RES_PART 40  // part
#define STR_RES_BPM 41  // bpm
#define STR_RES_LTCH 42  // ltch
#define STR_RES_LATCH 43  // latch
#define STR_RES_LOW 44  // low
#define STR_RES_HIGH 45  // high
#define STR_RES_GRID 46  // grid
#define STR_RES_SEQ1_LEN 47  // seq1 len
#define STR_RES_SEQ2_LEN 48  // seq2 len
#define STR_RES_PATT_LEN 49  // patt len
#define STR_RES_LEN1 50  // len1
#define STR_RES_LEN2 51  // len2
#define STR_RES_LENP 52  // lenp
#define STR_RES_GROOVE 53  // groove
#define STR_RES_MIDI 54  // midi
#define STR_RES_SNAP 55  // snap
#define STR_RES_HELP 56  // help
#define STR_RES_AUTO_BACKUP 57  // auto backup
#define STR_RES_LEDS 58  // leds
#define STR_RES_CARD_LEDS 59  // card leds
#define STR_RES_SWAP_COLORS 60  // swap colors
#define STR_RES_INPT_FILTER 61  // inpt filter
#define STR_RES_OUTP_MODE 62  // outp mode
#define STR_RES_EXT 63  // ext
#define STR_RES_OMNI 64  // omni
#define STR_RES_AMNT 65  // amnt
#define STR_RES_SRCE 66  // srce
#define STR_RES_OCT 67  // oct
#define STR_RES_SPRD 68  // sprd
#define STR_RES_A_SQ 69  // a/sq
#define STR_RES_OCTV 70  // octv
#define STR_RES_OFF 71  // off
#define STR_RES_ON 72  // on
#define STR_RES_NONE 73  // none
#define STR_RES_SAW 74  // saw
#define STR_RES_SQUARE 75  // square
#define STR_RES_TRIANGLE 76  // triangle
#define STR_RES_SINE 77  // sine
#define STR_RES_ZSAW 78  // zsaw
#define STR_RES_LPZSAW 79  // lpzsaw
#define STR_RES_PKZSAW 80  // pkzsaw
#define STR_RES_BPZSAW 81  // bpzsaw
#define STR_RES_HPZSAW 82  // hpzsaw
#define STR_RES_LPZPULSE 83  // lpzpulse
#define STR_RES_PKZPULSE 84  // pkzpulse
#define STR_RES_BPZPULSE 85  // bpzpulse
#define STR_RES_HPZPULSE 86  // hpzpulse
#define STR_RES_ZTRIANGLE 87  // ztriangle
#define STR_RES_PAD 88  // pad
#define STR_RES_FM 89  // fm
#define STR_RES_8BITS 90  // 8bits
#define STR_RES_PWM 91  // pwm
#define STR_RES_NOISE 92  // noise
#define STR_RES_VOWEL 93  // vowel
#define STR_RES_MALE 94  // male
#define STR_RES_FEMALE 95  // female
#define STR_RES_CHOIR 96  // choir
#define STR_RES_TAMPURA 97  // tampura
#define STR_RES_BOWED 98  // bowed
#define STR_RES_CELLO 99  // cello
#define STR_RES_VIBES 100  // vibes
#define STR_RES_SLAP 101  // slap
#define STR_RES_EPIANO 102  // epiano
#define STR_RES_ORGAN 103  // organ
#define STR_RES_WAVES 104  // waves
#define STR_RES_DIGITAL 105  // digital
#define STR_RES_DRONE_1 106  // drone 1
#define STR_RES_DRONE_2 107  // drone 2
#define STR_RES_METALLIC 108  // metallic
#define STR_RES_BELL 109  // bell
#define STR_RES_WAVQUENCE 110  // wavquence
#define STR_RES_TRI 111  // tri
#define STR_RES_SQR 112  // sqr
#define STR_RES_S_H 113  // s&h
#define STR_RES_RAMP 114  // ramp
#define STR_RES__SINE 115  // sine
#define STR_RES_HRM2 116  // hrm2
#define STR_RES_HRM3 117  // hrm3
#define STR_RES_HRM5 118  // hrm5
#define STR_RES_GRG1 119  // grg1
#define STR_RES_GRG2 120  // grg2
#define STR_RES_BAT1 121  // bat1
#define STR_RES_BAT2 122  // bat2
#define STR_RES_SPK1 123  // spk1
#define STR_RES_SPK2 124  // spk2
#define STR_RES_LSAW 125  // lsaw
#define STR_RES_LSQR 126  // lsqr
#define STR_RES_RSAW 127  // rsaw
#define STR_RES_RSQR 128  // rsqr
#define STR_RES_STP1 129  // stp1
#define STR_RES_STP2 130  // stp2
#define STR_RES___OFF 131  // off
#define STR_RES_SYNC 132  // sync
#define STR_RES_RINGMOD 133  // ringmod
#define STR_RES_XOR 134  // xor
#define STR_RES_FOLD 135  // fold
#define STR_RES_BITS 136  // bits
#define STR_RES_SQU1 137  // squ1
#define STR_RES_TRI1 138  // tri1
#define STR_RES_PUL1 139  // pul1
#define STR_RES_SQU2 140  // squ2
#define STR_RES_TRI2 141  // tri2
#define STR_RES_PUL2 142  // pul2
#define STR_RES_CLICK 143  // click
#define STR_RES_GLITCH 144  // glitch
#define STR_RES_BLOW 145  // blow
#define STR_RES_METAL 146  // metal
#define STR_RES_POP 147  // pop
#define STR_RES_ENV1 148  // env1
#define STR_RES_ENV2 149  // env2
#define STR_RES_ENV3 150  // env3
#define STR_RES_LFO1 151  // lfo1
#define STR_RES_LFO2 152  // lfo2
#define STR_RES_LFO3 153  // lfo3
#define STR_RES_LFO4 154  // lfo4
#define STR_RES_MOD1 155  // mod1
#define STR_RES_MOD2 156  // mod2
#define STR_RES_MOD3 157  // mod3
#define STR_RES_MOD4 158  // mod4
#define STR_RES_SEQ1 159  // seq1
#define STR_RES_SEQ2 160  // seq2
#define STR_RES_ARP 161  // arp
#define STR_RES_VELO 162  // velo
#define STR_RES_AFTR 163  // aftr
#define STR_RES_BEND 164  // bend
#define STR_RES_MWHL 165  // mwhl
#define STR_RES_WHL2 166  // whl2
#define STR_RES_PDAL 167  // pdal
#define STR_RES_NOTE 168  // note
#define STR_RES_GATE 169  // gate
#define STR_RES_NOIS 170  // nois
#define STR_RES_RAND 171  // rand
#define STR_RES_E256 172  // =256
#define STR_RES_E128 173  // =128
#define STR_RES_E64 174  // =64
#define STR_RES_E32 175  // =32
#define STR_RES_E16 176  // =16
#define STR_RES_E8 177  // =8
#define STR_RES_E4 178  // =4
#define STR_RES_PRM1 179  // prm1
#define STR_RES_PRM2 180  // prm2
#define STR_RES_OSC1 181  // osc1
#define STR_RES_OSC2 182  // osc2
#define STR_RES_31S2 183  // 1+2
#define STR_RES_VIBR 184  // vibr
#define STR_RES_MIX 185  // mix
#define STR_RES_XMOD 186  // xmod
#define STR_RES__NOIS 187  // nois
#define STR_RES_SUB 188  // sub
#define STR_RES_FUZZ 189  // fuzz
#define STR_RES_CRSH 190  // crsh
#define STR_RES_FREQ 191  // freq
#define STR_RES_RESO 192  // reso
#define STR_RES_ATTK 193  // attk
#define STR_RES_DECA 194  // deca
#define STR_RES_RELE 195  // rele
#define STR_RES__LFO4 196  // lfo4
#define STR_RES_VCA 197  // vca
#define STR_RES_ENV_1 198  // env 1
#define STR_RES_ENV_2 199  // env 2
#define STR_RES_ENV_3 200  // env 3
#define STR_RES_LFO_1 201  // lfo 1
#define STR_RES_LFO_2 202  // lfo 2
#define STR_RES_LFO_3 203  // lfo 3
#define STR_RES_LFO_4 204  // lfo 4
#define STR_RES_MOD__1 205  // mod. 1
#define STR_RES_MOD__2 206  // mod. 2
#define STR_RES_MOD__3 207  // mod. 3
#define STR_RES_MOD__4 208  // mod. 4
#define STR_RES_SEQ__1 209  // seq. 1
#define STR_RES_SEQ__2 210  // seq. 2
#define STR_RES__ARP 211  // arp
#define STR_RES__VELO 212  // velo
#define STR_RES_AFTTCH 213  // afttch
#define STR_RES_BENDER 214  // bender
#define STR_RES_MWHEEL 215  // mwheel
#define STR_RES_WHEEL2 216  // wheel2
#define STR_RES_PEDAL 217  // pedal
#define STR_RES__NOTE 218  // note
#define STR_RES__GATE 219  // gate
#define STR_RES__NOISE 220  // noise
#define STR_RES_RANDOM 221  // random
#define STR_RES_E_256 222  // = 256
#define STR_RES_E_32 223  // = 32
#define STR_RES_E_16 224  // = 16
#define STR_RES_E_8 225  // = 8
#define STR_RES_E_4 226  // = 4
#define STR_RES_PARAM_1 227  // param 1
#define STR_RES_PARAM_2 228  // param 2
#define STR_RES_OSC_1 229  // osc 1
#define STR_RES_OSC_2 230  // osc 2
#define STR_RES_OSC_1S2 231  // osc 1+2
#define STR_RES_VIBRATO 232  // vibrato
#define STR_RES__MIX 233  // mix
#define STR_RES__XMOD 234  // xmod
#define STR_RES___NOISE 235  // noise
#define STR_RES_SUBOSC 236  // subosc
#define STR_RES__FUZZ 237  // fuzz
#define STR_RES_CRUSH 238  // crush
#define STR_RES_FREQUENCY 239  // frequency
#define STR_RES__RESO 240  // reso
#define STR_RES__ATTACK 241  // attack
#define STR_RES__DECAY 242  // decay
#define STR_RES__RELEASE 243  // release
#define STR_RES__LFO_4 244  // lfo 4
#define STR_RES__VCA 245  // vca
#define STR_RES_LP 246  // lp
#define STR_RES_BP 247  // bp
#define STR_RES_HP 248  // hp
#define STR_RES_FREE 249  // free
#define STR_RES_ENVTLFO 250  // env~lfo
#define STR_RES_LFOTENV 251  // lfo~env
#define STR_RES_STEP_SEQ 252  // step seq
#define STR_RES_ARPEGGIO 253  // arpeggio
#define STR_RES__PATTERN 254  // pattern
#define STR_RES__OFF 255  // off
#define STR_RES_ADD 256  // add
#define STR_RES_PROD 257  // prod
#define STR_RES_ATTN 258  // attn
#define STR_RES_MAX 259  // max
#define STR_RES_MIN 260  // min
#define STR_RES__XOR 261  // xor
#define STR_RES_GE 262  // >=
#define STR_RES_LE 263  // <=
#define STR_RES_QTZ 264  // qtz
#define STR_RES_LAG 265  // lag
#define STR_RES_MONO 266  // mono
#define STR_RES_POLY 267  // poly
#define STR_RES_2X_UNISON 268  // 2x unison
#define STR_RES_UP 269  // up
#define STR_RES_DOWN 270  // down
#define STR_RES_UP_DOWN 271  // up&down
#define STR_RES_PLAYED 272  // played
#define STR_RES__RANDOM 273  // random
#define STR_RES_CHORD 274  // chord
#define STR_RES_1_1 275  // 1/1
#define STR_RES_3_4 276  // 3/4
#define STR_RES_2_3 277  // 2/3
#define STR_RES_1_2 278  // 1/2
#define STR_RES_3_8 279  // 3/8
#define STR_RES_1_3 280  // 1/3
#define STR_RES_1_4 281  // 1/4
#define STR_RES_1_6 282  // 1/6
#define STR_RES_1_8 283  // 1/8
#define STR_RES_1_12 284  // 1/12
#define STR_RES_1_16 285  // 1/16
#define STR_RES_1_24 286  // 1/24
#define STR_RES_1_32 287  // 1/32
#define STR_RES_1_48 288  // 1/48
#define STR_RES_1_96 289  // 1/96
#define STR_RES_THRU 290  // thru
#define STR_RES_SEQUENCER 291  // sequencer
#define STR_RES_CONTROLLR 292  // controllr
#define STR_RES_FULL 293  // full
#define STR_RES_____ 294  // ....
#define STR_RES____S 295  // ...s
#define STR_RES___P_ 296  // ..p.
#define STR_RES___PS 297  // ..ps
#define STR_RES__N__ 298  // .n..
#define STR_RES__N_S 299  // .n.s
#define STR_RES__NP_ 300  // .np.
#define STR_RES__NPS 301  // .nps
#define STR_RES_C___ 302  // c...
#define STR_RES_C__S 303  // c..s
#define STR_RES_C_P_ 304  // c.p.
#define STR_RES_C_PS 305  // c.ps
#define STR_RES_CN__ 306  // cn..
#define STR_RES_CN_S 307  // cn.s
#define STR_RES_CNP_ 308  // cnp.
#define STR_RES_CNPS 309  // cnps
#define STR_RES_SWING 310  // swing
#define STR_RES_SHUFFLE 311  // shuffle
#define STR_RES_PUSH 312  // push
#define STR_RES__LAG 313  // lag
#define STR_RES_HUMAN 314  // human
#define STR_RES_MONKEY 315  // monkey
#define STR_RES_OSCILLATOR_1 316  // oscillator 1
#define STR_RES_OSCILLATOR_2 317  // oscillator 2
#define STR_RES_MIXER 318  // mixer
#define STR_RES_LFO 319  // lfo
#define STR_RES_FILTER_1 320  // filter 1
#define STR_RES_FILTER_2 321  // filter 2
#define STR_RES_ENVELOPE 322  // envelope
#define STR_RES_ARPEGGIATOR 323  // arpeggiator
#define STR_RES_MULTI 324  // multi
#define STR_RES_CLOCK 325  // clock
#define STR_RES_PERFORMANCE 326  // performance
#define STR_RES_SYSTEM 327  // system
#define STR_RES_PT_X_PATCH 328  // pt X patch
#define STR_RES_PT_X_SEQUENCE 329  // pt X sequence
#define STR_RES_PT_X_PROGRAM 330  // pt X program
#define STR_RES_RANDOMIZE 331  // randomize
#define STR_RES_INIT 332  // init
#define STR_RES_PATCH 333  // PATCH
#define STR_RES_SEQUENCE 334  // SEQUENCE
#define STR_RES_PROGRAM 335  // PROGRAM
#define STR_RES__MULTI 336  // MULTI
#define STR_RES____ 337  // ___
#define STR_RES_EQUAL 338  // equal
#define STR_RES_JUST 339  // just
#define STR_RES_PYTHAGOREAN 340  // pythagorean
#define STR_RES_1_4_EB 341  // 1/4 eb
#define STR_RES_1_4_E 342  // 1/4 e
#define STR_RES_1_4_EA 343  // 1/4 ea
#define STR_RES_BHAIRAV 344  // bhairav
#define STR_RES_GUNAKRI 345  // gunakri
#define STR_RES_MARWA 346  // marwa
#define STR_RES_SHREE 347  // shree
#define STR_RES_PURVI 348  // purvi
#define STR_RES_BILAWAL 349  // bilawal
#define STR_RES_YAMAN 350  // yaman
#define STR_RES_KAFI 351  // kafi
#define STR_RES_BHIMPALASREE 352  // bhimpalasree
#define STR_RES_DARBARI 353  // darbari
#define STR_RES_BAGESHREE 354  // bageshree
#define STR_RES_RAGESHREE 355  // rageshree
#define STR_RES_KHAMAJ 356  // khamaj
#define STR_RES_MIMAL 357  // mi'mal
#define STR_RES_PARAMESHWARI 358  // parameshwari
#define STR_RES_RANGESHWARI 359  // rangeshwari
#define STR_RES_GANGESHWARI 360  // gangeshwari
#define STR_RES_KAMESHWARI 361  // kameshwari
#define STR_RES_PA__KAFI 362  // pa. kafi
#define STR_RES_NATBHAIRAV 363  // natbhairav
#define STR_RES_M_KAUNS 364  // m.kauns
#define STR_RES_BAIRAGI 365  // bairagi
#define STR_RES_B_TODI 366  // b.todi
#define STR_RES_CHANDRADEEP 367  // chandradeep
#define STR_RES_KAUSHIK_TODI 368  // kaushik todi
#define STR_RES_JOGESHWARI 369  // jogeshwari
#define STR_RES_RASIA 370  // rasia
#define LUT_RES_LFO_INCREMENTS 0
#define LUT_RES_LFO_INCREMENTS_SIZE 128
#define LUT_RES_SCALE_JUST 1
#define LUT_RES_SCALE_JUST_SIZE 12
#define LUT_RES_SCALE_PYTHAGOREAN 2
#define LUT_RES_SCALE_PYTHAGOREAN_SIZE 12
#define LUT_RES_SCALE_1_4_EB 3
#define LUT_RES_SCALE_1_4_EB_SIZE 12
#define LUT_RES_SCALE_1_4_E 4
#define LUT_RES_SCALE_1_4_E_SIZE 12
#define LUT_RES_SCALE_1_4_EA 5
#define LUT_RES_SCALE_1_4_EA_SIZE 12
#define LUT_RES_SCALE_BHAIRAV 6
#define LUT_RES_SCALE_BHAIRAV_SIZE 12
#define LUT_RES_SCALE_GUNAKRI 7
#define LUT_RES_SCALE_GUNAKRI_SIZE 12
#define LUT_RES_SCALE_MARWA 8
#define LUT_RES_SCALE_MARWA_SIZE 12
#define LUT_RES_SCALE_SHREE 9
#define LUT_RES_SCALE_SHREE_SIZE 12
#define LUT_RES_SCALE_PURVI 10
#define LUT_RES_SCALE_PURVI_SIZE 12
#define LUT_RES_SCALE_BILAWAL 11
#define LUT_RES_SCALE_BILAWAL_SIZE 12
#define LUT_RES_SCALE_YAMAN 12
#define LUT_RES_SCALE_YAMAN_SIZE 12
#define LUT_RES_SCALE_KAFI 13
#define LUT_RES_SCALE_KAFI_SIZE 12
#define LUT_RES_SCALE_BHIMPALASREE 14
#define LUT_RES_SCALE_BHIMPALASREE_SIZE 12
#define LUT_RES_SCALE_DARBARI 15
#define LUT_RES_SCALE_DARBARI_SIZE 12
#define LUT_RES_SCALE_BAGESHREE 16
#define LUT_RES_SCALE_BAGESHREE_SIZE 12
#define LUT_RES_SCALE_RAGESHREE 17
#define LUT_RES_SCALE_RAGESHREE_SIZE 12
#define LUT_RES_SCALE_KHAMAJ 18
#define LUT_RES_SCALE_KHAMAJ_SIZE 12
#define LUT_RES_SCALE_MIMAL 19
#define LUT_RES_SCALE_MIMAL_SIZE 12
#define LUT_RES_SCALE_PARAMESHWARI 20
#define LUT_RES_SCALE_PARAMESHWARI_SIZE 12
#define LUT_RES_SCALE_RANGESHWARI 21
#define LUT_RES_SCALE_RANGESHWARI_SIZE 12
#define LUT_RES_SCALE_GANGESHWARI 22
#define LUT_RES_SCALE_GANGESHWARI_SIZE 12
#define LUT_RES_SCALE_KAMESHWARI 23
#define LUT_RES_SCALE_KAMESHWARI_SIZE 12
#define LUT_RES_SCALE_PA__KAFI 24
#define LUT_RES_SCALE_PA__KAFI_SIZE 12
#define LUT_RES_SCALE_NATBHAIRAV 25
#define LUT_RES_SCALE_NATBHAIRAV_SIZE 12
#define LUT_RES_SCALE_M_KAUNS 26
#define LUT_RES_SCALE_M_KAUNS_SIZE 12
#define LUT_RES_SCALE_BAIRAGI 27
#define LUT_RES_SCALE_BAIRAGI_SIZE 12
#define LUT_RES_SCALE_B_TODI 28
#define LUT_RES_SCALE_B_TODI_SIZE 12
#define LUT_RES_SCALE_CHANDRADEEP 29
#define LUT_RES_SCALE_CHANDRADEEP_SIZE 12
#define LUT_RES_SCALE_KAUSHIK_TODI 30
#define LUT_RES_SCALE_KAUSHIK_TODI_SIZE 12
#define LUT_RES_SCALE_JOGESHWARI 31
#define LUT_RES_SCALE_JOGESHWARI_SIZE 12
#define LUT_RES_SCALE_RASIA 32
#define LUT_RES_SCALE_RASIA_SIZE 12
#define LUT_RES_ARPEGGIATOR_PATTERNS 33
#define LUT_RES_ARPEGGIATOR_PATTERNS_SIZE 22
#define LUT_RES_GROOVE_SWING 34
#define LUT_RES_GROOVE_SWING_SIZE 16
#define LUT_RES_GROOVE_SHUFFLE 35
#define LUT_RES_GROOVE_SHUFFLE_SIZE 16
#define LUT_RES_GROOVE_PUSH 36
#define LUT_RES_GROOVE_PUSH_SIZE 16
#define LUT_RES_GROOVE_LAG 37
#define LUT_RES_GROOVE_LAG_SIZE 16
#define LUT_RES_GROOVE_HUMAN 38
#define LUT_RES_GROOVE_HUMAN_SIZE 16
#define LUT_RES_GROOVE_MONKEY 39
#define LUT_RES_GROOVE_MONKEY_SIZE 16
#define CHR_RES_SPECIAL_CHARACTERS 0
#define CHR_RES_SPECIAL_CHARACTERS_SIZE 56
#define WAV_RES_LFO_WAVEFORMS 0
#define WAV_RES_LFO_WAVEFORMS_SIZE 4112
typedef avrlib::ResourcesManager<
    ResourceId,
    avrlib::ResourcesTables<
        string_table,
        lookup_table_table> > ResourcesManager; 

}  // namespace ambika

#endif  // CONTROLLER_RESOURCES_H_
