#include QMK_KEYBOARD_H

#include "keymap_extras/keymap_us_international_linux.h"
#include "oneshot.h"

// Used to extract the basic tapping keycode from a dual-role key.
// Example: GET_TAP_KC(MT(MOD_RSFT, KC_E)) == KC_E
#define GET_TAP_KC(dual_role_key) dual_role_key & 0xFF

uint16_t last_tap = KC_NO;
uint8_t last_modifier = 0;
uint8_t mods_state = 0;
uint8_t oneshot_mods_state = 0;


enum layers {
  _ABC,
  _ACT,
  _SYM,
};


// Custom keys.
enum keycodes {
    _C_ACT_FAKE = SAFE_RANGE,
    _S_SYM_FAKE,

    _OGUI,
    _OALT,
    _OCTL,
    _OSFT,

    _S_TIL_FAKE,
    _C_ACU_FAKE,
    _A_CIR_FAKE,
    _G_GRV_FAKE,

    _PIPE,
    _ARROW,
    _ARROW2,
    _RPT,
};


// Thumb keys
#define _C_ACT LT(_ACT, _C_ACT_FAKE)
#define _S_SYM LT(_SYM, _S_SYM_FAKE)

#define _STAB S(KC_TAB)

// Back/forward.
#define _BACK C(KC_LBRC)
#define _FRWD C(KC_RBRC)

// Undo/redo.
#define _UNDO C(KC_Z)
#define _REDO S(C(KC_Z))

// Beginning/end of file.
#define _BOF C(KC_HOME)
#define _EOF C(KC_END)

// Word navigation.
#define _WLEFT C(KC_LEFT)
#define _WRGHT C(KC_RIGHT)

// Volume keys.
#define  _VOLU KC__VOLUP
#define  _VOLD KC__VOLDOWN
#define  _MUTE KC__MUTE

// Left mod accents.
#define _G_GRV GUI_T(_G_GRV_FAKE)
#define _A_CIR ALT_T(_A_CIR_FAKE)
#define _C_ACU CTL_T(_C_ACU_FAKE)
#define _S_TIL SFT_T(_S_TIL_FAKE)


// Keymap.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_ABC] = LAYOUT(
       KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                    KC_J,     KC_L, KC_U,     KC_Y,   US_QUOT,
       KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                    KC_H,     KC_N, KC_E,     KC_I,   KC_O,
       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                    KC_K,     KC_M, KC_COMMA, KC_DOT, US_SCLN,
                                         _C_ACT,  _S_SYM,  KC_SPC,  KC_BSPC
  ),

  [_ACT] = LAYOUT(
     KC_PWR,  KC_ESC,   _BACK,   _FRWD, KC_PSCR,                    KC_PGUP, _STAB,   KC_UP,   KC_TAB,  _BOF,
      _OGUI,   _OALT,   _OCTL,   _OSFT,  KC_INS,                    KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,
    XXXXXXX,    _RPT,   _UNDO,   _REDO, XXXXXXX,                    XXXXXXX, _WLEFT,  XXXXXXX, _WRGHT,  _EOF,
                                        _______, XXXXXXX,  KC_ENT,  KC_DEL
  ),

  [_SYM] = LAYOUT(
    XXXXXXX,   _PIPE,  _ARROW, _ARROW2, XXXXXXX,                    US_BSLS, KC_1,    KC_2,    KC_3,    US_SLSH,
     _G_GRV,  _A_CIR,  _C_ACU,  _S_TIL, XXXXXXX,                    US_LBRC, KC_4,    KC_5,    KC_6,    US_RBRC,
    XXXXXXX, XXXXXXX, US_CCED, XXXXXXX, XXXXXXX,                    US_GRV, KC_7,    KC_8,    KC_9,    KC_0,
                                        XXXXXXX, _______,  US_EQL,  US_MINS
  )
};


/*
 * REPEAT
 */
void process_repeat_key(uint16_t keycode, const keyrecord_t *record) {
    if (keycode != _RPT) {
        // Early return when holding down a pure layer key
        // to retain modifiers
        switch (keycode) {
            case QK_DEF_LAYER ... QK_DEF_LAYER_MAX:
            case QK_MOMENTARY ... QK_MOMENTARY_MAX:
            case QK_LAYER_MOD ... QK_LAYER_MOD_MAX:
            case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:
            case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX:
            case QK_TO ... QK_TO_MAX:
            case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
                return;
        }

        switch (keycode) {
            case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            case QK_MOD_TAP ... QK_MOD_TAP_MAX:
                if (record->event.pressed && record->tap.count > 0) {
                    last_modifier = oneshot_mods_state > mods_state ? oneshot_mods_state : mods_state;
                    last_tap = GET_TAP_KC(keycode);
                }
                break;
            default:
                if (record->event.pressed) {
                    last_modifier = oneshot_mods_state > mods_state ? oneshot_mods_state : mods_state;
                    last_tap = keycode;
                }
                break;
        }
    } else { // keycode == REPEAT
        if (record->event.pressed) {
            register_mods(last_modifier);
            register_code16(last_tap);
        } else {
            unregister_code16(last_tap);
            unregister_mods(last_modifier);
        }
    }
}


/*
 * CAPS_WORD
 */

bool caps_word_on = false;

// by precondition
// CAPS_WORD: A "smart" Caps Lock key that only capitalizes the next identifier you type
// and then toggles off Caps Lock automatically when you're done.
void caps_word_enable(void) {
    caps_word_on = true;
    if (!(host_keyboard_led_state().caps_lock)) {
        tap_code(KC_CAPS);
    }
}

