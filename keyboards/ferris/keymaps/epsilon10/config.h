#pragma once

// For heavy chording.
#define QMK_KEYS_PER_SCAN 4

// Activate mods faster.
#define TAPPING_TERM 170
#define TAPPING_TERM_PER_KEY

// Prevent normal rollover on alphas from accidentally triggering mods.
/* #define IGNORE_MOD_TAP_INTERRUPT_PER_KEY */

// Prevent tap key repeat on second quick tap.
// https://docs.qmk.fm/#/tap_hold?id=quick-tap-term
#define QUICK_TAP_TERM_PER_KEY

// #define ONESHOT_TAP_TOGGLE 2
#define ONESHOT_TIMEOUT 900

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



