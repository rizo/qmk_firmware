#include QMK_KEYBOARD_H

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
  _NUM,
  _SYM,
};


// Custom keys.
enum keycodes {
    _ACTNUM_FAKE = SAFE_RANGE,
    _ABCSFT_FAKE,

    _OGUI_FAKE,
    _OALT_FAKE,
    _OCTL_FAKE,
    _OSFT_FAKE,

    _S_TIL_FAKE,
    _G_ACU_FAKE,
    _A_CIR_FAKE,
    _C_GRV_FAKE,

    _PIPE,
    _ARROW,
    _ARROW2,
    _CURDIR,
    _HOMDIR,
    _PRVDIR,

    _RPT,
    _RSTMOD,
};

// OS mods.
#define _OGUI GUI_T(_OGUI_FAKE)
#define _OALT ALT_T(_OALT_FAKE)
#define _OCTL CTL_T(_OCTL_FAKE)
#define _OSFT SFT_T(_OSFT_FAKE)

// Thumb keys
#define _ACTNUM LT(_NUM, _ACTNUM_FAKE)
#define _ABCSFT MT(MOD_LSFT, _ABCSFT_FAKE)
#define _SYMBSP LT(_SYM, KC_BSPC)

// Back/forward.
#define _BACK G(KC_LBRC)
#define _FRWD G(KC_RBRC)

// Word/line motion.
#define _WRDL A(KC_LEFT)
#define _WRDR A(KC_RIGHT)
#define _LNL G(KC_LEFT)
#define _LNR G(KC_RIGHT)

// Edit actions.
#define _CUT G(KC_X)
#define _COPY G(KC_C)
#define _PASTE G(KC_V)
#define _UNDO G(KC_Z)
#define _REDO S(G(KC_Z))

// Untab
#define _STAB S(KC_TAB)

// Volume keys.
#define  _VOLU KC__VOLUP
#define  _VOLD KC__VOLDOWN
#define  _MUTE KC__MUTE

// Left mod accents.
#define _C_GRV CTL_T(_C_GRV_FAKE)
#define _A_CIR ALT_T(_A_CIR_FAKE)
#define _G_ACU GUI_T(_G_ACU_FAKE)
#define _S_TIL SFT_T(_S_TIL_FAKE)

// INTL keys.
#define _ACUT A(KC_E)
#define _DTIL A(KC_N)
#define _DCIR A(KC_I)
#define _DGRV A(KC_GRV)
#define _CCED A(KC_C)

// Media keys.
#define _VOLU KC__VOLUP
#define _VOLD KC__VOLDOWN
#define _MUTE KC__MUTE


// Keymap.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_ABC] = LAYOUT(
       KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                    KC_J,     KC_L, KC_U,     KC_Y,   KC_QUOT,
       KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                    KC_H,     KC_N, KC_E,     KC_I,   KC_O,
       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                    KC_K,     KC_M, KC_COMM,  KC_DOT, KC_EXLM,
                                        _ACTNUM, _ABCSFT,   KC_SPC, _SYMBSP
  ),

  [_ACT] = LAYOUT(
    _RSTMOD,    _RPT,   _BACK,   _FRWD, KC_WH_U,                    KC_PGUP, KC_ESC,  KC_UP,   KC_TAB,  KC_HOME,
      _OCTL,   _OALT,   _OGUI,   _OSFT, KC_WH_D,                    KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,
      _UNDO,    _CUT,   _COPY,  _PASTE,   _REDO,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                        _______, _______,  KC_ENT,  KC_BSPC
  ),

  [_NUM] = LAYOUT(
    XXXXXXX,   _PIPE,  _ARROW, _ARROW2, _CURDIR,                    KC_PLUS, KC_1,    KC_2,    KC_3,    KC_CIRC,
      _OCTL,   _OALT,   _OGUI,   _OSFT, _HOMDIR,                    KC_MINS, KC_4,    KC_5,    KC_6,    KC_0,
    XXXXXXX, XXXXXXX,   _CCED, XXXXXXX, _PRVDIR,                    KC_ASTR, KC_7,    KC_8,    KC_9,    KC_SLSH,
                                        XXXXXXX, _______,  KC_EQL,  KC_UNDS
  ),

  [_SYM] = LAYOUT(
    KC_GRV,    KC_AT, KC_LCBR, KC_RCBR, KC_HASH,                    XXXXXXX, _MUTE,   _VOLD,   _VOLU,   XXXXXXX,
    KC_TILD, KC_PIPE, KC_LPRN, KC_RPRN, KC_PERC,                    XXXXXXX, KC_LSFT, KC_LGUI, KC_RALT, KC_LCTL,
    KC_BSLS,  KC_DLR, KC_LBRC, KC_RBRC, KC_AMPR,                    XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, RESET,
                                        KC_LABK, KC_RABK,  _______, XXXXXXX
  )
};

// S(KC_SPC) -> KC_UNDS
// const key_override_t spc_ent_ko = ko_make_basic(MOD_MASK_SHIFT, _SYMENT, KC_ENT);

