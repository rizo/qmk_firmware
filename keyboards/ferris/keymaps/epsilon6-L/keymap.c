#include QMK_KEYBOARD_H
#include "keymap_extras/keymap_portuguese.h"
#include "oneshot.h"


// --------------
// --- LAYERS ---
// --------------

enum layers {
  _ABC,
  _SYM,
  _NUM,
  _ACT,
  _FUN,
};

// -----------------------
// --- CUSTOM KEYCODES ---
// -----------------------

enum keycodes {
    _OS_SFT = SAFE_RANGE,
    _OS_CTL,
    _OS_ALT,
    _OS_GUI,
    _NUM_SFT_FAKE,
    _ACT_CTL_FAKE,
    _REPEAT,
    _TILD,
    _GRV,
    _CIRC,
    _PIPE,
    _ARROW,
    _ARROW2,
    _USHM_FAKE,
    _CDIR_FAKE,
    _PDIR_FAKE,
    _SFT_TILD_FAKE,
    _CTL_ACUT_FAKE,
    _ALT_CIRC_FAKE,
    _GUI_GRV_FAKE,
};

#define _ACT_CTL LT(_ACT, _ACT_CTL_FAKE)
#define _NUM_SFT LT(_NUM, _NUM_SFT_FAKE)
#define _SYM_SPC LT(_SYM, KC_SPC)
#define _FUN_ENT LT(_FUN, KC_ENT)

#define _C_HOME  C(KC_HOME)
#define _C_END   C(KC_END)

#define _BACK C(KC_LBRC)
#define _FRWD C(KC_RBRC)

#define _UNDO C(KC_Z)
#define _REDO S(C(KC_Z))
#define _COPY G(KC_C)
#define _PASTE G(KC_V)
#define _CUT G(KC_X)

#define  _VOLU KC__VOLUP
#define  _VOLD KC__VOLDOWN
#define  _MUTE KC__MUTE

#define _ACT_LT LT(_ACT, KC_LT)
#define _NUM_GT LT(_NUM, KC_GT)

#define _G_USHM GUI_T(_USHM_FAKE)
#define _A_CDIR ALT_T(_CDIR_FAKE)
#define _C_PDIR CTL_T(_PDIR_FAKE)
#define _S_SPC  SFT_T(KC_SPC)

#define _SFT_TILD SFT_T(_SFT_TILD_FAKE)
#define _CTL_ACUT GUI_T(_CTL_ACUT_FAKE)
#define _ALT_CIRC ALT_T(_ALT_CIRC_FAKE)
#define _GUI_GRV CTL_T(_GUI_GRV_FAKE)


// Keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_ABC] = LAYOUT(
    KC_Q,    KC_W,    KC_F,     KC_P,    KC_G,                 KC_J,     KC_L,     KC_U,     KC_Y,  PT_QUOT,
    KC_A,    KC_R,    KC_S,     KC_T,    KC_D,                 KC_H,     KC_N,     KC_E,     KC_I,     KC_O,
    KC_Z,    KC_X,    KC_C,     KC_V,    KC_B,                 KC_K,     KC_M, KC_COMMA,   KC_DOT,  KC_EXLM,
                                      _ACT_CTL, _NUM_SFT,  _SYM_SPC, _FUN_ENT
  ),

  [_SYM] = LAYOUT(
      _GRV,    PT_AT, PT_LCBR, PT_RCBR, PT_HASH,                     XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,  XXXXXXX,
      _TILD, PT_PIPE, PT_LPRN, PT_RPRN, PT_PERC,                     XXXXXXX, _SFT_TILD, _CTL_ACUT, _ALT_CIRC, _GUI_GRV,
    PT_BSLS,  PT_DLR, PT_LBRC, PT_RBRC, PT_AMPR,                     XXXXXXX,   XXXXXXX,   PT_CCED,   XXXXXXX,  XXXXXXX,
                                        _ACT_LT, _NUM_GT,   _______, XXXXXXX
  ),

  [_NUM] = LAYOUT(
    XXXXXXX,  _PIPE,   _ARROW, _ARROW2, XXXXXXX,                    PT_PLUS, KC_1, KC_2, KC_3,   _CIRC,
    _G_USHM, _A_CDIR, _C_PDIR,  _S_SPC, XXXXXXX,                    PT_MINS, KC_4, KC_5, KC_6,    KC_0,
    PT_EURO,  PT_PND, XXXXXXX, XXXXXXX, XXXXXXX,                    PT_ASTR, KC_7, KC_8, KC_9, PT_SLSH,
                                        XXXXXXX, _______,   PT_UNDS, PT_EQL
  ),

  [_ACT] = LAYOUT(
    XXXXXXX,  KC_ESC,   _BACK,   _FRWD, XXXXXXX,                  KC_PGUP,  KC_DEL,   KC_UP, KC_BSPC, _C_HOME,
    _OS_GUI, _OS_ALT, _OS_CTL, _OS_SFT, _REPEAT,                  KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _C_END,
      _UNDO,    _CUT,   _COPY,  _PASTE,   _REDO,                  XXXXXXX, KC_HOME,  KC_TAB,  KC_END, XXXXXXX,
                                         _______, XXXXXXX,  KC_SPC, KC_ENT
  ),

  [_FUN] = LAYOUT(
    KC_POWER, KC_F1,  KC_F2, KC_F3, KC_F10,                    DM_REC1,    _MUTE,    _VOLD,    _VOLU,  XXXXXXX,
   KC_INSERT, KC_F4,  KC_F5, KC_F6, KC_F11,                    DM_RSTP,  _OS_SFT,  _OS_CTL,  _OS_ALT,  _OS_GUI,
       RESET, KC_F7,  KC_F8, KC_F9, KC_F12,                    DM_PLY1,  KC_MPRV,  KC_MPLY,  KC_MNXT,  XXXXXXX,
                                   _______, KC_CAPS,  XXXXXXX, _______
  )
};


// ---------------------
// --- KEY OVERRIDES ---
// ---------------------

// S(KC_COMMA) -> KC_SCLN
const key_override_t scln_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_COMMA, PT_SCLN);

// S(KC_DOT) -> KC_COLN
const key_override_t coln_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, PT_COLN);

// S(KC_EXLM) -> KC_QUES
const key_override_t ques_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_EXLM, PT_QUES);

// S(PT_QUOT) -> PT_DQUO
const key_override_t dquo_key_override = _ko_make_strict(MOD_MASK_SHIFT, PT_QUOT, PT_DQUO);

const key_override_t **key_overrides = (const key_override_t *[]) {
  &scln_key_override,
  &coln_key_override,
  &ques_key_override,
  &dquo_key_override,
  NULL
};


// ---------------------
// --- ONE SHOT MODS ---
// ---------------------

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case _ACT_CTL:
    case _FUN_ENT:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case _ACT_CTL:
    case _FUN_ENT:
    case _NUM_SFT:
    case _SYM_SPC:
    case _OS_SFT:
    case _OS_CTL:
    case _OS_ALT:
    case _OS_GUI:
        return true;
    default:
        return false;
    }
}

oneshot_state os_sft_state = os_up_unqueued;
oneshot_state os_ctl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_gui_state = os_up_unqueued;


// ----------------------
// --- USER FUNCTIONS ---
// ----------------------

// State variables.
bool caps_lock_enabled = false;
uint16_t last_tap = KC_NO;
uint8_t last_modifier = 0;
uint8_t mods_state = 0;
uint8_t oneshot_mods_state = 0;

// Used to extract the basic tapping keycode from a dual-role key.
// Example: GET_TAP_KC(MT(MOD_RSFT, KC_E)) == KC_E
#define GET_TAP_KC(dual_role_key) dual_role_key & 0xFF

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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
  uprintf("0x%04X,%u,%u,%u,%b,0x%02X,0x%02X,%u\n",
    keycode,
    record->event.key.row,
    record->event.key.col,
    get_highest_layer(layer_state),
    record->event.pressed,
    get_mods(),
    get_oneshot_mods(),
    record->tap.count,
  );
