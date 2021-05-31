#pragma once


// For heavy chording.
#define QMK_KEYS_PER_SCAN 4

// Activate mods faster.
#define TAPPING_TERM 170

// Prevent normal rollover on alphas from accidentally triggering mods.
#define IGNORE_MOD_TAP_INTERRUPT_PER_KEY

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define TAPPING_FORCE_HOLD