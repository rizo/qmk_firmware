// TODO: Reduce tapping term for _APP_SWP

#include QMK_KEYBOARD_H


// FIXME: Doesn't work?
#define WITHOUT_MODS(...) \
  do { \
    const uint8_t _real_mods = get_mods(); \
    clear_mods(); \
    { __VA_ARGS__ } \
    set_mods(_real_mods); \
  } while (0)

enum layers {
  _ABC,
  _SYM,
  _NUM,
  _ACT,
  _FUN
};

// Custom keys.
enum keycodes {
    _COM_SCL = SAFE_RANGE,
    _DOT_COL,
    _EXC_QST,

    _UNREDO,

    _WIN_SWP_FAKE,
    _APP_SWP_FAKE,
    _SPL_SWP_FAKE,
    _TAB_SWP_FAKE,

    _FUN_SFT_FAKE,
    _FUN_GUI_FAKE,
    _FUN_ALT_FAKE,
    _FUN_CTL_FAKE,

    _SYM_LT_FAKE,
    _SYM_GT_FAKE,

    _CAPS_WORD,

    _OSFT_NUM_FAKE
};


// Tap dance
#ifdef _TAPDANCE_ENABLED

enum {
    TD_SLCT
};

// TD keys
#define _SLCT TD(TD_SLCT)

void dance_cln_finished(qk_tap_dance_state_t *state, void *user_data) {
  bool is_lctl_on = (get_mods() & MOD_BIT(KC_LCTL));
  
  if (state->count == 1) {
    if (is_lctl_on) {
      tap_code16(C(A(KC_LEFT)));
      tap_code16(S(C(A(KC_RIGHT))));
    } else {
      tap_code16(A(KC_LEFT));
      tap_code16(S(A(KC_RIGHT)));
    }
  } else if (state->count == 2) {
    tap_code16(G(KC_LEFT));
    tap_code16(S(G(KC_RIGHT)));
  } else {
    tap_code16(G(KC_A));
  }
}

// All tap dance functions would go here. Only showing this one.
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_SLCT] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, dance_cln_finished, NULL, 150)
};

#endif

// ABC: Home row mods
#ifdef _ENABLE_HOME_MODS
#define _A CTL_T(KC_A)
#define _R ALT_T(KC_R)
#define _S GUI_T(KC_S)
#define _T SFT_T(KC_T)

#define _N SFT_T(KC_N)
#define _E GUI_T(KC_E)
#define _I ALT_T(KC_I)
#define _O CTL_T(KC_O)
#else
#define _A KC_A
#define _R KC_R
#define _S KC_S
#define _T KC_T

#define _N KC_N
#define _E KC_E
#define _I KC_I
#define _O KC_O
#endif


// Thumb keys
#define _ACT_SPC  LT(_ACT, KC_SPC)
#define _NUM_TAB  LT(_NUM, KC_TAB)
#define _SYM_ENT  LT(_SYM, KC_ENT)
#define _FUN_BSP  LT(_FUN, KC_BSPC)
#define _OSFT_NUM LT(_NUM, _OSFT_NUM_FAKE)

// ACT keys
#define _LOCK G(C(KC_Q))
#define _CTL_ESC CTL_T(KC_ESC)
#define _UNDO G(KC_Z)
#define _REDO S(G(KC_Z))
#define _COPY G(KC_C)
#define _PAST G(KC_V)
#define _CUT G(KC_X)
#define  _VOLU KC__VOLUP
#define  _VOLD KC__VOLDOWN
#define  _MUTE KC__MUTE
#define _BACK G(KC_LBRC)
#define _FWRD G(KC_RBRC)
#define _SYM_WIN C(G(KC_SPC))


#define _WIN_SWP GUI_T(_WIN_SWP_FAKE)
#define _APP_SWP ALT_T(_APP_SWP_FAKE)
#define _SPL_SWP GUI_T(_SPL_SWP_FAKE)
#define _TAB_SWP SFT_T(_TAB_SWP_FAKE)

// FUN keys
#define _FUN_SFT SFT_T(_FUN_SFT_FAKE)
#define _FUN_GUI GUI_T(_FUN_GUI_FAKE)
#define _FUN_ALT ALT_T(_FUN_ALT_FAKE)
#define _FUN_CTL CTL_T(_FUN_CTL_FAKE)
#define _OS_SFT OSM(MOD_LSFT)
#define _OS_GUI OSM(MOD_LGUI)
#define _OS_ALT OSM(MOD_LALT)
#define _OS_CTL OSM(MOD_LCTL)

