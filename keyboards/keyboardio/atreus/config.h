/* Copyright (C) 2019, 2020  Keyboard.io, Inc
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

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */

#define VENDOR_ID       0x1209
#define PRODUCT_ID      0x2303
#define DEVICE_VER      0x0000
#define MANUFACTURER    Keyboardio
#define PRODUCT         Atreus

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 12

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* number of backlight levels */
//#define BACKLIGHT_LEVELS 3

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 */

#define MATRIX_ROW_PINS { F6, F5, F4, F1 }
#define MATRIX_COL_PINS { F7, E2, C7, C6, B6, B5, D7, D6, D4, D5, D3, D2 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION



// For heavy chording.
#define QMK_KEYS_PER_SCAN 4

// Activate mods faster.
#define TAPPING_TERM 170
#define TAPPING_TERM_PER_KEY

// Prevent normal rollover on alphas from accidentally triggering mods.
#define IGNORE_MOD_TAP_INTERRUPT_PER_KEY

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define TAPPING_FORCE_HOLD_PER_KEY

// #define ONESHOT_TAP_TOGGLE 2
#define ONESHOT_TIMEOUT 3000

#define _ENABLE_HOME_MODS


#define _COMBOS_ENABLED
#ifdef _COMBOS_ENABLED
  #define COMBO_MUST_TAP_PER_COMBO
  #define COMBO_TERM 25
#endif

// Mouse key speed and acceleration.
#undef MOUSEKEY_DELAY
#define MOUSEKEY_DELAY          0
#undef MOUSEKEY_INTERVAL
#define MOUSEKEY_INTERVAL       16
#undef MOUSEKEY_WHEEL_DELAY
#define MOUSEKEY_WHEEL_DELAY    0
#undef MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED      12
#undef MOUSEKEY_TIME_TO_MAX
#define MOUSEKEY_TIME_TO_MAX    60


#define _ko_make_strict(trigger_mods_, trigger_, replacement_) { \
  .trigger           = trigger_, \
  .trigger_mods      = trigger_mods_, \
  .layers            = ~0, \
  .suppressed_mods   = trigger_mods_, \
  .options           = ko_options_default, \
  .negative_mod_mask = (uint8_t) ~(trigger_mods_), \
  .custom_action     = NULL, \
  .context           = NULL, \
  .replacement       = replacement_, \
  .enabled           = NULL \
};

#define _ko_make_strict_negmods(trigger_mods_, trigger_, replacement_, negative_mod_mask_) { \
  .trigger           = trigger_, \
  .trigger_mods      = trigger_mods_, \
  .layers            = ~0, \
  .suppressed_mods   = trigger_mods_, \
  .options           = ko_options_default, \
  .negative_mod_mask = negative_mod_mask_, \
  .custom_action     = NULL, \
  .context           = NULL, \
  .replacement       = replacement_, \
  .enabled           = NULL \
};




