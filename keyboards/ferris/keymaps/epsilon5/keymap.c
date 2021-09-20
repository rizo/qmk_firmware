// TODO: Reduce tapping term for _APP_SWP

#include QMK_KEYBOARD_H


// Used to extract the basic tapping keycode from a dual-role key.
// Example: GET_TAP_KC(MT(MOD_RSFT, KC_E)) == KC_E
#define GET_TAP_KC(dual_role_key) dual_role_key & 0xFF


// FIXME: Doesn't work?
#define WITHOUT_MODS(...) \
  do { \
    const uint8_t _real_mods = get_mods(); \
    clear_mods(); \
    { __VA_ARGS__ } \
    set_mods(_real_mods); \
  } while (0)


uint16_t last_tap = KC_NO;
uint8_t last_modifier = 0;
uint8_t mods_state = 0;
uint8_t oneshot_mods_state = 0;


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
    
    _PIPE,
    _ARROW,
    _ARROW2,
    _USR_HOME_FAKE,

    _NUM_LPRN_FAKE,
    _NUM_RPRN_FAKE,

    _REPEAT,
    _CAPS_WORD,
    _INSERT,

    _ACT_TAB,

    _CAPS_NUM_FAKE,
    _MENU,

    _ACT_SPC
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
#define _F MT(MOD_LGUI | MOD_LCTL, KC_F)

#define _N SFT_T(KC_N)
#define _E GUI_T(KC_E)
#define _I ALT_T(KC_I)
#define _O CTL_T(KC_O)
#define _U MT(MOD_LGUI | MOD_LCTL, KC_U)
#else
#define _A KC_A
#define _R KC_R
#define _S KC_S
#define _T KC_T
#define _F KC_F

#define _N KC_N
#define _E KC_E
#define _I KC_I
#define _O KC_O
#define _U KC_U
#endif


// Thumb keys
#define _ACT_SPC  LT(_ACT, KC_SPC)
#define _NUM_TAB  LT(_NUM, KC_TAB)
#define _NUM_SPC  LT(_NUM, KC_SPC)
#define _SYM_ENT  LT(_SYM, KC_ENT)
#define _FUN_BSP  LT(_FUN, KC_BSPC)
#define _CAPS_NUM LT(_NUM, _CAPS_NUM_FAKE)
#define _SPC_NUM  LT(_NUM, KC_SPC)

// ACT keys
#define _LOCK G(C(KC_Q))
#define _CTL_ESC CTL_T(KC_ESC)
#define _UNDO G(KC_Z)
#define _REDO S(G(KC_Z))
#define _COPY G(KC_C)
#define _PASTE G(KC_V)
#define _PASTE2 S(A(G(KC_V)))
#define _CUT G(KC_X)
#define  _VOLU KC__VOLUP
#define  _VOLD KC__VOLDOWN
#define  _MUTE KC__MUTE
#define _BACK G(KC_LBRC)
#define _FRWD G(KC_RBRC)
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

// NUM & SYM keys
#define _ACT_LT LT(_ACT, KC_LT)
#define _NUM_GT LT(_NUM, KC_GT)
#define _INF A(KC_5)
#define _COPYR A(KC_G)
#define _GBP A(KC_3)
#define _EUR S(A(KC_2))
#define _TM A(KC_2)
#define _DGREE A(KC_0)
#define _SECTN A(KC_6)
#define _PLCRW A(KC_7)
#define _PLSMIN S(A(KC_EQL))
#define _ELLPSI A(KC_SCLN)
#define _CEDIL A(KC_C)
#define _BULLT A(KC_8)
#define _ENDSH A(KC_MINS)
#define _EMDSH S(A(KC_MINS))
#define _DIARS A(KC_U)
#define _QUATL A(KC_BSLS)
#define _QUATR S(A(KC_BSLS))
#define _NEQ A(KC_EQL)
#define _MUL S(A(KC_9))
#define _A_SPC RALT_T(KC_SPC)
#define _C_USHM CTL_T(_USR_HOME_FAKE)
#define _G_LPRN GUI_T(_NUM_LPRN_FAKE)
#define _S_RPRN SFT_T(_NUM_RPRN_FAKE)