void caps_word_disable(void) {
    caps_word_on = false;
    unregister_mods(MOD_MASK_SHIFT);
    if (host_keyboard_led_state().caps_lock) {
        tap_code(KC_CAPS);
    }
}


void process_caps_word(uint16_t keycode, const keyrecord_t *record) {
    // Update caps word state
    if (caps_word_on) {
        switch (keycode) {
            case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
                // Earlier return if this has not been considered tapped yet
                if (record->tap.count == 0) {
                  return;
                }
                // Get the base tapping keycode of a mod- or layer-tap key
                keycode = GET_TAP_KC(keycode);
                break;
            default:
                break;
        }

        switch (keycode) {
            // Keycodes to shift
            case KC_A ... KC_Z:
                if (record->event.pressed) {
                    if (get_oneshot_mods() & MOD_MASK_SHIFT) {
                        caps_word_disable();
                        add_oneshot_mods(MOD_MASK_SHIFT);
                    } else {
                        caps_word_enable();
                    }
                }
            // Keycodes that enable caps word but shouldn't get shifted
            case KC_DEL:
            case KC_BSPC:
            case KC_UNDS:
            case KC_MINS:
            case KC_1 ... KC_0:
                // If chording mods, disable caps word
                if (record->event.pressed && (get_mods() != 0)) {
                    caps_word_disable();
                }
                break;
            default:
                // Any other keycode should automatically disable caps
                if (record->event.pressed) {
                    caps_word_disable();
                }
                break;
        }
    }
}


// ONESHOT

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    // case LA_SYM:
    // case LA_NAV:
    //     return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case _C_ACT:
    case _S_SYM:
    case _OSFT:
    case _OCTL:
    case _OALT:
    case _OGUI:
        return true;
    default:
        return false;
    }
}


oneshot_state os_sft_state = os_up_unqueued;
oneshot_state os_ctl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_gui_state = os_up_unqueued;



// Function overrides.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
  uprintf("0x%04X,%u,%u,%u,%b,0x%02X,0x%02X,%u,%b\n",
    keycode,
    record->event.key.row,
    record->event.key.col,
    get_highest_layer(layer_state),
    record->event.pressed,
    get_mods(),
    get_oneshot_mods(),
    record->tap.count,
    caps_word_on
  );
#endif

  bool ret = true;

  update_oneshot(
    &os_sft_state, KC_LSFT, _OSFT,
    keycode, record
  );
  update_oneshot(
    &os_ctl_state, KC_LCTL, _OCTL,
    keycode, record
  );
  update_oneshot(
    &os_alt_state, KC_LALT, _OALT,
    keycode, record
  );
  update_oneshot(
    &os_gui_state, KC_LGUI, _OGUI,
    keycode, record
  );


  process_caps_word(keycode, record);

  mods_state = get_mods();
  oneshot_mods_state = get_oneshot_mods();

  // TAP(_C_ACT)
  if (keycode == _C_ACT && record->event.pressed && record->tap.count > 0) {
    // Second tap: clear mods.
    if (oneshot_mods_state & MOD_MASK_CTRL) {
      clear_oneshot_mods();
    }
    // First tap: set oneshot CTL.
    else {
      set_oneshot_mods(MOD_BIT(KC_LCTL));
    }
    ret = false;
  }

  // TAP(_S_SYM)
  else if (keycode == _S_SYM && record->event.pressed && record->tap.count > 0) {
    // Second tap: enable word caps.
    if (oneshot_mods_state & MOD_MASK_SHIFT) {
      clear_oneshot_mods();
      caps_word_enable();
    }
    // Caps word already enabled: disable.
    else if (caps_word_on) {
      caps_word_disable();
    }
    // First tap: set oneshot SFT.
    else {
      set_oneshot_mods(MOD_BIT(KC_LSFT));
    }
    ret = false;
  }

  // SYM: DTIL
  else if (keycode == _S_TIL && record->event.pressed && record->tap.count > 0) {
    tap_code16(US_DTIL);
    layer_off(_SYM);
    ret = false;
  }

  // SYM: ACUT
  else if (keycode == _C_ACU && record->event.pressed && record->tap.count > 0) {
    tap_code16(US_ACUT);
    layer_off(_SYM);
    ret = false;
  }

  // SYM: DCIR
  else if (keycode == _A_CIR && record->event.pressed && record->tap.count > 0) {
    tap_code16(US_DCIR);
    layer_off(_SYM);
    ret = false;
  }

  // SYM: DGRV
  else if (keycode == _G_GRV && record->event.pressed && record->tap.count > 0) {
    tap_code16(US_DGRV);
    layer_off(_SYM);
    ret = false;
  }

  // SYM: PIPE
  else if (keycode == _PIPE && record->event.pressed) {
    tap_code16(US_PIPE);
    tap_code16(US_RABK);
    ret = false;
  }
  
  // _ARROW
  else if (keycode == _ARROW && record->event.pressed) {
    tap_code(US_MINS);
    tap_code16(US_RABK);
    ret = false;
  }

  // _ARROW2
  else if (keycode == _ARROW2 && record->event.pressed) {
    tap_code16(US_EQL);
    tap_code16(US_RABK);
    ret = false;
  }

  process_repeat_key(keycode, record);

  return ret;
}


uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        default:
            return TAPPING_TERM;
    }
}


bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    default:
      return true;
  }
}

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        default:
            return true;
    }
}