// S(KC_COMMA) -> KC_SCLN
const key_override_t comma_scln_ko = ko_make_basic(MOD_MASK_SHIFT, KC_COMMA, KC_SCLN);

// S(KC_DOT) -> KC_COLN
const key_override_t dot_coln_ko = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_COLN);

// S(KC_EXLM) -> KC_QUES
const key_override_t exlm_ques_ko = ko_make_basic(MOD_MASK_SHIFT, KC_EXLM, KC_QUES);

// S(KC_LABK) -> KC_RABK
const key_override_t labk_rabk_ko = ko_make_basic(MOD_MASK_SHIFT, KC_LABK, KC_RABK);

const key_override_t **key_overrides = (const key_override_t *[]) {
  // &spc_ent_ko,
  &comma_scln_ko,
  &dot_coln_ko,
  &exlm_ques_ko,
  &labk_rabk_ko,
  NULL
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
    } else { // keycode == _RPT
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
    case _ACTNUM:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case _ACTNUM:
    case _ABCSFT:
    case _OSFT:
    case _OCTL:
    case _OALT:
    case _OGUI:
        return true;
    default:
        return false;
    }
}

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

  process_caps_word(keycode, record);

  mods_state = get_mods();
  oneshot_mods_state = get_oneshot_mods();

  // TAP(_ACTNUM)
  if (keycode == _ACTNUM && record->event.pressed && record->tap.count > 0) {
    layer_on(_ACT);
    ret = false;
  }

  // TAP(_ABCSFT)
  if (keycode == _ABCSFT && record->event.pressed && record->tap.count > 0) {
    layer_clear();
    ret = false;
  }

  // _RSTMOD
  else if (keycode == _RSTMOD && record->event.pressed) {
    clear_oneshot_mods();
    ret = false;
  }

  // TAP(_G_ACT)
  // else if (keycode == _G_ACT && record->event.pressed && record->tap.count > 0) {
  //   // set_oneshot_mods(MOD_BIT(KC_LGUI));
  //   clear_oneshot_mods();
  //   ret = false;
  // }

  // TAP(_OSFT)
  else if (keycode == _OSFT && record->event.pressed && record->tap.count > 0) {
    set_oneshot_mods(MOD_BIT(KC_LSFT) | oneshot_mods_state);
    ret = false;
  }

  // TAP(_OGUI)
  else if (keycode == _OGUI && record->event.pressed && record->tap.count > 0) {
    set_oneshot_mods(MOD_BIT(KC_LGUI) | oneshot_mods_state);
    ret = false;
  }

  // TAP(_OALT)
  else if (keycode == _OALT && record->event.pressed && record->tap.count > 0) {
    set_oneshot_mods(MOD_BIT(KC_LALT) | oneshot_mods_state);
    ret = false;
  }

  // TAP(_OCTL)
  else if (keycode == _OCTL && record->event.pressed && record->tap.count > 0) {
    set_oneshot_mods(MOD_BIT(KC_LCTL) | oneshot_mods_state);
    ret = false;
  }

  // SYM: DTIL
  else if (keycode == _S_TIL && record->event.pressed && record->tap.count > 0) {
    tap_code16(_DTIL);
    layer_off(_SYM);
    ret = false;
  }

  // SYM: ACUT
  else if (keycode == _G_ACU && record->event.pressed && record->tap.count > 0) {
    tap_code16(_ACUT);
    layer_off(_SYM);
    ret = false;
  }

  // SYM: DCIR
  else if (keycode == _A_CIR && record->event.pressed && record->tap.count > 0) {
    tap_code16(_DCIR);
    layer_off(_SYM);
    ret = false;
  }

  // SYM: DGRV
  else if (keycode == _C_GRV && record->event.pressed && record->tap.count > 0) {
    tap_code16(_DGRV);
    layer_off(_SYM);
    ret = false;
  }

  // SYM: PIPE
  else if (keycode == _PIPE && record->event.pressed) {
    tap_code16(KC_PIPE);
    tap_code16(KC_RABK);
    ret = false;
  }

  // _ARROW
  else if (keycode == _ARROW && record->event.pressed) {
    tap_code(KC_MINS);
    tap_code16(KC_RABK);
    ret = false;
  }

  // _ARROW2
  else if (keycode == _ARROW2 && record->event.pressed) {
    tap_code16(KC_EQL);
    tap_code16(KC_RABK);
    ret = false;
  }

  // _CURDIR
  else if (keycode == _CURDIR && record->event.pressed) {
    tap_code16(KC_DOT);
    tap_code16(KC_SLSH);
    ret = false;
  }

  // _HOMDIR
  else if (keycode == _HOMDIR && record->event.pressed) {
    tap_code16(KC_TILD);
    tap_code16(KC_SLSH);
    ret = false;
  }

  // _PRVDIR
  else if (keycode == _PRVDIR && record->event.pressed) {
    tap_code16(KC_DOT);
    tap_code16(KC_DOT);
    tap_code16(KC_SLSH);
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
