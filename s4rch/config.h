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

#define MASTER_RIGHT
#define SPLIT_LAYER_STATE_ENABLE

/* Tapping this number of times holds the key until tapped once again. */
#define ONESHOT_TAP_TOGGLE 5
/* Time (in ms) before the one shot key is released */
#define ONESHOT_TIMEOUT 5000

#define TAPPING_FORCE_HOLD
#define TAPPING_TERM 200

// VENDOR_ID => 0x04653
// PRODUCT_ID => 0x0001

/* #define DEVICE_VER   0x0001 */
/* #define MANUFACTURER foostan */
/* #define PRODUCT      Corne */

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

#ifdef OLED_ENABLE
#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"
#endif
