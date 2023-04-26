// TODO: Reduce tapping term for APP_SWP

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
  _FUN,
  _CUR,
};

// Custom keys.
enum keycodes {
    _COM_SCL = SAFE_RANGE,
    _DOT_COL,
    _EXC_QST,

    _UNREDO,
    _SEL,

    _SYM_LT_FAKE,
    _SYM_GT_FAKE,

    _PIPE,
    _ARROW,
    _ARROW2,

    FUN_C_FAKE,
    FUN_A_FAKE,
    FUN_G_FAKE,
    FUN_S_FAKE,

    SYM_C_FAKE,
    SYM_A_FAKE,
    SYM_G_FAKE,
    SYM_S_FAKE,

    REPEAT,
    _CAPS_WORD,
    INSERT,

    _ACT_TAB,

    ACT_GUI_FAKE,
    _MENU,

    _RPT,
    RSTMOD,

    ACT_SPC,
    _CUR_BTN2_FAKE,
    _LT_GT,
};


// ABC: Home row mods
#ifdef _ENABLE_HOME_MODS
#define _A LCTL_T(KC_A)
#define _R LALT_T(KC_R)
#define _S LGUI_T(KC_S)
#define _T LSFT_T(KC_T)
#define _F MT(MOD_LGUI | MOD_LCTL, KC_F)

#define _N RSFT_T(KC_N)
#define _E RGUI_T(KC_E)
#define _I RALT_T(KC_I)
#define _O RCTL_T(KC_O)
#define _U MT(MOD_RGUI | MOD_RCTL, KC_U)
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

#define _Z HYPR_T(KC_Z)
#define _CLR HYPR_T(KC_CLR)

// One-shot mods
#define OSCTL OSM(MOD_BIT(KC_LCTL))
#define OSALT OSM(MOD_BIT(KC_LALT))
#define OSGUI OSM(MOD_BIT(KC_LGUI))
#define OSSFT OSM(MOD_BIT(KC_LSFT))


// Thumb keys
#define ACT_SPC LT(_ACT, KC_SPC)
#define SFT_SPC MT(MOD_LSFT, KC_SPC)
#define SYM_ENT LT(_SYM, KC_ENT)
#define FUN_BSP LT(_FUN, KC_BSPC)


// ACT keys
#define UNDO G(KC_Z)
#define REDO S(G(KC_Z))
#define COPY G(KC_C)
#define PASTE G(KC_V)
#define PASTE2 S(A(G(KC_V)))
#define CUT G(KC_X)
#define VOLU KC__VOLUP
#define VOLD KC__VOLDOWN
#define MUTE KC__MUTE
#define BACK G(KC_LBRC)
#define FRWD G(KC_RBRC)
#define WORD_L A(KC_LEFT)
#define WORD_R A(KC_RIGHT)
#define STAB S(KC_TAB)


// FUN keys
#define FUN_S SFT_T(FUN_S_FAKE)
#define FUN_G GUI_T(FUN_G_FAKE)
#define FUN_A ALT_T(FUN_A_FAKE)
#define FUN_C CTL_T(FUN_C_FAKE)

// SYM keys
#define SYM_S SFT_T(SYM_S_FAKE)
#define SYM_G GUI_T(SYM_G_FAKE)
#define SYM_A ALT_T(SYM_A_FAKE)
#define SYM_C CTL_T(SYM_C_FAKE)

// Dead accent keys
#define DTIL A(KC_N)
#define ACUT A(KC_E)
#define DCIR A(KC_I)
#define DGRV A(KC_GRV)

#define _ACT_LT LT(_ACT, KC_LT)
#define _NUM_GT LT(_NUM, KC_GT)
#define _INF A(KC_5)
#define COPYR A(KC_G)
#define _GBP A(KC_3)
#define _EUR S(A(KC_2))
#define _SQRT A(KC_V)
#define _TM A(KC_2)
#define _DGREE A(KC_0)
#define _SECTN A(KC_6)
#define _PLCRW A(KC_7)
#define _PLSMIN S(A(KC_EQL))
#define _ELLPSI A(KC_SCLN)
#define CEDIL A(KC_C)
#define _BULLT A(KC_8)
#define _ENDSH A(KC_MINS)
#define _EMDSH S(A(KC_MINS))
#define _DIARS A(KC_U)
#define _QUATL A(KC_BSLS)
#define _QUATR S(A(KC_BSLS))
#define _NEQ A(KC_EQL)
#define _MUL S(A(KC_9))
#define _DIV A(KC_SLSH)



