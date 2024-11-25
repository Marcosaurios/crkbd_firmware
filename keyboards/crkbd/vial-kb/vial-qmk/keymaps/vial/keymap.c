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

enum layer_names {
    _BASE,
    _SELECTION,  // Switching with tri-layer TL_LOWR
    _SYMBOLS,    // Switching with tri-layer TL_UPPR
    _NUMBERS,    // Switching with tri-layer TL_LOWR+TL_UPPR pressed
    _FUNCTIONS
};


// Tap Dance definitions
enum {
    TD_LSFT_CAPS,
};

// If using VIAL, use this function. Otherwise, uncomment tap_dance_actions_user
#ifdef VIAL_ENABLE
void keyboard_post_init_user(void) {    
    #ifdef TAP_DANCE_ENABLE
    #define TAP_TAPPING_TERM 260
    vial_tap_dance_entry_t td0 = { KC_LSFT,         // On tap
                                XXXXXXX,            // On hold
                                KC_CAPS,            // On double tap
                                XXXXXXX,            // On tap hold
                                TAP_TAPPING_TERM };
    dynamic_keymap_set_tap_dance(TD_LSFT_CAPS, &td0); // the first value corresponds to the TD(i) slot
    #endif
}
#else
tap_dance_action_t tap_dance_actions_user[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_LSFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
};
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T, XXXXXXX,    KC_MPLY,    KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
TD(TD_LSFT_CAPS), KC_A,    KC_S,    KC_D,    KC_F,    KC_G, XXXXXXX,      MO(4),    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, TL_UPPR,  KC_SPC,     KC_ENT, TL_LOWR, KC_LEFT_ALT
                                      //`--------------------------'  `--------------------------'

  ),

  [_SELECTION] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
      _______, _______, _______, _______, _______, _______, XXXXXXX,    _______, _______, _______,   KC_UP, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______, XXXXXXX,    _______, _______, KC_LEFT, KC_DOWN,KC_RIGHT, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_SYMBOLS] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
      _______, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC, XXXXXXX,    KC_RCTL, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______, XXXXXXX,    QK_BOOT, KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_NUMBERS] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
      QK_BOOT,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5, XXXXXXX,    XXXXXXX,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, LM_TOGG, RGB_VAI, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX,   KC_P4,   KC_P5,   KC_P6, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX,   KC_P1,   KC_P2,   KC_P3, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______,   KC_P0
                                      //`--------------------------'  `--------------------------'
  ),

  [_FUNCTIONS] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
       EE_CLR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX,   KC_F7,   KC_F8,   KC_F9,  KC_F10, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX,   KC_F4,   KC_F5,   KC_F6,  KC_F11, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX,   KC_F1,   KC_F2,   KC_F3,  KC_F12, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  )
};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    oled_clear();
    return state;
}

bool oled_task_user(void) {
    led_t led_state = host_keyboard_led_state();
    oled_set_cursor(0,5);
    oled_write_P(led_state.caps_lock ? PSTR("CAPS") : PSTR("    "), false);

    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_set_cursor(0,0);
            oled_write_ln_P(PSTR("BASE"), false);
            break;
        case _SELECTION:
            oled_set_cursor(0,1);
            oled_write_ln_P(PSTR("SELEC"), false);
            break;
        case _SYMBOLS:
            oled_set_cursor(0,2);
            oled_write_ln_P(PSTR("SYMB"), false);
            break;
        case _NUMBERS:
            oled_set_cursor(0,3);
            oled_write_ln_P(PSTR("NUMB"), false);
            break;
        case _FUNCTIONS:
            oled_set_cursor(0,4);
            oled_write_ln_P(PSTR("FN"), false);
            break;
        default:
            oled_set_cursor(0,5);
            oled_write_ln_P(PSTR("Undef"), false);
            break;
    }
    return false;
}

void oled_render_boot(bool bootloader) {
    rgb_matrix_set_color_all(255, 0, 0);
    oled_clear();
    const char *txt[11];
    if (bootloader == true) {
        txt[0] = "   B  ";
        txt[1] = "   O  ";
        txt[2] = "   O  ";
        txt[3] = "   T  ";
        txt[4] = "   L  ";
        txt[5] = "   O  ";
        txt[6] = "   A  ";
        txt[7] = "   D  ";
        txt[8] = "   E  ";
        txt[9] = "   R  ";
        txt[10] = NULL;
    } else {
        txt[0] = "   R  ";
        txt[1] = "   E  ";
        txt[2] = "   B  ";
        txt[3] = "   O  ";
        txt[4] = "   O  ";
        txt[5] = "   T  ";
        txt[6] = NULL;
    }
    for (int i = 0; txt[i] != NULL; i++) {
        oled_set_cursor(0, i);
        oled_write_ln_P(txt[i], false);
    }

    oled_render_dirty(true);
}

bool shutdown_user(bool jump_to_bootloader) {
    oled_render_boot(jump_to_bootloader);
    return false;
}
#endif

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    for (uint8_t i = led_min; i < led_max; i++) {
        switch(get_highest_layer(layer_state|default_layer_state)) {
            case _BASE:                
                rgb_matrix_set_color(i, RGB_RED);
            break;
            case _SELECTION:
                rgb_matrix_set_color(i, RGB_TEAL);
                break;
            case _SYMBOLS:
                rgb_matrix_set_color(i, RGB_YELLOW);
                break;
            case _NUMBERS:
                rgb_matrix_set_color(i, RGB_WHITE);
                break;
            case _FUNCTIONS:
                rgb_matrix_set_color(i, RGB_MAGENTA);
                break;
            default:
                break;
            }
    }
    return false;
}

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [_BASE] = { ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(KC_VOLU, KC_VOLD), ENCODER_CCW_CW(XXXXXXX, XXXXXXX), },
  [_SELECTION] = { ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(RGB_VAI, RGB_VAD), ENCODER_CCW_CW(XXXXXXX, XXXXXXX), },
  [_SYMBOLS] = { ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(RGB_VAD, RGB_VAI), ENCODER_CCW_CW(XXXXXXX, XXXXXXX), },
  [_NUMBERS] = { ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(RGB_VAD, RGB_VAI), ENCODER_CCW_CW(XXXXXXX, XXXXXXX), },
  [_FUNCTIONS] = { ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(RGB_VAD, RGB_VAI), ENCODER_CCW_CW(XXXXXXX, XXXXXXX) }
};
#endif
