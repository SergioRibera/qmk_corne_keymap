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

#ifdef RGB_MATRIX_ENABLE
#include "config_led.h"
#endif

#define L_BASE 0
#define L_LOWER 1
#define L_RAISE 2
#define L_ADJUST 8

enum {
    TD_PIPE_TILD, // | ~
    TD_QUOT, // " ' 
    TD_ALT, // Left Alt   Right Alt
    TD_SCLN, // ; : -
    TD_SLSH, // / BackSlash
    TD_GRV, // ` _
    TD_DOT, // . ,

    TD_Z, // z <
    TD_X, // x >
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [ TD_PIPE_TILD ] = ACTION_TAP_DANCE_DOUBLE(KC_PIPE, KC_TILD),
    [    TD_ALT    ] = ACTION_TAP_DANCE_DOUBLE(KC_LALT, KC_RALT),
    [    TD_SCLN   ] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_MINS),
    [    TD_QUOT   ] = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_QUOT), KC_QUOT),
    [    TD_DOT    ] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_COMMA),
    [    TD_SLSH   ] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_BSLASH),
    [    TD_GRV    ] = ACTION_TAP_DANCE_DOUBLE(KC_GRV, LSFT(KC_MINS)),

    [     TD_Z     ] = ACTION_TAP_DANCE_DOUBLE(KC_Z, KC_LT),
    [     TD_X     ] = ACTION_TAP_DANCE_DOUBLE(KC_X, KC_GT),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [L_BASE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, TD(TD_SCLN), TD(TD_QUOT),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    TD(TD_Z),    TD(TD_X),    KC_C,    KC_V,    KC_B,                KC_N,    KC_M, TD(TD_DOT),  TD(TD_PIPE_TILD), TD(TD_SLSH),  TD(TD_GRV),
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                   MO(L_RAISE),   KC_LGUI,  KC_SPC,      KC_ENT,   MO(L_LOWER), KC_LCTL
                                      //`--------------------------'  `--------------------------'

  ),

  [L_LOWER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_ESC, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TAB, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  EE_CLR,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,  KC_LT,   KC_GT, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                       _______,   _______,  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  [L_RAISE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_TAB,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,     KC_7,    KC_8,    KC_9,    KC_0,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, LCA(KC_F1), LCA(KC_F2), LCA(KC_F3), LCA(KC_F4), LCA(KC_F7),        KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, XXXXXXX, KC_LSFT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_MUTE, KC_VOLD, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT,                      KC_BRID, KC_BRIU, XXXXXXX, XXXXXXX, KC_F12, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, QK_BOOT,  KC_SPC,     KC_ENT, MO(L_ADJUST), KC_LGUI 
                                      //`--------------------------'  `--------------------------'
  ),

  [L_ADJUST] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        RESET, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      QK_RBT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  )
};
// clang-format on

// on layer change, no matter where the change was initiated
// Then runs keymap's layer change check
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(HSV_PURPLE);
  } else {
    layer_off(layer3);
    rgb_matrix_sethsv_noeeprom(HSV_OFF);
  }
}

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
  hsv_t hsv = {0, 255, 255};

  if (layer_state_is(layer_state, 2)) {
    hsv = (hsv_t){130, 255, 255};
  } else {
    hsv = (hsv_t){30, 255, 255};
  }

  if (hsv.v > rgb_matrix_get_val()) {
    hsv.v = rgb_matrix_get_val();
  }
  rgb_t rgb = hsv_to_rgb(hsv);

  for (uint8_t i = led_min; i < led_max; i++) {
    if (HAS_FLAGS(g_led_config.flags[i], 0x01)) { // 0x01 == LED_FLAG_MODIFIER
      rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
  }
  return false;
}
#endif

void keyboard_post_init_user(void) {
#ifdef RGB_MATRIX_ENABLE
#endif
}