// --- COMBOS ---
#ifdef _COMBOS_ENABLED
const uint16_t PROGMEM ar_combo[] = {_A, _R, COMBO_END};
const uint16_t PROGMEM as_combo[] = {_A, _S, COMBO_END};
const uint16_t PROGMEM at_combo[] = {_A, _T, COMBO_END};
const uint16_t PROGMEM rs_combo[] = {_R, _S, COMBO_END};
const uint16_t PROGMEM rt_combo[] = {_R, _T, COMBO_END};
const uint16_t PROGMEM st_combo[] = {_S, _T, COMBO_END};
const uint16_t PROGMEM ars_combo[] = {_A, _R, _S, COMBO_END};
const uint16_t PROGMEM rst_combo[] = {_R, _S, _T, COMBO_END};
const uint16_t PROGMEM arst_combo[] = {_A, _R, _S, _T, COMBO_END};

uint16_t COMBO_LEN = 9;
combo_t key_combos[] = {
  COMBO(ar_combo, OSM(MOD_LCTL | MOD_LALT)),
  COMBO(as_combo, OSM(MOD_LCTL | MOD_LGUI)),
  COMBO(at_combo, OSM(MOD_LCTL | MOD_LSFT)),
  COMBO(rs_combo, OSM(MOD_LALT | MOD_LGUI)),
  COMBO(rt_combo, OSM(MOD_LALT | MOD_LSFT)),
  COMBO(st_combo, OSM(MOD_LGUI | MOD_LSFT)),
  COMBO(ars_combo, OSM(MOD_LCTL | MOD_LALT | MOD_LGUI)),
  COMBO(rst_combo, OSM(MOD_LALT | MOD_LGUI | MOD_LSFT)),
  COMBO(arst_combo, OSM(MOD_LCTL | MOD_LALT | MOD_LGUI | MOD_LSFT)),
};



bool get_combo_must_tap(uint16_t index, combo_t *combo) {
  return true;
}
#endif // COMBOS


// Keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_ABC] = LAYOUT(
       KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                      KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT,
       KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                      KC_H,    KC_N,    KC_E,    KC_I,    KC_O,
       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_EXLM,
                                        ACT_SPC, KC_LSFT,    SYM_ENT, FUN_BSP
  ),

  [_ACT] = LAYOUT(
     RSTMOD,  KC_ESC,    BACK,    FRWD,  INSERT,                      KC_PGUP, KC_DEL,  KC_UP,   KC_BSPC, KC_HOME,
      OSCTL,   OSALT,   OSGUI,   OSSFT,  REPEAT,                      KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,
       UNDO,     CUT,    COPY,   PASTE,    REDO,                      XXXXXXX, STAB,    KC_ESC,  KC_TAB,  XXXXXXX,
                                        _______, XXXXXXX,    KC_PENT, KC_BSPC
  ),

  [_SYM] = LAYOUT(
     KC_GRV,    KC_1,    KC_2,    KC_3,  KC_EQL,                      KC_ASTR, KC_LCBR, KC_DLR,  KC_RCBR, KC_HASH,
       KC_0,    KC_4,    KC_5,    KC_6, KC_MINS,                      KC_PLUS, SYM_S,   SYM_G,   SYM_A,   SYM_C,
    KC_BSLS,    KC_7,    KC_8,    KC_9, KC_SLSH,                      KC_AMPR, KC_LT,   KC_PIPE, KC_GT,   KC_CIRC,
                                        KC_LBRC, KC_RBRC,    _______, XXXXXXX
  ),

  [_FUN] = LAYOUT(
    XXXXXXX,   KC_F1,   KC_F2,   KC_F3,  KC_F10,                      DM_REC1, MUTE,    VOLD,    VOLU,   XXXXXXX,
     KC_PWR,   KC_F4,   KC_F5,   KC_F6,  KC_F11,                      DM_RSTP, FUN_S,   FUN_G,   FUN_A,   FUN_C,
      RESET,   KC_F7,   KC_F8,   KC_F9,  KC_F12,                      DM_PLY1, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX,
                                         KC_SPC, XXXXXXX,    XXXXXXX, _______
  )
};


// KEY OVERRIDES

// S(FUN_BSP) -> KC_UNDS
const key_override_t unds_key_override = ko_make_basic(MOD_MASK_SHIFT, FUN_BSP, KC_UNDS);

// S(FUN_BSP) -> KC_AT
const key_override_t at_key_override = ko_make_basic(MOD_MASK_SHIFT, SYM_ENT, KC_AT);

// S(KC_COMMA) -> KC_SCLN
const key_override_t scln_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_COMMA, KC_SCLN);

