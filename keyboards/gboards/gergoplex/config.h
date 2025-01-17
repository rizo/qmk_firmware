/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2013 Oleg Kostyuk <cub.uanic@gmail.com>

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

// Copy and worked on with love from the EZ team

#pragma once
#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID 0x6B0A
#define PRODUCT_ID 0x0002
#define DEVICE_VER 0x0001
#define MANUFACTURER g Heavy Industries
#define PRODUCT GergoPlex

/* key matrix size */
#define MATRIX_ROWS 10
#define MATRIX_ROWS_PER_SIDE (MATRIX_ROWS / 2)
#define MATRIX_COLS 4

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 */
// #define MATRIX_ROW_PINS { F6, F5, F4, F1 }
// #define MATRIX_COL_PINS { B1, B2, B3, D2, D3 }
#define UNUSED_PINS
#define COMBO_ALLOW_ACTION_KEYS
#define COMBO_VARIABLE_LEN

#define IS_COMMAND() (get_mods() == (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL)) || get_mods() == (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)))

#define DEBOUNCE 5




#pragma once


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

#undef _ENABLE_HOME_MODS


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



