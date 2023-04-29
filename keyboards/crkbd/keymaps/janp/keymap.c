/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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

#include QMK_KEYBOARD_H
#include <stdio.h>

enum layers{
  BAS,
  SYM,
  UNI,
  NAV,
  MSE,
  FN1,
  FN2
};

// Define a type containing as many tapdance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_DOUBLE_TAP,
    TD_TRIPLE_TAP,
    TD_QUAD_TAP,
    TD_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// Tap Dance enums
enum {
    BRA, // Single tap: [    Double tap:  ]   Hold: L_GUI
    COM,  // Single tap: <    Double tap:  >   Hold: L_SFT
    CUR, // Single tap: {    Double tap:  }   Hold: L_CTL
    PAR, // Single tap: (    Double tap:  )   Hold: L_ALT
    FNC,
    BSP,
    DEL,
    SLC,
    UNI_E
};

td_state_t complex_dance(qk_tap_dance_state_t *state);

// For the x tap dance. Put it here so it can be used in any keymap
void bra_finished(qk_tap_dance_state_t *state, void *user_data);
void bra_reset(qk_tap_dance_state_t *state, void *user_data);
void com_finished(qk_tap_dance_state_t *state, void *user_data);
void com_reset(qk_tap_dance_state_t *state, void *user_data);
void cur_finished(qk_tap_dance_state_t *state, void *user_data);
void cur_reset(qk_tap_dance_state_t *state, void *user_data);
void par_finished(qk_tap_dance_state_t *state, void *user_data);
void par_reset(qk_tap_dance_state_t *state, void *user_data);
void fnc_finished(qk_tap_dance_state_t *state, void *user_data);
void fnc_reset(qk_tap_dance_state_t *state, void *user_data);
void bsp_finished(qk_tap_dance_state_t *state, void *user_data);
void bsp_reset(qk_tap_dance_state_t *state, void *user_data);
void del_finished(qk_tap_dance_state_t *state, void *user_data);
void del_reset(qk_tap_dance_state_t *state, void *user_data);
void slc_finished(qk_tap_dance_state_t *state, void *user_data);
void slc_reset(qk_tap_dance_state_t *state, void *user_data);
void uni_e_finished(qk_tap_dance_state_t *state, void *user_data);
void uni_e_reset(qk_tap_dance_state_t *state, void *user_data);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BAS] = LAYOUT_split_3x6_3(
  //,----------------------------------------------------------------------------------------.                    ,-----------------------------------------------------------------------------------------------.
            KC_ESC,           KC_Q,           KC_W,           KC_F,           KC_P,      KC_B,                                KC_J,           KC_L,           KC_U,           KC_Y,        KC_QUOT,        TD(DEL),
  //|-------------+---------------+---------------+---------------+---------------+----------|                    |---------------+---------------+---------------+---------------+---------------+---------------|
            KC_TAB,   LGUI_T(KC_A),   LALT_T(KC_R),   LCTL_T(KC_S),   LSFT_T(KC_T),      KC_G,                                KC_M,   RSFT_T(KC_N),   RCTL_T(KC_E),   LALT_T(KC_I),   RGUI_T(KC_O),        KC_SCLN,
  //|-------------+---------------+---------------+---------------+---------------+----------|                    |---------------+---------------+---------------+---------------+---------------+---------------|
           TD(FNC),           KC_Z,           KC_X,           KC_C,           KC_D,      KC_V,                                KC_K,           KC_H,        KC_COMM,         KC_DOT,        KC_MINS,LT(UNI, KC_SLSH),
  //|-------------+---------------+---------------+---------------+---------------+----------+------|   |---------+---------------+---------------+---------------+---------------+---------------+---------------|
                                                                    KC_LCTL, TD(SLC), MO(NAV),                  KC_SPC,   TD(BSP),  KC_ENT 
                                                                //`---------------------------------'   `---------------------------------'

  ),

  [SYM] = LAYOUT_split_3x6_3(
  //,----------------------------------------------------------------------------------------.                    ,-----------------------------------------------------------------------------------------------.
           KC_TILD,         KC_GRV,        KC_EXLM,        KC_QUES,        KC_AMPR,   KC_PIPE,                             KC_PLUS,           KC_7,           KC_8,           KC_9,        KC_SLSH,        TD(DEL),
  //|-------------+---------------+---------------+---------------+---------------+----------|                    |---------------+---------------+---------------+---------------+---------------+---------------|
           KC_HASH,        TD(BRA),        TD(COM),        TD(CUR),        TD(PAR),   KC_UNDS,                             KC_MINS,   LGUI_T(KC_4),   LALT_T(KC_5),   LCTL_T(KC_6),LGUI_T(KC_ASTR),        KC_COMM,
  //|-------------+---------------+---------------+---------------+---------------+----------|                    |---------------+---------------+---------------+---------------+---------------+---------------|
           KC_CIRC,        KC_PERC,          KC_AT,         KC_DLR,         KC_EQL,   KC_MINS,                                KC_0,           KC_1,           KC_2,           KC_3,         KC_DOT,        KC_BSLS,
  //|-------------+---------------+---------------+---------------+---------------+----------+------|   |---------+---------------+---------------+---------------+---------------+---------------+---------------|
                                                                    KC_NO, TG(SYM),   KC_NO,          KC_SPC,   TD(BSP),   KC_ENT
                                                                //`---------------------------------'   `---------------------------------'

  ),

  [UNI] = LAYOUT_split_3x6_3(
  //,----------------------------------------------------------------------------------------.                    ,-----------------------------------------------------------------------------------------------.
             KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,     KC_NO,                               KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
  //|-------------+---------------+---------------+---------------+---------------+----------|                    |---------------+---------------+---------------+---------------+---------------+---------------|
             KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,     KC_NO,                               KC_NO,          KC_NO,      TD(UNI_E),           KC_I,           KC_O,        KC_LSFT,
  //|-------------+---------------+---------------+---------------+---------------+----------|                    |---------------+---------------+---------------+---------------+---------------+---------------|
             KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,     KC_NO,                               KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,        KC_TRNS,
  //|-------------+---------------+---------------+---------------+---------------+----------+------|   |---------+---------------+---------------+---------------+---------------+---------------+---------------|
                                                                                 KC_NO, KC_NO, KC_NO,    KC_NO,   KC_NO,  KC_NO 
                                                                //`---------------------------------'   `---------------------------------'

  ),

  [NAV] = LAYOUT_split_3x6_3(
  //,----------------------------------------------------------------------------------------.                    ,-----------------------------------------------------------------------------------------------.
             KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,     KC_NO,                             KC_PGUP,        KC_HOME,          KC_UP,         KC_END,          KC_NO,        TD(DEL),
  //|-------------+---------------+---------------+---------------+---------------+----------|                    |---------------+---------------+---------------+---------------+---------------+---------------|
             KC_NO,        KC_LGUI,        KC_LALT,        KC_LCTL,        KC_LSFT,     KC_NO,                             KC_PGDN,        KC_LEFT,        KC_DOWN,        KC_RGHT,        TD(DEL),          KC_NO,
  //|-------------+---------------+---------------+---------------+---------------+----------|                    |---------------+---------------+---------------+---------------+---------------+---------------|
             KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,     KC_NO,                               KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
  //|-------------+---------------+---------------+---------------+---------------+----------+------|   |---------+---------------+---------------+---------------+---------------+---------------+---------------|
                                                                           KC_NO,   KC_NO,   KC_TRNS,    LT(MSE, KC_SPC),   TD(BSP),   KC_ENT
                                                                //`---------------------------------'   `---------------------------------'

  ),

  [MSE] = LAYOUT_split_3x6_3(
  //,----------------------------------------------------------------------------------------.                    ,-----------------------------------------------------------------------------------------------.
             KC_NO,          KC_NO,          KC_NO,        KC_WH_U,          KC_NO,     KC_NO,                               KC_NO,          KC_NO,        KC_MS_U,          KC_NO,          KC_NO,          KC_NO,
  //|-------------+---------------+---------------+---------------+---------------+----------|                    |---------------+---------------+---------------+---------------+---------------+---------------|
             KC_NO,     C(KC_WH_U),          KC_NO,        KC_BTN2,        KC_BTN1,     KC_NO,                               KC_NO,        KC_MS_L,        KC_MS_D,        KC_MS_R,          KC_NO,          KC_NO,
  //|-------------+---------------+---------------+---------------+---------------+----------|                    |---------------+---------------+---------------+---------------+---------------+---------------|
             KC_NO,     C(KC_WH_D),          KC_NO,        KC_WH_D,          KC_NO,     KC_NO,                               KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,         KC_NO,
  //|-------------+---------------+---------------+---------------+---------------+----------+------|   |---------+---------------+---------------+---------------+---------------+---------------+---------------|
                                                                           KC_NO,   KC_NO,   KC_TRNS,            KC_TRNS,   KC_NO,   KC_NO
                                                                //`---------------------------------'   `---------------------------------'

  ),

  [FN1] = LAYOUT_split_3x6_3(
  //,----------------------------------------------------------------------------------------.                    ,-----------------------------------------------------------------------------------------------.
             KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,     KC_F6,                               KC_F7,          KC_F8,          KC_F9,         KC_F10,         KC_F11,         KC_F12,
  //|-------------+---------------+---------------+---------------+---------------+----------|                    |---------------+---------------+---------------+---------------+---------------+---------------|
           MO(FN2),          KC_NO,        KC_MRWD,        KC_MPLY,        KC_MFFD,     KC_NO,                             KC_BRIU,        KC_VOLD,        KC_MUTE,        KC_VOLU,          KC_NO,          KC_NO,
  //|-------------+---------------+---------------+---------------+---------------+----------|                    |---------------+---------------+---------------+---------------+---------------+---------------|
           KC_TRNS,        KC_PSCR,        KC_RALT,          KC_NO,          KC_NO,     KC_NO,                             KC_BRID,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
  //|-------------+---------------+---------------+---------------+---------------+----------+------|   |---------+---------------+---------------+---------------+---------------+---------------+---------------|
                                                                             KC_NO,   KC_NO,  KC_NO,              KC_NO,    KC_NO,   KC_NO
                                                                //`---------------------------------'   `---------------------------------'

  ),

  [FN2] = LAYOUT_split_3x6_3(
  //,----------------------------------------------------------------------------------------.                    ,-----------------------------------------------------------------------------------------------.
           QK_BOOT,          KC_NO,          KC_NO,          KC_NO,          KC_NO,     KC_NO,                             RGB_TOG,        RGB_VAI,        RGB_HUI,        RGB_SAI,        RGB_SPI,          KC_NO,
  //|-------------+---------------+---------------+---------------+---------------+----------|                    |---------------+---------------+---------------+---------------+---------------+---------------|
           KC_TRNS,          KC_NO,          KC_NO,          KC_NO,          KC_NO,     KC_NO,                             RGB_MOD,        RGB_VAD,        RGB_HUD,        RGB_SAD,        RGB_SPD,          KC_NO,
  //|-------------+---------------+---------------+---------------+---------------+----------|                    |---------------+---------------+---------------+---------------+---------------+---------------|
           KC_TRNS,          KC_NO,          KC_NO,          KC_NO,          KC_NO,     KC_NO,                               KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
  //|-------------+---------------+---------------+---------------+---------------+----------+------|   |---------+---------------+---------------+---------------+---------------+---------------+---------------|
                                                                              KC_NO,   KC_NO,  KC_NO,             KC_NO,   KC_NO,   KC_NO
                                                                //`---------------------------------'   `---------------------------------'

  )
};



