#include QMK_KEYBOARD_H


// -- Layers and keys ---

enum layer_names {
  _L_ABC,
  _L_NAV,
  _L_SYM,
  _L_ALT
};

enum keycodes {
    // Custom oneshot mod implementation with no timers.
    OS_SHFT = SAFE_RANGE,

    _K_STAB,  // Custom S(KC_TAB).
    _K_GDEL,  // Custom G(KC_DEL).
    _K_LT,    // Custom KC_LT.
    _K_GT,    // Custom KC_GT.
    _K_CIR,   // Custom KC_CIRC.

    _K_DOT,
    _K_COMM,
    _K_EXLM,

    _K_S_APP,  // Switch to next app (cmd-tab)
    _K_S_SPL,  // Switch to next split (cmd-])
};

#define _K_S_WIN G(KC_GRAVE)
#define _K_S_TAB C(KC_TAB)

#define _K_WD_L A(KC_LEFT)
#define _K_WD_R A(KC_RIGHT)
#define _K_LN_L G(KC_LEFT)
#define _K_LN_R G(KC_RIGHT)
#define _K_FL_T G(KC_UP)
#define _K_FL_B G(KC_DOWN)
#define _K_PG_U A(KC_UP)
#define _K_PG_D A(KC_DOWN)


// ConTrol ALt (Control in shortcuts, alt when held alone).
#define _K_CTAL ALT_T(KC_DEL)

#define _K_CMD LGUI_T(KC_TAB)
#define _K_SYM LT(_L_SYM, KC_ENT)
#define _K_NAV LT(_L_NAV, KC_SPC)
#define _K_SFT SFT_T(KC_ESC)
#define _K_ALT ALT_T(KC_BSPC)

// NAV mod-taps.
#define _K_NCMD LGUI_T(_K_STAB)
#define _K_NCTL LCTL_T(_K_GDEL)

// SYM mod-taps.
#define _K_SALT LALT_T(_K_LT)
#define _K_SCMD LGUI_T(_K_GT)
#define _K_SCIR SFT_T(_K_CIR)


#define _K_OSFT OSM(MOD_LSFT)
#define _K_OCTL OSM(MOD_LCTL)
#define _K_OALT OSM(MOD_LALT)
#define _K_OGUI OSM(MOD_LGUI)

#define _K_LOCK G(C(KC_Q))
#define _K_VOLU KC__VOLUP
#define _K_VOLD KC__VOLDOWN
#define _K_MUTE KC__MUTE

// Alt symbols
#define _K_AGRV A(KC_GRV)
#define _K_ATLD A(KC_N)
#define _K_ACNT A(KC_E)
#define _K_ACRC A(KC_I)

#define _K_DGRE S(A(KC_8))
#define _K_SCTN A(KC_6)
#define _K_PMIL S(A(KC_R))
#define _K_EURO S(A(KC_2))
#define _K_PND A(KC_3)
#define _K_CDL A(KC_C)
#define _K_QT_O A(KC_BSLS)
#define _K_QT_C S(A(KC_BSLS))
#define _K_PLMN S(A(KC_EQL))
#define _K_NEQL A(KC_EQL)
#define _K_NDSH A(KC_MINS)
#define _K_MDSH S(A(KC_MINS))
#define _K_BLLT A(KC_8)
#define _K_ELPS A(KC_SCLN)
#define _K_DIVD A(KC_SLSH)
#define _K_APRX A(KC_X)
#define _K_INFT A(KC_5)
#define _K_LTE A(KC_COMM)
#define _K_GTE A(KC_DOT)
#define _K_SL_O A(KC_O)

#define _K_EMOJ G(C(KC_SPC))
#define _K_DLWD A(KC_BSPC)


// --- COMBOS ---

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
// KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL

// A + R
const uint16_t PROGMEM   ar_mod_combo[] = {_K_CMD, KC_A, KC_R, COMBO_END};

