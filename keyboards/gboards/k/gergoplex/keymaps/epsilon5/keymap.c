#include QMK_KEYBOARD_H


// Layers keys

enum layer_names {
  _L_ABC,
  _L_ACT,
  _L_SYM,
  _L_NUM,
  _L_FUN
};


// Custom keys

enum keycodes {
    // Custom oneshot mod implementation with no timers.
    OS_SHFT = SAFE_RANGE,

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


// Home row mods
#define _K_A CTL_T(KC_A)
#define _K_R ALT_T(KC_R)
#define _K_S GUI_T(KC_S)
#define _K_T SFT_T(KC_T)

#define _K_N SFT_T(KC_N)
#define _K_E GUI_T(KC_E)
#define _K_I ALT_T(KC_I)
#define _K_O CTL_T(KC_O)

// Thumb keys
#define _LA_SP  LT(_L_ACT, KC_SPC)
#define _LN_TAB LT(_L_NUM, KC_TAB)
#define _LS_ENT LT(_L_SYM, KC_ENT)
#define _LF_BS  LT(_L_FUN, KC_BSPC)
#define _MC_ESC CTL_T(KC_ESC)
#define _MA_DEL ALT_T(KC_DEL)


// ACT keys
#define _K_UNDO G(KC_Z)
#define _K_REDO S(G(KC_Z))
#define _K_COPY G(KC_C)
#define _K_PAST G(KC_V)
#define _K_CUT G(KC_X)
#define _K_GENT G(KC_ENT)
#define _K_GSP G(KC_SPC)


// Movement keys
#define _K_WD_L A(KC_LEFT)
#define _K_WD_R A(KC_RIGHT)
#define _K_LN_L G(KC_LEFT)
#define _K_LN_R G(KC_RIGHT)
#define _K_FL_T G(KC_UP)
#define _K_FL_B G(KC_DOWN)
#define _K_PG_U A(KC_UP)
#define _K_PG_D A(KC_DOWN)


// One-shot mods
#define _K_OSFT OSM(MOD_LSFT)
#define _K_OCTL OSM(MOD_LCTL)
#define _K_OALT OSM(MOD_LALT)
#define _K_OGUI OSM(MOD_LGUI)


// FUN keys
#define _K_LOCK G(C(KC_Q))
#define _K_VOLU KC__VOLUP
#define _K_VOLD KC__VOLDOWN
#define _K_MUTE KC__MUTE


// Alt symbols
#define _K_AGRV A(KC_GRV)
#define _K_ATLD A(KC_N)
#define _K_ACNT A(KC_E)
#define _K_ACRC A(KC_I)
#define _K_DGRE A(KC_K)
#define _K_TM A(KC_2)
#define _K_SCTN A(KC_6)
#define _K_PCRW A(KC_7)
#define _K_PMIL S(A(KC_R))
#define _K_EURO S(A(KC_2))
#define _K_PND A(KC_3)
#define _K_CDL A(KC_C)
#define _K_CPRT A(KC_G)
#define _K_QT_O A(KC_BSLS)
#define _K_QT_C S(A(KC_BSLS))
#define _K_PLMN S(A(KC_EQL))
#define _K_NEQL A(KC_EQL)
#define _K_NDSH A(KC_MINS)
#define _K_MDSH S(A(KC_MINS))
#define _K_BLLT A(KC_8)
#define _K_ELPS A(KC_SCLN)
#define _K_SQRT A(KC_V)
#define _K_DIVD A(KC_SLSH)
#define _K_APRX A(KC_X)
#define _K_INFT A(KC_5)
#define _K_LTE A(KC_COMM)
#define _K_GTE A(KC_DOT)
#define _K_SL_O A(KC_O)
#define _K_EMOJ G(C(KC_SPC))
#define _K_DLWD A(KC_BSPC)



// --- KEYMAP ---

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_L_ABC] = LAYOUT_gergoplex(
  //,--------------------------------------------.                    ,--------------------------------------------.
         KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_QUOT,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
         _K_A,    _K_R,    _K_S,    _K_T,    KC_D,                         KC_H,    _K_N,    _K_E,    _K_I,    _K_O,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
         KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_K,    KC_M, _K_COMM,  _K_DOT, _K_EXLM,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                 _MC_ESC,  _LA_SP, _LN_TAB,    _LS_ENT,  _LF_BS, _MA_DEL
                             //`--------------------------'  `--------------------------'
  ),

  [_L_ACT] = LAYOUT_gergoplex(
  //,--------------------------------------------.                    ,--------------------------------------------.
      KC_ESC,  KC_MPRV, KC_MNXT, KC_MPLY, XXXXXXX,                      KC_PGUP, _K_UNDO,   KC_UP, _K_REDO, KC_HOME,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      _K_OCTL, _K_OALT, _K_OGUI, _K_OSFT, XXXXXXX,                      KC_PGDN, KC_LEFT, KC_DOWN,KC_RIGHT,  KC_END,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      XXXXXXX, _K_VOLD, _K_VOLU, _K_MUTE, XXXXXXX,                      XXXXXXX, _K_COPY, _K_PAST,  _K_CUT, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                 XXXXXXX, _______, XXXXXXX,    _______, _______, _______
                             //`--------------------------'  `--------------------------'
  ),

  [_L_SYM] = LAYOUT_gergoplex(
  //,--------------------------------------------.                    ,--------------------------------------------.
       KC_GRV,   KC_AT, KC_LBRC, KC_RBRC, KC_HASH,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      KC_TILD, KC_PIPE, KC_LPRN, KC_RPRN, KC_PERC,                      XXXXXXX, _K_OSFT, _K_OGUI, _K_OALT, _K_OCTL,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      KC_BSLS,  KC_DLR, KC_LCBR, KC_RCBR, KC_AMPR,                      KC_ASTR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                 _______,   KC_LT,   KC_GT,    _______, XXXXXXX, XXXXXXX
                             //`--------------------------'  `--------------------------'
  ),

  [_L_NUM] = LAYOUT_gergoplex(
  //,--------------------------------------------.                    ,--------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_PLUS,    KC_7,    KC_8,    KC_9, KC_CIRC,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      _K_OCTL, _K_OALT, _K_OGUI, _K_OSFT, XXXXXXX,                      KC_MINS,    KC_1,    KC_2,    KC_3,    KC_0,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_ASTR,    KC_4,    KC_5,    KC_6, KC_SLSH,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                 XXXXXXX, XXXXXXX, _______,     KC_EQL, KC_UNDS, _______
                             //`--------------------------'  `--------------------------'
  ),

  [_L_FUN] = LAYOUT_gergoplex(
  //,--------------------------------------------.                    ,--------------------------------------------.
      XXXXXXX, KC_MPRV, KC_MNXT, KC_MPLY, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      XXXXXXX, _K_VOLD, _K_VOLU, _K_MUTE, XXXXXXX,                      XXXXXXX, _K_OSFT, _K_OGUI, _K_OALT, _K_OCTL,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                 XXXXXXX,  KC_ESC, XXXXXXX,    XXXXXXX, _______, XXXXXXX
                             //`--------------------------'  `--------------------------'
  )
};



// --- Function overrides ---

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool ret = true;

  bool is_gui_on = (get_mods() & MOD_BIT(KC_LGUI));
  bool is_alt_on = (get_mods() & MOD_BIT(KC_LALT));
  bool is_sft_on = (get_mods() & MOD_BIT(KC_LSHIFT));
  bool is_ctl_on = (get_mods() & MOD_BIT(KC_LCTL));


  // '.' / ':'
  if (keycode == _K_DOT && record->event.pressed) {
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