td_state_t complex_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        else return TD_HOLD;
    } else if (state->count == 2 || !state->pressed) return TD_DOUBLE_TAP;
    else return TD_UNKNOWN; 
}

td_state_t uni_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        else return TD_UNKNOWN;
    } else if (state->count == 2) {
        if (state->interrupted || !state->pressed) return TD_DOUBLE_TAP;
        else return TD_UNKNOWN;
    } else if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_UNKNOWN;
    } else if (state->count == 4) {
        if (state->interrupted || !state->pressed) return TD_QUAD_TAP;
        else return TD_UNKNOWN;
    } else return TD_UNKNOWN;
}

  

// BRA
// Single tap:  [
// Double tap:  ]
// Hold:        GUI
static td_tap_t bra_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void bra_finished(qk_tap_dance_state_t *state, void *user_data) {
    bra_tap_state.state = complex_dance(state);
    switch (bra_tap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_LBRC); break;
        case TD_HOLD: register_code(KC_LGUI); break;
        case TD_DOUBLE_TAP: register_code(KC_RBRC); break;
        default: break;
    }
}

void bra_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (bra_tap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_LBRC); break;
        case TD_HOLD: unregister_code(KC_LGUI); break;
        case TD_DOUBLE_TAP: unregister_code(KC_RBRC); break;
        default: break;
    }
    bra_tap_state.state = TD_NONE;
}



