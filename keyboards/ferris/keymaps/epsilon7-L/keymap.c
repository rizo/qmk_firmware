// TODO: Reduce tapping term for _APP_SWP

#include QMK_KEYBOARD_H

#include "keymap_extras/keymap_us_international_linux.h"


// Used to extract the basic tapping keycode from a dual-role key.
// Example: GET_TAP_KC(MT(MOD_RSFT, KC_E)) == KC_E
#define GET_TAP_KC(dual_role_key) dual_role_key & 0xFF


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
};


// Custom keys.
enum keycodes {
    _ACT_OCTL_FAKE = SAFE_RANGE,
    _NUM_CAPS_FAKE,

    _SFT_A_N_FAKE,
    _GUI_A_E_FAKE,
    _ALT_FAKE_A_I,
    _CTL_A_GR_FAKE,

    _PIPE,
    _ARROW,
    _ARROW2,
    _USHM_FAKE,
    _DTSL_FAKE,

    _CDIR_FAKE,
    _PDIR_FAKE,

    _RPT,
};



// Thumb keys
#define _ACT_OCTL LT(_ACT, _ACT_OCTL_FAKE)
#define _NUM_CAPS LT(_NUM, _NUM_CAPS_FAKE)

#define _SYM_SPC  LT(_SYM, KC_SPC)
#define _FUN_BSP  LT(_FUN, KC_BSPC)

// ACT keys
#define OSGUI OSM(MOD_BIT(KC_LGUI))
#define OSALT OSM(MOD_BIT(KC_LALT))
#define OSCTL OSM(MOD_BIT(KC_LCTL))
#define OSSFT OSM(MOD_BIT(KC_LSFT))

#define _STAB S(KC_TAB)
#define _UNDO C(KC_Z)
#define _REDO S(C(KC_Z))
#define _COPY G(KC_C)
#define _PASTE G(KC_V)
#define _PASTE2 S(A(G(KC_V)))
#define _CUT G(KC_X)

#define _BACK C(KC_LBRC)
#define _FRWD C(KC_RBRC)


// FUN keys
#define  _VOLU KC__VOLUP
#define  _VOLD KC__VOLDOWN
#define  _MUTE KC__MUTE

#define _SFT_A_N SFT_T(_SFT_A_N_FAKE)
#define _GUI_A_E GUI_T(_GUI_A_E_FAKE)
#define _ALT_A_I ALT_T(_ALT_FAKE_A_I)
#define _CTL_A_GR CTL_T(_CTL_A_GR_FAKE)


// NUM & SYM keys
#define _ACT_LT LT(_ACT, KC_LT)
#define _NUM_GT LT(_NUM, KC_GT)
#define _INF A(KC_5)
#define _COPYR A(KC_G)
#define _GBP US_PND
#define _EUR US_EURO
#define _SQRT A(KC_V)
#define _TM A(KC_2)
#define _DGREE US_DEG
#define _SECTN US_SECT
#define _PLCRW A(KC_7)
#define _PLSMIN S(A(KC_EQL))
#define _ELLPSI A(KC_SCLN)
#define _CEDIL A(KC_C)
#define _BULLT A(KC_8)
#define _ENDSH A(KC_MINS)
#define _EMDSH S(A(KC_MINS))
#define _DIARS A(KC_U)
#define _QUATL US_LDAQ
#define _QUATR US_RDAQ
#define _NEQ A(KC_EQL)
#define _MUL S(A(KC_9))
#define _DIV A(KC_SLSH)

#define _C_USHM CTL_T(_USHM_FAKE)
#define _A_CDIR ALT_T(_CDIR_FAKE)
#define _G_PDIR GUI_T(_PDIR_FAKE)
#define _S_SPC  SFT_T(KC_SPC)



// Keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_ABC] = LAYOUT(
       KC_Q,    KC_W,    KC_F,     KC_P,     KC_G,                          KC_J,     KC_L, KC_U,     KC_Y,   US_QUOT,
       KC_A,    KC_R,    KC_S,     KC_T,     KC_D,                          KC_H,     KC_N, KC_E,     KC_I,   KC_O,
       KC_Z,    KC_X,    KC_C,     KC_V,     KC_B,                          KC_K,     KC_M, KC_COMMA, KC_DOT, KC_EXLM,
                                        _ACT_OCTL, _NUM_CAPS,  _SYM_SPC, _FUN_BSP
  ),

  [_SYM] = LAYOUT(
     US_GRV,   US_AT, US_LCBR, US_RCBR, US_HASH,                     _PLSMIN,   _EMDSH,   _DIARS, _QUATL,   _QUATR,
    US_TILD, US_PIPE, US_LPRN, US_RPRN, US_PERC,                      _ENDSH, _SFT_A_N, _GUI_A_E, _ALT_A_I, _CTL_A_GR,
    US_BSLS,  US_DLR, US_LBRC, US_RBRC, US_AMPR,                        _MUL,   _BULLT,  US_CCED, _ELLPSI,  _DIV,
                                         _ACT_LT, _NUM_GT,   _______, XXXXXXX
  ),

  [_NUM] = LAYOUT(
    XXXXXXX,   _PIPE,  _ARROW, _ARROW2, XXXXXXX,                     US_PLUS,    KC_1,    KC_2,    KC_3, US_CIRC,
    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,                     US_MINS,    KC_4,    KC_5,    KC_6,    KC_0,
    XXXXXXX,    _GBP,  _COPYR, XXXXXXX, XXXXXXX,                     US_ASTR,    KC_7,    KC_8,    KC_9, US_SLSH,
                                        XXXXXXX, _______,  US_UNDS, US_EQL
  ),

  [_ACT] = LAYOUT(
    KC_CAPS,  KC_ESC,   _STAB,  KC_TAB, KC_PGUP,                    KC_HOME,   _STAB,  KC_UP,   KC_TAB, XXXXXXX,
      OSGUI,   OSALT,   OSCTL,   OSSFT, KC_PGDN,                    KC_END,  KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX,
    XXXXXXX,    _RPT,   _UNDO,   _REDO, XXXXXXX,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                       TO(_ABC), XXXXXXX,   KC_ENT, KC_BSPC
  ),

  [_FUN] = LAYOUT(
    KC_POWER, KC_F1,  KC_F2, KC_F3, KC_F10,                    DM_REC1, _MUTE,   _VOLD,   _VOLU,   XXXXXXX,
     KC_EJCT, KC_F4,  KC_F5, KC_F6, KC_F11,                    DM_RSTP, OSSFT,   OSCTL,   OSALT,   OSGUI,
       RESET, KC_F7,  KC_F8, KC_F9, KC_F12,                    DM_PLY1, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX,
                                    KC_SPC, KC_TAB,   XXXXXXX, XXXXXXX
  )
};