// S(KC_DOT) -> KC_COLN
const key_override_t coln_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_COLN);

// S(KC_EXLM) -> KC_QUES
const key_override_t ques_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_EXLM, KC_QUES);

// S(KC_BSPC) -> KC_DEL
const key_override_t sbsp_key_override = _ko_make_strict_negmods(MOD_MASK_SHIFT, KC_BSPC, KC_DEL, MOD_BIT(KC_LGUI));

// G(S(KC_BSPC)) -> C(KC_K)
const key_override_t gsbsp_key_override = _ko_make_strict(MOD_BIT(KC_LGUI) | MOD_MASK_SHIFT, KC_BSPC, C(KC_K));

const key_override_t **key_overrides = (const key_override_t *[]) {
  &unds_key_override,
  &at_key_override,
  &scln_key_override,
  &coln_key_override,
  &ques_key_override,
  &sbsp_key_override,
  &gsbsp_key_override,
  NULL
};


// -- REPEAT ---

void processrepeat_key(uint16_t keycode, const keyrecord_t *record) {
    if (keycode != REPEAT) {
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


// INSERT

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



// CAPS_WORD

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

  ret = process_insert(keycode, record);

  if (keycode == _CAPS_WORD && record->event.pressed) {
    if (caps_word_on) {
      caps_word_disable();
      return false;
    } else {
      caps_word_enable();
      return false;
    }
  }

  else if (keycode == _SEL && record->event.pressed) {
    if (get_mods() & MOD_BIT(KC_LALT)) {
      unregister_mods(MOD_BIT(KC_LALT));
      tap_code16(G(KC_LEFT));
      tap_code16(S(G(KC_RIGHT)));
      register_mods(MOD_BIT(KC_LALT));
    }
    else if (get_mods() & MOD_BIT(KC_LGUI)) {
      tap_code16(G(KC_A));
    } else {
      tap_code16(A(KC_LEFT));
      tap_code16(S(A(KC_RIGHT)));
    }
  }

  // RSTMOD
  else if (keycode == RSTMOD && record->event.pressed) {
    clear_oneshot_mods();
    ret = false;
  }

  else if (keycode == INSERT && record->event.pressed) {
    if (insert_on) {
      insert_on = false;
      return false;
    } else {
      insert_on = true;
      return false;
    }
  }

  // else if (keycode == ACT_GUI && record->event.pressed && record->tap.count > 0) {
  //   clear_oneshot_mods();
  //   ret = false;
  // }

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

  // FUN_S: ã
  else if (keycode == FUN_S && record->event.pressed && record->tap.count > 0) {
    tap_code16(DTIL);
    layer_off(_NUM);
    ret = false;
  }

  // FUN_G: é
  else if (keycode == FUN_G && record->event.pressed && record->tap.count > 0) {
    tap_code16(ACUT);
    layer_off(_NUM);
    ret = false;
  }

  // FUN_A: ô
  else if (keycode == FUN_A && record->event.pressed && record->tap.count > 0) {
    tap_code16(DCIR);
    layer_off(_NUM);
    ret = false;
  }

  // FUN_C: à
  else if (keycode == FUN_C && record->event.pressed && record->tap.count > 0) {
    tap_code16(DGRV);
    layer_off(_NUM);
    ret = false;
  }

  // SYM_C: ~
  else if (keycode == SYM_C && record->event.pressed && record->tap.count > 0) {
    tap_code16(KC_TILD);
    ret = false;
  }

  // SYM_A: )
  else if (keycode == SYM_A && record->event.pressed && record->tap.count > 0) {
    tap_code16(KC_RPRN);
    ret = false;
  }

  // SYM_G: %
  else if (keycode == SYM_G && record->event.pressed && record->tap.count > 0) {
    tap_code16(KC_PERC);
    ret = false;
  }

  // SYM_S: (
  else if (keycode == SYM_S && record->event.pressed && record->tap.count > 0) {
    tap_code16(KC_LPRN);
    ret = false;
  }

  processrepeat_key(keycode, record);

  return ret;
}


// uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
//   switch (keycode) {
//     case _F_SFT:
//       return TAPPING_TERM + 100;
//     case SYM_ENT:
//       return TAPPING_TERM - 25;
//     default:
//       return TAPPING_TERM;
//   }
// }


// bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
//   switch (keycode) {
//     case _FUN_SAB:
//     case ACT_BSP:
//     case SYM_ENT:
//     case ACT_SPC:
//       return false;

//     default:
//       return true;
//   }
// }

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        default:
            return true;
    }
}
