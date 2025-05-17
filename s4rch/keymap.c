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
#ifdef RAW_ENABLE
#include "raw_hid.h"
#endif

#ifdef RGB_MATRIX_ENABLE
#include "config_led.h"
#endif

#ifdef CONSOLE_ENABLE
#include "print.h"
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

// on layer change, no matter where the change was initiated
// Then runs keymap's layer change check
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
    if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
        layer_on(layer3);
    } else {
        layer_off(layer3);
    }
}
#endif

void keyboard_post_init_user(void) {
#ifdef CONSOLE_ENABLE
    debug_enable=true;
    /* debug_matrix=true; */
    debug_keyboard=true;
#endif
    rgb_matrix_sethsv_noeeprom(HSV_PURPLE);
}

#ifdef RAW_ENABLE

#ifndef VIA_ENABLE
enum via_command_id {
    id_get_keyboard_value                   = 0x01,
    id_set_keyboard_value                   = 0x02,
    id_get_rgb_value                        = 0x03,
    id_set_rgb_value                        = 0x04,

    id_get_rgb_current_flag                 = 0x00,
    id_unhandled                            = 0xFF,
};
#endif

#endif

#ifdef RGB_MATRIX_ENABLE
#ifndef VIA_ENABLE
void raw_hid_receive(uint8_t *data, uint8_t length) {
    uint8_t command_id   = data[0];
#ifdef CONSOLE_ENABLE
    uprintf("Command Received: 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X", data[0], data[1], data[2], data[3], data[4], data[5], length);
#endif
    switch (command_id) {
        case id_set_rgb_value:
            /* rgb_matrix_set_flags(LED_FLAG_NONE); */
            uint8_t index = data[2];
            uint8_t r     = data[3];
            uint8_t g     = data[4];
            uint8_t b     = data[5];
            switch (data[1]) {
                // set flag
                case 0:
                    rgb_matrix_set_flags(index);
                    /* rgb_matrix_set_color_all(r, g, b); */
                    break;
                // Set one led to color
                case 1:
                    // rgb_matrix_set_color(index, r, g, b);
                    /* rgblight_setrgb_at(r, g, b, index); */
                    rgb_matrix_set_color(index, r, g, b);
                    break;
                // set full color
                case 2:
                    /* rgblight_setrgb(r, g, b); */
                    /* rgb_matrix_set_color_all(r, g, b); */
                    rgb_matrix_sethsv_noeeprom(r, g, b);
                    break;
                // Set one row to color
                case 3:
                    switch (index) {
                        case 1:  // First row
                            /* rgblight_setrgb_range(r, g, b, 0, 14); */
                            set_led_range(0, 14, r, g, b);
                            break;
                        case 2:  // Second row
                            /* rgblight_setrgb_range(r, g, b, 15, 29); */
                            set_led_range(15, 29, r, g, b);
                            break;
                        case 3:  // Third row
                            /* rgblight_setrgb_range(r, g, b, 30, 43); */
                            set_led_range(30, 43, r, g, b);
                            break;
                        case 4:  // Fourth row
                            /* rgblight_setrgb_range(r, g, b, 44, 57); */
                            set_led_range(44, 57, r, g, b);
                            break;
                        case 5:  // Fifth row
                            /* rgblight_setrgb_range(r, g, b, 58, 66); */
                            set_led_range(58, 66, r, g, b);
                            break;
                        case 6:  // Bottom underglow
                            /* rgblight_setrgb_range(r, g, b, 67, 81); */
                            set_led_range(67, 81, r, g, b);
                            break;
                        case 7:  // Right underglow
                            /* rgblight_setrgb_range(r, g, b, 82, 86); */
                            set_led_range(82, 86, r, g, b);
                            break;
                        case 8:  // Top underglow
                            /* rgblight_setrgb_range(r, g, b, 87, 99); */
                            set_led_range(87, 99, r, g, b);
                            break;
                        case 9:  // Left underglow
                            /* rgblight_setrgb_range(r, g, b, 100, 104); */
                            set_led_range(100, 104, r, g, b);
                            break;
                    }
                    break;
            }
            break;
        case id_get_rgb_value:
            switch (data[1]) {
                /* case id_get_rgb_current_flag: */
                /*     uint8_t s_data[1]; */
                /* data[0] = id_set_rgb_value; */
                /*     s_data[0] = rgb_matrix_get_flags(); */
                /*      * Send Data: */
                /*      *       */
                /*      *      0      =>   Type send [ key, led state ] */
                /*      *      1      =>   flag */
                /*      *      2..4   =>   HSV */
                /*      * */
                /*     raw_hid_send(s_data, 1); */
                /*     break; */
                case id_get_rgb_value:
                    uint8_t s_data[3];
                    s_data[0] = rgb_matrix_get_hue();
                    s_data[1] = rgb_matrix_get_sat();
                    s_data[2] = rgb_matrix_get_val();
                    /* s_data[0] = rgblight_get_hue(); */
                    /* s_data[1] = rgblight_get_sat(); */
                    /* s_data[2] = rgblight_get_val(); */
                    /*
                     * Send Data:
                     *      
                     *      0      =>   Type send [ key, led state ]
                     *      1      =>   flag
                     *      2..4   =>   HSV
                     *
                     */
                    raw_hid_send(s_data, 3);
                    break;
            }
            break;
        default:
            break;
    }
}
#endif
#endif

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}


void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case L_BASE:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case L_LOWER:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case L_RAISE:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case L_ADJUST:
        case L_ADJUST|L_LOWER:
        case L_ADJUST|L_RAISE:
        case L_ADJUST|L_LOWER|L_RAISE:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
    }
}


char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
    char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
            (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
    if (keycode < 60) {
        name = code_to_name[keycode];
    }

    // update keylog
    snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
            record->event.key.row, record->event.key.col,
            keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
    return false;
}
#endif // OLED_DRIVER_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef OLED_ENABLE
    if (record->event.pressed) {
        set_keylog(keycode, record);
    }
#endif
#ifdef RAW_ENABLE
    uint8_t data[3];
    data[0] = id_set_keyboard_value;
    data[1] = record->event.pressed ? 1 : 0;
    data[2] = keycode >> 8;
    /*
     * Send Data:
     *      
     *      0      =>   Type send [ key, led state ]
     *      1..n   =>   values
     *
     */
    raw_hid_send(data, 3);
#endif
    return true;
}