// --- COMBOS ---
#ifdef _COMBOS_ENABLED
const uint16_t PROGMEM   _ar_combo[] = {_A, _R, COMBO_END};
const uint16_t PROGMEM   _rs_combo[] = {_R, _S, COMBO_END};
const uint16_t PROGMEM   _wf_combo[] = {KC_W, _F, COMBO_END};
const uint16_t PROGMEM   _fp_combo[] = {_F, KC_P, COMBO_END};
const uint16_t PROGMEM   _st_combo[] = {_S, _T, COMBO_END};
const uint16_t PROGMEM   _xc_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM   _ne_combo[] = {_N, _E, COMBO_END};

uint16_t COMBO_LEN = 7;
combo_t key_combos[] = {
  COMBO(_ar_combo,   G(KC_A)),
  COMBO(_rs_combo,   G(KC_S)),
  COMBO(_wf_combo,   G(KC_W)),
  COMBO(_st_combo,   G(KC_T)),
  COMBO(_fp_combo,   G(KC_F)),
  COMBO(_xc_combo,   G(KC_SLSH)),
  COMBO(_ne_combo,   G(KC_N)),
};


bool get_combo_must_tap(uint16_t index, combo_t *combo) {
  return true;
}

#endif



// Keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_ABC] = LAYOUT(
        KC_Q,    KC_W,      _F,     KC_P,     KC_G,                          KC_J,     KC_L,       _U,     KC_Y,  KC_QUOT,
          _A,      _R,      _S,       _T,     KC_D,                          KC_H,       _N,       _E,       _I,       _O,
        KC_Z,    KC_X,    KC_C,     KC_V,     KC_B,                          KC_K,     KC_M, KC_COMMA,    KC_DOT, KC_EXLM,
                                          _ACT_SPC, _NUM_TAB,  _SYM_ENT, _FUN_BSP
  ),

  [_SYM] = LAYOUT(
        KC_GRV,   KC_AT, KC_LBRC,  KC_RBRC,  KC_HASH,                   _PLSMIN,   _EMDSH,   _DIARS,   _QUATL,   _QUATR,
       KC_TILD, KC_PIPE, KC_LPRN,  KC_RPRN,  KC_PERC,                    _ENDSH, _FUN_SFT, _FUN_GUI, _FUN_ALT, _FUN_CTL,
       KC_BSLS,  KC_DLR, KC_LCBR,  KC_RCBR,  KC_AMPR,                      _MUL,   _BULLT,   _DGREE,  _ELLPSI,     _NEQ,
                                    _ACT_LT, _NUM_GT,    _______, XXXXXXX
),

  [_NUM] = LAYOUT(
       _TM,     _COPYR,  _ARROW, _ARROW2, _PLCRW,                    KC_PLUS,    KC_1,    KC_2,    KC_3, KC_CIRC,
      _C_USHM,  _A_SPC, _G_LPRN, _S_RPRN,   _INF,                    KC_MINS,    KC_4,    KC_5,    KC_6,    KC_0,
         _EUR,    _GBP,  _CEDIL,   _PIPE, _SECTN,                    KC_ASTR,    KC_7,    KC_8,    KC_9, KC_SLSH,
                                         XXXXXXX, _______,   KC_EQL, KC_UNDS
  ),

  [_ACT] = LAYOUT(
    KC_CAPS,   KC_TAB,    _UNDO,    _REDO, _INSERT,                       KC_PGUP, A(KC_LEFT),   KC_UP, A(KC_RIGHT), G(KC_UP),
   _CTL_ESC, _APP_SWP, _WIN_SWP, _TAB_SWP, _REPEAT,                    G(KC_LEFT),    KC_LEFT, KC_DOWN,    KC_RIGHT, G(KC_RIGHT),
     KC_CLR,     _CUT,    _COPY,   _PASTE, _PASTE2,                       KC_PGDN,      _BACK,   _MENU,       _FRWD, G(KC_DOWN),
                                            _______, XXXXXXX,  KC_KP_ENTER, KC_BSPC
  ),

  [_FUN] = LAYOUT(
    KC_POWER, KC_F1,  KC_F2, KC_F3, KC_F10,                    DM_REC1,   _MUTE,    _VOLD,    _VOLU, XXXXXXX,
      KC_ESC, KC_F4,  KC_F5, KC_F6, KC_F11,                    DM_RSTP, _OS_SFT,  _OS_GUI,  _OS_ALT, _OS_CTL,
       RESET, KC_F7,  KC_F8, KC_F9, KC_F12,                    DM_PLY1, KC_MPRV,  KC_MPLY,  KC_MNXT, XXXXXXX,
                                    KC_SPC, _SYM_WIN, XXXXXXX, XXXXXXX
  )
};