// SYM keys
#define _ACT_LT LT(_ACT, KC_LT)
#define _NUM_GT LT(_NUM, KC_GT)



// --- COMBOS ---
#ifdef _COMBOS_ENABLED

enum combo_events {
  _E_AR_MOD,
  _E_AS_MOD,
  _E_AT_MOD,
  _E_RS_MOD,
  _E_RT_MOD,
  _E_ST_MOD,
  _E_ARS_MOD,
  _E_ART_MOD,
  _E_AST_MOD,
  _E_RST_MOD,
  _E_ARST_MOD
};


//       A,       R,       S,       T
// KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT

// A + R
const uint16_t PROGMEM   ar_mod_combo[] = {_A, _R, COMBO_END};

// A + S
const uint16_t PROGMEM   as_mod_combo[] = {_A, _S, COMBO_END};

// A + T
const uint16_t PROGMEM   at_mod_combo[] = {_A, _T, COMBO_END};

// R + S
const uint16_t PROGMEM   rs_mod_combo[] = {_R, _S, COMBO_END};

// R + T
const uint16_t PROGMEM   rt_mod_combo[] = {_R, _T, COMBO_END};

// S + T
const uint16_t PROGMEM   st_mod_combo[] = {_S, _T, COMBO_END};

// A + R + S 
const uint16_t PROGMEM  ars_mod_combo[] = {_A, _R, _S, COMBO_END};

// A + R + T 
const uint16_t PROGMEM  art_mod_combo[] = {_A, _R, _T, COMBO_END};

// A + S + T 
const uint16_t PROGMEM  ast_mod_combo[] = {_A, _S, _T, COMBO_END};

// R + S + T 
const uint16_t PROGMEM  rst_mod_combo[] = {_R, _S, _T, COMBO_END};

// A + R + S + T 
const uint16_t PROGMEM arst_mod_combo[] = {_A, _R, _S, _T, COMBO_END};


combo_t key_combos[COMBO_COUNT] = {
  [_E_AR_MOD] = COMBO_ACTION(ar_mod_combo),
  [_E_AS_MOD] = COMBO_ACTION(as_mod_combo),
  [_E_AT_MOD] = COMBO_ACTION(at_mod_combo),
  [_E_RS_MOD] = COMBO_ACTION(rs_mod_combo),
  [_E_RT_MOD] = COMBO_ACTION(rt_mod_combo),
  [_E_ST_MOD] = COMBO_ACTION(st_mod_combo),
  [_E_ARS_MOD] = COMBO_ACTION(ars_mod_combo),
  [_E_ART_MOD] = COMBO_ACTION(art_mod_combo),
  [_E_AST_MOD] = COMBO_ACTION(ast_mod_combo),
  [_E_RST_MOD] = COMBO_ACTION(rst_mod_combo),
  [_E_ARST_MOD] = COMBO_ACTION(arst_mod_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {

  case _E_AR_MOD:
    if (pressed) {
      set_oneshot_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LALT));
    }
    break;

  case _E_AS_MOD:
    if (pressed) {
      set_oneshot_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI));
    }
    break;

  case _E_AT_MOD:
    if (pressed) {
      set_oneshot_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT));
    }
    break;

  case _E_RS_MOD:
    if (pressed) {
      set_oneshot_mods(MOD_BIT(KC_LALT) | MOD_BIT(KC_LGUI));
    }
    break;

  case _E_RT_MOD:
    if (pressed) {
      set_oneshot_mods(MOD_BIT(KC_LALT) | MOD_BIT(KC_LSFT));
    }
    break;

  case _E_ST_MOD:
    if (pressed) {
      set_oneshot_mods(MOD_BIT(KC_LGUI) | MOD_BIT(KC_LSFT));
    }
    break;

  case _E_ARS_MOD:
    if (pressed) {
      set_oneshot_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LALT) | MOD_BIT(KC_LGUI));
    }
    break;

  case _E_ART_MOD:
    if (pressed) {
      set_oneshot_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LALT) | MOD_BIT(KC_LSFT));
    }
    break;

  case _E_AST_MOD:
    if (pressed) {
      set_oneshot_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI) | MOD_BIT(KC_LSFT));
    }
    break;

  case _E_RST_MOD:
    if (pressed) {
      set_oneshot_mods(MOD_BIT(KC_LALT) | MOD_BIT(KC_LGUI) | MOD_BIT(KC_LSFT));
    }
    break;

  case _E_ARST_MOD:
    if (pressed) {
      set_oneshot_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LALT) | MOD_BIT(KC_LGUI) | MOD_BIT(KC_LSFT));
    }
    break;
  }
}
#endif




// Keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_ABC] = LAYOUT(
        KC_Q,    KC_W,    KC_F,     KC_P,     KC_G,                          KC_J,     KC_L,     KC_U,     KC_Y,  KC_QUOT,
          _A,      _R,      _S,       _T,     KC_D,                          KC_H,       _N,       _E,       _I,       _O,
        KC_Z,    KC_X,    KC_C,     KC_V,     KC_B,                          KC_K,     KC_M, _COM_SCL, _DOT_COL, _EXC_QST,
                                          _ACT_SPC, _OSFT_NUM,  _SYM_ENT, _FUN_BSP
  ),

  [_SYM] = LAYOUT(
        KC_GRV,   KC_AT, KC_LBRC,  KC_RBRC,  KC_HASH,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
       KC_AMPR, KC_PIPE, KC_LPRN,  KC_RPRN,  KC_PERC,                   XXXXXXX, KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL,
       KC_BSLS,  KC_DLR, KC_LCBR,  KC_RCBR,  KC_TILD,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                    _ACT_LT, _NUM_GT,    _______, XXXXXXX
  ),

  [_NUM] = LAYOUT(
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    KC_PLUS,    KC_1,    KC_2,    KC_3, KC_CIRC,
      KC_LCTL, KC_LSFT, KC_LGUI, KC_LALT, XXXXXXX,                    KC_MINS,    KC_4,    KC_5,    KC_6,    KC_0,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    KC_ASTR,    KC_7,    KC_8,    KC_9, KC_SLSH,
                                          XXXXXXX, _______,   KC_EQL, KC_UNDS
  ),

  [_ACT] = LAYOUT(
      _LOCK,   KC_TAB,    _UNDO,    _REDO, XXXXXXX,                       KC_PGUP, A(KC_LEFT),   KC_UP, A(KC_RIGHT), G(KC_UP),
   _CTL_ESC, _APP_SWP, _WIN_SWP, _TAB_SWP, _CAPS_WORD,                    KC_PGDN,    KC_LEFT, KC_DOWN,    KC_RIGHT, G(KC_DOWN),
    XXXXXXX,     _CUT,    _COPY,    _PAST, XXXXXXX,                       XXXXXXX, G(KC_LEFT), G(KC_A), G(KC_RIGHT), XXXXXXX,
                                          _______, XXXXXXX,  KC_KP_ENTER, KC_BSPC
  ),

  [_FUN] = LAYOUT(
      KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,                   XXXXXXX, KC_MPRV,  KC_MPLY,  KC_MNXT, KC_EJCT,
      KC_F6,  KC_F7,  KC_F8,  KC_F9, KC_F10,                   XXXXXXX, _OS_SFT,  _OS_GUI,  _OS_ALT, _OS_CTL,
     KC_F11, KC_F12, KC_F13, KC_F14, KC_F15,                   XXXXXXX,   _MUTE,    _VOLD,    _VOLU, XXXXXXX,
                                     KC_SPC,_SYM_WIN, XXXXXXX, XXXXXXX
  )
};


// Swapper

bool _s_app_active = false;


bool switch_app(bool *active, uint16_t keycode, keyrecord_t *record) {
  bool is_lctl_on = (get_mods() & MOD_BIT(KC_LCTL));

  // Swapper key detected.
  if (keycode == _APP_SWP) {
    // It is a tap, not hold.
    if (record->tap.count > 0) {
      // Pressed.
      if (record->event.pressed) {

        // Register LGUI on activation.
        if (!*active) {
          *active = true;
          register_code(KC_LGUI); 
        }

        // Treat CTL as shift.
        if (is_lctl_on) {
          unregister_code(KC_LCTL);
          tap_code16(S(KC_TAB));
          register_code(KC_LCTL);
        } else {
          tap_code(KC_TAB);
        }

        return false;
      }
      // Released.
      else {
        // Don't unregister KC_LGUI yet.
        unregister_code(KC_TAB);
        return false;
      }
    }
    // It is a hold. Do nothing.
    else {
      return true;
    }
  }

  // Unregister KC_LGUI on layer release.
  else if (keycode == _ACT_SPC && !record->event.pressed) {
    unregister_code(KC_LGUI);
    *active = false;
    return true;
  }

  // Ensure the state is fully reset on keys that end swp.
  else if (*active && ((keycode == KC_ESC || keycode == KC_ENT || keycode == KC_SPC) && record->event.pressed)) {
    tap_code(keycode);
    unregister_code(KC_LGUI);
    *active = false;
    return false;
  } else {
    return true;
  }
}


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