// A + S
const uint16_t PROGMEM   as_mod_combo[] = {_K_CMD, KC_A, KC_S, COMBO_END};

// A + T
const uint16_t PROGMEM   at_mod_combo[] = {_K_CMD, KC_A, KC_T, COMBO_END};

// R + S
const uint16_t PROGMEM   rs_mod_combo[] = {_K_CMD, KC_R, KC_S, COMBO_END};

// R + T
const uint16_t PROGMEM   rt_mod_combo[] = {_K_CMD, KC_R, KC_T, COMBO_END};

// S + T
const uint16_t PROGMEM   st_mod_combo[] = {_K_CMD, KC_S, KC_T, COMBO_END};

// A + R + S 
const uint16_t PROGMEM  ars_mod_combo[] = {_K_CMD, KC_A, KC_R, KC_S, COMBO_END};

// A + R + T 
const uint16_t PROGMEM  art_mod_combo[] = {_K_CMD, KC_A, KC_R, KC_T, COMBO_END};

// A + S + T 
const uint16_t PROGMEM  ast_mod_combo[] = {_K_CMD, KC_A, KC_S, KC_T, COMBO_END};

// R + S + T 
const uint16_t PROGMEM  rst_mod_combo[] = {_K_CMD, KC_R, KC_S, KC_T, COMBO_END};

// A + R + S + T 
const uint16_t PROGMEM arst_mod_combo[] = {_K_CMD, KC_A, KC_R, KC_S, KC_T, COMBO_END};


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
      set_oneshot_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_LGUI));
    }
    break;

  case _E_AS_MOD:
    if (pressed) {
      set_oneshot_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_LALT));
    }
    break;

  case _E_AT_MOD:
    if (pressed) {
      set_oneshot_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_LCTL));
    }
    break;

  case _E_RS_MOD:
    if (pressed) {
      set_oneshot_mods(MOD_BIT(KC_LGUI) | MOD_BIT(KC_LALT));
    }
    break;

  case _E_RT_MOD:
    if (pressed) {
      set_oneshot_mods(MOD_BIT(KC_LGUI) | MOD_BIT(KC_LCTL));
    }
    break;

  case _E_ST_MOD:
    if (pressed) {
      set_oneshot_mods(MOD_BIT(KC_LALT) | MOD_BIT(KC_LCTL));
    }
    break;

  case _E_ARS_MOD:
    if (pressed) {
      set_oneshot_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_LGUI) | MOD_BIT(KC_LALT));
    }
    break;

  case _E_ART_MOD:
    if (pressed) {
      set_oneshot_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_LGUI) | MOD_BIT(KC_LCTL));
    }
    break;

  case _E_AST_MOD:
    if (pressed) {
      set_oneshot_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_LALT) | MOD_BIT(KC_LCTL));
    }
    break;

  case _E_RST_MOD:
    if (pressed) {
      set_oneshot_mods(MOD_BIT(KC_LGUI) | MOD_BIT(KC_LALT) | MOD_BIT(KC_LCTL));
    }
    break;

  case _E_ARST_MOD:
    if (pressed) {
      set_oneshot_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_LGUI) | MOD_BIT(KC_LALT) | MOD_BIT(KC_LCTL));
    }
    break;
  }
}





