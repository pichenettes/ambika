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


#include "controller/resources.h"

namespace ambika {

static const prog_char str_res_waveform[] PROGMEM = "waveform";
static const prog_char str_res_parameter[] PROGMEM = "parameter";
static const prog_char str_res_range[] PROGMEM = "range";
static const prog_char str_res_tune[] PROGMEM = "tune";
static const prog_char str_res_osc_mix[] PROGMEM = "osc mix";
static const prog_char str_res_sub_osc_[] PROGMEM = "sub osc.";
static const prog_char str_res_crossmod_[] PROGMEM = "crossmod.";
static const prog_char str_res_operator[] PROGMEM = "operator";
static const prog_char str_res_amount[] PROGMEM = "amount";
static const prog_char str_res_resonance[] PROGMEM = "resonance";
static const prog_char str_res_mode[] PROGMEM = "mode";
static const prog_char str_res_env2Tvcf[] PROGMEM = "env2~vcf";
static const prog_char str_res_lfo2Tvcf[] PROGMEM = "lfo2~vcf";
static const prog_char str_res_attack[] PROGMEM = "attack";
static const prog_char str_res_decay[] PROGMEM = "decay";
static const prog_char str_res_sustain[] PROGMEM = "sustain";
static const prog_char str_res_release[] PROGMEM = "release";
static const prog_char str_res_trigger[] PROGMEM = "trigger";
static const prog_char str_res_rate[] PROGMEM = "rate";
static const prog_char str_res_lfo_eg[] PROGMEM = "lfo/eg";
static const prog_char str_res_voice_lfo[] PROGMEM = "voice lfo";
static const prog_char str_res_source[] PROGMEM = "source";
static const prog_char str_res_destination[] PROGMEM = "destination";
static const prog_char str_res_in1[] PROGMEM = "in1";
static const prog_char str_res_in2[] PROGMEM = "in2";
static const prog_char str_res_modulation[] PROGMEM = "modulation";
static const prog_char str_res_modul_[] PROGMEM = "modul.";
static const prog_char str_res_modifier[] PROGMEM = "modifier";
static const prog_char str_res_modif_[] PROGMEM = "modif.";
static const prog_char str_res_volume[] PROGMEM = "volume";
static const prog_char str_res_octave[] PROGMEM = "octave";
static const prog_char str_res_spread[] PROGMEM = "spread";
static const prog_char str_res_legato[] PROGMEM = "legato";
static const prog_char str_res_portamento[] PROGMEM = "portamento";
static const prog_char str_res_arp_seq[] PROGMEM = "arp/seq";
static const prog_char str_res_raga[] PROGMEM = "raga";
static const prog_char str_res_direction[] PROGMEM = "direction";
static const prog_char str_res_pattern[] PROGMEM = "pattern";
static const prog_char str_res_channel[] PROGMEM = "channel";
static const prog_char str_res_part[] PROGMEM = "part";
static const prog_char str_res_bpm[] PROGMEM = "bpm";
static const prog_char str_res_ltch[] PROGMEM = "ltch";
static const prog_char str_res_latch[] PROGMEM = "latch";
static const prog_char str_res_low[] PROGMEM = "low";
static const prog_char str_res_high[] PROGMEM = "high";
static const prog_char str_res_grid[] PROGMEM = "grid";
static const prog_char str_res_seq1_len[] PROGMEM = "seq1 len";
static const prog_char str_res_seq2_len[] PROGMEM = "seq2 len";
static const prog_char str_res_patt_len[] PROGMEM = "patt len";
static const prog_char str_res_len1[] PROGMEM = "len1";
static const prog_char str_res_len2[] PROGMEM = "len2";
static const prog_char str_res_lenp[] PROGMEM = "lenp";
static const prog_char str_res_groove[] PROGMEM = "groove";
static const prog_char str_res_midi[] PROGMEM = "midi";
static const prog_char str_res_snap[] PROGMEM = "snap";
static const prog_char str_res_help[] PROGMEM = "help";
static const prog_char str_res_auto_backup[] PROGMEM = "auto backup";
static const prog_char str_res_leds[] PROGMEM = "leds";
static const prog_char str_res_card_leds[] PROGMEM = "card leds";
static const prog_char str_res_swap_colors[] PROGMEM = "swap colors";
static const prog_char str_res_inpt_filter[] PROGMEM = "inpt filter";
static const prog_char str_res_outp_mode[] PROGMEM = "outp mode";
static const prog_char str_res_ext[] PROGMEM = "ext";
static const prog_char str_res_omni[] PROGMEM = "omni";
static const prog_char str_res_amnt[] PROGMEM = "amnt";
static const prog_char str_res_srce[] PROGMEM = "srce";
static const prog_char str_res_oct[] PROGMEM = "oct";
static const prog_char str_res_sprd[] PROGMEM = "sprd";
static const prog_char str_res_a_sq[] PROGMEM = "a/sq";
static const prog_char str_res_octv[] PROGMEM = "octv";
static const prog_char str_res_off[] PROGMEM = "off";
static const prog_char str_res_on[] PROGMEM = "on";
static const prog_char str_res_none[] PROGMEM = "none";
static const prog_char str_res_saw[] PROGMEM = "saw";
static const prog_char str_res_square[] PROGMEM = "square";
static const prog_char str_res_triangle[] PROGMEM = "triangle";
static const prog_char str_res_sine[] PROGMEM = "sine";
static const prog_char str_res_zsaw[] PROGMEM = "zsaw";
static const prog_char str_res_lpzsaw[] PROGMEM = "lpzsaw";
static const prog_char str_res_pkzsaw[] PROGMEM = "pkzsaw";
static const prog_char str_res_bpzsaw[] PROGMEM = "bpzsaw";
static const prog_char str_res_hpzsaw[] PROGMEM = "hpzsaw";
static const prog_char str_res_lpzpulse[] PROGMEM = "lpzpulse";
static const prog_char str_res_pkzpulse[] PROGMEM = "pkzpulse";
static const prog_char str_res_bpzpulse[] PROGMEM = "bpzpulse";
static const prog_char str_res_hpzpulse[] PROGMEM = "hpzpulse";
static const prog_char str_res_ztriangle[] PROGMEM = "ztriangle";
static const prog_char str_res_pad[] PROGMEM = "pad";
static const prog_char str_res_fm[] PROGMEM = "fm";
static const prog_char str_res_8bits[] PROGMEM = "8bits";
static const prog_char str_res_pwm[] PROGMEM = "pwm";
static const prog_char str_res_noise[] PROGMEM = "noise";
static const prog_char str_res_vowel[] PROGMEM = "vowel";
static const prog_char str_res_male[] PROGMEM = "male";
static const prog_char str_res_female[] PROGMEM = "female";
static const prog_char str_res_choir[] PROGMEM = "choir";
static const prog_char str_res_tampura[] PROGMEM = "tampura";
static const prog_char str_res_bowed[] PROGMEM = "bowed";
static const prog_char str_res_cello[] PROGMEM = "cello";
static const prog_char str_res_vibes[] PROGMEM = "vibes";
static const prog_char str_res_slap[] PROGMEM = "slap";
static const prog_char str_res_epiano[] PROGMEM = "epiano";
static const prog_char str_res_organ[] PROGMEM = "organ";
static const prog_char str_res_waves[] PROGMEM = "waves";
static const prog_char str_res_digital[] PROGMEM = "digital";
static const prog_char str_res_drone_1[] PROGMEM = "drone 1";
static const prog_char str_res_drone_2[] PROGMEM = "drone 2";
static const prog_char str_res_metallic[] PROGMEM = "metallic";
static const prog_char str_res_bell[] PROGMEM = "bell";
static const prog_char str_res_wavquence[] PROGMEM = "wavquence";
static const prog_char str_res_tri[] PROGMEM = "tri";
static const prog_char str_res_sqr[] PROGMEM = "sqr";
static const prog_char str_res_s_h[] PROGMEM = "s&h";
static const prog_char str_res_ramp[] PROGMEM = "ramp";
static const prog_char str_res_hrm2[] PROGMEM = "hrm2";
static const prog_char str_res_hrm3[] PROGMEM = "hrm3";
static const prog_char str_res_hrm5[] PROGMEM = "hrm5";
static const prog_char str_res_grg1[] PROGMEM = "grg1";
static const prog_char str_res_grg2[] PROGMEM = "grg2";
static const prog_char str_res_bat1[] PROGMEM = "bat1";
static const prog_char str_res_bat2[] PROGMEM = "bat2";
static const prog_char str_res_spk1[] PROGMEM = "spk1";
static const prog_char str_res_spk2[] PROGMEM = "spk2";
static const prog_char str_res_lsaw[] PROGMEM = "lsaw";
static const prog_char str_res_lsqr[] PROGMEM = "lsqr";
static const prog_char str_res_rsaw[] PROGMEM = "rsaw";
static const prog_char str_res_rsqr[] PROGMEM = "rsqr";
static const prog_char str_res_stp1[] PROGMEM = "stp1";
static const prog_char str_res_stp2[] PROGMEM = "stp2";
static const prog_char str_res_sync[] PROGMEM = "sync";
static const prog_char str_res_ringmod[] PROGMEM = "ringmod";
static const prog_char str_res_xor[] PROGMEM = "xor";
static const prog_char str_res_fold[] PROGMEM = "fold";
static const prog_char str_res_bits[] PROGMEM = "bits";
static const prog_char str_res_squ1[] PROGMEM = "squ1";
static const prog_char str_res_tri1[] PROGMEM = "tri1";
static const prog_char str_res_pul1[] PROGMEM = "pul1";
static const prog_char str_res_squ2[] PROGMEM = "squ2";
static const prog_char str_res_tri2[] PROGMEM = "tri2";
static const prog_char str_res_pul2[] PROGMEM = "pul2";
static const prog_char str_res_click[] PROGMEM = "click";
static const prog_char str_res_glitch[] PROGMEM = "glitch";
static const prog_char str_res_blow[] PROGMEM = "blow";
static const prog_char str_res_metal[] PROGMEM = "metal";
static const prog_char str_res_pop[] PROGMEM = "pop";
static const prog_char str_res_env1[] PROGMEM = "env1";
static const prog_char str_res_env2[] PROGMEM = "env2";
static const prog_char str_res_env3[] PROGMEM = "env3";
static const prog_char str_res_lfo1[] PROGMEM = "lfo1";
static const prog_char str_res_lfo2[] PROGMEM = "lfo2";
static const prog_char str_res_lfo3[] PROGMEM = "lfo3";
static const prog_char str_res_lfo4[] PROGMEM = "lfo4";
static const prog_char str_res_mod1[] PROGMEM = "mod1";
static const prog_char str_res_mod2[] PROGMEM = "mod2";
static const prog_char str_res_mod3[] PROGMEM = "mod3";
static const prog_char str_res_mod4[] PROGMEM = "mod4";
static const prog_char str_res_seq1[] PROGMEM = "seq1";
static const prog_char str_res_seq2[] PROGMEM = "seq2";
static const prog_char str_res_arp[] PROGMEM = "arp";
static const prog_char str_res_velo[] PROGMEM = "velo";
static const prog_char str_res_aftr[] PROGMEM = "aftr";
static const prog_char str_res_bend[] PROGMEM = "bend";
static const prog_char str_res_mwhl[] PROGMEM = "mwhl";
static const prog_char str_res_whl2[] PROGMEM = "whl2";
static const prog_char str_res_pdal[] PROGMEM = "pdal";
static const prog_char str_res_note[] PROGMEM = "note";
static const prog_char str_res_gate[] PROGMEM = "gate";
static const prog_char str_res_nois[] PROGMEM = "nois";
static const prog_char str_res_rand[] PROGMEM = "rand";
static const prog_char str_res_e256[] PROGMEM = "=256";
static const prog_char str_res_e128[] PROGMEM = "=128";
static const prog_char str_res_e64[] PROGMEM = "=64";
static const prog_char str_res_e32[] PROGMEM = "=32";
static const prog_char str_res_e16[] PROGMEM = "=16";
static const prog_char str_res_e8[] PROGMEM = "=8";
static const prog_char str_res_e4[] PROGMEM = "=4";
static const prog_char str_res_prm1[] PROGMEM = "prm1";
static const prog_char str_res_prm2[] PROGMEM = "prm2";
static const prog_char str_res_osc1[] PROGMEM = "osc1";
static const prog_char str_res_osc2[] PROGMEM = "osc2";
static const prog_char str_res_31S2[] PROGMEM = "1+2";
static const prog_char str_res_vibr[] PROGMEM = "vibr";
static const prog_char str_res_mix[] PROGMEM = "mix";
static const prog_char str_res_xmod[] PROGMEM = "xmod";
static const prog_char str_res_sub[] PROGMEM = "sub";
static const prog_char str_res_fuzz[] PROGMEM = "fuzz";
static const prog_char str_res_crsh[] PROGMEM = "crsh";
static const prog_char str_res_freq[] PROGMEM = "freq";
static const prog_char str_res_reso[] PROGMEM = "reso";
static const prog_char str_res_attk[] PROGMEM = "attk";
static const prog_char str_res_deca[] PROGMEM = "deca";
static const prog_char str_res_rele[] PROGMEM = "rele";
static const prog_char str_res_vca[] PROGMEM = "vca";
static const prog_char str_res_env_1[] PROGMEM = "env 1";
static const prog_char str_res_env_2[] PROGMEM = "env 2";
static const prog_char str_res_env_3[] PROGMEM = "env 3";
static const prog_char str_res_lfo_1[] PROGMEM = "lfo 1";
static const prog_char str_res_lfo_2[] PROGMEM = "lfo 2";
static const prog_char str_res_lfo_3[] PROGMEM = "lfo 3";
static const prog_char str_res_lfo_4[] PROGMEM = "lfo 4";
static const prog_char str_res_mod__1[] PROGMEM = "mod. 1";
static const prog_char str_res_mod__2[] PROGMEM = "mod. 2";
static const prog_char str_res_mod__3[] PROGMEM = "mod. 3";
static const prog_char str_res_mod__4[] PROGMEM = "mod. 4";
static const prog_char str_res_seq__1[] PROGMEM = "seq. 1";
static const prog_char str_res_seq__2[] PROGMEM = "seq. 2";
static const prog_char str_res_afttch[] PROGMEM = "afttch";
static const prog_char str_res_bender[] PROGMEM = "bender";
static const prog_char str_res_mwheel[] PROGMEM = "mwheel";
static const prog_char str_res_wheel2[] PROGMEM = "wheel2";
static const prog_char str_res_pedal[] PROGMEM = "pedal";
static const prog_char str_res_random[] PROGMEM = "random";
static const prog_char str_res_e_256[] PROGMEM = "= 256";
static const prog_char str_res_e_32[] PROGMEM = "= 32";
static const prog_char str_res_e_16[] PROGMEM = "= 16";
static const prog_char str_res_e_8[] PROGMEM = "= 8";
static const prog_char str_res_e_4[] PROGMEM = "= 4";
static const prog_char str_res_param_1[] PROGMEM = "param 1";
static const prog_char str_res_param_2[] PROGMEM = "param 2";
static const prog_char str_res_osc_1[] PROGMEM = "osc 1";
static const prog_char str_res_osc_2[] PROGMEM = "osc 2";
static const prog_char str_res_osc_1S2[] PROGMEM = "osc 1+2";
static const prog_char str_res_vibrato[] PROGMEM = "vibrato";
static const prog_char str_res_subosc[] PROGMEM = "subosc";
static const prog_char str_res_crush[] PROGMEM = "crush";
static const prog_char str_res_frequency[] PROGMEM = "frequency";
static const prog_char str_res_lp[] PROGMEM = "lp";
static const prog_char str_res_bp[] PROGMEM = "bp";
static const prog_char str_res_hp[] PROGMEM = "hp";
static const prog_char str_res_free[] PROGMEM = "free";
static const prog_char str_res_envTlfo[] PROGMEM = "env~lfo";
static const prog_char str_res_lfoTenv[] PROGMEM = "lfo~env";
static const prog_char str_res_step_seq[] PROGMEM = "step seq";
static const prog_char str_res_arpeggio[] PROGMEM = "arpeggio";
static const prog_char str_res_add[] PROGMEM = "add";
static const prog_char str_res_prod[] PROGMEM = "prod";
static const prog_char str_res_attn[] PROGMEM = "attn";
static const prog_char str_res_max[] PROGMEM = "max";
static const prog_char str_res_min[] PROGMEM = "min";
static const prog_char str_res_ge[] PROGMEM = ">=";
static const prog_char str_res_le[] PROGMEM = "<=";
static const prog_char str_res_qtz[] PROGMEM = "qtz";
static const prog_char str_res_lag[] PROGMEM = "lag";
static const prog_char str_res_mono[] PROGMEM = "mono";
static const prog_char str_res_poly[] PROGMEM = "poly";
static const prog_char str_res_2x_unison[] PROGMEM = "2x unison";
static const prog_char str_res_cyclic[] PROGMEM = "cyclic";
static const prog_char str_res_up[] PROGMEM = "up";
static const prog_char str_res_down[] PROGMEM = "down";
static const prog_char str_res_up_down[] PROGMEM = "up&down";
static const prog_char str_res_played[] PROGMEM = "played";
static const prog_char str_res_chord[] PROGMEM = "chord";
static const prog_char str_res_1_1[] PROGMEM = "1/1";
static const prog_char str_res_3_4[] PROGMEM = "3/4";
static const prog_char str_res_2_3[] PROGMEM = "2/3";
static const prog_char str_res_1_2[] PROGMEM = "1/2";
static const prog_char str_res_3_8[] PROGMEM = "3/8";
static const prog_char str_res_1_3[] PROGMEM = "1/3";
static const prog_char str_res_1_4[] PROGMEM = "1/4";
static const prog_char str_res_1_6[] PROGMEM = "1/6";
static const prog_char str_res_1_8[] PROGMEM = "1/8";
static const prog_char str_res_1_12[] PROGMEM = "1/12";
static const prog_char str_res_1_16[] PROGMEM = "1/16";
static const prog_char str_res_1_24[] PROGMEM = "1/24";
static const prog_char str_res_1_32[] PROGMEM = "1/32";
static const prog_char str_res_1_48[] PROGMEM = "1/48";
static const prog_char str_res_1_96[] PROGMEM = "1/96";
static const prog_char str_res_thru[] PROGMEM = "thru";
static const prog_char str_res_sequencer[] PROGMEM = "sequencer";
static const prog_char str_res_controllr[] PROGMEM = "controllr";
static const prog_char str_res_full[] PROGMEM = "full";
static const prog_char str_res_____[] PROGMEM = "....";
static const prog_char str_res____s[] PROGMEM = "...s";
static const prog_char str_res___p_[] PROGMEM = "..p.";
static const prog_char str_res___ps[] PROGMEM = "..ps";
static const prog_char str_res__n__[] PROGMEM = ".n..";
static const prog_char str_res__n_s[] PROGMEM = ".n.s";
static const prog_char str_res__np_[] PROGMEM = ".np.";
static const prog_char str_res__nps[] PROGMEM = ".nps";
static const prog_char str_res_c___[] PROGMEM = "c...";
static const prog_char str_res_c__s[] PROGMEM = "c..s";
static const prog_char str_res_c_p_[] PROGMEM = "c.p.";
static const prog_char str_res_c_ps[] PROGMEM = "c.ps";
static const prog_char str_res_cn__[] PROGMEM = "cn..";
static const prog_char str_res_cn_s[] PROGMEM = "cn.s";
static const prog_char str_res_cnp_[] PROGMEM = "cnp.";
static const prog_char str_res_cnps[] PROGMEM = "cnps";
static const prog_char str_res_swing[] PROGMEM = "swing";
static const prog_char str_res_shuffle[] PROGMEM = "shuffle";
static const prog_char str_res_push[] PROGMEM = "push";
static const prog_char str_res_human[] PROGMEM = "human";
static const prog_char str_res_monkey[] PROGMEM = "monkey";
static const prog_char str_res_oscillator_1[] PROGMEM = "oscillator 1";
static const prog_char str_res_oscillator_2[] PROGMEM = "oscillator 2";
static const prog_char str_res_mixer[] PROGMEM = "mixer";
static const prog_char str_res_lfo[] PROGMEM = "lfo";
static const prog_char str_res_filter_1[] PROGMEM = "filter 1";
static const prog_char str_res_filter_2[] PROGMEM = "filter 2";
static const prog_char str_res_envelope[] PROGMEM = "envelope";
static const prog_char str_res_arpeggiator[] PROGMEM = "arpeggiator";
static const prog_char str_res_multi[] PROGMEM = "multi";
static const prog_char str_res_clock[] PROGMEM = "clock";
static const prog_char str_res_performance[] PROGMEM = "performance";
static const prog_char str_res_system[] PROGMEM = "system";
static const prog_char str_res_pt_x_patch[] PROGMEM = "pt X patch";
static const prog_char str_res_pt_x_sequence[] PROGMEM = "pt X sequence";
static const prog_char str_res_pt_x_program[] PROGMEM = "pt X program";
static const prog_char str_res_randomize[] PROGMEM = "randomize";
static const prog_char str_res_init[] PROGMEM = "init";
static const prog_char str_res_patch[] PROGMEM = "PATCH";
static const prog_char str_res_sequence[] PROGMEM = "SEQUENCE";
static const prog_char str_res_program[] PROGMEM = "PROGRAM";
static const prog_char str_res__multi[] PROGMEM = "MULTI";
static const prog_char str_res____[] PROGMEM = "___";
static const prog_char str_res_equal[] PROGMEM = "equal";
static const prog_char str_res_just[] PROGMEM = "just";
static const prog_char str_res_pythagorean[] PROGMEM = "pythagorean";
static const prog_char str_res_1_4_eb[] PROGMEM = "1/4 eb";
static const prog_char str_res_1_4_e[] PROGMEM = "1/4 e";
static const prog_char str_res_1_4_ea[] PROGMEM = "1/4 ea";
static const prog_char str_res_bhairav[] PROGMEM = "bhairav";
static const prog_char str_res_gunakri[] PROGMEM = "gunakri";
static const prog_char str_res_marwa[] PROGMEM = "marwa";
static const prog_char str_res_shree[] PROGMEM = "shree";
static const prog_char str_res_purvi[] PROGMEM = "purvi";
static const prog_char str_res_bilawal[] PROGMEM = "bilawal";
static const prog_char str_res_yaman[] PROGMEM = "yaman";
static const prog_char str_res_kafi[] PROGMEM = "kafi";
static const prog_char str_res_bhimpalasree[] PROGMEM = "bhimpalasree";
static const prog_char str_res_darbari[] PROGMEM = "darbari";
static const prog_char str_res_bageshree[] PROGMEM = "bageshree";
static const prog_char str_res_rageshree[] PROGMEM = "rageshree";
static const prog_char str_res_khamaj[] PROGMEM = "khamaj";
static const prog_char str_res_mimal[] PROGMEM = "mi'mal";
static const prog_char str_res_parameshwari[] PROGMEM = "parameshwari";
static const prog_char str_res_rangeshwari[] PROGMEM = "rangeshwari";
static const prog_char str_res_gangeshwari[] PROGMEM = "gangeshwari";
static const prog_char str_res_kameshwari[] PROGMEM = "kameshwari";
static const prog_char str_res_pa__kafi[] PROGMEM = "pa. kafi";
static const prog_char str_res_natbhairav[] PROGMEM = "natbhairav";
static const prog_char str_res_m_kauns[] PROGMEM = "m.kauns";
static const prog_char str_res_bairagi[] PROGMEM = "bairagi";
static const prog_char str_res_b_todi[] PROGMEM = "b.todi";
static const prog_char str_res_chandradeep[] PROGMEM = "chandradeep";
static const prog_char str_res_kaushik_todi[] PROGMEM = "kaushik todi";
static const prog_char str_res_jogeshwari[] PROGMEM = "jogeshwari";
static const prog_char str_res_rasia[] PROGMEM = "rasia";


PROGMEM const prog_char* string_table[] = {
  str_res_waveform,
  str_res_parameter,
  str_res_range,
  str_res_tune,
  str_res_osc_mix,
  str_res_sub_osc_,
  str_res_crossmod_,
  str_res_operator,
  str_res_amount,
  str_res_resonance,
  str_res_mode,
  str_res_env2Tvcf,
  str_res_lfo2Tvcf,
  str_res_attack,
  str_res_decay,
  str_res_sustain,
  str_res_release,
  str_res_trigger,
  str_res_rate,
  str_res_lfo_eg,
  str_res_voice_lfo,
  str_res_source,
  str_res_destination,
  str_res_in1,
  str_res_in2,
  str_res_modulation,
  str_res_modul_,
  str_res_modulation,
  str_res_modifier,
  str_res_modif_,
  str_res_volume,
  str_res_octave,
  str_res_spread,
  str_res_legato,
  str_res_portamento,
  str_res_arp_seq,
  str_res_raga,
  str_res_direction,
  str_res_pattern,
  str_res_channel,
  str_res_part,
  str_res_bpm,
  str_res_ltch,
  str_res_latch,
  str_res_low,
  str_res_high,
  str_res_grid,
  str_res_seq1_len,
  str_res_seq2_len,
  str_res_patt_len,
  str_res_len1,
  str_res_len2,
  str_res_lenp,
  str_res_groove,
  str_res_midi,
  str_res_snap,
  str_res_help,
  str_res_auto_backup,
  str_res_leds,
  str_res_card_leds,
  str_res_swap_colors,
  str_res_inpt_filter,
  str_res_outp_mode,
  str_res_ext,
  str_res_omni,
  str_res_amnt,
  str_res_srce,
  str_res_oct,
  str_res_sprd,
  str_res_a_sq,
  str_res_octv,
  str_res_off,
  str_res_on,
  str_res_none,
  str_res_saw,
  str_res_square,
  str_res_triangle,
  str_res_sine,
  str_res_zsaw,
  str_res_lpzsaw,
  str_res_pkzsaw,
  str_res_bpzsaw,
  str_res_hpzsaw,
  str_res_lpzpulse,
  str_res_pkzpulse,
  str_res_bpzpulse,
  str_res_hpzpulse,
  str_res_ztriangle,
  str_res_pad,
  str_res_fm,
  str_res_8bits,
  str_res_pwm,
  str_res_noise,
  str_res_vowel,
  str_res_male,
  str_res_female,
  str_res_choir,
  str_res_tampura,
  str_res_bowed,
  str_res_cello,
  str_res_vibes,
  str_res_slap,
  str_res_epiano,
  str_res_organ,
  str_res_waves,
  str_res_digital,
  str_res_drone_1,
  str_res_drone_2,
  str_res_metallic,
  str_res_bell,
  str_res_wavquence,
  str_res_tri,
  str_res_sqr,
  str_res_s_h,
  str_res_ramp,
  str_res_sine,
  str_res_hrm2,
  str_res_hrm3,
  str_res_hrm5,
  str_res_grg1,
  str_res_grg2,
  str_res_bat1,
  str_res_bat2,
  str_res_spk1,
  str_res_spk2,
  str_res_lsaw,
  str_res_lsqr,
  str_res_rsaw,
  str_res_rsqr,
  str_res_stp1,
  str_res_stp2,
  str_res_off,
  str_res_sync,
  str_res_ringmod,
  str_res_xor,
  str_res_fold,
  str_res_bits,
  str_res_squ1,
  str_res_tri1,
  str_res_pul1,
  str_res_squ2,
  str_res_tri2,
  str_res_pul2,
  str_res_click,
  str_res_glitch,
  str_res_blow,
  str_res_metal,
  str_res_pop,
  str_res_env1,
  str_res_env2,
  str_res_env3,
  str_res_lfo1,
  str_res_lfo2,
  str_res_lfo3,
  str_res_lfo4,
  str_res_mod1,
  str_res_mod2,
  str_res_mod3,
  str_res_mod4,
  str_res_seq1,
  str_res_seq2,
  str_res_arp,
  str_res_velo,
  str_res_aftr,
  str_res_bend,
  str_res_mwhl,
  str_res_whl2,
  str_res_pdal,
  str_res_note,
  str_res_gate,
  str_res_nois,
  str_res_rand,
  str_res_e256,
  str_res_e128,
  str_res_e64,
  str_res_e32,
  str_res_e16,
  str_res_e8,
  str_res_e4,
  str_res_prm1,
  str_res_prm2,
  str_res_osc1,
  str_res_osc2,
  str_res_31S2,
  str_res_vibr,
  str_res_mix,
  str_res_xmod,
  str_res_nois,
  str_res_sub,
  str_res_fuzz,
  str_res_crsh,
  str_res_freq,
  str_res_reso,
  str_res_attk,
  str_res_deca,
  str_res_rele,
  str_res_lfo4,
  str_res_vca,
  str_res_env_1,
  str_res_env_2,
  str_res_env_3,
  str_res_lfo_1,
  str_res_lfo_2,
  str_res_lfo_3,
  str_res_lfo_4,
  str_res_mod__1,
  str_res_mod__2,
  str_res_mod__3,
  str_res_mod__4,
  str_res_seq__1,
  str_res_seq__2,
  str_res_arp,
  str_res_velo,
  str_res_afttch,
  str_res_bender,
  str_res_mwheel,
  str_res_wheel2,
  str_res_pedal,
  str_res_note,
  str_res_gate,
  str_res_noise,
  str_res_random,
  str_res_e_256,
  str_res_e_32,
  str_res_e_16,
  str_res_e_8,
  str_res_e_4,
  str_res_param_1,
  str_res_param_2,
  str_res_osc_1,
  str_res_osc_2,
  str_res_osc_1S2,
  str_res_vibrato,
  str_res_mix,
  str_res_xmod,
  str_res_noise,
  str_res_subosc,
  str_res_fuzz,
  str_res_crush,
  str_res_frequency,
  str_res_reso,
  str_res_attack,
  str_res_decay,
  str_res_release,
  str_res_lfo_4,
  str_res_vca,
  str_res_lp,
  str_res_bp,
  str_res_hp,
  str_res_free,
  str_res_envTlfo,
  str_res_lfoTenv,
  str_res_step_seq,
  str_res_arpeggio,
  str_res_pattern,
  str_res_off,
  str_res_add,
  str_res_prod,
  str_res_attn,
  str_res_max,
  str_res_min,
  str_res_xor,
  str_res_ge,
  str_res_le,
  str_res_qtz,
  str_res_lag,
  str_res_mono,
  str_res_poly,
  str_res_2x_unison,
  str_res_cyclic,
  str_res_up,
  str_res_down,
  str_res_up_down,
  str_res_played,
  str_res_random,
  str_res_chord,
  str_res_1_1,
  str_res_3_4,
  str_res_2_3,
  str_res_1_2,
  str_res_3_8,
  str_res_1_3,
  str_res_1_4,
  str_res_1_6,
  str_res_1_8,
  str_res_1_12,
  str_res_1_16,
  str_res_1_24,
  str_res_1_32,
  str_res_1_48,
  str_res_1_96,
  str_res_thru,
  str_res_sequencer,
  str_res_controllr,
  str_res_full,
  str_res_____,
  str_res____s,
  str_res___p_,
  str_res___ps,
  str_res__n__,
  str_res__n_s,
  str_res__np_,
  str_res__nps,
  str_res_c___,
  str_res_c__s,
  str_res_c_p_,
  str_res_c_ps,
  str_res_cn__,
  str_res_cn_s,
  str_res_cnp_,
  str_res_cnps,
  str_res_swing,
  str_res_shuffle,
  str_res_push,
  str_res_lag,
  str_res_human,
  str_res_monkey,
  str_res_oscillator_1,
  str_res_oscillator_2,
  str_res_mixer,
  str_res_lfo,
  str_res_filter_1,
  str_res_filter_2,
  str_res_envelope,
  str_res_arpeggiator,
  str_res_multi,
  str_res_clock,
  str_res_performance,
  str_res_system,
  str_res_pt_x_patch,
  str_res_pt_x_sequence,
  str_res_pt_x_program,
  str_res_randomize,
  str_res_init,
  str_res_patch,
  str_res_sequence,
  str_res_program,
  str_res__multi,
  str_res____,
  str_res_equal,
  str_res_just,
  str_res_pythagorean,
  str_res_1_4_eb,
  str_res_1_4_e,
  str_res_1_4_ea,
  str_res_bhairav,
  str_res_gunakri,
  str_res_marwa,
  str_res_shree,
  str_res_purvi,
  str_res_bilawal,
  str_res_yaman,
  str_res_kafi,
  str_res_bhimpalasree,
  str_res_darbari,
  str_res_bageshree,
  str_res_rageshree,
  str_res_khamaj,
  str_res_mimal,
  str_res_parameshwari,
  str_res_rangeshwari,
  str_res_gangeshwari,
  str_res_kameshwari,
  str_res_pa__kafi,
  str_res_natbhairav,
  str_res_m_kauns,
  str_res_bairagi,
  str_res_b_todi,
  str_res_chandradeep,
  str_res_kaushik_todi,
  str_res_jogeshwari,
  str_res_rasia,
};

const prog_uint16_t lut_res_lfo_increments[] PROGMEM = {
       4,      4,      4,      4,      5,      5,      5,      6,
       6,      7,      7,      7,      8,      8,      9,      9,
      10,     11,     11,     12,     13,     14,     14,     15,
      16,     17,     18,     20,     21,     22,     23,     25,
      26,     28,     30,     31,     33,     35,     37,     40,
      42,     45,     47,     50,     53,     57,     60,     64,
      67,     71,     76,     80,     85,     90,     96,    101,
     108,    114,    121,    128,    136,    144,    153,    162,
     172,    182,    193,    204,    217,    230,    243,    258,
     273,    290,    307,    325,    345,    366,    388,    411,
     435,    461,    489,    518,    549,    582,    617,    654,
     693,    735,    779,    825,    875,    927,    982,   1041,
    1104,   1170,   1240,   1314,   1392,   1476,   1564,   1657,
    1757,   1862,   1973,   2091,   2216,   2349,   2489,   2638,
    2796,   2963,   3141,   3329,   3528,   3739,   3962,   4199,
    4451,   4717,   4999,   5298,   5615,   5951,   6307,   6684,
};
const prog_uint16_t lut_res_scale_just[] PROGMEM = {
       0,     15,      5,     20,    -17,     -2,    -12,      2,
      17,    -20,     -5,    -15,
};
const prog_uint16_t lut_res_scale_pythagorean[] PROGMEM = {
       0,     15,      5,     -7,     10,     -2,    -12,      2,
      17,    -20,     -5,     12,
};
const prog_uint16_t lut_res_scale_1_4_eb[] PROGMEM = {
       0,      0,      0,      0,    -64,      0,      0,      0,
       0,      0,      0,    -64,
};
const prog_uint16_t lut_res_scale_1_4_e[] PROGMEM = {
       0,      0,      0,      0,    -64,      0,      0,      0,
       0,      0,      0,      0,
};
const prog_uint16_t lut_res_scale_1_4_ea[] PROGMEM = {
       0,      0,      0,      0,    -64,      0,      0,      0,
       0,    -64,      0,      0,
};
const prog_uint16_t lut_res_scale_bhairav[] PROGMEM = {
       0,    -12,  32767,  32767,    -17,     -2,  32767,      2,
     -10,  32767,  32767,    -15,
};
const prog_uint16_t lut_res_scale_gunakri[] PROGMEM = {
       0,     15,  32767,  32767,  32767,     -2,  32767,      2,
      17,  32767,  32767,  32767,
};
const prog_uint16_t lut_res_scale_marwa[] PROGMEM = {
       0,     15,  32767,  32767,    -17,  32767,    -12,  32767,
   32767,    -20,  32767,    -15,
};
const prog_uint16_t lut_res_scale_shree[] PROGMEM = {
       0,    -12,  32767,  32767,    -17,  32767,    -12,      2,
     -10,  32767,  32767,    -15,
};
const prog_uint16_t lut_res_scale_purvi[] PROGMEM = {
       0,     15,  32767,  32767,    -17,  32767,    -12,      2,
      17,  32767,  32767,    -15,
};
const prog_uint16_t lut_res_scale_bilawal[] PROGMEM = {
       0,  32767,      5,  32767,    -17,     -2,  32767,      2,
   32767,      7,  32767,    -15,
};
const prog_uint16_t lut_res_scale_yaman[] PROGMEM = {
       0,  32767,      5,  32767,     10,  32767,     15,      2,
   32767,      7,  32767,     12,
};
const prog_uint16_t lut_res_scale_kafi[] PROGMEM = {
       0,  32767,    -22,     -7,  32767,     -2,  32767,      2,
   32767,    -20,     -5,  32767,
};
const prog_uint16_t lut_res_scale_bhimpalasree[] PROGMEM = {
       0,  32767,      5,     20,  32767,     -2,  32767,      2,
   32767,      7,     22,  32767,
};
const prog_uint16_t lut_res_scale_darbari[] PROGMEM = {
       0,  32767,      5,     -7,  32767,     -2,  32767,      2,
     -10,  32767,     -5,  32767,
};
const prog_uint16_t lut_res_scale_rageshree[] PROGMEM = {
       0,  32767,      5,  32767,    -17,     -2,  32767,      2,
   32767,    -20,     -5,  32767,
};
const prog_uint16_t lut_res_scale_khamaj[] PROGMEM = {
       0,  32767,      5,  32767,    -17,     -2,  32767,      2,
   32767,      7,     -5,     12,
};
const prog_uint16_t lut_res_scale_mimal[] PROGMEM = {
       0,  32767,      5,     -7,  32767,     -2,  32767,      2,
   32767,    -20,     -5,    -15,
};
const prog_uint16_t lut_res_scale_parameshwari[] PROGMEM = {
       0,    -12,  32767,     -7,  32767,     -2,  32767,  32767,
   32767,    -20,     -5,  32767,
};
const prog_uint16_t lut_res_scale_rangeshwari[] PROGMEM = {
       0,  32767,      5,     -7,  32767,     -2,  32767,      2,
   32767,  32767,  32767,    -15,
};
const prog_uint16_t lut_res_scale_gangeshwari[] PROGMEM = {
       0,  32767,  32767,  32767,    -17,     -2,  32767,      2,
     -10,  32767,     -5,  32767,
};
const prog_uint16_t lut_res_scale_kameshwari[] PROGMEM = {
       0,  32767,      5,  32767,  32767,  32767,    -12,      2,
   32767,    -20,     -5,  32767,
};
const prog_uint16_t lut_res_scale_pa__kafi[] PROGMEM = {
       0,  32767,      5,     -7,  32767,     -2,  32767,      2,
   32767,      7,     -5,  32767,
};
const prog_uint16_t lut_res_scale_natbhairav[] PROGMEM = {
       0,  32767,      5,  32767,    -17,     -2,  32767,      2,
     -10,  32767,  32767,    -15,
};
const prog_uint16_t lut_res_scale_m_kauns[] PROGMEM = {
       0,  32767,      5,  32767,     10,     -2,  32767,  32767,
     -10,  32767,     -5,  32767,
};
const prog_uint16_t lut_res_scale_bairagi[] PROGMEM = {
       0,    -12,  32767,  32767,  32767,     -2,  32767,      2,
   32767,  32767,     -5,  32767,
};
const prog_uint16_t lut_res_scale_b_todi[] PROGMEM = {
       0,    -12,  32767,     -7,  32767,  32767,  32767,      2,
   32767,  32767,     -5,  32767,
};
const prog_uint16_t lut_res_scale_chandradeep[] PROGMEM = {
       0,  32767,  32767,     -7,  32767,     -2,  32767,      2,
   32767,  32767,     -5,  32767,
};
const prog_uint16_t lut_res_scale_kaushik_todi[] PROGMEM = {
       0,  32767,  32767,     -7,  32767,     -2,    -12,  32767,
     -10,  32767,  32767,  32767,
};
const prog_uint16_t lut_res_scale_jogeshwari[] PROGMEM = {
       0,  32767,  32767,     -7,    -17,     -2,  32767,  32767,
   32767,    -20,     -5,  32767,
};
const prog_uint16_t lut_res_arpeggiator_patterns[] PROGMEM = {
   21845,  62965,  46517,  54741,  43861,  22869,  38293,   2313,
   37449,  21065,  18761,  54553,  27499,  23387,  30583,  28087,
   22359,  28527,  30431,  43281,  28609,  53505,
};
const prog_uint16_t lut_res_groove_swing[] PROGMEM = {
     127,    127,   -127,   -127,    127,    127,   -127,   -127,
     127,    127,   -127,   -127,    127,    127,   -127,   -127,
};
const prog_uint16_t lut_res_groove_shuffle[] PROGMEM = {
     127,   -127,    127,   -127,    127,   -127,    127,   -127,
     127,   -127,    127,   -127,    127,   -127,    127,   -127,
};
const prog_uint16_t lut_res_groove_push[] PROGMEM = {
     -63,    -63,    127,      0,   -127,      0,      0,     88,
       0,      0,     88,    -50,    -88,      0,     88,      0,
};
const prog_uint16_t lut_res_groove_lag[] PROGMEM = {
      19,     44,     93,     -4,     32,    -53,    -90,   -127,
     117,     32,   -102,    -53,    105,    -53,     93,    -53,
};
const prog_uint16_t lut_res_groove_human[] PROGMEM = {
      88,   -101,    107,    -95,     88,    -88,     50,    -38,
      65,    -88,    101,    -95,    101,   -127,     63,    -31,
};
const prog_uint16_t lut_res_groove_monkey[] PROGMEM = {
      70,    -84,     84,   -112,     84,    -98,    112,    -98,
      54,    -70,    127,    -84,    127,   -112,     84,    -84,
};


PROGMEM const prog_uint16_t* lookup_table_table[] = {
  lut_res_lfo_increments,
  lut_res_scale_just,
  lut_res_scale_pythagorean,
  lut_res_scale_1_4_eb,
  lut_res_scale_1_4_e,
  lut_res_scale_1_4_ea,
  lut_res_scale_bhairav,
  lut_res_scale_gunakri,
  lut_res_scale_marwa,
  lut_res_scale_shree,
  lut_res_scale_purvi,
  lut_res_scale_bilawal,
  lut_res_scale_yaman,
  lut_res_scale_kafi,
  lut_res_scale_bhimpalasree,
  lut_res_scale_darbari,
  lut_res_scale_kafi,
  lut_res_scale_rageshree,
  lut_res_scale_khamaj,
  lut_res_scale_mimal,
  lut_res_scale_parameshwari,
  lut_res_scale_rangeshwari,
  lut_res_scale_gangeshwari,
  lut_res_scale_kameshwari,
  lut_res_scale_pa__kafi,
  lut_res_scale_natbhairav,
  lut_res_scale_m_kauns,
  lut_res_scale_bairagi,
  lut_res_scale_b_todi,
  lut_res_scale_chandradeep,
  lut_res_scale_kaushik_todi,
  lut_res_scale_jogeshwari,
  lut_res_scale_yaman,
  lut_res_arpeggiator_patterns,
  lut_res_groove_swing,
  lut_res_groove_shuffle,
  lut_res_groove_push,
  lut_res_groove_lag,
  lut_res_groove_human,
  lut_res_groove_monkey,
};

const prog_uint8_t chr_res_special_characters[] PROGMEM = {
       2,      3,      3,      2,      2,     14,     30,     12,
       0,      0,      4,      4,     14,     31,     31,      0,
       0,      0,      8,     21,      2,      0,      0,      0,
       1,      1,      1,      3,      3,      0,     18,     12,
       0,     25,     27,      6,      2,      4,      4,      8,
       0,     16,      8,      4,      2,      1,      0,      0,
       4,      0,      4,      0,      4,      0,      4,      0,
};


const prog_uint8_t* character_table[] = {
  chr_res_special_characters,
};

const prog_uint8_t wav_res_lfo_waveforms[] PROGMEM = {
     128,    131,    134,    137,    140,    143,    146,    149,
     152,    155,    158,    161,    164,    167,    170,    173,
     176,    179,    182,    184,    187,    190,    193,    195,
     198,    200,    203,    205,    208,    210,    212,    215,
     217,    219,    221,    223,    225,    227,    229,    231,
     233,    234,    236,    238,    239,    240,    242,    243,
     244,    246,    247,    248,    249,    249,    250,    251,
     252,    252,    253,    253,    253,    254,    254,    254,
     254,    254,    254,    254,    253,    253,    253,    252,
     252,    251,    250,    249,    249,    248,    247,    246,
     244,    243,    242,    240,    239,    238,    236,    234,
     233,    231,    229,    227,    225,    223,    221,    219,
     217,    215,    212,    210,    208,    205,    203,    200,
     198,    195,    193,    190,    187,    184,    182,    179,
     176,    173,    170,    167,    164,    161,    158,    155,
     152,    149,    146,    143,    140,    137,    134,    131,
     128,    124,    121,    118,    115,    112,    109,    106,
     103,    100,     97,     94,     91,     88,     85,     82,
      79,     76,     73,     71,     68,     65,     62,     60,
      57,     55,     52,     50,     47,     45,     43,     40,
      38,     36,     34,     32,     30,     28,     26,     24,
      22,     21,     19,     17,     16,     15,     13,     12,
      11,      9,      8,      7,      6,      6,      5,      4,
       3,      3,      2,      2,      2,      1,      1,      1,
       1,      1,      1,      1,      2,      2,      2,      3,
       3,      4,      5,      6,      6,      7,      8,      9,
      11,     12,     13,     15,     16,     17,     19,     21,
      22,     24,     26,     28,     30,     32,     34,     36,
      38,     40,     43,     45,     47,     50,     52,     55,
      57,     60,     62,     65,     68,     71,     73,     76,
      79,     82,     85,     88,     91,     94,     97,    100,
     103,    106,    109,    112,    115,    118,    121,    124,
     128,    128,    133,    138,    143,    148,    153,    157,
     162,    167,    172,    177,    181,    186,    190,    194,
     199,    203,    207,    210,    214,    218,    221,    224,
     227,    230,    233,    236,    238,    241,    243,    245,
     246,    248,    249,    251,    252,    252,    253,    254,
     254,    254,    254,    254,    253,    253,    252,    251,
     250,    249,    248,    246,    244,    243,    241,    239,
     237,    234,    232,    230,    227,    224,    222,    219,
     216,    213,    210,    207,    204,    201,    198,    195,
     192,    189,    185,    182,    179,    176,    173,    170,
     167,    164,    161,    159,    156,    153,    151,    148,
     146,    143,    141,    139,    137,    135,    133,    131,
     130,    128,    127,    125,    124,    123,    122,    121,
     120,    120,    119,    119,    118,    118,    118,    118,
     118,    118,    118,    118,    119,    119,    120,    120,
     121,    121,    122,    123,    123,    124,    125,    126,
     127,    128,    128,    129,    130,    131,    132,    132,
     133,    134,    134,    135,    135,    136,    136,    137,
     137,    137,    137,    137,    137,    137,    137,    136,
     136,    135,    135,    134,    133,    132,    131,    130,
     128,    127,    125,    124,    122,    120,    118,    116,
     114,    112,    109,    107,    104,    102,     99,     96,
      94,     91,     88,     85,     82,     79,     76,     73,
      70,     66,     63,     60,     57,     54,     51,     48,
      45,     42,     39,     36,     33,     31,     28,     25,
      23,     21,     18,     16,     14,     12,     11,      9,
       7,      6,      5,      4,      3,      2,      2,      1,
       1,      1,      1,      1,      2,      3,      3,      4,
       6,      7,      9,     10,     12,     14,     17,     19,
      22,     25,     28,     31,     34,     37,     41,     45,
      48,     52,     56,     61,     65,     69,     74,     78,
      83,     88,     93,     98,    102,    107,    112,    117,
     122,    128,    128,    135,    143,    150,    158,    165,
     172,    180,    186,    193,    199,    205,    211,    217,
     222,    227,    231,    235,    239,    242,    245,    248,
     250,    251,    253,    254,    254,    254,    254,    253,
     252,    250,    249,    247,    244,    242,    239,    236,
     232,    229,    225,    221,    217,    213,    209,    205,
     201,    198,    194,    190,    186,    183,    179,    176,
     173,    170,    168,    165,    163,    162,    160,    159,
     158,    158,    158,    158,    158,    159,    160,    162,
     163,    165,    168,    170,    173,    176,    179,    183,
     186,    190,    194,    198,    201,    205,    209,    213,
     217,    221,    225,    229,    232,    236,    239,    242,
     244,    247,    249,    250,    252,    253,    254,    254,
     254,    254,    253,    251,    250,    248,    245,    242,
     239,    235,    231,    227,    222,    217,    211,    205,
     199,    193,    186,    180,    172,    165,    158,    150,
     143,    135,    128,    120,    112,    105,     97,     90,
      83,     75,     69,     62,     56,     50,     44,     38,
      33,     28,     24,     20,     16,     13,     10,      7,
       5,      4,      2,      1,      1,      1,      1,      2,
       3,      5,      6,      8,     11,     13,     16,     19,
      23,     26,     30,     34,     38,     42,     46,     50,
      54,     57,     61,     65,     69,     72,     76,     79,
      82,     85,     87,     90,     92,     93,     95,     96,
      97,     97,     97,     97,     97,     96,     95,     93,
      92,     90,     87,     85,     82,     79,     76,     72,
      69,     65,     61,     57,     54,     50,     46,     42,
      38,     34,     30,     26,     23,     19,     16,     13,
      11,      8,      6,      5,      3,      2,      1,      1,
       1,      1,      2,      4,      5,      7,     10,     13,
      16,     20,     24,     28,     33,     38,     44,     50,
      56,     62,     69,     75,     83,     90,     97,    105,
     112,    120,    128,    128,    136,    144,    152,    159,
     167,    173,    180,    185,    190,    195,    198,    201,
     203,    204,    204,    204,    203,    201,    199,    196,
     192,    188,    184,    179,    174,    169,    164,    160,
     155,    151,    147,    143,    140,    138,    136,    135,
     135,    135,    136,    138,    141,    144,    148,    153,
     158,    164,    170,    176,    183,    190,    197,    204,
     211,    217,    224,    229,    235,    240,    244,    247,
     250,    252,    254,    254,    254,    252,    250,    247,
     244,    240,    235,    229,    224,    217,    211,    204,
     197,    190,    183,    176,    170,    164,    158,    153,
     148,    144,    141,    138,    136,    135,    135,    135,
     136,    138,    140,    143,    147,    151,    155,    160,
     164,    169,    174,    179,    184,    188,    192,    196,
     199,    201,    203,    204,    204,    204,    203,    201,
     198,    195,    190,    185,    180,    173,    167,    159,
     152,    144,    136,    128,    119,    111,    103,     96,
      88,     82,     75,     70,     65,     60,     57,     54,
      52,     51,     51,     51,     52,     54,     56,     59,
      63,     67,     71,     76,     81,     86,     91,     95,
     100,    104,    108,    112,    115,    117,    119,    120,
     120,    120,    119,    117,    114,    111,    107,    102,
      97,     91,     85,     79,     72,     65,     58,     51,
      44,     38,     31,     26,     20,     15,     11,      8,
       5,      3,      1,      1,      1,      3,      5,      8,
      11,     15,     20,     26,     31,     38,     44,     51,
      58,     65,     72,     79,     85,     91,     97,    102,
     107,    111,    114,    117,    119,    120,    120,    120,
     119,    117,    115,    112,    108,    104,    100,     95,
      91,     86,     81,     76,     71,     67,     63,     59,
      56,     54,     52,     51,     51,     51,     52,     54,
      57,     60,     65,     70,     75,     82,     88,     96,
     103,    111,    119,    128,      1,      1,      1,      1,
       1,      2,      3,      3,      5,      6,      8,     10,
      13,     16,     19,     23,     27,     32,     37,     43,
      49,     56,     62,     70,     77,     85,     93,    102,
     110,    119,    128,    137,    145,    154,    163,    172,
     180,    188,    196,    204,    211,    218,    224,    230,
     235,    239,    243,    247,    250,    252,    253,    254,
     254,    253,    252,    250,    248,    244,    241,    236,
     231,    226,    220,    213,    206,    199,    191,    184,
     176,    167,    159,    150,    142,    133,    125,    116,
     108,    100,     92,     84,     76,     69,     62,     55,
      49,     43,     37,     32,     27,     23,     19,     15,
      12,      9,      6,      4,      2,      1,      1,      1,
       1,      1,      1,      1,      1,      1,      1,      1,
       1,      1,      1,      1,      1,      1,      1,      1,
       1,      1,      1,      1,      1,      1,      1,      1,
       1,      1,      1,      1,      1,      1,      1,      1,
       1,      1,      1,      1,      2,      2,      2,      2,
       3,      3,      3,      4,      4,      5,      5,      6,
       6,      6,      7,      7,      7,      7,      6,      6,
       5,      4,      3,      2,      1,      1,      1,      1,
       1,      1,      1,      1,      1,      1,      1,      1,
       1,      1,      1,      1,      1,      1,      1,      1,
       1,      1,      1,      1,      1,      1,      1,      1,
       1,      1,      1,      1,      1,      1,      1,      1,
       1,      1,      1,      1,      1,      1,      1,      1,
       1,      1,      1,      1,      1,      1,      1,      1,
       1,      1,      1,      1,      1,      1,      1,      1,
       1,      1,      1,      1,      1,      1,      1,      1,
       1,      1,      1,      1,      1,      1,      1,      1,
       1,      1,      1,      1,      1,      1,      1,      1,
       1,      1,      1,      1,      1,      1,      1,      1,
       1,      1,      1,      1,      1,      1,      1,      1,
       1,      2,      3,      5,      7,      9,     13,     17,
      22,     27,     34,     41,     49,     58,     67,     77,
      88,     99,    110,    122,    134,    145,    157,    169,
     180,    191,    201,    211,    220,    228,    235,    241,
     246,    249,    252,    254,    254,    253,    251,    248,
     244,    239,    234,    227,    220,    212,    204,    195,
     187,    178,    169,    161,    153,    146,    139,    132,
     127,    122,    119,    116,    115,    114,    115,    116,
     119,    122,    127,    132,    139,    146,    153,    161,
     169,    178,    187,    195,    204,    212,    220,    227,
     234,    239,    244,    248,    251,    253,    254,    254,
     252,    249,    246,    241,    235,    228,    220,    211,
     201,    191,    180,    169,    157,    145,    134,    122,
     110,     99,     88,     77,     67,     58,     49,     41,
      34,     27,     22,     17,     13,      9,      7,      5,
       3,      2,      1,      1,      1,      1,      1,      1,
       1,      1,      1,      1,      1,      1,      1,      1,
       1,      1,      1,      1,      1,      1,      1,      1,
       1,      1,      1,      1,      1,      1,      1,      1,
       1,      1,      1,      1,      1,      1,      1,      1,
       1,      1,      1,      1,      1,      1,      1,      1,
       1,      1,      1,      1,      1,      1,      1,      1,
       1,      1,      1,      1,      1,      1,      1,      1,
       1,      1,      1,      1,      1,      1,      1,      1,
       1,      1,      1,      1,      1,      1,      1,      1,
       1,      1,      1,      1,      1,      1,      1,      1,
       1,      1,      1,      1,      1,      1,      1,      1,
       1,      1,      1,      1,      1,      1,      1,      1,
       1,      1,      1,      1,      1,      1,      1,      1,
       1,      1,      1,      1,      1,      1,      1,      1,
       1,      1,      1,      1,      1,      1,      1,      1,
       1,      1,      1,      1,      1,      1,     64,     61,
      58,     55,     52,     49,     46,     43,     40,     37,
      34,     31,     28,     25,     22,     19,     16,     13,
      10,      7,      4,      1,      2,      5,      8,     11,
      14,     17,     20,     23,     26,     29,     32,     35,
      38,     41,     44,     47,     50,     53,     56,     59,
      62,     65,     68,     71,     74,     77,     80,     83,
      86,     89,     92,     95,     98,    101,    104,    107,
     110,    113,    116,    119,    122,    125,    128,    130,
     133,    136,    139,    142,    145,    148,    151,    154,
     157,    160,    163,    166,    169,    172,    175,    178,
     181,    184,    187,    190,    193,    196,    199,    202,
     205,    208,    211,    214,    217,    220,    223,    226,
     229,    232,    235,    238,    241,    244,    247,    250,
     253,    254,    251,    248,    245,    242,    239,    236,
     233,    230,    227,    224,    221,    218,    215,    212,
     209,    206,    203,    200,    197,    194,    191,    194,
     197,    200,    203,    206,    209,    212,    215,    218,
     221,    224,    227,    230,    233,    236,    239,    242,
     245,    248,    251,    254,    253,    250,    247,    244,
     241,    238,    235,    232,    229,    226,    223,    220,
     217,    214,    211,    208,    205,    202,    199,    196,
     193,    190,    187,    184,    181,    178,    175,    172,
     169,    166,    163,    160,    157,    154,    151,    148,
     145,    142,    139,    136,    133,    130,    128,    125,
     122,    119,    116,    113,    110,    107,    104,    101,
      98,     95,     92,     89,     86,     83,     80,     77,
      74,     71,     68,     65,     62,     59,     56,     53,
      50,     47,     44,     41,     38,     35,     32,     29,
      26,     23,     20,     17,     14,     11,      8,      5,
       2,      1,      4,      7,     10,     13,     16,     19,
      22,     25,     28,     31,     34,     37,     40,     43,
      46,     49,     52,     55,     58,     61,     64,    128,
     124,    120,    116,    112,    108,    104,    100,     96,
      92,     88,     84,     80,     76,     72,     68,     64,
      60,     56,     52,     48,     44,     41,     37,     33,
      29,     25,     21,     17,     13,      9,      5,      1,
       5,      9,     13,     17,     21,     25,     29,     33,
      37,     41,     44,     48,     52,     56,     60,     64,
      68,     72,     76,     80,     84,     88,     92,     96,
     100,    104,    108,    112,    116,    120,    124,    128,
     131,    135,    139,    143,    147,    151,    155,    159,
     163,    167,    171,    175,    179,    183,    187,    191,
     195,    199,    203,    207,    211,    214,    218,    222,
     226,    230,    234,    238,    242,    246,    250,    254,
     250,    246,    242,    238,    234,    230,    226,    222,
     218,    214,    211,    207,    203,    199,    195,    191,
     187,    183,    179,    175,    171,    167,    163,    159,
     155,    151,    147,    143,    139,    135,    131,    128,
     131,    135,    139,    143,    147,    151,    155,    159,
     163,    167,    171,    175,    179,    183,    187,    191,
     195,    199,    203,    207,    211,    214,    218,    222,
     226,    230,    234,    238,    242,    246,    250,    254,
     250,    246,    242,    238,    234,    230,    226,    222,
     218,    214,    211,    207,    203,    199,    195,    191,
     187,    183,    179,    175,    171,    167,    163,    159,
     155,    151,    147,    143,    139,    135,    131,    128,
     124,    120,    116,    112,    108,    104,    100,     96,
      92,     88,     84,     80,     76,     72,     68,     64,
      60,     56,     52,     48,     44,     41,     37,     33,
      29,     25,     21,     17,     13,      9,      5,      1,
       5,      9,     13,     17,     21,     25,     29,     33,
      37,     41,     44,     48,     52,     56,     60,     64,
      68,     72,     76,     80,     84,     88,     92,     96,
     100,    104,    108,    112,    116,    120,    124,    128,
       1,      1,      2,      2,      3,      3,      3,      4,
       4,      5,      5,      6,      6,      6,      7,      7,
       8,      9,      9,     10,     10,     11,     11,     12,
      12,     13,     14,     14,     15,     16,     16,     17,
      18,     19,     19,     20,     21,     22,     23,     23,
      24,     25,     26,     27,     28,     29,     30,     31,
      32,     33,     34,     35,     36,     37,     38,     40,
      41,     42,     43,     45,     46,     47,     49,     50,
      52,     53,     55,     56,     58,     59,     61,     63,
      64,     66,     68,     70,     72,     74,     76,     78,
      80,     82,     84,     86,     88,     90,     93,     95,
      98,    100,    103,    105,    108,    111,    113,    116,
     119,    122,    125,    128,    131,    135,    138,    141,
     145,    148,    152,    155,    159,    163,    167,    171,
     175,    179,    183,    188,    192,    197,    201,    206,
     211,    216,    221,    226,    232,    237,    243,    248,
     254,    248,    243,    237,    232,    226,    221,    216,
     211,    206,    201,    197,    192,    188,    183,    179,
     175,    171,    167,    163,    159,    155,    152,    148,
     145,    141,    138,    135,    131,    128,    125,    122,
     119,    116,    113,    111,    108,    105,    103,    100,
      98,     95,     93,     90,     88,     86,     84,     82,
      80,     78,     76,     74,     72,     70,     68,     66,
      64,     63,     61,     59,     58,     56,     55,     53,
      52,     50,     49,     47,     46,     45,     43,     42,
      41,     40,     38,     37,     36,     35,     34,     33,
      32,     31,     30,     29,     28,     27,     26,     25,
      24,     23,     23,     22,     21,     20,     19,     19,
      18,     17,     16,     16,     15,     14,     14,     13,
      12,     12,     11,     11,     10,     10,      9,      9,
       8,      7,      7,      6,      6,      6,      5,      5,
       4,      4,      3,      3,      3,      2,      2,      1,
       1,      1,      7,     12,     17,     22,     27,     32,
      36,     41,     45,     48,     52,     56,     59,     62,
      65,     68,     71,     74,     77,     79,     82,     84,
      86,     88,     90,     92,     94,     96,     98,     99,
     101,    102,    104,    105,    106,    108,    109,    110,
     111,    112,    113,    114,    115,    116,    117,    118,
     118,    119,    120,    120,    121,    122,    122,    123,
     123,    124,    125,    125,    125,    126,    126,    127,
     127,    128,    128,    128,    129,    129,    130,    130,
     130,    131,    132,    132,    133,    133,    134,    135,
     135,    136,    137,    137,    138,    139,    140,    141,
     142,    143,    144,    145,    146,    147,    149,    150,
     151,    153,    154,    156,    157,    159,    161,    163,
     165,    167,    169,    171,    173,    176,    178,    181,
     184,    187,    190,    193,    196,    199,    203,    207,
     210,    214,    219,    223,    228,    233,    238,    243,
     248,    254,    248,    243,    238,    233,    228,    223,
     219,    214,    210,    207,    203,    199,    196,    193,
     190,    187,    184,    181,    178,    176,    173,    171,
     169,    167,    165,    163,    161,    159,    157,    156,
     154,    153,    151,    150,    149,    147,    146,    145,
     144,    143,    142,    141,    140,    139,    138,    137,
     137,    136,    135,    135,    134,    133,    133,    132,
     132,    131,    130,    130,    130,    129,    129,    128,
     128,    128,    127,    127,    126,    126,    125,    125,
     125,    124,    123,    123,    122,    122,    121,    120,
     120,    119,    118,    118,    117,    116,    115,    114,
     113,    112,    111,    110,    109,    108,    106,    105,
     104,    102,    101,     99,     98,     96,     94,     92,
      90,     88,     86,     84,     82,     79,     77,     74,
      71,     68,     65,     62,     59,     56,     52,     48,
      45,     41,     36,     32,     27,     22,     17,     12,
       7,      1,    241,    229,    217,    205,    194,    184,
     174,    164,    155,    147,    138,    130,    123,    116,
     109,    102,     96,     90,     84,     79,     74,     69,
      64,     60,     55,     51,     48,     44,     41,     38,
      35,     32,     29,     27,     24,     22,     20,     18,
      16,     14,     13,     11,     10,      9,      8,      7,
       6,      5,      4,      4,      3,      3,      2,      2,
       1,      1,      1,      1,      1,      1,      1,      1,
       1,      2,      2,      2,      3,      3,      4,      4,
       5,      5,      6,      6,      7,      8,      9,      9,
      10,     11,     12,     13,     13,     14,     15,     16,
      17,     18,     19,     20,     21,     22,     23,     25,
      26,     27,     28,     29,     30,     31,     33,     34,
      35,     36,     37,     39,     40,     41,     42,     44,
      45,     46,     48,     49,     50,     51,     53,     54,
      55,     57,     58,     59,     61,     62,     64,     65,
      66,     68,     69,     70,     72,     73,     75,     76,
      77,     79,     80,     82,     83,     84,     86,     87,
      89,     90,     92,     93,     94,     96,     97,     99,
     100,    102,    103,    104,    106,    107,    109,    110,
     112,    113,    115,    116,    117,    119,    120,    122,
     123,    125,    126,    128,    129,    130,    132,    133,
     135,    136,    138,    139,    141,    142,    144,    145,
     147,    148,    149,    151,    152,    154,    155,    157,
     158,    160,    161,    163,    164,    166,    167,    169,
     170,    172,    173,    174,    176,    177,    179,    180,
     182,    183,    185,    186,    188,    189,    191,    192,
     194,    195,    197,    198,    199,    201,    202,    204,
     205,    207,    208,    210,    211,    213,    214,    216,
     217,    219,    220,    222,    223,    225,    226,    227,
     229,    230,    232,    233,    235,    236,    238,    239,
     241,    242,    244,    245,    247,    248,    250,    251,
     253,    254,    241,     11,     20,     29,     38,     46,
      54,     62,     69,     77,     83,     90,     96,    102,
     108,    114,    119,    125,    130,    134,    139,    144,
     148,    152,    156,    160,    163,    167,    170,    174,
     177,    180,    183,    186,    188,    191,    193,    196,
     198,    200,    202,    204,    206,    208,    210,    212,
     213,    215,    217,    218,    220,    221,    222,    224,
     225,    226,    227,    228,    229,    230,    231,    232,
     233,    234,    235,    236,    236,    237,    238,    239,
     239,    240,    240,    241,    242,    242,    243,    243,
     244,    244,    245,    245,    245,    246,    246,    247,
     247,    247,    248,    248,    248,    248,    249,    249,
     249,    249,    250,    250,    250,    250,    251,    251,
     251,    251,    251,    252,    252,    252,    252,    252,
     252,    252,    253,    253,    253,    253,    253,    253,
     253,    253,    253,    253,    254,    254,    254,    254,
     254,    254,    254,    244,    235,    226,    217,    209,
     201,    193,    186,    178,    172,    165,    159,    153,
     147,    141,    136,    130,    125,    121,    116,    111,
     107,    103,     99,     95,     92,     88,     85,     81,
      78,     75,     72,     69,     67,     64,     62,     59,
      57,     55,     53,     51,     49,     47,     45,     43,
      42,     40,     38,     37,     35,     34,     33,     31,
      30,     29,     28,     27,     26,     25,     24,     23,
      22,     21,     20,     19,     19,     18,     17,     16,
      16,     15,     15,     14,     13,     13,     12,     12,
      11,     11,     10,     10,     10,      9,      9,      8,
       8,      8,      7,      7,      7,      7,      6,      6,
       6,      6,      5,      5,      5,      5,      4,      4,
       4,      4,      4,      3,      3,      3,      3,      3,
       3,      3,      2,      2,      2,      2,      2,      2,
       2,      2,      2,      2,      1,      1,      1,      1,
       1,      1,      1,     11,    254,    248,    236,    220,
     199,    176,    151,    125,    100,     77,     55,     37,
      22,     11,      4,      1,      2,      6,     13,     23,
      35,     49,     63,     78,     92,    106,    118,    129,
     138,    145,    150,    153,    153,    152,    149,    145,
     139,    133,    126,    120,    113,    107,    101,     96,
      93,     90,     88,     88,     89,     90,     93,     96,
     100,    104,    109,    114,    118,    123,    127,    130,
     133,    136,    138,    139,    140,    140,    139,    139,
     138,    136,    135,    133,    132,    131,    129,    129,
     128,    128,    128,    128,    129,    130,    131,    132,
     134,    136,    137,    139,    141,    143,    144,    146,
     147,    148,    149,    150,    151,    151,    152,    152,
     152,    152,    152,    152,    153,    153,    153,    153,
     153,    154,    154,    155,    155,    156,    157,    158,
     159,    160,    161,    162,    163,    164,    165,    166,
     167,    167,    168,    169,    169,    170,    171,    171,
     172,    172,    173,    173,    174,    174,    175,    175,
     176,    176,    177,    178,    178,    179,    180,    181,
     181,    182,    183,    184,    184,    185,    186,    187,
     187,    188,    189,    189,    190,    191,    191,    192,
     193,    193,    194,    195,    195,    196,    196,    197,
     198,    198,    199,    200,    200,    201,    202,    202,
     203,    204,    204,    205,    206,    206,    207,    208,
     209,    209,    210,    211,    211,    212,    213,    213,
     214,    215,    215,    216,    217,    217,    218,    218,
     219,    220,    220,    221,    222,    222,    223,    224,
     225,    225,    226,    227,    227,    228,    229,    229,
     230,    231,    231,    232,    233,    233,    234,    235,
     235,    236,    237,    237,    238,    239,    239,    240,
     241,    241,    242,    243,    243,    244,    245,    245,
     246,    247,    247,    248,    249,    249,    250,    251,
     251,    252,    253,    253,    254,     67,     72,     81,
      93,    108,    125,    143,    162,    180,    197,    213,
     226,    237,    246,    251,    254,    254,    251,    247,
     240,    232,    223,    213,    203,    193,    184,    176,
     169,    163,    158,    155,    154,    154,    155,    158,
     161,    166,    171,    176,    181,    186,    191,    196,
     200,    203,    205,    207,    207,    207,    207,    205,
     204,    201,    199,    196,    193,    190,    188,    185,
     183,    181,    180,    179,    179,    179,    179,    180,
     181,    182,    184,    185,    187,    188,    190,    191,
     192,    193,    193,    194,    194,    194,    194,    194,
     193,    192,    192,    191,    190,    189,    188,    188,
     187,    187,    186,    186,    186,    186,    186,    186,
     187,    187,    187,    188,    188,    189,    189,    189,
     190,    190,    190,    190,    190,    190,    190,    190,
     190,    190,    190,    189,    189,    189,    189,    189,
     188,    188,    188,    188,    188,    188,    183,    174,
     162,    147,    130,    112,     93,     75,     58,     42,
      29,     18,      9,      4,      1,      1,      4,      8,
      15,     23,     32,     42,     52,     62,     71,     79,
      86,     92,     97,    100,    101,    101,    100,     97,
      94,     89,     84,     79,     74,     69,     64,     59,
      55,     52,     50,     48,     48,     48,     48,     50,
      51,     54,     56,     59,     62,     65,     67,     70,
      72,     74,     75,     76,     76,     76,     76,     75,
      74,     73,     71,     70,     68,     67,     65,     64,
      63,     62,     62,     61,     61,     61,     61,     61,
      62,     63,     63,     64,     65,     66,     67,     67,
      68,     68,     69,     69,     69,     69,     69,     69,
      68,     68,     68,     67,     67,     66,     66,     66,
      65,     65,     65,     65,     65,     65,     65,     65,
      65,     65,     65,     66,     66,     66,     66,     66,
      67,     67,     67,     67,     67,     67,      1,      1,
       1,      1,      1,      1,      1,      1,      1,      1,
       1,      1,      1,      1,      1,      1,      1,      1,
       1,      1,      1,      1,     85,     85,     85,     85,
      85,     85,     85,     85,     85,     85,     85,     85,
      85,     85,     85,     85,     85,     85,     85,     85,
      85,     85,     85,     85,     85,     85,     85,     85,
      85,     85,     85,     85,     85,     85,     85,     85,
      85,     85,     85,     85,     85,     85,    170,    170,
     170,    170,    170,    170,    170,    170,    170,    170,
     170,    170,    170,    170,    170,    170,    170,    170,
     170,    170,    170,    170,    170,    170,    170,    170,
     170,    170,    170,    170,    170,    170,    170,    170,
     170,    170,    170,    170,    170,    170,    170,    170,
     170,    254,    254,    254,    254,    254,    254,    254,
     254,    254,    254,    254,    254,    254,    254,    254,
     254,    254,    254,    254,    254,    254,    254,    254,
     254,    254,    254,    254,    254,    254,    254,    254,
     254,    254,    254,    254,    254,    254,    254,    254,
     254,    254,    254,    254,    170,    170,    170,    170,
     170,    170,    170,    170,    170,    170,    170,    170,
     170,    170,    170,    170,    170,    170,    170,    170,
     170,    170,    170,    170,    170,    170,    170,    170,
     170,    170,    170,    170,    170,    170,    170,    170,
     170,    170,    170,    170,    170,    170,    170,     85,
      85,     85,     85,     85,     85,     85,     85,     85,
      85,     85,     85,     85,     85,     85,     85,     85,
      85,     85,     85,     85,     85,     85,     85,     85,
      85,     85,     85,     85,     85,     85,     85,     85,
      85,     85,     85,     85,     85,     85,     85,     85,
      85,      1,      1,      1,      1,      1,      1,      1,
       1,      1,      1,      1,      1,      1,      1,      1,
       1,      1,      1,      1,      1,      1,      1,      1,
       1,      1,      1,      1,     18,     18,     18,     18,
      18,     18,     18,     18,     35,     35,     35,     35,
      35,     35,     35,     35,     35,     52,     52,     52,
      52,     52,     52,     52,     52,     68,     68,     68,
      68,     68,     68,     68,     68,     68,     85,     85,
      85,     85,     85,     85,     85,     85,    102,    102,
     102,    102,    102,    102,    102,    102,    102,    119,
     119,    119,    119,    119,    119,    119,    119,    136,
     136,    136,    136,    136,    136,    136,    136,    136,
     153,    153,    153,    153,    153,    153,    153,    153,
     153,    170,    170,    170,    170,    170,    170,    170,
     170,    187,    187,    187,    187,    187,    187,    187,
     187,    187,    203,    203,    203,    203,    203,    203,
     203,    203,    220,    220,    220,    220,    220,    220,
     220,    220,    220,    237,    237,    237,    237,    237,
     237,    237,    237,    254,    254,    254,    254,    254,
     254,    254,    254,    254,    237,    237,    237,    237,
     237,    237,    237,    237,    220,    220,    220,    220,
     220,    220,    220,    220,    220,    203,    203,    203,
     203,    203,    203,    203,    203,    187,    187,    187,
     187,    187,    187,    187,    187,    187,    170,    170,
     170,    170,    170,    170,    170,    170,    153,    153,
     153,    153,    153,    153,    153,    153,    153,    136,
     136,    136,    136,    136,    136,    136,    136,    136,
     119,    119,    119,    119,    119,    119,    119,    119,
     102,    102,    102,    102,    102,    102,    102,    102,
     102,     85,     85,     85,     85,     85,     85,     85,
      85,     68,     68,     68,     68,     68,     68,     68,
      68,     68,     52,     52,     52,     52,     52,     52,
      52,     52,     35,     35,     35,     35,     35,     35,
      35,     35,     35,     18,     18,     18,     18,     18,
      18,     18,     18,      1,      1,      1,      1,      1,
};


const prog_uint8_t* waveform_table[] = {
  wav_res_lfo_waveforms,
};


}  // namespace ambika
