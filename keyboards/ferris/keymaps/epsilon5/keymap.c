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

    _REPEAT,
    _CAPS_WORD,

    _ACT_TAB,

    _CAPS_NUM_FAKE
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
#define _CAPS_NUM LT(_NUM, _CAPS_NUM_FAKE)

// ACT keys
#define _LOCK G(C(KC_Q))
#define _CTL_ESC CTL_T(KC_ESC)
#define _UNDO G(KC_Z)
#define _REDO S(G(KC_Z))
#define _COPY G(KC_C)
#define _PASTE G(KC_V)
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
  _E_ARST_MOD,
  COMBO_COUNT
};
uint16_t COMBO_LEN = COMBO_COUNT;


//       A,       R,       S,       T
// KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT
const uint16_t PROGMEM   ar_mod_combo[] = {_A, _R, COMBO_END};
const uint16_t PROGMEM   as_mod_combo[] = {_A, _S, COMBO_END};
const uint16_t PROGMEM   at_mod_combo[] = {_A, _T, COMBO_END};
const uint16_t PROGMEM   rs_mod_combo[] = {_R, _S, COMBO_END};
const uint16_t PROGMEM   rt_mod_combo[] = {_R, _T, COMBO_END};
const uint16_t PROGMEM   st_mod_combo[] = {_S, _T, COMBO_END};
const uint16_t PROGMEM  ars_mod_combo[] = {_A, _R, _S, COMBO_END};
const uint16_t PROGMEM  art_mod_combo[] = {_A, _R, _T, COMBO_END};
const uint16_t PROGMEM  ast_mod_combo[] = {_A, _S, _T, COMBO_END};
const uint16_t PROGMEM  rst_mod_combo[] = {_R, _S, _T, COMBO_END};
const uint16_t PROGMEM arst_mod_combo[] = {_A, _R, _S, _T, COMBO_END};


combo_t key_combos[] = {
  [_E_AR_MOD]   = COMBO(ar_mod_combo,   OSM(MOD_LCTL | MOD_LALT)),
  [_E_AS_MOD]   = COMBO(as_mod_combo,   OSM(MOD_LCTL | MOD_LGUI)),
  [_E_AT_MOD]   = COMBO(at_mod_combo,   OSM(MOD_LCTL | MOD_LSFT)),
  [_E_RS_MOD]   = COMBO(rs_mod_combo,   OSM(MOD_LALT | MOD_LGUI)),
  [_E_RT_MOD]   = COMBO(rt_mod_combo,   OSM(MOD_LALT | MOD_LSFT)),
  [_E_ST_MOD]   = COMBO(st_mod_combo,   OSM(MOD_LGUI | MOD_LSFT)),
  [_E_ARS_MOD]  = COMBO(ars_mod_combo,  OSM(MOD_LCTL | MOD_LALT | MOD_LGUI)),
  [_E_ART_MOD]  = COMBO(art_mod_combo,  OSM(MOD_LCTL | MOD_LALT | MOD_LSFT)),
  [_E_AST_MOD]  = COMBO(ast_mod_combo,  OSM(MOD_LCTL | MOD_LGUI | MOD_LSFT)),
  [_E_RST_MOD]  = COMBO(rst_mod_combo,  OSM(MOD_LALT | MOD_LGUI | MOD_LSFT)),
  [_E_ARST_MOD] = COMBO(arst_mod_combo, OSM(MOD_LCTL | MOD_LALT | MOD_LGUI | MOD_LSFT)),
};

#endif



// Keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_ABC] = LAYOUT(
        KC_Q,    KC_W,    KC_F,     KC_P,     KC_G,                          KC_J,     KC_L,     KC_U,     KC_Y,  KC_QUOT,
          _A,      _R,      _S,       _T,     KC_D,                          KC_H,       _N,       _E,       _I,       _O,
        KC_Z,    KC_X,    KC_C,     KC_V,     KC_B,                          KC_K,     KC_M, KC_COMMA, KC_DOT, KC_EXLM,
                                          _ACT_SPC, _CAPS_NUM,  _SYM_ENT, _FUN_BSP
  ),

  [_SYM] = LAYOUT(
        KC_GRV,   KC_AT, KC_LBRC,  KC_RBRC,  KC_HASH,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
       KC_AMPR, KC_PIPE, KC_LPRN,  KC_RPRN,  KC_PERC,                   XXXXXXX, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT,
       KC_BSLS,  KC_DLR, KC_LCBR,  KC_RCBR,  KC_TILD,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                    _ACT_LT, _NUM_GT,    _______, XXXXXXX
  ),

  [_NUM] = LAYOUT(
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    KC_PLUS,    KC_1,    KC_2,    KC_3, KC_CIRC,
      KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, XXXXXXX,                    KC_MINS,    KC_4,    KC_5,    KC_6,    KC_0,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    KC_ASTR,    KC_7,    KC_8,    KC_9, KC_SLSH,
                                          XXXXXXX, _______,   KC_EQL, KC_UNDS
  ),

  [_ACT] = LAYOUT(
      _LOCK,   KC_TAB,    _BACK,    _FRWD, XXXXXXX,                       KC_PGUP, A(KC_LEFT),   KC_UP, A(KC_RIGHT), G(KC_UP),
   _CTL_ESC, _APP_SWP, _WIN_SWP, _TAB_SWP,  KC_CLR,                    G(KC_LEFT),    KC_LEFT, KC_DOWN,    KC_RIGHT, G(KC_RIGHT),
    XXXXXXX,     _CUT,    _COPY,   _PASTE, XXXXXXX,                       KC_PGDN,      _UNDO, _REPEAT,       _REDO, G(KC_DOWN),
                                            _______, XXXXXXX,  KC_KP_ENTER, KC_BSPC
  ),

  [_FUN] = LAYOUT(
      KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,                   XXXXXXX, KC_MPRV,  KC_MPLY,  KC_MNXT, KC_EJCT,
      KC_F6,  KC_F7,  KC_F8,  KC_F9, KC_F10,                HYPR(KC_H), _OS_SFT,  _OS_GUI,  _OS_ALT, _OS_CTL,
     KC_F11, KC_F12, KC_F13, KC_F14, KC_F15,                   XXXXXXX,   _MUTE,    _VOLD,    _VOLU, XXXXXXX,
                                     KC_SPC,_SYM_WIN, XXXXXXX, XXXXXXX
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

const key_override_t **key_overrides = (const key_override_t *[]) {
  &scln_key_override,
  &coln_key_override,
  &ques_key_override,
  &gdel1_key_override,
  &del1_key_override,
  &gdel2_key_override,
  &del2_key_override,
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

  if (keycode == _CAPS_WORD && record->event.pressed) {
    if (caps_word_on) {
      caps_word_disable();
      return false;
    } else {
      caps_word_enable();
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


  // _CAPS_NUM
  else if (keycode == _CAPS_NUM) {
    if (record->event.pressed && record->tap.count > 0) {
      // Enable word caps on second tap.
      if (get_oneshot_mods() & MOD_MASK_SHIFT) {
        clear_oneshot_mods();
        caps_word_enable();
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