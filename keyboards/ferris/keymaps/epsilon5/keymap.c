// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H

enum layers {
  _ABC,
  _SYM,
  _NUM,
  _ACT
};

// Custom keys.
enum keycodes {
    _COM_SCL = SAFE_RANGE,
    _DOT_COL,
    _EXC_QST,

    _GUI_TAB // GUI Tab switcher
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
#define _NUM_ESC  LT(_NUM, KC_ESC)
#define _SYM_ENT  LT(_SYM, KC_ENT)
#define _NUM_BSP  LT(_NUM, KC_BSPC)

// ACT keys
#define _UNDO G(KC_Z)
#define _REDO S(G(KC_Z))
#define _COPY G(KC_C)
#define _PAST G(KC_V)
#define _CUT G(KC_X)
#define  _VOLU KC__VOLUP
#define  _VOLD KC__VOLDOWN
#define  _MUTE KC__MUTE

#define _SFT_ESC SFT_T(KC_ESC)


// Keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_ABC] = LAYOUT(
        KC_Q,    KC_W,    KC_F,     KC_P,     KC_G,                          KC_J,     KC_L,     KC_U,     KC_Y,  KC_QUOT,
          _A,      _R,      _S,       _T,     KC_D,                          KC_H,       _N,       _E,       _I,       _O,
        KC_Z,    KC_X,    KC_C,     KC_V,     KC_B,                          KC_K,     KC_M, _COM_SCL, _DOT_COL, _EXC_QST,
                                          _ACT_TAB, _NUM_ESC,  _SYM_ENT, _NUM_BSP
  ),

  [_SYM] = LAYOUT(
      KC_GRV,   KC_AT, KC_LBRC,  KC_RBRC,  KC_HASH,                  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
     KC_TILD, KC_PIPE, KC_LPRN,  KC_RPRN,  KC_PERC,                  XXXXXXX, KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL,
     KC_BSLS,  KC_DLR, KC_LCBR,  KC_RCBR,  KC_AMPR,                  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                             KC_LT,  KC_GT,  _______, _______  
  ),

  [_NUM] = LAYOUT(
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_ASTR, KC_1, KC_2, KC_3, KC_CIRC,
      KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, XXXXXXX,                   KC_MINS, KC_4, KC_5, KC_6, KC_0,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_PLUS, KC_7, KC_8, KC_9, KC_SLSH,
                                          _______, _______,  KC_EQL, KC_UNDS
  ),

  [_ACT] = LAYOUT(
      XXXXXXX, KC_MPRV,  KC_MNXT,  KC_MPLY, XXXXXXX,                   KC_PGUP,   _UNDO,   KC_UP,   _REDO, KC_HOME,
      KC_LCTL, KC_LALT, _GUI_TAB, _SFT_ESC, XXXXXXX,                   KC_PGDN, KC_LEFT, KC_DOWN,KC_RIGHT,  KC_END,
      XXXXXXX,   _VOLD,    _VOLU,    _MUTE, XXXXXXX,                   XXXXXXX,   _COPY,   _PAST,    _CUT, XXXXXXX,
                                            _______, _______,  KC_EQL, KC_BSPC
  )
};


// Swapper

bool _s_app_active = false;

bool switch_app(bool *active, uint16_t keycode, keyrecord_t *record) {
  // Activate swapper.
  if (keycode == _GUI_TAB) {
    if (record->event.pressed) {
      if (!*active) {
        *active = true;
        register_code(KC_LGUI);
        register_code(KC_TAB);
        return false;
      } else {
        register_code(KC_TAB);
        return false;
      }
    } else { // released
      // Don't unregister KC_LGUI yet.
      unregister_code(KC_TAB);
      return false;
    }
  } 
  // Release the layer key.
  else if (keycode == _ACT_TAB && !record->event.pressed) {
    unregister_code(KC_LGUI);
    *active = false;
    return true;
  }
  // Terminate on ESC.
  else if (*active && (keycode == KC_ESC && record->event.pressed)) {
    *active = false;
    return true;
  } else {
    return true;
  }
}


bool switch_tab(uint16_t keycode, keyrecord_t *record) {
  if (keycode == _K_S_TAB) {
    if (record->event.pressed) {
      tap_code16(get_mods() & MOD_BIT(KC_LSHIFT) ? G(S(KC_LBRC)) : G(S(KC_RBRC)));
    }
    return false;
  } else {
    return true;
  }
}

bool switch_spl(uint16_t keycode, keyrecord_t *record) {
  if (keycode == _K_S_SPL) {
    if (record->event.pressed) {
      if (get_mods() & MOD_BIT(KC_LSHIFT)) {
        unregister_code(KC_LSHIFT);
        tap_code16(G(KC_LBRC));
      } else {
        tap_code16(G(KC_RBRC));
      }
    }
    return false;
  } else {
    return true;
  }
}


// Function overrides.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool ret = true;

  bool is_gui_on = (get_mods() & MOD_BIT(KC_LGUI));
  bool is_alt_on = (get_mods() & MOD_BIT(KC_LALT));
  bool is_sft_on = (get_mods() & MOD_BIT(KC_LSHIFT));
  bool is_ctl_on = (get_mods() & MOD_BIT(KC_LCTL));


  // Switcher
  if (IS_LAYER_ON(_ACT)) {
    ret = switch_app(&_s_app_active, keycode, record);
  }


  // '.' / ':'
  if (keycode == _DOT_COL && record->event.pressed) {
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

  return ret;
}