// COM
// Single tap:  <
// Double tap:  >
// Hold:        ALT

static td_tap_t com_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void com_finished(qk_tap_dance_state_t *state, void *user_data) {
    com_tap_state.state = complex_dance(state);
    switch (com_tap_state.state) {
        case TD_SINGLE_TAP: register_mods(MOD_BIT(KC_LSFT)); register_code(KC_COMM); break;
        case TD_HOLD: register_code(KC_LALT); break;
        case TD_DOUBLE_TAP: register_mods(MOD_BIT(KC_LSFT)); register_code(KC_DOT); break;
        default: break;
    }
}

void com_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (com_tap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_COMM); unregister_mods(MOD_BIT(KC_LSFT)); break;
        case TD_HOLD: unregister_code(KC_LALT); break;
        case TD_DOUBLE_TAP: unregister_code(KC_DOT); unregister_mods(MOD_BIT(KC_LSFT)); break;
        default: break;
    }
    com_tap_state.state = TD_NONE;
}



// CUR
// Single tap:  {
// Double tap:  }
// Hold:        CTRL
static td_tap_t cur_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void cur_finished(qk_tap_dance_state_t *state, void *user_data) {
    cur_tap_state.state = complex_dance(state);
    switch (cur_tap_state.state) {
        case TD_SINGLE_TAP: register_mods(MOD_BIT(KC_LSFT)); register_code(KC_LBRC); break;
        case TD_HOLD: register_code(KC_LCTL); break;
        case TD_DOUBLE_TAP: register_mods(MOD_BIT(KC_LSFT)); register_code(KC_RBRC); break;
        default: break;
    }
}

