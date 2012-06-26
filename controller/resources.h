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
#define STR_RES_INPT_FILTER 60  // inpt filter
#define STR_RES_OUTP_MODE 61  // outp mode
#define STR_RES_EXT 62  // ext
#define STR_RES_OMNI 63  // omni
#define STR_RES_AMNT 64  // amnt
#define STR_RES_SRCE 65  // srce
#define STR_RES_OCT 66  // oct
#define STR_RES_SPRD 67  // sprd
#define STR_RES_A_SQ 68  // a/sq
#define STR_RES_OCTV 69  // octv
#define STR_RES_OFF 70  // off
#define STR_RES_ON 71  // on
#define STR_RES_NONE 72  // none
#define STR_RES_SAW 73  // saw
#define STR_RES_SQUARE 74  // square
#define STR_RES_TRIANGLE 75  // triangle
#define STR_RES_SINE 76  // sine
#define STR_RES_ZSAW 77  // zsaw
#define STR_RES_LPZSAW 78  // lpzsaw
#define STR_RES_PKZSAW 79  // pkzsaw
#define STR_RES_BPZSAW 80  // bpzsaw
#define STR_RES_HPZSAW 81  // hpzsaw
#define STR_RES_LPZPULSE 82  // lpzpulse
#define STR_RES_PKZPULSE 83  // pkzpulse
#define STR_RES_BPZPULSE 84  // bpzpulse
#define STR_RES_HPZPULSE 85  // hpzpulse
#define STR_RES_ZTRIANGLE 86  // ztriangle
#define STR_RES_PAD 87  // pad
#define STR_RES_FM 88  // fm
#define STR_RES_8BITS 89  // 8bits
#define STR_RES_PWM 90  // pwm
#define STR_RES_NOISE 91  // noise
#define STR_RES_VOWEL 92  // vowel
#define STR_RES_MALE 93  // male
#define STR_RES_FEMALE 94  // female
#define STR_RES_CHOIR 95  // choir
#define STR_RES_TAMPURA 96  // tampura
#define STR_RES_BOWED 97  // bowed
#define STR_RES_CELLO 98  // cello
#define STR_RES_VIBES 99  // vibes
#define STR_RES_SLAP 100  // slap
#define STR_RES_EPIANO 101  // epiano
#define STR_RES_ORGAN 102  // organ
#define STR_RES_WAVES 103  // waves
#define STR_RES_DIGITAL 104  // digital
#define STR_RES_DRONE_1 105  // drone 1
#define STR_RES_DRONE_2 106  // drone 2
#define STR_RES_METALLIC 107  // metallic
#define STR_RES_BELL 108  // bell
#define STR_RES_WAVQUENCE 109  // wavquence
#define STR_RES_TRI 110  // tri
#define STR_RES_SQR 111  // sqr
#define STR_RES_S_H 112  // s&h
#define STR_RES_RAMP 113  // ramp
#define STR_RES__SINE 114  // sine
#define STR_RES_HRM2 115  // hrm2
#define STR_RES_HRM3 116  // hrm3
#define STR_RES_HRM5 117  // hrm5
#define STR_RES_GRG1 118  // grg1
#define STR_RES_GRG2 119  // grg2
#define STR_RES_BAT1 120  // bat1
#define STR_RES_BAT2 121  // bat2
#define STR_RES_SPK1 122  // spk1
#define STR_RES_SPK2 123  // spk2
#define STR_RES_LSAW 124  // lsaw
#define STR_RES_LSQR 125  // lsqr
#define STR_RES_RSAW 126  // rsaw
#define STR_RES_RSQR 127  // rsqr
#define STR_RES_STP1 128  // stp1
#define STR_RES_STP2 129  // stp2
#define STR_RES___OFF 130  // off
#define STR_RES_SYNC 131  // sync
#define STR_RES_RINGMOD 132  // ringmod
#define STR_RES_XOR 133  // xor
#define STR_RES_FOLD 134  // fold
#define STR_RES_BITS 135  // bits
#define STR_RES_SQU1 136  // squ1
#define STR_RES_TRI1 137  // tri1
#define STR_RES_PUL1 138  // pul1
#define STR_RES_SQU2 139  // squ2
#define STR_RES_TRI2 140  // tri2
#define STR_RES_PUL2 141  // pul2
#define STR_RES_CLICK 142  // click
#define STR_RES_GLITCH 143  // glitch
#define STR_RES_BLOW 144  // blow
#define STR_RES_METAL 145  // metal
#define STR_RES_POP 146  // pop
#define STR_RES_ENV1 147  // env1
#define STR_RES_ENV2 148  // env2
#define STR_RES_ENV3 149  // env3
#define STR_RES_LFO1 150  // lfo1
#define STR_RES_LFO2 151  // lfo2
#define STR_RES_LFO3 152  // lfo3
#define STR_RES_LFO4 153  // lfo4
#define STR_RES_MOD1 154  // mod1
#define STR_RES_MOD2 155  // mod2
#define STR_RES_MOD3 156  // mod3
#define STR_RES_MOD4 157  // mod4
#define STR_RES_SEQ1 158  // seq1
#define STR_RES_SEQ2 159  // seq2
#define STR_RES_ARP 160  // arp
#define STR_RES_VELO 161  // velo
#define STR_RES_AFTR 162  // aftr
#define STR_RES_BEND 163  // bend
#define STR_RES_MWHL 164  // mwhl
#define STR_RES_WHL2 165  // whl2
#define STR_RES_PDAL 166  // pdal
#define STR_RES_NOTE 167  // note
#define STR_RES_GATE 168  // gate
#define STR_RES_NOIS 169  // nois
#define STR_RES_RAND 170  // rand
#define STR_RES_E256 171  // =256
#define STR_RES_E128 172  // =128
#define STR_RES_E64 173  // =64
#define STR_RES_E32 174  // =32
#define STR_RES_E16 175  // =16
#define STR_RES_E8 176  // =8
#define STR_RES_E4 177  // =4
#define STR_RES_PRM1 178  // prm1
#define STR_RES_PRM2 179  // prm2
#define STR_RES_OSC1 180  // osc1
#define STR_RES_OSC2 181  // osc2
#define STR_RES_31S2 182  // 1+2
#define STR_RES_VIBR 183  // vibr
#define STR_RES_MIX 184  // mix
#define STR_RES_XMOD 185  // xmod
#define STR_RES__NOIS 186  // nois
#define STR_RES_SUB 187  // sub
#define STR_RES_FUZZ 188  // fuzz
#define STR_RES_CRSH 189  // crsh
#define STR_RES_FREQ 190  // freq
#define STR_RES_RESO 191  // reso
#define STR_RES_ATTK 192  // attk
#define STR_RES_DECA 193  // deca
#define STR_RES_RELE 194  // rele
#define STR_RES__LFO4 195  // lfo4
#define STR_RES_VCA 196  // vca
#define STR_RES_ENV_1 197  // env 1
#define STR_RES_ENV_2 198  // env 2
#define STR_RES_ENV_3 199  // env 3
#define STR_RES_LFO_1 200  // lfo 1
#define STR_RES_LFO_2 201  // lfo 2
#define STR_RES_LFO_3 202  // lfo 3
#define STR_RES_LFO_4 203  // lfo 4
#define STR_RES_MOD__1 204  // mod. 1
#define STR_RES_MOD__2 205  // mod. 2
#define STR_RES_MOD__3 206  // mod. 3
#define STR_RES_MOD__4 207  // mod. 4
#define STR_RES_SEQ__1 208  // seq. 1
#define STR_RES_SEQ__2 209  // seq. 2
#define STR_RES__ARP 210  // arp
#define STR_RES__VELO 211  // velo
#define STR_RES_AFTTCH 212  // afttch
#define STR_RES_BENDER 213  // bender
#define STR_RES_MWHEEL 214  // mwheel
#define STR_RES_WHEEL2 215  // wheel2
#define STR_RES_PEDAL 216  // pedal
#define STR_RES__NOTE 217  // note
#define STR_RES__GATE 218  // gate
#define STR_RES__NOISE 219  // noise
#define STR_RES_RANDOM 220  // random
#define STR_RES_E_256 221  // = 256
#define STR_RES_E_32 222  // = 32
#define STR_RES_E_16 223  // = 16
#define STR_RES_E_8 224  // = 8
#define STR_RES_E_4 225  // = 4
#define STR_RES_PARAM_1 226  // param 1
#define STR_RES_PARAM_2 227  // param 2
#define STR_RES_OSC_1 228  // osc 1
#define STR_RES_OSC_2 229  // osc 2
#define STR_RES_OSC_1S2 230  // osc 1+2
#define STR_RES_VIBRATO 231  // vibrato
#define STR_RES__MIX 232  // mix
#define STR_RES__XMOD 233  // xmod
#define STR_RES___NOISE 234  // noise
#define STR_RES_SUBOSC 235  // subosc
#define STR_RES__FUZZ 236  // fuzz
#define STR_RES_CRUSH 237  // crush
#define STR_RES_FREQUENCY 238  // frequency
#define STR_RES__RESO 239  // reso
#define STR_RES__ATTACK 240  // attack
#define STR_RES__DECAY 241  // decay
#define STR_RES__RELEASE 242  // release
#define STR_RES__LFO_4 243  // lfo 4
#define STR_RES__VCA 244  // vca
#define STR_RES_LP 245  // lp
#define STR_RES_BP 246  // bp
#define STR_RES_HP 247  // hp
#define STR_RES_FREE 248  // free
#define STR_RES_ENVTLFO 249  // env~lfo
#define STR_RES_LFOTENV 250  // lfo~env
#define STR_RES_STEP_SEQ 251  // step seq
#define STR_RES_ARPEGGIO 252  // arpeggio
#define STR_RES__PATTERN 253  // pattern
#define STR_RES__OFF 254  // off
#define STR_RES_ADD 255  // add
#define STR_RES_PROD 256  // prod
#define STR_RES_ATTN 257  // attn
#define STR_RES_MAX 258  // max
#define STR_RES_MIN 259  // min
#define STR_RES__XOR 260  // xor
#define STR_RES_GE 261  // >=
#define STR_RES_LE 262  // <=
#define STR_RES_QTZ 263  // qtz
#define STR_RES_LAG 264  // lag
#define STR_RES_MONO 265  // mono
#define STR_RES_POLY 266  // poly
#define STR_RES_2X_UNISON 267  // 2x unison
#define STR_RES_UP 268  // up
#define STR_RES_DOWN 269  // down
#define STR_RES_UP_DOWN 270  // up&down
#define STR_RES_PLAYED 271  // played
#define STR_RES__RANDOM 272  // random
#define STR_RES_CHORD 273  // chord
#define STR_RES_1_1 274  // 1/1
#define STR_RES_3_4 275  // 3/4
#define STR_RES_2_3 276  // 2/3
#define STR_RES_1_2 277  // 1/2
#define STR_RES_3_8 278  // 3/8
#define STR_RES_1_3 279  // 1/3
#define STR_RES_1_4 280  // 1/4
#define STR_RES_1_6 281  // 1/6
#define STR_RES_1_8 282  // 1/8
#define STR_RES_1_12 283  // 1/12
#define STR_RES_1_16 284  // 1/16
#define STR_RES_1_24 285  // 1/24
#define STR_RES_1_32 286  // 1/32
#define STR_RES_1_48 287  // 1/48
#define STR_RES_1_96 288  // 1/96
#define STR_RES_THRU 289  // thru
#define STR_RES_SEQUENCER 290  // sequencer
#define STR_RES_CONTROLLR 291  // controllr
#define STR_RES_FULL 292  // full
#define STR_RES_____ 293  // ....
#define STR_RES____S 294  // ...s
#define STR_RES___P_ 295  // ..p.
#define STR_RES___PS 296  // ..ps
#define STR_RES__N__ 297  // .n..
#define STR_RES__N_S 298  // .n.s
#define STR_RES__NP_ 299  // .np.
#define STR_RES__NPS 300  // .nps
#define STR_RES_C___ 301  // c...
#define STR_RES_C__S 302  // c..s
#define STR_RES_C_P_ 303  // c.p.
#define STR_RES_C_PS 304  // c.ps
#define STR_RES_CN__ 305  // cn..
#define STR_RES_CN_S 306  // cn.s
#define STR_RES_CNP_ 307  // cnp.
#define STR_RES_CNPS 308  // cnps
#define STR_RES_SWING 309  // swing
#define STR_RES_SHUFFLE 310  // shuffle
#define STR_RES_PUSH 311  // push
#define STR_RES__LAG 312  // lag
#define STR_RES_HUMAN 313  // human
#define STR_RES_MONKEY 314  // monkey
#define STR_RES_OSCILLATOR_1 315  // oscillator 1
#define STR_RES_OSCILLATOR_2 316  // oscillator 2
#define STR_RES_MIXER 317  // mixer
#define STR_RES_LFO 318  // lfo
#define STR_RES_FILTER_1 319  // filter 1
#define STR_RES_FILTER_2 320  // filter 2
#define STR_RES_ENVELOPE 321  // envelope
#define STR_RES_ARPEGGIATOR 322  // arpeggiator
#define STR_RES_MULTI 323  // multi
#define STR_RES_CLOCK 324  // clock
#define STR_RES_PERFORMANCE 325  // performance
#define STR_RES_SYSTEM 326  // system
#define STR_RES_PT_X_PATCH 327  // pt X patch
#define STR_RES_PT_X_SEQUENCE 328  // pt X sequence
#define STR_RES_PT_X_PROGRAM 329  // pt X program
#define STR_RES_RANDOMIZE 330  // randomize
#define STR_RES_INIT 331  // init
#define STR_RES_PATCH 332  // PATCH
#define STR_RES_SEQUENCE 333  // SEQUENCE
#define STR_RES_PROGRAM 334  // PROGRAM
#define STR_RES__MULTI 335  // MULTI
#define STR_RES____ 336  // ___
#define STR_RES_EQUAL 337  // equal
#define STR_RES_JUST 338  // just
#define STR_RES_PYTHAGOREAN 339  // pythagorean
#define STR_RES_1_4_EB 340  // 1/4 eb
#define STR_RES_1_4_E 341  // 1/4 e
#define STR_RES_1_4_EA 342  // 1/4 ea
#define STR_RES_BHAIRAV 343  // bhairav
#define STR_RES_GUNAKRI 344  // gunakri
#define STR_RES_MARWA 345  // marwa
#define STR_RES_SHREE 346  // shree
#define STR_RES_PURVI 347  // purvi
#define STR_RES_BILAWAL 348  // bilawal
#define STR_RES_YAMAN 349  // yaman
#define STR_RES_KAFI 350  // kafi
#define STR_RES_BHIMPALASREE 351  // bhimpalasree
#define STR_RES_DARBARI 352  // darbari
#define STR_RES_BAGESHREE 353  // bageshree
#define STR_RES_RAGESHREE 354  // rageshree
#define STR_RES_KHAMAJ 355  // khamaj
#define STR_RES_MIMAL 356  // mi'mal
#define STR_RES_PARAMESHWARI 357  // parameshwari
#define STR_RES_RANGESHWARI 358  // rangeshwari
#define STR_RES_GANGESHWARI 359  // gangeshwari
#define STR_RES_KAMESHWARI 360  // kameshwari
#define STR_RES_PA__KAFI 361  // pa. kafi
#define STR_RES_NATBHAIRAV 362  // natbhairav
#define STR_RES_M_KAUNS 363  // m.kauns
#define STR_RES_BAIRAGI 364  // bairagi
#define STR_RES_B_TODI 365  // b.todi
#define STR_RES_CHANDRADEEP 366  // chandradeep
#define STR_RES_KAUSHIK_TODI 367  // kaushik todi
#define STR_RES_JOGESHWARI 368  // jogeshwari
#define STR_RES_RASIA 369  // rasia
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
