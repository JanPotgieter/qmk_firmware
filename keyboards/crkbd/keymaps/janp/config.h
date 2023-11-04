/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#define MASTER_LEFT

#define TAPPING_TERM 180
#define TAPPING_TERM_PER_KEY
#define TAPPING_FORCE_HOLD
#define PERMISSIVE_HOLD
#define TAPPING_TOGGLE 1

#define CAPS_WORD_IDLE_TIMEOUT 1500  // 1.5 seconds

#define UNICODE_SELECTED_MODES UNICODE_MODE_LINUX

#ifdef RGB_MATRIX_ENABLE
#    define SPLIT_TRANSPORT_MIRROR
#    define RGB_MATRIX_KEYPRESSES
#    define RGB_TRIGGER_ON_KEYDOWN
#    define SPLIT_LAYER_STATE_ENABLE
#    define SPLIT_LED_STATE_ENABLE
#    define RGB_MATRIX_LED_FLUSH_LIMIT 30

#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 100
#    define RGB_MATRIX_DEFAULT_VAL 0
#    define RGB_MATRIX_DEFAULT_HUE 0
#    define RGB_MATRIX_DEFAULT_SAT 0

#    define RGB_MATRIX_HUE_STEP 25
#    define RGB_MATRIX_SAT_STEP 25
#    define RGB_MATRIX_VAL_STEP 25
#    define RGB_MATRIX_SPD_STEP 25
#endif
