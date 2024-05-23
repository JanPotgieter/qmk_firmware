/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

// #define VIAL_KEYBOARD_UID {0x11, 0x6B, 0xDE, 0x73, 0x99, 0x79, 0xE0, 0x60}

#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES

#define DYNAMIC_KEYMAP_LAYER_COUNT 4

#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD

#define TAPPING_TERM 220
#define IGNORE_MOD_TAP_INTERRUPT
#define TAPPING_FORCE_HOLD
#define PERMISSIVE_HOLD

 // if you tap and hold within 60ms, it will repeat the tapped key, not the hold key - set to 0 to disable
#define QUICK_TAP_TERM 60