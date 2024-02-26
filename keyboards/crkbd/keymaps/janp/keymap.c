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
  BSE,
  SYM,
  NAV,
  MSE
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

enum {
    BRA,
    COM,
    CUR,
    PAR,
    CPS,
    UNI,
    SC1,
    SC2,
    SC3,
    SC4,
    BOOT
};

td_state_t tap_dance(tap_dance_state_t *state);

void bra_finished(tap_dance_state_t *state, void *user_data);
void bra_reset(tap_dance_state_t *state, void *user_data);
void com_finished(tap_dance_state_t *state, void *user_data);
void com_reset(tap_dance_state_t *state, void *user_data);
void cur_finished(tap_dance_state_t *state, void *user_data);
void cur_reset(tap_dance_state_t *state, void *user_data);
void par_finished(tap_dance_state_t *state, void *user_data);
void par_reset(tap_dance_state_t *state, void *user_data);
void cps_finished(tap_dance_state_t *state, void *user_data);
void cps_reset(tap_dance_state_t *state, void *user_data);
void uni_finished(tap_dance_state_t *state, void *user_data);
void uni_reset(tap_dance_state_t *state, void *user_data);
void sc1_finished(tap_dance_state_t *state, void *user_data);
void sc1_reset(tap_dance_state_t *state, void *user_data);
void sc2_finished(tap_dance_state_t *state, void *user_data);
void sc2_reset(tap_dance_state_t *state, void *user_data);
void sc3_finished(tap_dance_state_t *state, void *user_data);
void sc3_reset(tap_dance_state_t *state, void *user_data);
void sc4_finished(tap_dance_state_t *state, void *user_data);
void sc4_reset(tap_dance_state_t *state, void *user_data);
void boot_finished(tap_dance_state_t *state, void *user_data);
void boot_reset(tap_dance_state_t *state, void *user_data);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BSE] = LAYOUT_split_3x6_3(
  //|-----------------------------------------------------------------------------------------------------------------------|          |-----------------------------------------------------------------------------------------------------------------------|
                 KC_ESC,               KC_Q,               KC_W,               KC_F,               KC_P,               KC_B,                          KC_J,               KC_L,               KC_U,               KC_Y,            KC_MINS,            KC_QUOT,
  //|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|          |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
                TD(CPS),        GUI_T(KC_A),        ALT_T(KC_R),        CTL_T(KC_S),        SFT_T(KC_T),               KC_G,                          KC_M,        SFT_T(KC_N),        CTL_T(KC_E),        ALT_T(KC_I),        GUI_T(KC_O),            KC_SCLN,
  //|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|          |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
                KC_LCTL,        ALT_T(KC_Z),        GUI_T(KC_X),               KC_C,               KC_D,               KC_V,                          KC_K,               KC_H,            KC_COMM,             KC_DOT,            KC_SLSH,            KC_ALGR,
  //|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|          |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
                                                                    LT(MSE, KC_ENT),     LT(SYM, KC_TAB),   LT(NAV, KC_SPC),                        KC_SPC,            KC_BSPC,             KC_DEL
  //                                                            |-------------------|-------------------|-------------------|          |-------------------|-------------------|-------------------|

  ),

  [SYM] = LAYOUT_split_3x6_3(
  //|-----------------------------------------------------------------------------------------------------------------------|          |-----------------------------------------------------------------------------------------------------------------------|
                KC_TILD,             KC_GRV,            KC_EXLM,            KC_QUES,            KC_AMPR,            KC_PIPE,                       KC_ASTR,               KC_7,               KC_8,               KC_9,            KC_SLSH,              KC_NO,
  //|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|          |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
                KC_MINS,            TD(COM),            TD(BRA),            TD(CUR),            TD(PAR),             KC_EQL,                       KC_PLUS,        SFT_T(KC_4),        CTL_T(KC_5),        ALT_T(KC_6),      GUI_T(KC_DOT),            KC_PERC,
  //|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|          |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
                KC_CIRC,            KC_BSLS,            KC_HASH,             KC_DLR,              KC_AT,              KC_NO,                       KC_MINS,               KC_1,               KC_2,               KC_3,            KC_COMM,              KC_NO,
  //|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|          |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
                                                                             KC_ENT,            KC_TRNS,             KC_SPC,                       KC_BSPC,               KC_0,             KC_DEL
  //                                                            |-------------------|-------------------|-------------------|          |-------------------|-------------------|-------------------|

  ),

  [NAV] = LAYOUT_split_3x6_3(
  //|-----------------------------------------------------------------------------------------------------------------------|          |-----------------------------------------------------------------------------------------------------------------------|
                  KC_F1,              KC_F2,              KC_F3,              KC_F4,              KC_F5,              KC_F6,                         KC_NO,            KC_HOME,            KC_PGDN,            KC_PGUP,             KC_END,              KC_NO,
  //|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|          |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
           SFT_T(KC_F7),       GUI_T(KC_F8),       ALT_T(KC_F9),      CTL_T(KC_F10),      SFT_T(KC_F11),             KC_F12,                         KC_NO,            KC_LEFT,            KC_DOWN,              KC_UP,            KC_RGHT,              KC_NO,
  //|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|          |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
                KC_BRID,            KC_BRIU,            KC_MPLY,            KC_VOLD,            KC_VOLU,            KC_MUTE,                       KC_PSCR,            KC_LSFT,            KC_LCTL,            KC_LALT,            KC_LGUI,           TD(BOOT),
  //|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|          |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
                                                                             KC_ENT,             KC_TAB,            KC_TRNS,                        KC_SPC,            KC_BSPC,             KC_DEL
  //                                                            |-------------------|-------------------|-------------------|          |-------------------|-------------------|-------------------|

  ),

  [MSE] = LAYOUT_split_3x6_3(
  //|-----------------------------------------------------------------------------------------------------------------------|          |-----------------------------------------------------------------------------------------------------------------------|
                  KC_NO,            G(KC_1),            G(KC_2),            G(KC_3),            G(KC_4),         A(KC_LBRC),                         KC_NO,            KC_WH_L,            KC_WH_D,            KC_WH_U,            KC_WH_R,              KC_NO,
  //|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|          |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
                  KC_NO,            TD(SC1),            TD(SC2),            TD(SC3),            TD(SC4),         A(KC_RBRC),                         KC_NO,            KC_MS_L,            KC_MS_D,            KC_MS_U,            KC_MS_R,              KC_NO,
  //|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|          |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
                  KC_NO,              KC_NO,            TD(UNI),               KC_I,               KC_O,              KC_NO,                         KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,
  //|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|          |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
                                                                            KC_TRNS,              KC_NO,              KC_NO,                       KC_BTN2,            KC_BTN1,              KC_NO
  //                                                            |-------------------|-------------------|-------------------|          |-------------------|-------------------|-------------------|

  )
};