// KEY OVERRIDES


// S(KC_COMMA) -> KC_SCLN
const key_override_t scln_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_COMMA, US_SCLN);

// S(KC_DOT) -> KC_COLN
const key_override_t coln_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, US_COLN);

// S(KC_EXLM) -> KC_QUES
const key_override_t ques_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_EXLM, US_QUES);

// S(US_QUOT) -> US_DQUO
  const key_override_t dquo_key_override = _ko_make_strict(MOD_MASK_SHIFT, US_QUOT, US_DQUO);

const key_override_t **key_overrides = (const key_override_t *[]) {
  &scln_key_override,
  &coln_key_override,
  &ques_key_override,
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

  // TAP(_ACT_OCTL)
  if (keycode == _ACT_OCTL && record->event.pressed && record->tap.count > 0) {
    // Second tap: activate act.
    if (oneshot_mods_state & MOD_MASK_CTRL) {
      clear_oneshot_mods();
      layer_on(_ACT);
    }
    // First tap: set oneshot CTL.
    else {
      set_oneshot_mods(MOD_BIT(KC_LCTL));
    }
    ret = false;
  }

  // TAP(_NUM_CAPS)
  else if (keycode == _NUM_CAPS && record->event.pressed && record->tap.count > 0) {
    // Second tap: enable word caps.
    if (oneshot_mods_state & MOD_MASK_SHIFT) {
      clear_oneshot_mods();
      caps_word_enable();
    }
    // Caps word already enabled: disable.
    else if (caps_word_on) {
      caps_word_disable();
    }
    // First tap: set oneshot SFT.
    else {
      set_oneshot_mods(MOD_BIT(KC_LSFT));
    }
    ret = false;
  }

  // _ACT_LT -> KC_LT
  else if (keycode == _ACT_LT && record->event.pressed && record->tap.count > 0) {
    tap_code16(US_LABK);
    ret = false;
  }

  // _NUM_GT -> KC_GT
  else if (keycode == _NUM_GT && record->event.pressed && record->tap.count > 0) {
    tap_code16(US_RABK);
    ret = false;
  }

  // FUN: DTIL
  else if (keycode == _SFT_A_N && record->event.pressed && record->tap.count > 0) {
    tap_code16(US_DTIL);
    layer_off(_SYM);
    ret = false;
  }

  // FUN: ACUT
  else if (keycode == _GUI_A_E && record->event.pressed && record->tap.count > 0) {
    tap_code16(US_ACUT);
    layer_off(_SYM);
    ret = false;
  }

  // FUN: DCIR
  else if (keycode == _ALT_A_I && record->event.pressed && record->tap.count > 0) {
    tap_code16(US_DCIR);
    layer_off(_SYM);
    ret = false;
  }

  // FUN: DGRV
  else if (keycode == _CTL_A_GR && record->event.pressed && record->tap.count > 0) {
    tap_code16(US_DGRV);
    layer_off(_SYM);
    ret = false;
  }

  // SYM: PIPE
  else if (keycode == _PIPE && record->event.pressed) {
    tap_code16(US_PIPE);
    tap_code16(US_RABK);
    ret = false;
  }
  
  // _ARROW
  else if (keycode == _ARROW && record->event.pressed) {
    tap_code(US_MINS);
    tap_code16(US_RABK);
    ret = false;
  }

  // _ARROW2
  else if (keycode == _ARROW2 && record->event.pressed) {
    tap_code16(US_EQL);
    tap_code16(US_RABK);
    ret = false;
  }

  // _C_USHM
  else if (keycode == _C_USHM && record->event.pressed && record->tap.count > 0) {
    tap_code16(US_TILD);
    tap_code16(US_SLSH);
    ret = false;
  }

  // _A_CDIR
  else if (keycode == _A_CDIR && record->event.pressed && record->tap.count > 0) {
    tap_code16(US_DOT);
    tap_code16(US_SLSH);
    ret = false;
  }

  // _G_PDIR
  else if (keycode == _G_PDIR && record->event.pressed && record->tap.count > 0) {
    tap_code16(US_DOT);
    tap_code16(US_DOT);
    tap_code16(US_SLSH);
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