#endif

  mods_state = get_mods();
  oneshot_mods_state = get_oneshot_mods();

  bool ret = true;

  update_oneshot(
      &os_sft_state, KC_LSFT, _OS_SFT,
      keycode, record
  );
  update_oneshot(
      &os_ctl_state, KC_LCTL, _OS_CTL,
      keycode, record
  );
  update_oneshot(
      &os_alt_state, KC_LALT, _OS_ALT,
      keycode, record
  );
  update_oneshot(
      &os_gui_state, KC_LGUI, _OS_GUI,
      keycode, record
  );

  if (keycode == _ACT_CTL && record->event.pressed && record->tap.count > 0) {
    set_oneshot_mods(MOD_BIT(KC_LCTL));
    ret = false;
  }

  else if (keycode == _TILD && record->event.pressed) {
    tap_code16(PT_TILD);
    tap_code16(PT_TILD);
    ret = false;
  }

  else if (keycode == _GRV && record->event.pressed) {
    tap_code16(PT_GRV);
    tap_code16(PT_GRV);
    ret = false;
  }

  else if (keycode == _CIRC && record->event.pressed) {
    tap_code16(PT_CIRC);
    tap_code16(PT_CIRC);
    ret = false;
  }

  // _ACT_LT -> KC_LT
  else if (keycode == _ACT_LT && record->event.pressed && record->tap.count > 0) {
    tap_code16(PT_LABK);
    ret = false;
  }

  // _NUM_GT -> KC_GT
  else if (keycode == _NUM_GT && record->event.pressed && record->tap.count > 0) {
    tap_code16(PT_RABK);
    ret = false;
  }

  // FUN: DEAD(~)
  else if (keycode == _SFT_TILD && record->event.pressed && record->tap.count > 0) {
    tap_code16(PT_TILD);
    layer_off(_SYM);
    ret = false;
  }

  // FUN: DEAD(´)
  else if (keycode == _CTL_ACUT && record->event.pressed && record->tap.count > 0) {
    tap_code16(PT_ACUT);
    layer_off(_SYM);
    ret = false;
  }

  // FUN: DEAD(^)
  else if (keycode == _ALT_CIRC && record->event.pressed && record->tap.count > 0) {
    tap_code16(PT_CIRC);
    layer_off(_SYM);
    ret = false;
  }

  // FUN: DEAD(`)
  else if (keycode == _GUI_GRV && record->event.pressed && record->tap.count > 0) {
    tap_code16(PT_GRV);
    layer_off(_SYM);
    ret = false;
  }

  // SYM: PIPE
  else if (keycode == _PIPE && record->event.pressed) {
    tap_code16(PT_PIPE);
    tap_code16(PT_RABK);
    ret = false;
  }
  
  // _ARROW
  else if (keycode == _ARROW && record->event.pressed) {
    tap_code16(PT_MINS);
    tap_code16(PT_RABK);
    ret = false;
  }

  // _ARROW2
  else if (keycode == _ARROW2 && record->event.pressed) {
    tap_code16(PT_EQL);
    tap_code16(PT_RABK);
    ret = false;
  }

  // _G_USHM
  else if (keycode == _G_USHM && record->event.pressed && record->tap.count > 0) {
    tap_code16(PT_TILD);
    tap_code16(PT_TILD);
    tap_code16(PT_SLSH);
    ret = false;
  }

  // _A_CDIR
  else if (keycode == _A_CDIR && record->event.pressed && record->tap.count > 0) {
    tap_code16(PT_DOT);
    tap_code16(PT_SLSH);
    ret = false;
  }

  // _C_PDIR
  else if (keycode == _C_PDIR && record->event.pressed && record->tap.count > 0) {
    tap_code16(PT_DOT);
    tap_code16(PT_DOT);
    tap_code16(PT_SLSH);
    ret = false;
  }

  // _NUM_SFT
  else if (keycode == _NUM_SFT && record->event.pressed && record->tap.count > 0) {
    if (caps_lock_enabled) {
      tap_code16(KC_CAPS);
      caps_lock_enabled = false;
      ret = false;
    } else if (get_oneshot_mods() & MOD_MASK_SHIFT) {
      clear_oneshot_mods();
      tap_code(KC_CAPS);
      caps_lock_enabled = true;
      ret = false;
    } else {
      set_oneshot_mods(MOD_BIT(KC_LSFT));
      ret = false;
    }
  }

  process_repeat_key(keycode, record);

  return ret;
}