td_state_t tap_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        else return TD_HOLD;
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

void bra_finished(tap_dance_state_t *state, void *user_data) {
    bra_tap_state.state = tap_dance(state);
    switch (bra_tap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_LBRC); break;
        case TD_HOLD: register_code(KC_LGUI); break;
        case TD_DOUBLE_TAP: register_code(KC_RBRC); break;
        default: break;
    }
}

void bra_reset(tap_dance_state_t *state, void *user_data) {
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

void com_finished(tap_dance_state_t *state, void *user_data) {
    com_tap_state.state = tap_dance(state);
    switch (com_tap_state.state) {
        case TD_SINGLE_TAP: register_mods(MOD_BIT(KC_LSFT)); register_code(KC_COMM); break;
        case TD_HOLD: register_code(KC_LALT); break;
        case TD_DOUBLE_TAP: register_mods(MOD_BIT(KC_LSFT)); register_code(KC_DOT); break;
        default: break;
    }
}

void com_reset(tap_dance_state_t *state, void *user_data) {
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

void cur_finished(tap_dance_state_t *state, void *user_data) {
    cur_tap_state.state = tap_dance(state);
    switch (cur_tap_state.state) {
        case TD_SINGLE_TAP: register_mods(MOD_BIT(KC_LSFT)); register_code(KC_LBRC); break;
        case TD_HOLD: register_code(KC_LCTL); break;
        case TD_DOUBLE_TAP: register_mods(MOD_BIT(KC_LSFT)); register_code(KC_RBRC); break;
        default: break;
    }
}

void cur_reset(tap_dance_state_t *state, void *user_data) {
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

void par_finished(tap_dance_state_t *state, void *user_data) {
    par_tap_state.state = tap_dance(state);
    switch (par_tap_state.state) {
        case TD_SINGLE_TAP: register_mods(MOD_BIT(KC_LSFT)); register_code(KC_9); break;
        case TD_HOLD: register_code(KC_LSFT); break;
        case TD_DOUBLE_TAP: register_mods(MOD_BIT(KC_LSFT)); register_code(KC_0); break;
        default: break;
    }
}

void par_reset(tap_dance_state_t *state, void *user_data) {
    switch (par_tap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_9); unregister_mods(MOD_BIT(KC_LSFT)); break;
        case TD_HOLD: unregister_code(KC_LSFT); break;
        case TD_DOUBLE_TAP: unregister_code(KC_0); unregister_mods(MOD_BIT(KC_LSFT)); break;
        default: break;
    }
    par_tap_state.state = TD_NONE;
}



// CPS
// Single tap:  CAPS_WORD
// Double tap:  CAPS_LOCK
// Hold:        LSFT

static bool is_td_cps_held = false;
static bool is_caps_on = false;

bool is_tapped(tap_dance_state_t *state) {
    return state->count == 1 && ((state->interrupted && !is_td_cps_held) || !state->pressed);
}

bool is_double_tapped(tap_dance_state_t *state) {
    return state->count == 2 && (state->interrupted || !state->pressed);
}

void cps_on_each_tap(tap_dance_state_t *state, void *user_data) {
    register_mods(MOD_BIT(KC_LSFT));
}

void cps_finished(tap_dance_state_t *state, void *user_data) {
    if (is_tapped(state)) {
        unregister_mods(MOD_BIT(KC_LSFT));
        if (is_caps_on) {
            register_code(KC_CAPS);
            is_caps_on = false;
        } else caps_word_on();
    } else if (is_double_tapped(state)) {
        unregister_mods(MOD_BIT(KC_LSFT));
        register_code(KC_CAPS);
        is_caps_on = !is_caps_on;
    }
}

void cps_reset(tap_dance_state_t *state, void *user_data) {
    unregister_code(KC_CAPS);
    unregister_mods(MOD_BIT(KC_LSFT));
}



bool isShifted(void) {
    return get_mods() & MOD_BIT(KC_LSFT);
}



// UNI
static td_tap_t uni_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void uni_finished(tap_dance_state_t *state, void *user_data) {
    uni_tap_state.state = tap_dance(state);
    switch (uni_tap_state.state) {
        case TD_HOLD: add_mods(MOD_MASK_CTRL); break;
        case TD_SINGLE_TAP: isShifted() ? send_unicode_string("Ê") : send_unicode_string("ê"); break;
        case TD_DOUBLE_TAP: isShifted() ? send_unicode_string("Ë") : send_unicode_string("ë"); break;
        case TD_TRIPLE_TAP: isShifted() ? send_unicode_string("É") : send_unicode_string("é"); break;
        case TD_QUAD_TAP:   isShifted() ? send_unicode_string("È") : send_unicode_string("è"); break;
        default: break;
    }
}

void uni_reset(tap_dance_state_t *state, void *user_data) {
    switch (uni_tap_state.state) {
        case TD_HOLD: clear_mods(); break;
        default: break;
    }
    uni_tap_state.state = TD_NONE;
}



// SC1
// Single tap:  Switch to screen 1
// Hold:        GUI
static td_tap_t sc1_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void sc1_finished(tap_dance_state_t *state, void *user_data) {
    sc1_tap_state.state = tap_dance(state);
    switch (sc1_tap_state.state) {
        case TD_SINGLE_TAP: register_mods(MOD_BIT(KC_LALT)); register_code(KC_1); break;
        case TD_HOLD: register_mods(MOD_BIT(KC_LGUI)); break;
        default: break;
    }
}

void sc1_reset(tap_dance_state_t *state, void *user_data) {
    switch (sc1_tap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_1); unregister_mods(MOD_BIT(KC_LALT)); break;
        case TD_HOLD: unregister_mods(MOD_BIT(KC_LGUI)); break;
        default: break;
    }
    sc1_tap_state.state = TD_NONE;
}



// SC2
// Single tap:  Switch to screen 2
// Hold:        ALT
static td_tap_t sc2_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void sc2_finished(tap_dance_state_t *state, void *user_data) {
    sc2_tap_state.state = tap_dance(state);
    switch (sc2_tap_state.state) {
        case TD_SINGLE_TAP: register_mods(MOD_BIT(KC_LALT)); register_code(KC_2); break;
        case TD_HOLD: register_mods(MOD_BIT(KC_LALT)); break;
        default: break;
    }
}

void sc2_reset(tap_dance_state_t *state, void *user_data) {
    switch (sc2_tap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_2); unregister_mods(MOD_BIT(KC_LALT)); break;
        case TD_HOLD: unregister_mods(MOD_BIT(KC_LALT)); break;
        default: break;
    }
    sc2_tap_state.state = TD_NONE;
}



