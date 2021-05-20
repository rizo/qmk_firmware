// TODO: Reduce tapping term for _APP_SWP

#include QMK_KEYBOARD_H


// Doesn't work?
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
    _TAB_SWP_FAKE
};


// Home row mods
#define _A CTL_T(KC_A)
#define _R ALT_T(KC_R)
#define _S GUI_T(KC_S)
#define _T SFT_T(KC_T)

#define _N SFT_T(KC_N)
#define _E GUI_T(KC_E)
#define _I ALT_T(KC_I)
#define _O CTL_T(KC_O)


// Thumb keys
#define _ACT_TAB  LT(_ACT, KC_TAB)
#define _SYM_SPC  LT(_SYM, KC_SPC)
#define _SFT_ENT  SFT_T(KC_ENT)
#define _FUN_BSP  LT(_FUN, KC_BSPC)

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
                                          _ACT_TAB, _SYM_SPC,  _SFT_ENT, _FUN_BSP
  ),

  [_SYM] = LAYOUT(
      KC_CIRC, KC_HASH, KC_LCBR,  KC_RCBR,  KC_ASTR,                     KC_EQL, KC_1, KC_2, KC_3, KC_GRV,
        KC_AT, KC_PIPE, KC_LPRN,  KC_RPRN,  KC_PLUS,                    KC_MINS, KC_4, KC_5, KC_6, KC_0,
       KC_DLR, KC_AMPR,   KC_LT,    KC_GT,  KC_PERC,                    KC_SLSH, KC_7, KC_8, KC_9, KC_BSLS,
                                            XXXXXXX, _______,  KC_LBRC, KC_RBRC
  ),

  [_NUM] = LAYOUT(
       KC_GRV, KC_1, KC_2, KC_3,  KC_EQL,                    KC_ASTR, KC_LCBR, KC_RCBR,  KC_HASH, KC_CIRC,
         KC_0, KC_4, KC_5, KC_6, KC_MINS,                    KC_PLUS, KC_LPRN, KC_RPRN,  KC_PIPE, KC_AT,
      KC_BSLS, KC_7, KC_8, KC_9, KC_SLSH,                    KC_PERC,   KC_LT,   KC_GT,  KC_AMPR, KC_DLR,
                                 KC_LBRC, KC_RBRC,  _______, XXXXXXX
  ),

  [_ACT] = LAYOUT(
     KC_ESC,  G(KC_W),G(KC_LBRC),G(KC_RBRC), _UNREDO,                    KC_PGUP, A(KC_LEFT),   KC_UP, A(KC_RIGHT), G(KC_UP),
   _WIN_SWP, _APP_SWP,  _SPL_SWP,  _TAB_SWP, G(KC_A),                    KC_PGDN,    KC_LEFT, KC_DOWN,    KC_RIGHT, G(KC_DOWN),
      _UNDO,     _CUT,     _COPY,     _PAST,   _REDO,                    XXXXXXX, G(KC_LEFT), KC_CAPS, G(KC_RIGHT), XXXXXXX,
                                              _______, XXXXXXX,  KC_ESC, KC_BSPC
  ),

  [_FUN] = LAYOUT(
       KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_EJCT,                   XXXXXXX,   _MUTE,   _VOLD,    _VOLU, XXXXXXX,
       KC_F5,  KC_F6,  KC_F7,  KC_F8,   KC_CLR,                   XXXXXXX, KC_LSFT, KC_LGUI,  KC_LALT, KC_LCTL,
       KC_F9,  KC_F10, KC_F11, KC_F12, XXXXXXX,                   XXXXXXX, KC_MPLY, KC_MPRV,  KC_MNXT, XXXXXXX,
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
  else if (keycode == _ACT_TAB && !record->event.pressed) {
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
  bool is_ctl_on = (get_mods() & MOD_BIT(KC_LCTL));
  bool no_mods_on = !is_gui_on && !is_alt_on && !is_sft_on && !is_ctl_on;


  // Switcher
  if (IS_LAYER_ON(_ACT)) {
    ret = switch_app(&_s_app_active, keycode, record);
  }

  // SFT BSP to DEL
  if (((keycode == _FUN_BSP && record->tap.count > 0) || keycode == KC_BSPC) && record->event.pressed) {
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
      // No other mods.
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

  // ABC: SFT(_SYM_SPC) -> UNDS
  else if (keycode == _SYM_SPC && is_sft_on && record->event.pressed && record->tap.count > 0) {
    tap_code16(KC_UNDS);
    ret = false;
  }

  // ABC: SFT(_ACT_TAB) -> TILD
  else if (keycode == _ACT_TAB && is_sft_on && record->event.pressed && record->tap.count > 0) {
    tap_code16(KC_TILD);
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
    if (is_sft_on) {
      tap_code16(KC_SCLN); // ':' because sft is on
    } else {
      tap_code(KC_DOT);
    }
    ret = false;
  }

  // ',' / ';'
  else if (keycode == _COM_SCL && record->event.pressed) {
    if (is_sft_on) {
      unregister_code(KC_LSFT);
      tap_code16(KC_SCLN);
      register_code(KC_LSFT);
    } else {
      tap_code(KC_COMM);
    }
    ret = false;
  }

  // '!' / '?' / MOD '/'
  else if (keycode == _EXC_QST && record->event.pressed) {
    // Only whe no mods are on. Otherwise use '/'.
    if (!is_alt_on && !is_gui_on && !is_ctl_on && !is_sft_on) {
      keycode = S(KC_1); // '!'
    }
    else {
      keycode = KC_SLSH;
    }
    tap_code16(keycode);
    ret = false;
  }

  // UNDOREDO
  else if (keycode == _UNREDO && record->event.pressed) {
    tap_code16(G(KC_Z));
    tap_code16(S(G(KC_Z)));
    ret = false;
  }

  return ret;
}


bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case _SYM_SPC:
      return false;
    case _FUN_BSP:
      return false;
    case _SFT_ENT:
      return false;
    case _ACT_TAB:
      return false;
    
    default:
      return true;
  }
}