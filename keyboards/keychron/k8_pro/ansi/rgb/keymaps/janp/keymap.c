/* Copyright 2021 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum layers{
  QWERTY,
  BLANK,
  COLEMAK,
  EXTEND,
  SYMBOLS,
  QK,
  GAMING
};

// Tap Dance keycodes
enum td_keycodes {
    SYM_PAR, // Single tap: (    Double tap:  )
    SYM_BRA, // Single tap: [    Double tap:  ]
    SYM_CUR, // Single tap: {    Double tap:  }
    SYM_COM, // Single tap: <    Double tap:  > 
    SYM_QUE // Single tap: ?    Double tap:  ! 
};

// Define a type containing as many tapdance states as you need
typedef enum {
    TD_NONE,
    TD_SINGLE_TAP,
    TD_DOUBLE_TAP
} td_state_t;

// Create a global instance of the tapdance state type
static td_state_t td_state;

// Declare your tapdance functions:

// Function to determine the current tapdance state
td_state_t cur_dance(qk_tap_dance_state_t *state);

// `finished` and `reset` functions for each tapdance keycode
void sym_par_finished(qk_tap_dance_state_t *state, void *user_data);
void sym_par_reset(qk_tap_dance_state_t *state, void *user_data);
void sym_bra_finished(qk_tap_dance_state_t *state, void *user_data);
void sym_bra_reset(qk_tap_dance_state_t *state, void *user_data);
void sym_cur_finished(qk_tap_dance_state_t *state, void *user_data);
void sym_cur_reset(qk_tap_dance_state_t *state, void *user_data);
void sym_com_finished(qk_tap_dance_state_t *state, void *user_data);
void sym_com_reset(qk_tap_dance_state_t *state, void *user_data);
void sym_que_finished(qk_tap_dance_state_t *state, void *user_data);
void sym_que_reset(qk_tap_dance_state_t *state, void *user_data);

// Determine the tapdance state to return
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        else return TD_NONE;
    }

    if (state->count == 2) return TD_DOUBLE_TAP;
    else return TD_NONE; // Any number higher than the maximum state value you return above
}

// Handle the possible states for each tapdance keycode you define:

void sym_par_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            register_code16(KC_9);
            break;
        case TD_DOUBLE_TAP: // Allow nesting of 2 parens `((` within tapping term
            register_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            register_code16(KC_0);
            break;
        default:
            break;
    }
}

void sym_par_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_9);
            unregister_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        case TD_DOUBLE_TAP:
            unregister_code16(KC_0);
            unregister_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        default:
            break;
    }
}




void sym_bra_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_code16(KC_LBRC);
            break;
        case TD_DOUBLE_TAP: // Allow nesting of 2 parens `((` within tapping term
            register_code16(KC_RBRC);
            break;
        default:
            break;
    }
}

void sym_bra_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_LBRC);
            break;
        case TD_DOUBLE_TAP:
            unregister_code16(KC_RBRC);
            break;
        default:
            break;
    }
}





void sym_cur_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            register_code16(KC_LBRC);
            break;
        case TD_DOUBLE_TAP: // Allow nesting of 2 parens `((` within tapping term
            register_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            register_code16(KC_RBRC);
            break;
        default:
            break;
    }
}

void sym_cur_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_LBRC);
            unregister_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        case TD_DOUBLE_TAP:
            unregister_code16(KC_RBRC);
            unregister_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        default:
            break;
    }
}





void sym_com_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            register_code16(KC_COMM);
            break;
        case TD_DOUBLE_TAP: // Allow nesting of 2 parens `((` within tapping term
            register_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            register_code16(KC_DOT);
            break;
        default:
            break;
    }
}

void sym_com_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_COMM);
            unregister_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        case TD_DOUBLE_TAP:
            unregister_code16(KC_DOT);
            unregister_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        default:
            break;
    }
}




void sym_que_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            register_code16(KC_SLSH);
            break;
        case TD_DOUBLE_TAP: // Allow nesting of 2 parens `((` within tapping term
            register_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            register_code16(KC_1);
            break;
        default:
            break;
    }
}

void sym_que_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_SLSH);
            unregister_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        case TD_DOUBLE_TAP:
            unregister_code16(KC_1);
            unregister_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        default:
            break;
    }
}

// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
qk_tap_dance_action_t tap_dance_actions[] = {
    [SYM_PAR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sym_par_finished, sym_par_reset),
    [SYM_BRA] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sym_bra_finished, sym_bra_reset),
    [SYM_CUR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sym_cur_finished, sym_cur_reset),
    [SYM_COM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sym_com_finished, sym_com_reset),
    [SYM_QUE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sym_que_finished, sym_que_reset)
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[QWERTY] = LAYOUT_ansi_87( 
     KC_ESC,                  KC_F1,          KC_F2,         KC_F3,          KC_F4,          KC_F5,           KC_F6,                   KC_F7,         KC_F8,          KC_F9,           KC_F10,                 KC_F11,              KC_F12,                    KC_PSCR,      KC_NO,           RGB_TOG,
     KC_GRV,                  KC_1,           KC_2,          KC_3,           KC_4,           KC_5,            KC_6,                    KC_EQL,        KC_7,           KC_8,            KC_9,                   KC_0,                KC_MINS,       KC_BSPC,    KC_INS,       KC_HOME,         KC_PGUP,
     KC_TAB,                  KC_Q,           KC_W,          KC_E,           KC_R,           KC_T,            KC_LBRC,                 KC_Y,          KC_U,           KC_I,            KC_O,                   KC_P,                KC_QUOT,       KC_BSLS,    KC_DEL,       KC_END,          KC_PGDN,
     LT(EXTEND, KC_BSPC),     LGUI_T(KC_A),   LALT_T(KC_S),  LCTL_T(KC_D),   LSFT_T(KC_F),   KC_G,            KC_RBRC,                 KC_H,          RSFT_T(KC_J),   RCTL_T(KC_K),    LALT_T(KC_L),           RGUI_T(KC_SCOLON),                  KC_ENT,                 
     KC_LSFT,                                 KC_Z,          KC_X,           KC_C,           KC_V,            KC_B,                    KC_SLSH,       KC_N,           KC_M,            KC_COMM,                KC_DOT,                             KC_RSFT,                  KC_UP,    
     KC_LCTL,                 KC_LGUI,        KC_LALT,                                                        LT(SYMBOLS, KC_SPC),                                                     LT(EXTEND, KC_BSPC),    KC_RALT,             KC_RGUI,       KC_RCTL,    KC_LEFT,      KC_DOWN,         KC_RGHT),
[BLANK] = LAYOUT_ansi_87( 
     KC_TRNS,                 KC_TRNS,        KC_TRNS,       KC_TRNS,        KC_TRNS,        KC_TRNS,         KC_TRNS,                 KC_TRNS,       KC_TRNS,        KC_TRNS,         KC_TRNS,                KC_TRNS,             KC_TRNS,                   KC_TRNS,      KC_TRNS,         KC_TRNS,
     KC_TRNS,                 KC_TRNS,        KC_TRNS,       KC_TRNS,        KC_TRNS,        KC_TRNS,         KC_TRNS,                 KC_TRNS,       KC_TRNS,        KC_TRNS,         KC_TRNS,                KC_TRNS,             KC_TRNS,       KC_TRNS,    KC_TRNS,      KC_TRNS,         KC_TRNS,
     KC_TRNS,                 KC_TRNS,        KC_TRNS,       KC_TRNS,        KC_TRNS,        KC_TRNS,         KC_TRNS,                 KC_TRNS,       KC_TRNS,        KC_TRNS,         KC_TRNS,                KC_TRNS,             KC_TRNS,       KC_TRNS,    KC_TRNS,      KC_TRNS,         KC_TRNS,
     KC_TRNS,                 KC_TRNS,        KC_TRNS,       KC_TRNS,        KC_TRNS,        KC_TRNS,         KC_TRNS,                 KC_TRNS,       KC_TRNS,        KC_TRNS,         KC_TRNS,                KC_TRNS,                            KC_TRNS,                 
     KC_TRNS,                                 KC_TRNS,       KC_TRNS,        KC_TRNS,        KC_TRNS,         KC_TRNS,                 KC_TRNS,       KC_TRNS,        KC_TRNS,         KC_TRNS,                KC_TRNS,                            KC_TRNS,                  KC_TRNS,    
     KC_TRNS,                 KC_TRNS,        KC_TRNS,                                                        KC_TRNS,                                                                 KC_TRNS,                KC_TRNS,             KC_TRNS,       KC_TRNS,    KC_TRNS,      KC_TRNS,         KC_TRNS),
[COLEMAK] = LAYOUT_ansi_87( 
     KC_ESC,                  KC_F1,          KC_F2,         KC_F3,          KC_F4,          KC_F5,           KC_F6,                   KC_F7,         KC_F8,          KC_F9,           KC_F10,                 KC_F11,              KC_F12,                    KC_PSCR,      KC_NO,           RGB_TOG,
     KC_GRV,                  KC_1,           KC_2,          KC_3,           KC_4,           KC_5,            KC_6,                    KC_EQL,        KC_7,           KC_8,            KC_9,                   KC_0,                KC_MINS,       KC_BSPC,    KC_INS,       KC_HOME,         KC_PGUP,
     KC_TAB,                  KC_Q,           KC_W,          KC_F,           KC_P,           KC_B,            KC_LBRC,                 KC_J,          KC_L,           KC_U,            KC_Y,                   KC_SCLN,             KC_QUOT,       KC_BSLS,    KC_DEL,       KC_END,          KC_PGDN,
     LT(EXTEND, KC_BSPC),     LGUI_T(KC_A),   LALT_T(KC_R),  LCTL_T(KC_S),   LSFT_T(KC_T),   KC_G,            KC_RBRC,                 KC_M,          RSFT_T(KC_N),   RCTL_T(KC_E),    LALT_T(KC_I),           RGUI_T(KC_O),                       KC_ENT,                 
     KC_LSFT,                                 KC_X,          KC_C,           KC_D,           KC_V,            KC_Z,                    KC_SLSH,       KC_K,           KC_H,            KC_COMM,                KC_DOT,                             KC_RSFT,                  KC_UP,    
     KC_LCTL,                 KC_LGUI,        KC_LALT,                                                        LT(SYMBOLS, KC_SPC),                                                     LT(EXTEND, KC_BSPC),    KC_RALT,             KC_RGUI,       KC_RCTL,    KC_LEFT,      KC_DOWN,         KC_RGHT),

[EXTEND] = LAYOUT_ansi_87(      
     TG(GAMING),              KC_BRID,        KC_BRIU,       KC_NO,          KC_NO,          RGB_VAD,         RGB_VAI,                 KC_MPRV,       KC_MPLY,        KC_MNXT,         KC_MUTE,                KC_VOLD,             KC_VOLU,                   RGB_MOD,      RGB_RMOD,        RGB_TOG,
     KC_CAPS,                 BT_HST1,        BT_HST2,       BT_HST3,        KC_NO,          KC_NO,           KC_NO,                   KC_NO,         KC_NO,          KC_NO,           KC_NO,                  KC_NO,               KC_NO,         KC_BSPC,    RGB_VAI,      RGB_HUI,         RGB_SAI,
     KC_TRNS,                 KC_ESC,         KC_NO,         KC_NO,          KC_NO,          KC_NO,           KC_NO,                   KC_PGUP,       KC_HOME,        KC_UP,           KC_END,                 KC_DEL,              KC_NO,         KC_NO,      RGB_VAD,      RGB_HUD,         RGB_SAD,
     KC_BSPC,                 KC_LGUI,        KC_LALT,       KC_LCTRL,       KC_LSHIFT,      KC_NO,           KC_NO,                   KC_PGDN,       KC_LEFT,        KC_DOWN,         KC_RIGHT,               KC_BSPACE,                          KC_ENT,                 
     KC_TRNS,                                 LCTL(KC_Z),    LCTL(KC_X),     LCTL(KC_C),     LCTL(KC_V),      KC_NO,                   KC_NO,         KC_NO,          KC_NO,           KC_NO,                  KC_NO,                              KC_RSFT,                  KC_UP,    
     KC_TRNS,                 KC_LGUI,        KC_LALT,                                                        KC_SPC,                                                                  KC_NO,                  KC_RALT,             KC_RGUI,       KC_RCTL,    KC_LEFT,      KC_DOWN,         KC_RGHT),

[SYMBOLS] = LAYOUT_ansi_87( 
     TO(QK),                  KC_NO,          KC_NO,         KC_NO,          KC_NO,          KC_NO,           KC_NO,                   KC_NO,         KC_NO,          KC_NO,           KC_NO,                  KC_NO,               KC_NO,                     KC_NO,        KC_NO,           KC_NO,
     KC_NO,                   KC_NO,          KC_NO,         KC_NO,          KC_NO,          KC_NO,           KC_NO,                   KC_NO,         KC_NO,          KC_NO,           KC_NO,                  KC_NO,               KC_NO,         KC_BSPC,    KC_NO,        KC_NO,           KC_NO,
     KC_NO,                   TD(SYM_QUE),    KC_GRV,        LSFT(KC_MINS),  KC_MINS,        LSFT(KC_EQL),    KC_NO,                   KC_SLSH,       KC_7,           KC_8,            KC_9,                   LSFT(KC_EQL),        KC_MINS,       KC_NO,      KC_NO,        KC_NO,           KC_NO,
     KC_BSPC,                 TD(SYM_COM),    TD(SYM_BRA),   TD(SYM_CUR),    TD(SYM_PAR),    KC_EQL,          KC_NO,                   LSFT(KC_8),    KC_4,           KC_5,            KC_6,                   KC_DOT,                             KC_ENT,                 
     KC_TRNS,                                 KC_SLSH,       LSFT(KC_4),     LSFT(KC_7),     LSFT(KC_BSLS),   KC_NO,                   KC_NO,         KC_0,           KC_1,            KC_2,                   KC_3,                               KC_RSFT,                  KC_UP,    
     KC_NO,                   KC_NO,          KC_NO,                                                          KC_NO,                                                                   KC_SPC,                 KC_NO,               KC_NO,         KC_NO,      KC_LEFT,      KC_DOWN,         KC_RGHT),
[GAMING] = LAYOUT_ansi_87( 
     KC_ESC,                  KC_F1,          KC_F2,         KC_F3,          TG(GAMING),     KC_F5,           KC_F6,                   KC_F7,         KC_F8,          KC_F9,           KC_F10,                 KC_F11,              KC_F12,                    KC_PSCR,      KC_NO,           RGB_TOG,
     KC_GRV,                  KC_1,           KC_2,          KC_3,           KC_4,           KC_5,            KC_6,                    KC_EQL,        KC_7,           KC_8,            KC_9,                   KC_0,                KC_MINS,       KC_BSPC,    KC_INS,       KC_HOME,         KC_PGUP,
     KC_TAB,                  KC_Q,           KC_W,          KC_E,           KC_R,           KC_T,            KC_LBRC,                 KC_Y,          KC_U,           KC_I,            KC_O,                   KC_P,                KC_QUOT,       KC_BSLS,    KC_DEL,       KC_END,          KC_PGDN,
     KC_CAPS,                 KC_A,           KC_S,          KC_D,           KC_F,           KC_G,            KC_RBRC,                 KC_H,          KC_J,           KC_K,            KC_L,                   KC_SCOLON,                          KC_ENT,                 
     KC_LSFT,                                 KC_Z,          KC_X,           KC_C,           KC_V,            KC_B,                    KC_SLSH,       KC_N,           KC_M,            KC_COMM,                KC_DOT,                             KC_RSFT,                  KC_UP,    
     KC_LCTL,                 KC_LGUI,        KC_LALT,                                                        KC_SPC,                                                                  LT(EXTEND, KC_BSPC),    KC_RALT,             KC_RGUI,       KC_RCTL,    KC_LEFT,      KC_DOWN,         KC_RGHT)
};
