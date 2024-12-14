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
    _FUNCTIONS,
    _GAME
};

// Home Row mods STICKY
// #define HR_CTL OSM(MOD_LCTL)
// #define HR_SFT OSM(MOD_LSFT)
// #define HR_ALT OSM(MOD_LALT)
// #define HR_GUI OSM(MOD_LGUI)
// Home row mods mod taps
#define HR_SFT_A LSFT_T(KC_A)
#define HR_ALT_S LALT_T(KC_S)
#define HR_GUI_D LGUI_T(KC_D)
#define HR_CTL_F LCTL_T(KC_F)

#define HR_CTL_J LCTL_T(KC_J)
#define HR_GUI_K LGUI_T(KC_K)
#define HR_ALT_L LALT_T(KC_L)
#define HR_SFT_SC LSFT_T(KC_SCLN)

void oneshot_mods_changed_user(uint8_t mods) {
  if (mods & MOD_MASK_SHIFT) {
    oled_set_cursor(0,6);
    oled_write_P(PSTR("S"), false);
  }
  if (mods & MOD_MASK_CTRL) {
    oled_set_cursor(1,6);
    oled_write_P(PSTR("A"), false);
  }
  if (mods & MOD_MASK_ALT) {
    oled_set_cursor(2,6);
    oled_write_P(PSTR("G"), false);
  }
  if (mods & MOD_MASK_GUI) {
    oled_set_cursor(3,6);
    oled_write_P(PSTR("C"), false);
  }
  if (!mods) {
    oled_set_cursor(0,6);
    oled_write_P(PSTR("empty"), false);
  }
}

// Tap Dance definitions
enum {
    TD_LSFT_CAPS,
    TD_FN_GAME
};
#define TD_SFT_LCK TD(TD_LSFT_CAPS)
#define TD_FN_GM TD(TD_FN_GAME)
// If using VIAL, use this function. Otherwise, uncomment tap_dance_actions_user
#ifdef VIAL_ENABLE
void keyboard_post_init_user(void) {
    #ifdef TAP_DANCE_ENABLE
    #define TAP_TAPPING_TERM 200
    vial_tap_dance_entry_t td0 = { 
        KC_LSFT,         // On tap
        KC_NO,           // On hold
        KC_CAPS,         // On double tap
        KC_NO,           // On tap hold
        TAP_TAPPING_TERM
    };
    dynamic_keymap_set_tap_dance(TD_LSFT_CAPS, &td0); // the first value corresponds to the TD(i) slot
    
    vial_tap_dance_entry_t td1 = { 
        MO(_FUNCTIONS),  // On tap
        KC_NO,           // On hold
        TG(_GAME),       // On double tap
        KC_NO,           // On tap hold
        TAP_TAPPING_TERM
    };
    dynamic_keymap_set_tap_dance(TD_FN_GAME, &td1); // the first value corresponds to the TD(i) slot
    #endif
}
#else
tap_dance_action_t tap_dance_actions_user[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_LSFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
    // Tap once for FN layer, twice for toggling GAME layer
    [TD_FN_GAME] = ACTION_TAP_DANCE_DOUBLE(MO(_FUNCTIONS),TG(_GAME))
};
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T, XXXXXXX,    KC_MPLY,    KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
   TD_SFT_LCK,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G, XXXXXXX,   TD_FN_GM,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, TL_UPPR,  KC_SPC, MO(_FUNCTIONS), TL_LOWR, KC_LEFT_ALT
                                      //`--------------------------'  `--------------------------'
  ),
  
[_SELECTION] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
      _______, _______, _______, _______, _______, _______, XXXXXXX,    _______, _______, _______,   KC_UP, _______, _______, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      _______,HR_SFT_A,HR_ALT_S,HR_GUI_D,HR_CTL_F, _______, XXXXXXX,    _______, _______, KC_LEFT, KC_DOWN,KC_RIGHT, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______,  KC_ENT,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

[_SYMBOLS] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
      _______, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC, XXXXXXX,    KC_RCTL, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      _______,HR_SFT_A,HR_ALT_S,HR_GUI_D,HR_CTL_F, _______, XXXXXXX,    QK_BOOT, KC_EQL,  KC_LPRN, KC_LCBR, KC_LBRC, KC_MINS,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, KC_BSLS, KC_PIPE, KC_AMPR,                      KC_PLUS, KC_RPRN, KC_RCBR, KC_RBRC, KC_UNDS, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, KC_ENT,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

[_NUMBERS] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
      QK_BOOT,   KC_F7,   KC_F8,   KC_F9,  KC_F10, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX,    KC_7,    KC_8,    KC_9,    KC_0,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      RGB_TOG,   KC_F4,   KC_F5,   KC_F6,  KC_F11, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX,    KC_4,    KC_5,    KC_6, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      RGB_MOD,   KC_F1,   KC_F2,   KC_F3,  KC_F12, XXXXXXX,                      XXXXXXX,    KC_1,    KC_2,    KC_3, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, KC_ENT,    _______, _______,     KC_0
                                      //`--------------------------'  `--------------------------'
  ),

// TODO WIP
[_FUNCTIONS] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
       EE_CLR, _______, _______, _______, _______, _______, XXXXXXX,    _______, _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      _______,HR_SFT_A,HR_ALT_S,HR_GUI_D,HR_CTL_F, _______, XXXXXXX,    XXXXXXX, _______,HR_CTL_J,HR_GUI_K,HR_ALT_L,HR_SFT_SC, _______,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, KC_ENT,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

[_GAME] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T, XXXXXXX,    KC_MPLY,    KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
   TD_SFT_LCK,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G, XXXXXXX,   TD_FN_GM,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, TL_UPPR,  KC_SPC,     KC_ENT, TL_LOWR, KC_LEFT_ALT
                                      //`--------------------------'  `--------------------------'
  ),
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
    oled_set_cursor(0,6);
    oled_write_P(led_state.caps_lock ? PSTR("CAPS") : PSTR("    "), false);
    // oled_set_cursor(0,7);
    // uint8_t oneshot_mods = get_oneshot_mods();
    // oled_write_P(PSTR(""+oneshot_mods), false);

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
            oled_write_ln_P(PSTR("CTRL"), false);
            break;
        case _GAME:
            oled_set_cursor(0,5);
            oled_write_ln_P(PSTR("GAME"), false);
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

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [_BASE] = { ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(KC_VOLU, KC_VOLD), ENCODER_CCW_CW(XXXXXXX, XXXXXXX), },
  [_SELECTION] = { ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(RGB_VAI, RGB_VAD), ENCODER_CCW_CW(XXXXXXX, XXXXXXX), },
  [_SYMBOLS] = { ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(UG_NEXT, UG_PREV), ENCODER_CCW_CW(XXXXXXX, XXXXXXX), },
  [_NUMBERS] = { ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(RGB_VAD, RGB_VAI), ENCODER_CCW_CW(XXXXXXX, XXXXXXX), },
  [_FUNCTIONS] = { ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(RGB_VAD, RGB_VAI), ENCODER_CCW_CW(XXXXXXX, XXXXXXX) },
  [_GAME] = { ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(RGB_VAD, RGB_VAI), ENCODER_CCW_CW(XXXXXXX, XXXXXXX) }
};
#endif