// KEY OVERRIDES


// S(KC_COMMA) -> KC_SCLN
const key_override_t scln_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_COMMA, KC_SCLN);

// S(KC_DOT) -> KC_COLN
const key_override_t coln_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_COLN);

// S(KC_EXLM) -> KC_QUES
const key_override_t ques_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_EXLM, KC_QUES);

// G(S(_FUN_BSP)) -> C(KC_K)
const key_override_t gdel1_key_override = _ko_make_strict(MOD_BIT(KC_LGUI) | MOD_BIT(KC_LSFT), _FUN_BSP, C(KC_K));

// S(_FUN_BSP) -> KC_DEL
const key_override_t del1_key_override = _ko_make_strict_negmods(MOD_BIT(KC_LSFT), _FUN_BSP, KC_DEL, MOD_BIT(KC_LGUI));

// G(S(KC_BSPC)) -> C(KC_K)
const key_override_t gdel2_key_override = _ko_make_strict(MOD_BIT(KC_LGUI) | MOD_BIT(KC_LSFT), KC_BSPC, C(KC_K));

// S(KC_BSPC) -> KC_DEL
const key_override_t del2_key_override = _ko_make_strict_negmods(MOD_BIT(KC_LSFT), KC_BSPC, KC_DEL, MOD_BIT(KC_LGUI));

// A(_ACT_SPC) -> KC_BSPC
const key_override_t bsp1_key_override = _ko_make_strict(MOD_MASK_ALT, _ACT_SPC, KC_BSPC);
const key_override_t bsp2_key_override = _ko_make_strict(MOD_BIT(KC_RALT), KC_UNDS, KC_BSPC);

const key_override_t **key_overrides = (const key_override_t *[]) {
  &scln_key_override,
  &coln_key_override,
  &ques_key_override,
  &gdel1_key_override,
  &del1_key_override,
  &gdel2_key_override,
  &del2_key_override,
  &bsp1_key_override,
  &bsp2_key_override,
  NULL
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
          unregister_mods(MOD_BIT(KC_LCTL));
          tap_code16(S(KC_TAB));
          register_mods(MOD_BIT(KC_LCTL));
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
  else if (*active && ((keycode == KC_ESC || keycode == KC_ENT || keycode == KC_KP_ENTER || keycode == KC_SPC) && record->event.pressed)) {
    tap_code(keycode);
    unregister_code(KC_LGUI);
    *active = false;
    return false;
  } else {
    return true;
  }
}




/*
 * REPEAT
 */

