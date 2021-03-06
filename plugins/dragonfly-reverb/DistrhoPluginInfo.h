/*
 * Dragonfly Reverb, a hall-style reverb plugin
 * Copyright (c) 2018 Michael Willis
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3 of
 * the License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * For a full copy of the GNU General Public License see the LICENSE file.
 */

#include <cstdint>

#ifndef DISTRHO_PLUGIN_INFO_H_INCLUDED
#define DISTRHO_PLUGIN_INFO_H_INCLUDED

#define DISTRHO_PLUGIN_BRAND "Dragonfly"
#define DISTRHO_PLUGIN_NAME  "Dragonfly Reverb"
#define DISTRHO_PLUGIN_URI   "https://github.com/michaelwillis/dragonfly-reverb"

#define DISTRHO_PLUGIN_HAS_UI        1
#define DISTRHO_PLUGIN_IS_RT_SAFE    1
#define DISTRHO_PLUGIN_NUM_INPUTS    2
#define DISTRHO_PLUGIN_NUM_OUTPUTS   2
// #define DISTRHO_PLUGIN_WANT_PROGRAMS 1
// #define DISTRHO_PLUGIN_WANT_STATE    1
// #define DISTRHO_UI_USE_NANOVG      1

#define DISTRHO_PLUGIN_LV2_CATEGORY "lv2:ReverbPlugin"

enum Parameters
{
    paramDry_level = 0,
    paramEarly_level,
    paramLate_level,
    paramSize,
    paramWidth,
    paramPredelay,
    paramDiffuse,
    paramLow_cut,
    paramLow_xover,
    paramLow_mult,
    paramHigh_cut,
    paramHigh_xover,
    paramHigh_mult,
    paramSpin,
    paramWander,
    paramCount
};

typedef struct {
  const char *name;
  const char *symbol;
  float range_min;
  float range_max;
  const char *unit;
} Param;

static Param params[paramCount] = {
  {"Dry Level",       "dry_level",    0.0f,   100.0f,   "%"},
  {"Early Level",     "early_level",  0.0f,   100.0f,   "%"},
  {"Late Level",      "late_level",   0.0f,   100.0f,   "%"},
  {"Size",            "size",        10.0f,    60.0f,   "m"},
  {"Width",           "width",       50.0f,   150.0f,   "%"},
  {"Predelay",        "delay",        0.0f,   100.0f,  "ms"},
  {"Diffuse",         "diffuse",      0.0f,   100.0f,   "%"},
  {"Low Cut",         "low_cut",      0.0f,   100.0f,  "Hz"},
  {"Low Crossover",   "low_xo",     200.0f,  1200.0f,  "Hz"},
  {"Low Decay Mult",  "low_mult",     0.5f,     2.5f,   "X"},
  {"High Cut",        "high_cut",     0.0f, 20000.0f,  "Hz"},
  {"High Crossover",  "high_xo",      0.0f, 20000.0f,  "Hz"},
  {"High Decay Mult", "high_mult",    0.2f,     1.2f,   "X"},
  {"Spin",            "spin",         1.0f,     5.0f,  "Hz"},
  {"Wander",          "wander",       5.0f,    25.0f,  "ms"}
};

typedef struct {
  const char *name;
  const float params[paramCount];
} Preset;

#define NUM_PRESETS 24

