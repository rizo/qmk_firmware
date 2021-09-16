#pragma once


// For heavy chording.
#define QMK_KEYS_PER_SCAN 4

// Activate mods faster.
#define TAPPING_TERM 170

// Prevent normal rollover on alphas from accidentally triggering mods.
#define IGNORE_MOD_TAP_INTERRUPT_PER_KEY

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define TAPPING_FORCE_HOLD_PER_KEY

// #define ONESHOT_TAP_TOGGLE 2
#define ONESHOT_TIMEOUT 3000

#define _ENABLE_HOME_MODS

#undef _COMBOS_ENABLED
#undef _TAPDANCE_ENABLED

#ifdef _COMBOS_ENABLED

#define COMBO_COUNT 11
#define COMBO_TERM 25

#endif
