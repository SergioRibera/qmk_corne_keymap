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

//#define USE_MATRIX_I2C

/* Select hand configuration */

/* #define MASTER_LEFT */
#define MASTER_RIGHT
// #define EE_HANDS

#define USE_SERIAL_PD2

#define ONESHOT_TAP_TOGGLE 5  /* Tapping this number of times holds the key until tapped once again. */
#define ONESHOT_TIMEOUT 5000  /* Time (in ms) before the one shot key is released */

#define TAPPING_FORCE_HOLD
#define TAPPING_TERM 200

#ifdef RGBLIGHT_ENABLE
    /* #undef RGBLED_NUM */
    /* #define RGBLED_NUM 27 */
    /* #define RGBLIGHT_ANIMATIONS // Enable all animations */
    #define RGBLIGHT_EFFECT_RAINBOW_MOOD
    /* #define RGBLIGHT_MODE_RGB_TEST */

    /* #define RGBLIGHT_LAYER_BLINK */
    #define RGBLIGHT_SLEEP
    #define RGBLIGHT_SPLIT
    /* #define RGBLIGHT_LIMIT_VAL 120 */
    /* #define RGBLIGHT_HUE_STEP 10 */
    #define RGBLIGHT_SAT_STEP 17
    /* #define RGBLIGHT_VAL_STEP 17 */
#endif

// VENDOR_ID => 0x04653
// PRODUCT_ID => 0x0001

/* #undef VENDOR_ID */
/* #undef PRODUCT_ID */
/* #define VENDOR_ID    0x4653 */
/* #define PRODUCT_ID   0x4D4D */

/* #define DEVICE_VER   0x0001 */
/* #define MANUFACTURER foostan */
/* #define PRODUCT      Corne */

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"
