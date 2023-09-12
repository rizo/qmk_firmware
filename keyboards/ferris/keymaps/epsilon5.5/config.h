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
#define ONESHOT_TIMEOUT 900

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