// Used to extract the basic tapping keycode from a dual-role key.
// Example: GET_TAP_KC(MT(MOD_RSFT, KC_E)) == KC_E
#define GET_TAP_KC(dual_role_key) dual_role_key & 0xFF

void process_caps_word(uint16_t keycode, const keyrecord_t *record) {
    // Update caps word state
    if (caps_word_on) {
        switch (keycode) {
            case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
                // Earlier return if this has not been considered tapped yet
                if (record->tap.count == 0) { return; }
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
            case KC_MINS:
            case KC_BSPC:
            case KC_UNDS:
            case KC_PIPE:
            case _CAPS_WORD:
            case KC_LPRN:
            case KC_RPRN:
                // If chording mods, disable caps word
                if (record->event.pressed && (get_mods() != MOD_LSFT) && (get_mods() != 0)) {
                    caps_word_disable();
                }
                break;
            default:
                // Any other keycode should automatically disable caps
                if (record->event.pressed && !(get_oneshot_mods() & MOD_MASK_SHIFT)) {
                    caps_word_disable();
                }
                break;
        }
    }
}


uint16_t prev_keycode = KC_F20;


// Function overrides.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {  
  bool ret = true;

  uint8_t mods = get_mods();
  uint8_t oneshot_mods = get_oneshot_mods();

  bool is_lgui_on = (mods & MOD_BIT(KC_LGUI) || oneshot_mods & MOD_BIT(KC_LGUI));
  bool is_lsft_on = (mods & MOD_BIT(KC_LSHIFT) || oneshot_mods & MOD_BIT(KC_LSHIFT));
  bool is_rsft_on = (mods & MOD_BIT(KC_RSHIFT) || oneshot_mods & MOD_BIT(KC_RSHIFT));
  bool is_lctl_on = (mods & MOD_BIT(KC_LCTL)) || oneshot_mods & MOD_BIT(KC_LCTL);
  
  process_caps_word(keycode, record);

  // Switcher
  if (IS_LAYER_ON(_ACT)) {
    ret = switch_app(&_s_app_active, keycode, record);
  }

  // SFT BSP to DEL
  if (((keycode == _FUN_BSP && record->tap.count > 0) || keycode == KC_BSPC) && record->event.pressed) {
    if (is_rsft_on) {
      tap_code16(KC_UNDS);
      ret = false;
    } else if (is_lsft_on) {
      del_oneshot_mods(MOD_BIT(KC_LSFT));
      unregister_code(KC_LSHIFT);

      if (is_lgui_on) {
        unregister_code(KC_LGUI);
        tap_code16(C(KC_K));
        register_code(KC_LSHIFT);
        register_code(KC_LGUI);
        ret = false;
      } 
      // CTL
      else if (is_lctl_on) {
        tap_code16(A(KC_DEL));
        register_code(KC_LSHIFT);
        ret = false;
      }
      // Only SFT: DEL.
      else {
        tap_code(KC_DEL);
        register_code(KC_LSHIFT);
        ret = false;
      }
    } else if (is_lctl_on) {
      tap_code16(A(KC_BSPC));
      ret = false;
    }
  }

  else if (keycode == _CAPS_WORD && record->event.pressed) {
    if (caps_word_on) {
      caps_word_disable();
      ret = false;
    } else {
      caps_word_enable();
      ret = false;
    }
  }

  // ACT: WIN SWP tap action
  else if (keycode == _WIN_SWP && record->event.pressed && record->tap.count > 0) {
    // Treat CTL as SFT.
    if (is_lctl_on) {
      unregister_code(KC_LCTL);
      tap_code16(S(G(KC_GRV)));
      register_code(KC_LCTL);
    } else {
      tap_code16(G(KC_GRV));
    }
    ret = false;
  }

  else if (keycode == _CTL_ESC && record->event.pressed && record->tap.count > 0) {
    clear_oneshot_mods();
    // Normal ESC.
    ret = true;
  }

  // ACT: tab tap action
  else if (IS_LAYER_ON(_ACT) && keycode == KC_TAB) {
    if (record->event.pressed) {
      // Treat CTL as SFT.
      if (is_lctl_on) {
        unregister_code(KC_LCTL);
        register_code(KC_LSFT);
        ret = true;
      } else {
        // Normal tab.
        ret = true;
      }
    } else {
      if (is_lsft_on) {
        unregister_code(KC_LSFT);
        register_code(KC_LCTL);
      }
    }
  }

  // ACT: SPL SWP
  else if (keycode == _SPL_SWP && record->event.pressed && record->tap.count > 0) {
    // Treat CTL as SFT.
    if (is_lctl_on) {
      unregister_code(KC_LCTL);
      tap_code16(S(A(KC_TAB)));
      register_code(KC_LCTL);
    } else {
      tap_code16(A(KC_TAB));
    }
    ret = false;
  }

  // ACT: TAB SWP
  else if (keycode == _TAB_SWP && record->event.pressed && record->tap.count > 0) {
    // Treat CTL as SFT.
    if (is_lctl_on) {
      tap_code16(S(KC_TAB));
    } else {
      tap_code16(C(KC_TAB));
    }
    ret = false;
  }


  // SYM: ACT LT
  else if (keycode == _ACT_LT && record->event.pressed && record->tap.count > 0) {
    tap_code16(S(KC_COMM));
    ret = false;
  }

  // SYM: NUM GT
  else if (keycode == _NUM_GT && record->event.pressed && record->tap.count > 0) {
    tap_code16(S(KC_DOT));
    ret = false;
  }


  // OST SFT
  else if (keycode == _OSFT_NUM) {
    if (record->event.pressed) {
      if (record->tap.count == 0) { // hold
        ret = true;
      }
      if (record->tap.count > 0) { // tap
        if (prev_keycode == _OSFT_NUM) {
          caps_word_enable();
          ret = false;
        } else {
          set_oneshot_mods(MOD_BIT(KC_LSFT));
          ret = false;
        }
      }
    } else {
      ret = true;
    }
  }

  // FUN: A(N)
  else if (keycode == _FUN_SFT && record->event.pressed && record->tap.count > 0) {
    tap_code16(A(KC_N));
    ret = false;
  }

  // FUN: A(E)
  else if (keycode == _FUN_GUI && record->event.pressed && record->tap.count > 0) {
    tap_code16(A(KC_E));
    ret = false;
  }

  // FUN: A(I)
  else if (keycode == _FUN_ALT && record->event.pressed && record->tap.count > 0) {
    tap_code16(A(KC_I));
    ret = false;
  }

  // FUN: A(GRV)
  else if (keycode == _FUN_CTL && record->event.pressed && record->tap.count > 0) {
    tap_code16(A(KC_GRV));
    ret = false;
  }

  // '.' / ':'
  else if (keycode == _DOT_COL && record->event.pressed) {
    if (is_lsft_on || is_rsft_on) {
      tap_code16(KC_SCLN); // ':' because sft is on
    } else {
      tap_code(KC_DOT);
    }
    ret = false;
  }

  // ',' / ';'
  else if (keycode == _COM_SCL && record->event.pressed) {
    if (is_lsft_on || is_rsft_on) {
      clear_oneshot_mods();
      clear_mods();
      tap_code(KC_SCLN);
      set_mods(mods);
    } else {
      tap_code(KC_COMM);
    }
    ret = false;
  }

  // '!' / '?'
  else if (keycode == _EXC_QST && record->event.pressed) {
    if (is_lsft_on || is_rsft_on) {
      tap_code16(S(KC_SLSH)); // ?
    }
    else {
      tap_code16(S(KC_1)); // !
    }
    ret = false;
  }

  // UNDOREDO
  else if (keycode == _UNREDO && record->event.pressed) {
    tap_code16(G(KC_Z));
    tap_code16(S(G(KC_Z)));
    ret = false;
  }

  if (record->event.pressed)
    prev_keycode = keycode;

  return ret;
}


bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case _NUM_TAB:
    case _FUN_BSP:
    case _SYM_ENT:
    case _ACT_SPC:
      return false;
    
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