void process_repeat_key(uint16_t keycode, const keyrecord_t *record) {
    if (keycode != _REPEAT) {
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
 * _INSERT
 */

bool insert_on = false;


bool process_insert(uint16_t keycode, const keyrecord_t *record) {
  if (insert_on && record->event.pressed) {
    switch (keycode) {
      case KC_A ... KC_Z:
      case KC_1 ... KC_0:
      case KC_UNDS:
      case KC_MINS:
        tap_code(KC_DEL);
        if (record->event.pressed) {
          register_code(keycode);
        } else {
          unregister_code(keycode);
        }
        return false;
      default:
        insert_on = false;
        return true;
    }
  } else {
    return true;
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

  // Switcher
  ret = switch_app(&_s_app_active, keycode, record);

  // ret = process_insert(keycode, record);

  if (keycode == _CAPS_WORD && record->event.pressed) {
    if (caps_word_on) {
      caps_word_disable();
      return false;
    } else {
      caps_word_enable();
      return false;
    }
  }

  else if (keycode == _INSERT && record->event.pressed) {
    if (insert_on) {
      insert_on = false;
      return false;
    } else {
      insert_on = true;
      return false;
    }
  }

  // _WIN_SWP -> G(KC_GRV)
  // C(_WIN_SWP) -> S(G(KC_GRV))
  else if (keycode == _WIN_SWP && record->event.pressed && record->tap.count > 0) {
    if (mods_state & MOD_BIT(KC_LCTL)) {
      unregister_mods(MOD_BIT(KC_LCTL));
      tap_code16(S(G(KC_GRV)));
      register_mods(MOD_BIT(KC_LCTL));
    } else {
      tap_code16(G(KC_GRV));
    }
    ret = false;
  }

  // C(KC_TAB) -> S(KC_TAB)
  else if (keycode == KC_TAB) {
    if (record->event.pressed) {
      if (mods_state & MOD_BIT(KC_LCTL)) {
        unregister_mods(MOD_BIT(KC_LCTL));
        register_mods(MOD_BIT(KC_LSFT));
      }
    } else {
      if (mods_state & MOD_BIT(KC_LSFT)) {
        unregister_mods(MOD_BIT(KC_LSFT));
        register_mods(MOD_BIT(KC_LCTL));
      }
    }
    ret = true;
  }

  // ACT: TAB SWP
  else if (keycode == _TAB_SWP && record->event.pressed && record->tap.count > 0) {
    if (mods_state & MOD_BIT(KC_LCTL)) {
      tap_code16(S(KC_TAB));
    } else {
      tap_code16(C(KC_TAB));
    }
    ret = false;
  }

  // _ACT_LT -> KC_LT
  else if (keycode == _ACT_LT && record->event.pressed && record->tap.count > 0) {
    tap_code16(S(KC_COMM));
    ret = false;
  }

  // _NUM_GT -> KC_GT
  else if (keycode == _NUM_GT && record->event.pressed && record->tap.count > 0) {
    tap_code16(S(KC_DOT));
    ret = false;
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

  // NUM: LPRN
  else if (keycode == _G_LPRN && record->event.pressed && record->tap.count > 0) {
    tap_code16(KC_LPRN);
    ret = false;
  }

  // NUM: RPRN
  else if (keycode == _S_RPRN && record->event.pressed && record->tap.count > 0) {
    tap_code16(KC_RPRN);
    ret = false;
  }

  // ACT: MENU
  else if (keycode == _MENU && record->event.pressed) {
    tap_code16(C(KC_F2));
    tap_code(KC_F);
    tap_code(KC_DOWN);
    ret = false;
  }

  // SYM: PIPE
  else if (keycode == _PIPE && record->event.pressed) {
    tap_code16(S(KC_BSLS));
    tap_code16(S(KC_DOT));
    ret = false;
  }
  
  // _ARROW
  else if (keycode == _ARROW && record->event.pressed) {
    tap_code(KC_MINS);
    tap_code16(S(KC_DOT));
    ret = false;
  }

  // _ARROW2
  else if (keycode == _ARROW2 && record->event.pressed) {
    tap_code(KC_EQL);
    tap_code16(S(KC_DOT));
    ret = false;
  }

  // _C_USHM
  else if (keycode == _C_USHM && record->event.pressed) {
    tap_code16(KC_TILD);
    tap_code(KC_SLSH);
    ret = false;
  }

  // _CAPS_NUM
  else if (keycode == _CAPS_NUM) {
    if (record->event.pressed && record->tap.count > 0) {
      // Enable word caps on second tap.
      if (get_oneshot_mods() & MOD_MASK_SHIFT) {
        clear_oneshot_mods();
        caps_word_enable();
        ret = false;
      } else if (mods_state & MOD_BIT(KC_LALT)) {
        unregister_mods(MOD_BIT(KC_LALT));
        tap_code(KC_ENT);
        register_mods(MOD_BIT(KC_LALT));
        ret = false;
      } else {
        set_oneshot_mods(MOD_BIT(KC_LSFT));
        ret = false;
      }
    }
  }
  
  process_repeat_key(keycode, record);

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