// SC3
// Single tap:  Switch to screen 3
// Hold:        CTL
static td_tap_t sc3_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void sc3_finished(tap_dance_state_t *state, void *user_data) {
    sc3_tap_state.state = tap_dance(state);
    switch (sc3_tap_state.state) {
        case TD_SINGLE_TAP: register_mods(MOD_BIT(KC_LALT)); register_code(KC_3); break;
        case TD_HOLD: register_mods(MOD_BIT(KC_LCTL)); break;
        default: break;
    }
}

void sc3_reset(tap_dance_state_t *state, void *user_data) {
    switch (sc3_tap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_3); unregister_mods(MOD_BIT(KC_LALT)); break;
        case TD_HOLD: unregister_mods(MOD_BIT(KC_LCTL)); break;
        default: break;
    }
    sc3_tap_state.state = TD_NONE;
}



// SC4
// Single tap:  Switch to screen 4
// Hold:        SFT
static td_tap_t sc4_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void sc4_finished(tap_dance_state_t *state, void *user_data) {
    sc4_tap_state.state = tap_dance(state);
    switch (sc4_tap_state.state) {
        case TD_SINGLE_TAP: register_mods(MOD_BIT(KC_LALT)); register_code(KC_4); break;
        case TD_HOLD: register_mods(MOD_BIT(KC_LSFT)); break;
        default: break;
    }
}

