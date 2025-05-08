#pragma once

// For heavy chording.
#define QMK_KEYS_PER_SCAN 4

// Activate mods faster.
#define TAPPING_TERM 170
#define TAPPING_TERM_PER_KEY

// MOD action within TAPPING_TERM
#define PERMISSIVE_HOLD_PER_KEY

// Prevent tap key repeat on second quick tap.
// https://docs.qmk.fm/#/tap_hold?id=quick-tap-term
#define QUICK_TAP_TERM_PER_KEY
#define QUICK_TAP_TERM 120

// #define ONESHOT_TAP_TOGGLE 2
#define ONESHOT_TIMEOUT 900

// Mouse options
#define MOUSEKEY_WHEEL_DELAY 0
#define MOUSEKEY_WHEEL_INTERVAL 15
#define MOUSEKEY_WHEEL_DELTA 2