void cur_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (cur_tap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_LBRC); unregister_mods(MOD_BIT(KC_LSFT)); break;
        case TD_HOLD: unregister_code(KC_LCTL); break;
        case TD_DOUBLE_TAP: unregister_code(KC_RBRC); unregister_mods(MOD_BIT(KC_LSFT)); break;
        default: break;
    }
    cur_tap_state.state = TD_NONE;
}



// PAR
// Single tap:  (
// Double tap:  )  
// Hold:        SHIFT
static td_tap_t par_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void par_finished(qk_tap_dance_state_t *state, void *user_data) {
    par_tap_state.state = complex_dance(state);
    switch (par_tap_state.state) {
        case TD_SINGLE_TAP: register_mods(MOD_BIT(KC_LSFT)); register_code(KC_9); break;
        case TD_HOLD: register_code(KC_LSFT); break;
        case TD_DOUBLE_TAP: register_mods(MOD_BIT(KC_LSFT)); register_code(KC_0); break;
        default: break;
    }
}

void par_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (par_tap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_9); unregister_mods(MOD_BIT(KC_LSFT)); break;
        case TD_HOLD: unregister_code(KC_LSFT); break;
        case TD_DOUBLE_TAP: unregister_code(KC_0); unregister_mods(MOD_BIT(KC_LSFT)); break;
        default: break;
    }
    par_tap_state.state = TD_NONE;
}



// FNC
// Single tap:  CAPS_WORD
// Double tap:  CAPS_LOCK
// Hold:        MO(FN1)


// static td_tap_t fnc_tap_state = {
//     .is_press_action = true,
//     .state = TD_NONE
// };
static bool is_td_fnc_held = false;
static bool is_caps_on = false;

bool is_tapped(qk_tap_dance_state_t *state) {
    return state->count == 1 && ((state->interrupted && !is_td_fnc_held) || !state->pressed);
}

bool is_double_tapped(qk_tap_dance_state_t *state) {
    return state->count == 2 && (state->interrupted || !state->pressed);
}



void fnc_on_each_tap(qk_tap_dance_state_t *state, void *user_data) {
    layer_on(FN1);
}

void fnc_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (is_tapped(state)) {
        layer_off(FN1);
        if (is_caps_on) {
            register_code(KC_CAPS);
            is_caps_on = false;
        } else caps_word_on();
    } else if (is_double_tapped(state)) {
        layer_off(FN1);
        register_code(KC_CAPS);
        is_caps_on = !is_caps_on;
    }
}

void fnc_reset(qk_tap_dance_state_t *state, void *user_data) {
    unregister_code(KC_CAPS);
    layer_off(FN1); 
}



// BSP
// Single tap:  BSPC
// Hold:        CTRL + BSPC

void bsp_on_each_tap(qk_tap_dance_state_t *state, void *user_data) {
    register_code(KC_BSPC);
}