static Preset presets[NUM_PRESETS] = {
                             // dry, e_lev, l_lev, size, width, delay, diffuse, low_cut, low_xo, low_mult, high_cut, high_xo, high_mult, spin, wander
  {"Bright Room",            { 80.0,  10.0,  10.0, 10.0,  90.0,   4.0,    90.0,     4.0,    500,     0.80,    20000,    8000,      0.75,  1.0, 25.0 }},
  {"Clear Room",             { 80.0,  10.0,  10.0, 10.0,  90.0,   4.0,    90.0,     4.0,    500,     0.90,    16000,    6000,      0.50,  1.0, 25.0 }},
  {"Dark Room",              { 80.0,  10.0,  10.0, 10.0,  90.0,   4.0,    50.0,     4.0,    500,     1.20,     7000,    5000,      0.35,  1.0, 25.0 }},
  {"Acoustic Studio",        { 85.0,   5.0,  10.0, 12.0,  90.0,   8.0,    75.0,     4.0,    450,     1.50,     7500,    5000,      0.80,  2.5,  7.0 }},
  {"Electric Studio",        { 85.0,   5.0,  10.0, 12.0,  90.0,   6.0,    45.0,     4.0,    250,     1.25,     7500,    6000,      0.70,  2.5,  7.0 }},
  {"Percussion Studio",      { 90.0,   0.0,  10.0, 12.0,  90.0,   6.0,    20.0,    20.0,    200,     1.75,     6000,    5000,      0.45,  2.5,  7.0 }},
  {"Vocal Studio",           { 90.0,   0.0,  10.0, 12.0,  90.0,   0.0,    60.0,     4.0,    400,     1.20,     6000,    5000,      0.40,  2.5,  7.0 }},
  {"Small Chamber",          { 80.0,  10.0,  15.0, 16.0,  80.0,   8.0,    70.0,     4.0,    500,     1.10,     8000,    5500,      0.35,  1.2, 10.0 }},
  {"Large Chamber",          { 80.0,  10.0,  15.0, 20.0,  80.0,   8.0,    90.0,     4.0,    500,     1.30,     7000,    5000,      0.25,  1.8, 12.0 }},
  {"Small Bright Hall",      { 80.0,  10.0,  15.0, 24.0,  80.0,  12.0,    90.0,     4.0,    400,     1.10,    12000,    6000,      0.75,  2.5, 13.0 }},
  {"Small Clear Hall",       { 80.0,  10.0,  15.0, 24.0, 100.0,   4.0,    90.0,     4.0,    500,     1.30,     7500,    5500,      0.50,  3.3, 15.0 }},
  {"Small Dark Hall",        { 80.0,  10.0,  15.0, 24.0, 100.0,  12.0,    60.0,     4.0,    500,     1.50,     6000,    4000,      0.35,  2.5, 10.0 }},
  {"Small Percussion Hall",  { 85.0,   0.0,  15.0, 24.0, 100.0,  12.0,    30.0,    20.0,    250,     2.00,     5000,    4000,      0.35,  2.0, 13.0 }},
  {"Small Vocal Hall",       { 85.0,   0.0,  15.0, 24.0, 100.0,   4.0,    60.0,     4.0,    500,     1.25,     6000,    5000,      0.35,  3.1, 15.0 }},
  {"Medium Bright Hall",     { 80.0,   5.0,  20.0, 30.0, 100.0,  18.0,    90.0,     4.0,    400,     1.25,    10000,    6000,      0.60,  2.9, 15.0 }},
  {"Medium Clear Hall",      { 80.0,   5.0,  20.0, 30.0, 100.0,   8.0,    90.0,     4.0,    500,     1.50,     7500,    5500,      0.50,  2.9, 15.0 }},
  {"Medium Dark Hall",       { 80.0,   5.0,  20.0, 30.0, 100.0,  18.0,    60.0,     4.0,    500,     1.75,     6000,    4000,      0.40,  2.9, 15.0 }},
  {"Medium Vocal Hall",      { 80.0,   0.0,  20.0, 30.0, 100.0,   8.0,    75.0,     4.0,    600,     1.50,     6000,    5000,      0.40,  2.8, 16.0 }},
  {"Large Bright Hall",      { 75.0,   0.0,  25.0, 40.0, 100.0,  20.0,    90.0,     4.0,    400,     1.50,     8000,    6000,      0.50,  2.1, 20.0 }},
  {"Large Clear Hall",       { 75.0,   0.0,  25.0, 40.0, 100.0,  12.0,    80.0,     4.0,    550,     2.00,     8000,    5000,      0.40,  2.1, 20.0 }},
  {"Large Dark Hall",        { 75.0,   0.0,  25.0, 40.0, 100.0,  20.0,    60.0,     4.0,    600,     2.50,     6000,    3200,      0.20,  2.1, 20.0 }},
  {"Large Vocal Hall",       { 75.0,   0.0,  25.0, 40.0, 100.0,  12.0,    80.0,     4.0,    700,     2.25,     6000,    4500,      0.30,  2.1, 17.0 }},
  {"Great Hall",             { 70.0,   0.0,  30.0, 50.0,  90.0,  20.0,    95.0,     4.0,    750,     2.50,     5500,    4000,      0.30,  2.6, 22.0 }},
  {"Cathedral",              { 70.0,   0.0,  30.0, 60.0,  80.0,  24.0,    90.0,     4.0,    850,     2.25,     6000,    3200,      0.30,  2.0, 25.0 }}
};

const uint32_t defaultPreset = 15; // Medium Clear Hall

#endif // DISTRHO_PLUGIN_INFO_H_INCLUDED