void sc4_reset(tap_dance_state_t *state, void *user_data) {
    switch (sc4_tap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_4); unregister_mods(MOD_BIT(KC_LALT)); break;
        case TD_HOLD: unregister_mods(MOD_BIT(KC_LSFT)); break;
        default: break;
    }
    sc4_tap_state.state = TD_NONE;
}



// BOOT
// Double tap:  cut
static td_tap_t boot_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void boot_finished(tap_dance_state_t *state, void *user_data) {
    boot_tap_state.state = tap_dance(state);
    switch (boot_tap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_SLEP); break;
        case TD_DOUBLE_TAP: reset_keyboard(); break;
        default: break;
    }
}

void boot_reset(tap_dance_state_t *state, void *user_data) {
    switch (boot_tap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_SLEP); break;
        default: break;
    }
    boot_tap_state.state = TD_NONE;
}



tap_dance_action_t tap_dance_actions[] = {
    [BRA] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, bra_finished, bra_reset),
    [COM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, com_finished, com_reset),
    [CUR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, cur_finished, cur_reset),
    [PAR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, par_finished, par_reset),
    [CPS] = ACTION_TAP_DANCE_FN_ADVANCED(cps_on_each_tap, cps_finished, cps_reset),
    [UNI] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, uni_finished, uni_reset),
    [SC1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sc1_finished, sc1_reset),
    [SC2] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sc2_finished, sc2_reset),
    [SC3] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sc3_finished, sc3_reset),
    [SC4] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sc4_finished, sc4_reset),
    [BOOT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, boot_finished, boot_reset)
};


uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(CPS):
            return 160;
        default:
            return TAPPING_TERM;
    }
}

void keyboard_post_init_user(void) {
    rgb_matrix_enable();
    rgb_matrix_set_color_all(RGB_OFF);
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(9, RGB_RED);
        rgb_matrix_set_color(36, RGB_RED);
    }
    if (is_caps_word_on()) {
        rgb_matrix_set_color(36, RGB_ORANGE);
        rgb_matrix_set_color(9, RGB_ORANGE);
    }
    switch(get_highest_layer(layer_state|default_layer_state)) {
        case SYM:
            rgb_matrix_set_color(9, RGB_CYAN);
            rgb_matrix_set_color(36, RGB_CYAN);
            break;
        default:
            break;
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (IS_LAYER_ON(MSE)) {
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
            case TD(CPS):
                if (record->event.pressed) {
                    is_td_cps_held = true;
                } else {
                    is_td_cps_held = false;
                }
            default: return true;
        }
    }
}