void bsp_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->pressed && !state->interrupted) {
        register_mods(MOD_BIT(KC_LCTL)); register_code(KC_BSPC);
    }
}

void bsp_reset(qk_tap_dance_state_t *state, void *user_data) {
    unregister_code(KC_BSPC); unregister_mods(MOD_BIT(KC_LCTL));
}



// DEL
// Single tap:  DEL
// Hold:        CTRL + DEL

void del_on_each_tap(qk_tap_dance_state_t *state, void *user_data) {
    register_code(KC_DEL);
}

void del_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->pressed && !state->interrupted) {
        register_mods(MOD_BIT(KC_LCTL)); register_code(KC_DEL);
    }
}

void del_reset(qk_tap_dance_state_t *state, void *user_data) {
    unregister_code(KC_DEL); unregister_mods(MOD_BIT(KC_LCTL));
}



// SLC
// Double tap:  TO(SYM)
// Hold:        MO(SYM)
static td_tap_t slc_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void slc_finished(qk_tap_dance_state_t *state, void *user_data) {
    slc_tap_state.state = complex_dance(state);
    switch (slc_tap_state.state) {
        case TD_HOLD: layer_on(SYM); break;
        case TD_DOUBLE_TAP: layer_invert(SYM); break;
        default: break;
    }
}

void slc_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (slc_tap_state.state) {
        case TD_HOLD: layer_off(SYM); break;
        default: break;
    }
    slc_tap_state.state = TD_NONE;
}



bool isShifted(void) {
    return get_mods() & MOD_BIT(KC_LSFT);
}

// UNI_E
static td_tap_t uni_e_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void uni_e_finished(qk_tap_dance_state_t *state, void *user_data) {
    uni_e_tap_state.state = uni_dance(state);
    switch (uni_e_tap_state.state) {
        case TD_SINGLE_TAP: isShifted() ? send_unicode_string("Ê") : send_unicode_string("ê"); break;
        case TD_DOUBLE_TAP: isShifted() ? send_unicode_string("Ë") : send_unicode_string("ë"); break;
        case TD_TRIPLE_TAP: isShifted() ? send_unicode_string("É") : send_unicode_string("é"); break;
        case TD_QUAD_TAP:   isShifted() ? send_unicode_string("È") : send_unicode_string("è"); break;
        default: break;
    }
}

void uni_e_reset(qk_tap_dance_state_t *state, void *user_data) {
    uni_e_tap_state.state = TD_NONE;
}


qk_tap_dance_action_t tap_dance_actions[] = {
    [BRA] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, bra_finished, bra_reset),
    [COM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, com_finished, com_reset),
    [CUR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, cur_finished, cur_reset),
    [PAR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, par_finished, par_reset),
    [BSP] = ACTION_TAP_DANCE_FN_ADVANCED(bsp_on_each_tap, bsp_finished, bsp_reset),
    [DEL] = ACTION_TAP_DANCE_FN_ADVANCED(del_on_each_tap, del_finished, del_reset),
    [FNC] = ACTION_TAP_DANCE_FN_ADVANCED(fnc_on_each_tap, fnc_finished, fnc_reset),
    [SLC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, slc_finished, slc_reset),
    [UNI_E] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, uni_e_finished, uni_e_reset)
};


uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(DEL):
            return 160;
        case TD(BSP):
            return 160;
        case TD(FNC):
            return 160;
        default:
            return TAPPING_TERM;
    }
}


static bool is_td_slc_held = false;

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(26, RGB_RED);
    }
    if (is_caps_word_on()) {
        rgb_matrix_set_color(26, RGB_ORANGE);
    }
    switch(get_highest_layer(layer_state|default_layer_state)) {
        case SYM:
            if (!is_td_slc_held) {
                rgb_matrix_set_color(13, RGB_GREEN);
            }
            break;
        default:
            break;
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (IS_LAYER_ON(UNI)) {
        switch (keycode) {
            case KC_I:
                if (record->event.pressed) send_unicode_string("ï");
                return false;
            case KC_O:
                if (record->event.pressed) send_unicode_string("ô");
                return false;
            default: return true;
        }
    } else {
        switch (keycode) {
            case TD(SLC):
                if (record->event.pressed) {
                    is_td_slc_held = true;
                } else {
                    is_td_slc_held = false;
                }
                return true;
            case TD(FNC):
                if (record->event.pressed) {
                    is_td_fnc_held = true;
                } else {
                    is_td_fnc_held = false;
                }
            default: return true;
        }
    }
}