// --- KEYMAP ---

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_L_ABC] = LAYOUT_gergoplex(
  //,--------------------------------------------.                    ,--------------------------------------------.
         KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_QUOT,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
         KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                         KC_H,    KC_N,    KC_E,    KC_I,    KC_O,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
         KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_K,    KC_M, _K_COMM,  _K_DOT, _K_EXLM,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                  _K_CTAL, _K_CMD,  _K_SFT,     _K_SYM,  _K_NAV,  _K_ALT
                             //`--------------------------'  `--------------------------'
  ),

  [_L_NAV] = LAYOUT_gergoplex(
  //,--------------------------------------------.                    ,--------------------------------------------.
      _K_LOCK,_K_S_SPL,_K_S_APP,_K_S_TAB,_K_S_WIN,                      XXXXXXX, _K_WD_L,   KC_UP, _K_WD_R, XXXXXXX,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      _K_OSFT, _K_OGUI, _K_OALT, _K_OCTL, _K_MUTE,                      _K_LN_L, KC_LEFT, KC_DOWN,KC_RIGHT, _K_LN_R,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _K_VOLD,                      XXXXXXX, _K_PG_D, _K_PG_U, _K_FL_T, _K_FL_B,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                 _K_NCTL, _K_NCMD, _______,    XXXXXXX, _______, XXXXXXX
                             //`--------------------------'  `--------------------------'
  ),

  [_L_SYM] = LAYOUT_gergoplex(
  //,--------------------------------------------.                    ,--------------------------------------------.
       KC_GRV,   KC_AT, KC_LBRC, KC_RBRC, KC_AMPR,                      KC_PLUS,    KC_7,    KC_8,    KC_9, _K_SCIR,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      KC_TILD, KC_PIPE, KC_LPRN, KC_RPRN, KC_PERC,                      KC_MINS,    KC_1,    KC_2,    KC_3,    KC_0,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      KC_BSLS,  KC_DLR, KC_LCBR, KC_RCBR, KC_HASH,                      KC_ASTR,    KC_4,    KC_5,    KC_6, KC_SLSH,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                 _K_SALT, _K_SCMD,  KC_EQL,    _______, XXXXXXX, XXXXXXX
                             //`--------------------------'  `--------------------------'
  ),

  [_L_ALT] = LAYOUT_gergoplex(
  //,--------------------------------------------.                    ,--------------------------------------------.
      _K_AGRV,  KC_ESC,_K_S_APP, _K_DGRE, _K_SCTN,                      _K_PLMN, _K_INFT, _K_LTE,   _K_GTE, _K_APRX,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      KC_LSFT,_K_S_WIN,_K_S_SPL,_K_S_TAB, _K_PMIL,                      _K_NEQL, _K_ATLD, _K_ACNT, _K_ACRC, _K_SL_O,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      _K_EURO,  _K_PND,  _K_CDL, _K_QT_O, _K_QT_C,                      _K_NDSH, _K_MDSH, _K_BLLT, _K_ELPS, _K_DIVD,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                 _______, XXXXXXX, XXXXXXX,    _______, _K_EMOJ, _K_DLWD
                             //`--------------------------'  `--------------------------'
  )
};



// --- Swapper ---

bool _s_app_active = false;

