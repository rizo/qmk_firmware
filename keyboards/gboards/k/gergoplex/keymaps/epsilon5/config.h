#pragma once

// #define COMBO_ALLOW_ACTION_KEYS 
// #define COMBO_VARIABLE_LEN

// Recommended for heavy chording.
#define QMK_KEYS_PER_SCAN 4

#define TAPPING_TERM 170

// Prevent normal rollover on alphas from accidentally triggering mods.
#define IGNORE_MOD_TAP_INTERRUPT

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define TAPPING_FORCE_HOLD