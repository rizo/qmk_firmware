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

    WIN_SWP_FAKE,
    APP_SWP_FAKE,
    TAB_SWP_FAKE,

    SFT_A_N_FAKE,
    GUI_A_E_FAKE,
    _ALT_FAKE_A_I,
    CTL_A_GR_FAKE,

    _F_SFT_FAKE,
    _F_GUI_FAKE,
    _F_ALT_FAKE,
    _F_CTL_FAKE,

    _SYM_LT_FAKE,
    _SYM_GT_FAKE,

    _PIPE,
    _ARROW,
    _ARROW2,

    NUM_A_FAKE,
    NUM_R_FAKE,
    NUM_S_FAKE,
    NUM_T_FAKE,

    REPEAT,
    _CAPS_WORD,
    INSERT,

    _ACT_TAB,

    NUM_SFT_FAKE,
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
#define ACT_SPC  LT(_ACT, KC_SPC)
#define _NUM_TAB  LT(_NUM, KC_TAB)
#define _NUM_SPC  LT(_NUM, KC_SPC)
#define SYM_ENT  LT(_SYM, KC_ENT)
#define ACT_BSP  LT(_ACT, KC_BSPC)
#define NUM_SFT LT(_NUM, NUM_SFT_FAKE)
#define _SPC_NUM  LT(_NUM, KC_SPC)

// ACT keys
#define _LOCK G(C(KC_Q))
#define _CTL_ESC CTL_T(KC_ESC)
#define UNDO G(KC_Z)
#define REDO S(G(KC_Z))
#define COPY G(KC_C)
#define PASTE G(KC_V)
#define PASTE2 S(A(G(KC_V)))
#define CUT G(KC_X)
#define  _VOLU KC__VOLUP
#define  _VOLD KC__VOLDOWN
#define  _MUTE KC__MUTE
#define BACK G(KC_LBRC)
#define FRWD G(KC_RBRC)
#define WORD_L A(KC_LEFT)
#define WORD_R A(KC_RIGHT)
#define _SYM_WIN C(G(KC_SPC))
#define _SPC_R C(KC_RIGHT)
#define _MOUSE TG(_CUR)

#define SFT_TAB S(KC_TAB)


#define WIN_SWP GUI_T(WIN_SWP_FAKE)
#define APP_SWP ALT_T(APP_SWP_FAKE)
#define _SPL_SWP G(A(KC_TAB))
#define TAB_SWP SFT_T(TAB_SWP_FAKE)

// FUN keys
#define SFT_A_N SFT_T(SFT_A_N_FAKE)
#define GUI_A_E GUI_T(GUI_A_E_FAKE)
#define ALT_A_I ALT_T(_ALT_FAKE_A_I)
#define CTL_A_GR CTL_T(CTL_A_GR_FAKE)

#define _OS_SFT OSM(MOD_LSFT)
#define _OS_GUI OSM(MOD_LGUI)
#define _OS_ALT OSM(MOD_LALT)
#define _OS_CTL OSM(MOD_LCTL)

#define _F_SFT SFT_T(_F_SFT_FAKE)
#define _F_GUI GUI_T(_F_GUI_FAKE)
#define _F_ALT ALT_T(_F_ALT_FAKE)
#define _F_CTL CTL_T(_F_CTL_FAKE)


// NUM & SYM keys

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



#define NUM_A CTL_T(NUM_A_FAKE)
#define NUM_R ALT_T(NUM_R_FAKE)
#define NUM_S GUI_T(NUM_S_FAKE)
#define NUM_T SFT_T(NUM_T_FAKE)

#define _CUR_BTN2 CTL_T(_CUR_BTN2_FAKE)


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
       KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                      KC_J,    KC_L,    KC_U,      KC_Y,    KC_QUOT,
       KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                      KC_H,    KC_N,      KC_E,      KC_I,      KC_O,
       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_EXLM,
                                        ACT_SPC, NUM_SFT,    SYM_ENT, ACT_BSP
  ),

  [_SYM] = LAYOUT(
     KC_GRV,   KC_AT, KC_LCBR, KC_RCBR, KC_HASH,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_TILD, KC_PIPE, KC_LPRN, KC_RPRN, KC_PERC,                      XXXXXXX, KC_RSFT, KC_RGUI, KC_RALT, KC_RCTL,
    KC_BSLS,  KC_DLR, KC_LBRC, KC_RBRC, KC_AMPR,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                        _ACT_LT, _NUM_GT,    _______, XXXXXXX
  ),

  [_NUM] = LAYOUT(
    XXXXXXX,   _PIPE,  _ARROW, _ARROW2, XXXXXXX,                      KC_PLUS, KC_1,    KC_2,    KC_3,    KC_CIRC,
      NUM_A,   NUM_R,   NUM_S,   NUM_T, XXXXXXX,                      KC_MINS, KC_4,    KC_5,    KC_6,    KC_0,
       _GBP,    _EUR,   CEDIL, XXXXXXX, XXXXXXX,                      KC_ASTR, KC_7,    KC_8,    KC_9,    KC_SLSH,
                                        XXXXXXX, _______,    KC_EQL,  KC_UNDS
  ),

  [_ACT] = LAYOUT(
    XXXXXXX,  KC_ESC,    BACK,    FRWD,  INSERT,                      KC_PGUP, SFT_TAB, KC_UP,   KC_TAB,  KC_HOME,
      OSCTL,   OSALT,   OSGUI,   OSSFT,  REPEAT,                      KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,
       UNDO,     CUT,    COPY,   PASTE,    REDO,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                        _______, XXXXXXX,    KC_PENT, KC_BSPC
  ),

  [_FUN] = LAYOUT(
     KC_PWR,   KC_F1,   KC_F2,   KC_F3,  KC_F10,                      DM_REC1, _MUTE,   _VOLD,   _VOLU,   XXXXXXX,
     KC_ESC,   KC_F4,   KC_F5,   KC_F6,  KC_F11,                      DM_RSTP, _F_SFT,  _F_GUI,  _F_ALT,  _F_CTL,
      RESET,   KC_F7,   KC_F8,   KC_F9,  KC_F12,                      DM_PLY1, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX,
                                         KC_SPC, XXXXXXX,    XXXXXXX, XXXXXXX
  )
};


// KEY OVERRIDES

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

  else if (keycode == _LT_GT && record->event.pressed) {
    SEND_STRING("</>");
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

  // NUM_A: ô
  else if (keycode == NUM_A && record->event.pressed && record->tap.count > 0) {
    tap_code16(DCIR);
    layer_off(_NUM);
    ret = false;
  }

  // NUM_R: à
  else if (keycode == NUM_R && record->event.pressed && record->tap.count > 0) {
    tap_code16(DGRV);
    layer_off(_NUM);
    ret = false;
  }

  // NUM_S: é
  else if (keycode == NUM_S && record->event.pressed && record->tap.count > 0) {
    tap_code16(ACUT);
    layer_off(_NUM);
    ret = false;
  }

  // NUM_T: ã
  else if (keycode == NUM_T && record->event.pressed && record->tap.count > 0) {
    tap_code16(DTIL);
    layer_off(_NUM);
    ret = false;
  }

  // NUM_SFT
  else if (keycode == NUM_SFT) {
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

  processrepeat_key(keycode, record);

  return ret;
}


uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case _F_SFT:
      return TAPPING_TERM + 100;
    case SYM_ENT:
      return TAPPING_TERM - 25;
    default:
      return TAPPING_TERM;
  }
}


bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case _NUM_TAB:
    case ACT_BSP:
    case SYM_ENT:
    case ACT_SPC:
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