bool switch_app(bool *active, uint16_t keycode, keyrecord_t *record) {
    if (keycode == _K_S_APP) {
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
    } else if (keycode == _K_NAV && !record->event.pressed) {
        unregister_code(KC_LGUI);
        *active = false;
        return true;
    } else if (*active && (keycode == KC_ESC && record->event.pressed)) {
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



// --- Function overrides ---

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static bool k_ctal_interrupted = false;
  static bool k_ctal_pressed = false;

  bool ret = true;

  bool is_gui_on = (get_mods() & MOD_BIT(KC_LGUI));
  bool is_alt_on = (get_mods() & MOD_BIT(KC_LALT));
  bool is_sft_on = (get_mods() & MOD_BIT(KC_LSHIFT));
  bool is_ctl_on = (get_mods() & MOD_BIT(KC_LCTL));

  // Check if we are interrupting ALT.
  // If so, unregister alt and register ctl.
  // _K_ALT (i.e. bspc) does not alter alt.
  if (k_ctal_pressed && !k_ctal_interrupted && record->event.pressed && keycode != _K_CTAL && keycode != _K_ALT) {
    k_ctal_interrupted = true;
    if (is_alt_on) unregister_code(KC_LALT);
    if (!is_ctl_on) register_code(KC_LCTL);
  }

  // Process ALT layer actions.
  if (IS_LAYER_ON(_L_NAV)) {
    ret = switch_app(&_s_app_active, keycode, record);
    ret = switch_spl(keycode, record);
  }

  // Process keycodes.
  if (false) { }

  else if (keycode == _K_CTAL) {
    if(record->event.pressed) {
      k_ctal_pressed = true;

      // For non-basic _K_CTAL tap codes.
      // if (record->tap.count > 0) {
      //   // Custom tap action.
      //   tap_code16(S(KC_TAB));
      //   ret = false;
      // } else {
      //   // Allow QMK to set ALT naturally.
      //   ret = true;
      // }

      ret = true;
    } else { // released
      k_ctal_pressed = false;
      if (k_ctal_interrupted) {
        // We need to unregister CTL set on iterruption.
        if (is_ctl_on) unregister_code(KC_LCTL);
        k_ctal_interrupted = false;
        ret = true; // XXX should this be false? ALT was already unregistered on interruption.
      } else {
        // No need to do anything, ALT will be unregistered by QMK.
        ret = true;
      }
    }
  }

  // NAV: CMD S-TAB
  else if (keycode == _K_NCMD) {
    // S(KC_TAB)
    // FIXME: Repeat on second tap doesn't work.
    if (record->tap.count > 0) {
      if (record->event.pressed) {
        tap_code16(S(KC_TAB));
      }
      ret = false;
    }
  }


  // NAV: CTL G(DEL)
  else if (keycode == _K_NCTL) {
    // S(KC_TAB)
    // FIXME: Repeat on second tap doesn't work.
    if (record->tap.count > 0) {
      if (record->event.pressed) {
        tap_code16(C(KC_K));
      }
      ret = false;
    }
  }

  // NAV SP / UNDS
  else if (keycode == _K_NAV) {
    // S(KC_TAB)
    // FIXME: Repeat on second tap doesn't work.
    if (record->tap.count > 0) {
      if (record->event.pressed) {
        tap_code16(is_sft_on ? KC_UNDS : KC_SPC);
      }
      ret = false;
    }
  }

  // CMD GT
  else if (keycode == _K_SCMD) {
    // FIXME: Repeat on second tap doesn't work.
    if (record->tap.count > 0) {
      if (record->event.pressed) {
        tap_code16(KC_GT);
      }
      ret = false;
    }
  }

  // SFT CIRC
  else if (keycode == _K_SCIR) {
    // FIXME: Repeat on second tap doesn't work.
    if (record->tap.count > 0) {
      if (record->event.pressed) {
        tap_code16(KC_CIRC);
      }
      ret = false;
    }
  }

  // ALT LT
  else if (keycode == _K_SALT) {
    // FIXME: Repeat on second tap doesn't work.
    if (record->tap.count > 0) {
      if (record->event.pressed) {
        tap_code16(KC_LT);
      }
      ret = false;
    }
  }

  // '.' / ':'
  else if (keycode == _K_DOT && record->event.pressed) {
    if (is_sft_on) {
      tap_code16(KC_SCLN); // ':' because sft is on
    } else {
      tap_code(KC_DOT);
    }
    ret = false;
  }
  
  // ',' / ';'
  else if (keycode == _K_COMM && record->event.pressed) {
    if (is_sft_on) {
      unregister_code(KC_LSFT);
      tap_code16(KC_SCLN);
      register_code(KC_LSFT);
    } else {
      tap_code(KC_COMM);
    }
    ret = false;
  }

  // '!' / '?'
  else if (keycode == _K_EXLM && record->event.pressed) {
    // No mods
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


uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case _K_CTAL:
    // Easier alt.
    // S-TAB requires a more precise tap.
    return 150;
  default:
    return TAPPING_TERM;
  }
}

// --- Debugging ---

// void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  // debug_enable=true;
  // debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
// }