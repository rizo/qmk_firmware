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

    _LPRN_FAKE,
    _ASTR_FAKE,
    _RPRN_FAKE,
    _AT_FAKE,

    _WIN_SWP_FAKE,
    _APP_SWP_FAKE,
    _SPL_SWP_FAKE,
    _TAB_SWP_FAKE
};


// Tap dance

enum {
    TD_SLCT,
    TD_AR_L,
    TD_AR_R
};

void dance_cln_finished(qk_tap_dance_state_t *state, void *user_data) {
  bool is_ctl_on = (get_mods() & MOD_BIT(KC_LCTL));
  
  if (state->count == 1) {
    if (is_ctl_on) {
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


void dance_arl_finished(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    tap_code16(KC_LT);
  } else {
    SEND_STRING("<-");
  }
}


void dance_arr_finished(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    tap_code16(KC_GT);
  } else {
    SEND_STRING("->");
  }
}


// All tap dance functions would go here. Only showing this one.
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_SLCT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_cln_finished, NULL),
    [TD_AR_L] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_arl_finished, NULL),
    [TD_AR_R] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_arr_finished, NULL),
};


// ABC: Home row mods
#define _A CTL_T(KC_A)
#define _R ALT_T(KC_R)
#define _S GUI_T(KC_S)
#define _T SFT_T(KC_T)

#define _N SFT_T(KC_N)
#define _E GUI_T(KC_E)
#define _I ALT_T(KC_I)
#define _O CTL_T(KC_O)

// SYM: Home row mods
#define _LPRN SFT_T(_LPRN_FAKE)
#define _ASTR GUI_T(_ASTR_FAKE)
#define _RPRN ALT_T(_RPRN_FAKE)
#define _AT CTL_T(_AT_FAKE)

// TD keys
#define _SLCT TD(TD_SLCT)
#define _LT TD(TD_AR_L)
#define _GT TD(TD_AR_R)

// Thumb keys
#define _ACT_BSP  LT(_ACT, KC_BSPC)
#define _SFT_TAB  RSFT_T(KC_TAB)
#define _SYM_ENT  LT(_NUM, KC_ENT)
#define _FUN_SPC  LT(_FUN, KC_SPC)

// ACT keys
#define _UNDO G(KC_Z)
#define _REDO S(G(KC_Z))
#define _COPY G(KC_C)
#define _PAST G(KC_V)
#define _CUT G(KC_X)
#define  _VOLU KC__VOLUP
#define  _VOLD KC__VOLDOWN
#define  _MUTE KC__MUTE


#define _WIN_SWP CTL_T(_WIN_SWP_FAKE)
#define _APP_SWP ALT_T(KC_J)
#define _SPL_SWP GUI_T(_SPL_SWP_FAKE)
#define _TAB_SWP SFT_T(_TAB_SWP_FAKE)


// Keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_ABC] = LAYOUT(
        KC_Q,    KC_W,    KC_F,     KC_P,     KC_G,                          KC_J,     KC_L,     KC_U,     KC_Y,  KC_QUOT,
          _A,      _R,      _S,       _T,     KC_D,                          KC_H,       _N,       _E,       _I,       _O,
        KC_Z,    KC_X,    KC_C,     KC_V,     KC_B,                          KC_K,     KC_M, _COM_SCL, _DOT_COL, _EXC_QST,
                                          _ACT_BSP, _SFT_TAB,  _SYM_ENT, _FUN_SPC
  ),

  [_SYM] = LAYOUT(
      KC_CIRC, KC_HASH, KC_LCBR,  KC_RCBR,  KC_ASTR,                     KC_EQL, KC_1, KC_2, KC_3, KC_GRV,
        KC_AT, KC_PIPE, KC_LPRN,  KC_RPRN,  KC_PLUS,                    KC_MINS, KC_4, KC_5, KC_6, KC_0,
       KC_DLR, KC_AMPR,   KC_LT,    KC_GT,  KC_PERC,                    KC_SLSH, KC_7, KC_8, KC_9, KC_BSLS,
                                            XXXXXXX, _______,  KC_LBRC, KC_RBRC
  ),

  [_NUM] = LAYOUT(
       KC_GRV, KC_1, KC_2, KC_3, KC_PLUS,                    KC_HASH, KC_LCBR, KC_PERC, KC_RCBR, KC_CIRC,
         KC_0, KC_4, KC_5, KC_6, KC_MINS,                    KC_TILD,   _LPRN,   _ASTR,   _RPRN,    _AT,
      KC_BSLS, KC_7, KC_8, KC_9, KC_SLSH,                    KC_AMPR,     _LT, KC_PIPE,     _GT, KC_DLR,
                                 KC_LBRC, KC_RBRC,  _______, XXXXXXX
  ),

  [_ACT] = LAYOUT(
     KC_ESC,  G(KC_W),G(KC_LBRC),G(KC_RBRC), _UNREDO,                    KC_PGUP, A(KC_LEFT),   KC_UP, A(KC_RIGHT), G(KC_UP),
   _WIN_SWP, _APP_SWP,  _SPL_SWP,  _TAB_SWP, C(KC_L),                    KC_PGDN,    KC_LEFT, KC_DOWN,    KC_RIGHT, G(KC_DOWN),
      _UNDO,     _CUT,     _COPY,     _PAST,   _REDO,                    XXXXXXX, G(KC_LEFT),   _SLCT, G(KC_RIGHT), XXXXXXX,
                                              _______, XXXXXXX,  KC_ESC, KC_ENT
  ),

  [_FUN] = LAYOUT(
     KC_F10,  KC_F1,  KC_F2,  KC_F3,  KC_EJCT,                   XXXXXXX,   _MUTE,   _VOLD,    _VOLU, XXXXXXX,
     KC_F11,  KC_F4,  KC_F5,  KC_F6,  KC_CAPS,                   XXXXXXX, KC_LSFT, KC_LGUI,  KC_LALT, KC_LCTL,
     KC_F12,  KC_F7,  KC_F8,  KC_F9,  XXXXXXX,                   XXXXXXX, KC_MPLY, KC_MPRV,  KC_MNXT, XXXXXXX,
                                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  )
};


// Swapper

bool _s_app_active = false;


