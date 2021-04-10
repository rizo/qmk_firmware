#include QMK_KEYBOARD_H


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
// KC_LCTL, KC_LSFT, KC_LGUI, KC_LALT

// A + R -> CTL + SFT
const uint16_t PROGMEM   ar_mod_combo[] = {KC_LGUI, KC_A, KC_R, COMBO_END};

// A + S -> CTL + GUI
const uint16_t PROGMEM   as_mod_combo[] = {KC_LGUI, KC_A, KC_S, COMBO_END};

// A + T -> CTL + ALT
const uint16_t PROGMEM   at_mod_combo[] = {KC_LGUI, KC_A, KC_T, COMBO_END};

// R + S -> SFT + GUI
const uint16_t PROGMEM   rs_mod_combo[] = {KC_LGUI, KC_R, KC_S, COMBO_END};

// R + T -> SFT + ALT
const uint16_t PROGMEM   rt_mod_combo[] = {KC_LGUI, KC_R, KC_T, COMBO_END};

// S + T -> GUI + ALT
const uint16_t PROGMEM   st_mod_combo[] = {KC_LGUI, KC_S, KC_T, COMBO_END};

// A + R + S  -> CTL + SFT + GUI
const uint16_t PROGMEM  ars_mod_combo[] = {KC_LGUI, KC_A, KC_R, KC_S, COMBO_END};

// A + R + T  -> CTL + SFT + ALT
const uint16_t PROGMEM  art_mod_combo[] = {KC_LGUI, KC_A, KC_R, KC_T, COMBO_END};

// A + S + T  -> CTL + GUI + ALT
const uint16_t PROGMEM  ast_mod_combo[] = {KC_LGUI, KC_A, KC_S, KC_T, COMBO_END};

// R + S + T  -> SFT + GUI + ALT
const uint16_t PROGMEM  rst_mod_combo[] = {KC_LGUI, KC_R, KC_S, KC_T, COMBO_END};

// A + R + S + T  -> CGI + SFT + GUI + ALT
const uint16_t PROGMEM arst_mod_combo[] = {KC_LGUI, KC_A, KC_R, KC_S, KC_T, COMBO_END};


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
      set_oneshot_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT));
    }
    break;

  case _E_AS_MOD:
    if (pressed) {
      set_oneshot_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI));
    }
    break;

  case _E_AT_MOD:
    if (pressed) {
      set_oneshot_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LALT));
    }
    break;

  case _E_RS_MOD:
    if (pressed) {
      set_oneshot_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_LGUI));
    }
    break;

  case _E_RT_MOD:
    if (pressed) {
      set_oneshot_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_LALT));
    }
    break;

  case _E_ST_MOD:
    if (pressed) {
      set_oneshot_mods(MOD_BIT(KC_LGUI) | MOD_BIT(KC_LALT));
    }
    break;

  case _E_ARS_MOD:
    if (pressed) {
      set_oneshot_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT) | MOD_BIT(KC_LGUI));
    }
    break;

  case _E_ART_MOD:
    if (pressed) {
      set_oneshot_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT) | MOD_BIT(KC_LALT));
    }
    break;

  case _E_AST_MOD:
    if (pressed) {
      set_oneshot_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI) | MOD_BIT(KC_LALT));
    }
    break;

  case _E_RST_MOD:
    if (pressed) {
      set_oneshot_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_LGUI) | MOD_BIT(KC_LALT));
    }
    break;

  case _E_ARST_MOD:
    if (pressed) {
      set_oneshot_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT) | MOD_BIT(KC_LGUI) | MOD_BIT(KC_LALT));
    }
    break;
  }
}


// --- KEYMAP ---

enum layer_names {
  _L_ABC,
  _L_NAV,
  _L_SYM,
  _L_FUN
};

// Home row mods.
// #define _K_A LCTL_T(KC_A)
// #define _K_R LALT_T(KC_R)
// #define _K_S LGUI_T(KC_S)
// #define _K_T LSFT_T(KC_T)

// #define _K_N LSFT_T(KC_N)
// #define _K_E LGUI_T(KC_E)
// #define _K_I LALT_T(KC_I)
// #define _K_O LCTL_T(KC_O)

#define _K_A KC_A
#define _K_R KC_R
#define _K_S KC_S
#define _K_T KC_T

#define _K_N KC_N
#define _K_E KC_E
#define _K_I KC_I
#define _K_O KC_O

#define _K_CMD LGUI_T(KC_TAB)
#define _K_SYM LT(_L_SYM, KC_ENT)
#define _K_NAV LT(_L_NAV, KC_SPC)
#define _K_SFT SFT_T(KC_ESC)
#define _K_CTL CTL_T(KC_TAB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_L_ABC] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     KC_TAPP,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TAPU,    _K_A,    _K_R,    _K_S,    _K_T,    KC_D,                         KC_H,    _K_N,    _K_E,    _K_I,    _K_O, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TAPD,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_K,    KC_M, KC_COMM,  KC_DOT, KC_EXLM, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LALT, KC_LGUI,  _K_SFT,     _K_SYM,  _K_NAV,  _K_CTL
                                      //`--------------------------'  `--------------------------'
  ),

  [_L_NAV] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX,  KC_DEL,   KC_UP, KC_BSPC, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_LCTL, KC_LSFT, KC_LGUI, KC_LALT, XXXXXXX,                      KC_PGUP, KC_LEFT, KC_DOWN,KC_RIGHT, KC_HOME, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, _______, _______, _______, _______, XXXXXXX,                      KC_PGDN, XXXXXXX, XXXXXXX, XXXXXXX,  KC_END, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    XXXXXXX, _______, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

  [_L_SYM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX,  KC_GRV, KC_HASH, KC_LBRC, KC_RBRC, KC_AMPR,                      KC_PLUS,    KC_4,    KC_5,    KC_6, KC_ASTR, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,   KC_AT, KC_PIPE, KC_LPRN, KC_RPRN, KC_PERC,                       KC_EQL,    KC_1,    KC_2,    KC_3,    KC_0, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_BSLS,  KC_DLR, KC_LCBR, KC_RCBR, KC_TILD,                      KC_MINS,    KC_7,    KC_8,    KC_9, KC_SLSH, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_LT,   KC_GT, KC_CIRC,    _______, XXXXXXX, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

  [_L_FUN] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        RESET, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  )
};




bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  
  return true;
}