bool switch_app(bool *active, uint16_t keycode, keyrecord_t *record) {
  bool is_ctl_on = (get_mods() & MOD_BIT(KC_LCTL));

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
        if (is_ctl_on) {
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
  else if (keycode == _ACT_BSP && !record->event.pressed) {
    unregister_code(KC_LGUI);
    *active = false;
    return true;
  }

  // Simulate ESC. We do this to ensure the state is fully reset on ESC.
  else if (*active && (keycode == KC_ESC && record->event.pressed)) {
    tap_code(KC_ESC);
    unregister_code(KC_LGUI);
    *active = false;
    return false;
  } else {
    return true;
  }
}


bool _caps_active = false;


// Function overrides.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {  
  bool ret = true;

  bool is_gui_on = (get_mods() & MOD_BIT(KC_LGUI));
  bool is_alt_on = (get_mods() & MOD_BIT(KC_LALT));
  bool is_sft_on = (get_mods() & MOD_BIT(KC_LSHIFT));
  bool is_rsft_on = (get_mods() & MOD_BIT(KC_RSHIFT));
  bool is_ctl_on = (get_mods() & MOD_BIT(KC_LCTL));
  bool no_mods_on = !is_gui_on && !is_alt_on && !is_sft_on && !is_ctl_on;


  // Switcher
  if (IS_LAYER_ON(_ACT)) {
    ret = switch_app(&_s_app_active, keycode, record);
  }

  // SFT BSP to DEL
  if (((keycode == _ACT_BSP && record->tap.count > 0) || keycode == KC_BSPC) && record->event.pressed) {
    if (is_sft_on) {
      if (is_gui_on) {
        unregister_code(KC_LSHIFT);
        unregister_code(KC_LGUI);
        tap_code16(C(KC_K));
        register_code(KC_LSHIFT);
        register_code(KC_LGUI);
        ret = false;
      } 
      // CTL
      else if (is_ctl_on) {
        unregister_code(KC_LSHIFT);
        tap_code16(A(KC_DEL));
        register_code(KC_LSHIFT);
        ret = false;
      }
      // Only SFT: DEL.
      else {
        unregister_code(KC_LSHIFT);
        tap_code(KC_DEL);
        register_code(KC_LSHIFT);
        ret = false;
      }
    } else if (is_ctl_on) {
      tap_code16(A(KC_BSPC));
      ret = false;
    }
  }

  // SELECTION CAPS
  if (keycode == KC_CAPS && record->event.pressed) {
    if (no_mods_on) {
      _caps_active = !_caps_active;
      if (_caps_active) {
        tap_code(KC_CAPS);
        register_code(KC_RSHIFT);
      } else {
        unregister_code(KC_RSHIFT);
        tap_code(KC_CAPS);
      }
    }
    // Select line.
    else if (is_gui_on) {
      tap_code16(G(KC_LEFT));
      tap_code16(S(G(KC_RIGHT)));
    }
    // Select word.
    else if (is_ctl_on) {
      tap_code16(C(A(KC_LEFT)));
      tap_code16(S(C(A(KC_RIGHT))));
    }
    // Select Word.
    else if (is_alt_on) {
      tap_code16(A(KC_LEFT));
      tap_code16(S(A(KC_RIGHT)));
    }
    // Select all.
    else if (is_sft_on) {
      unregister_code(KC_LSHIFT);
      tap_code16(G(KC_A));
      register_code(KC_LSHIFT);
    }

    ret = false;
  }

  // ACT: WIN SWP tap action
  else if (keycode == _WIN_SWP && record->event.pressed && record->tap.count > 0) {
    tap_code16(G(KC_GRV));
    ret = false;
  }

  // ABC: RSFT(_FUN_SPC) -> UNDS
  else if (keycode == _FUN_SPC && is_rsft_on && record->event.pressed && record->tap.count > 0) {
    tap_code16(KC_UNDS);
    ret = false;
  }

  // ABC: RSFT(_SYM_ENT) -> EQL
  else if (keycode == _SYM_ENT && is_rsft_on && record->event.pressed && record->tap.count > 0) {
    unregister_code(KC_RSFT);
    tap_code16(KC_EQL);
    register_code(KC_RSFT);
    ret = false;
  }

  // ACT: SPL SWP
  else if (keycode == _SPL_SWP && record->event.pressed && record->tap.count > 0) {
    if (is_ctl_on) {
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
    if (is_ctl_on) {
      tap_code16(S(KC_TAB));
    } else {
      tap_code16(C(KC_TAB));
    }
    ret = false;
  }

  // '.' / ':'
  else if (keycode == _DOT_COL && record->event.pressed) {
    if (is_sft_on || is_rsft_on) {
      tap_code16(KC_SCLN); // ':' because sft is on
    } else {
      tap_code(KC_DOT);
    }
    ret = false;
  }

  // ',' / ';'
  else if (keycode == _COM_SCL && record->event.pressed) {
    if (is_sft_on || is_rsft_on) {
      unregister_code(KC_RSFT);
      tap_code16(KC_SCLN);
      register_code(KC_RSFT);
    } else {
      tap_code(KC_COMM);
    }
    ret = false;
  }

  // '!' / '?'
  else if (keycode == _EXC_QST && record->event.pressed) {
    if (is_sft_on || is_rsft_on) {
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

  // SYM SFT(LPRN)
  else if (keycode == _LPRN && record->event.pressed && record->tap.count > 0) {
    tap_code16(KC_LPRN);
    ret = false;
  }

  // SYM GUI(ASTR)
  else if (keycode == _ASTR && record->event.pressed && record->tap.count > 0) {
    tap_code16(KC_ASTR);
    ret = false;
  }

  // SYM ALT(RPRN)
  else if (keycode == _RPRN && record->event.pressed && record->tap.count > 0) {
    tap_code16(KC_RPRN);
    ret = false;
  }
  
  // SYM CTL(AT)
  else if (keycode == _AT && record->event.pressed && record->tap.count > 0) {
    tap_code16(KC_AT);
    ret = false;
  }

  return ret;
}


bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case _SFT_TAB:
      return false;
    case _FUN_SPC:
      return false;
    case _SYM_ENT:
      return false;
    case _ACT_BSP:
      return false;
    
    default:
      return true;
  }
}