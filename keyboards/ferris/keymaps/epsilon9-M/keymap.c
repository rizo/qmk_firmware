#include QMK_KEYBOARD_H

// Used to extract the basic tapping keycode from a dual-role key.
// Example: GET_TAP_KC(MT(MOD_RSFT, KC_E)) == KC_E
#define GET_TAP_KC(dual_role_key) dual_role_key & 0xFF

uint16_t last_tap = KC_NO;
uint8_t last_modifier = 0;
uint8_t mods_state = 0;
uint8_t oneshot_mods_state = 0;


enum layers {
  ABC,
  ACT,
  NUM,
  SYM,
};


// Custom keys.
enum keycodes {
    NUM_ACT_FAKE = SAFE_RANGE,
    SFT_ABC_FAKE,

    _OGUI_FAKE,
    _OALT_FAKE,
    _OCTL_FAKE,
    _OSFT_FAKE,

    _S_TIL_FAKE,
    _G_ACU_FAKE,
    _A_CIR_FAKE,
    _C_GRV_FAKE,

    _PIPE,
    _ARROW,
    _ARROW2,
    _CURDIR,
    _HOMDIR,
    _PRVDIR,

    _RPT,
    _RSTMOD,

    XMOD,
};

// OS mods.
#define _OGUI GUI_T(_OGUI_FAKE)
#define _OALT ALT_T(_OALT_FAKE)
#define _OCTL CTL_T(_OCTL_FAKE)
#define _OSFT SFT_T(_OSFT_FAKE)

// Thumb keys
#define NUM_ACT LT(NUM, NUM_ACT_FAKE)
#define SFT_ABC MT(MOD_RSFT, SFT_ABC_FAKE)
#define SYM_ENT LT(SYM, KC_ENT)

// Back/forward.
#define _BACK G(KC_LBRC)
#define _FRWD G(KC_RBRC)

// Word/line motion.
#define _WRDL A(KC_LEFT)
#define _WRDR A(KC_RIGHT)
#define _LNL G(KC_LEFT)
#define _LNR G(KC_RIGHT)

// Edit actions.
#define _CUT G(KC_X)
#define _COPY G(KC_C)
#define _PASTE G(KC_V)
#define _UNDO G(KC_Z)
#define _REDO S(G(KC_Z))

// Untab
#define _STAB S(KC_TAB)

// Volume keys.
#define  _VOLU KC__VOLUP
#define  _VOLD KC__VOLDOWN
#define  _MUTE KC__MUTE

// Left mod accents.
#define _C_GRV CTL_T(_C_GRV_FAKE)
#define _A_CIR ALT_T(_A_CIR_FAKE)
#define _G_ACU GUI_T(_G_ACU_FAKE)
#define _S_TIL SFT_T(_S_TIL_FAKE)

// INTL keys.
#define _ACUT A(KC_E)
#define _DTIL A(KC_N)
#define _DCIR A(KC_I)
#define _DGRV A(KC_GRV)
#define _CCED A(KC_C)

// Media keys.
#define _VOLU KC__VOLUP
#define _VOLD KC__VOLDOWN
#define _MUTE KC__MUTE


// Keymap.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [ABC] = LAYOUT(
       KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                    KC_J,    KC_L, KC_U,     KC_Y,   KC_QUOT,
       KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                    KC_H,    KC_N, KC_E,     KC_I,   KC_O,
       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                    KC_K,    KC_M, KC_COMM,  KC_DOT, KC_EXLM,
                                        NUM_ACT, SFT_ABC,   KC_SPC, SYM_ENT
  ),

  [ACT] = LAYOUT(
    _RSTMOD, KC_CAPS,   _BACK,   _FRWD, KC_WH_U,                    KC_PGUP, KC_ESC,  KC_UP,   KC_BSPC, KC_HOME,
      _OCTL,   _OALT,   _OGUI,   _OSFT, KC_WH_D,                    KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,
      _UNDO,    _CUT,   _COPY,  _PASTE,   _REDO,                    XXXXXXX, _STAB,   KC_ESC,  KC_TAB,  XXXXXXX,
                                        _______, _______,   KC_SPC, KC_ENT
  ),

  [SYM] = LAYOUT(
    KC_GRV,  KC_1,    KC_2,    KC_3, KC_PLUS,                    KC_PLUS, KC_1,    KC_2,    KC_3,    KC_CIRC,
      _OCTL, KC_4,    KC_5,    KC_6, KC_MINS,                    KC_MINS, KC_4,    KC_5,    KC_6,    KC_0,
    KC_BSLS, KC_7,    KC_8,    KC_9, KC_SLSH,                    KC_ASTR, KC_7,    KC_8,    KC_9,    KC_SLSH,
                                     KC_LBRC, KC_AMPR,  _______, _______
  ),

  [NUM] = LAYOUT(
    XXXXXXX,   _PIPE,  _ARROW, _ARROW2, _CURDIR,                    KC_PLUS, KC_1,    KC_2,    KC_3,    KC_CIRC,
      _OCTL,   _OALT,   _OGUI,   _OSFT, _HOMDIR,                    KC_MINS, KC_4,    KC_5,    KC_6,    KC_0,
    XXXXXXX, XXXXXXX,   _CCED, XXXXXXX, _PRVDIR,                    KC_ASTR, KC_7,    KC_8,    KC_9,    KC_SLSH,
                                        XXXXXXX, _______,  KC_SPC,  KC_EQL
  ),

  [SYM] = LAYOUT(
    KC_GRV,    KC_AT, KC_LCBR, KC_RCBR, KC_HASH,                    XXXXXXX, _MUTE,   _VOLD,   _VOLU,   XXXXXXX,
    KC_TILD, KC_PIPE, KC_LPRN, KC_RPRN, KC_PERC,                    XXXXXXX, KC_LSFT, KC_LGUI, KC_RALT, KC_LCTL,
    KC_BSLS,  KC_DLR, KC_LBRC, KC_RBRC, KC_AMPR,                    XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, RESET,
                                        KC_LABK, KC_RABK,  _______, XXXXXXX
  )
};


// --- OVERRIDES ---

// S(KC_SPC) -> KC_ENT
const key_override_t spc_ent_ko = ko_make_basic(MOD_BIT(KC_RSFT), KC_SPC, KC_ENT);

// S(SYM_BSP) -> KC_UNDS
const key_override_t bsp_unds_ko = ko_make_basic(MOD_BIT(KC_RSFT), SYM_BSP, KC_UNDS);

// S(KC_COMMA) -> KC_SCLN
const key_override_t comma_scln_ko = ko_make_basic(MOD_MASK_SHIFT, KC_COMMA, KC_SCLN);

// S(KC_DOT) -> KC_COLN
const key_override_t dot_coln_ko = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_COLN);

// S(KC_EXLM) -> KC_QUES
const key_override_t exlm_ques_ko = ko_make_basic(MOD_MASK_SHIFT, KC_EXLM, KC_QUES);

const key_override_t **key_overrides = (const key_override_t *[]) {
  &spc_ent_ko,
  &bsp_unds_ko,
  &comma_scln_ko,
  &dot_coln_ko,
  &exlm_ques_ko,
  NULL
};


// --- PROCESS ---

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool ret = true;

  mods_state = get_mods();
  oneshot_mods_state = get_oneshot_mods();

  // TAP(NUM_ACT)
  if (keycode == NUM_ACT && record->event.pressed && record->tap.count > 0) {
    layer_on(ACT);
    ret = false;
  }

  // TAP(SFT_ABC)
  if (keycode == SFT_ABC && record->event.pressed && record->tap.count > 0) {
    layer_clear();
    ret = false;
  }

  // _RSTMOD
  else if (keycode == _RSTMOD && record->event.pressed) {
    clear_oneshot_mods();
    ret = false;
  }

  // TAP(_OSFT)
  else if (keycode == _OSFT && record->event.pressed && record->tap.count > 0) {
    set_oneshot_mods(MOD_BIT(KC_LSFT) | oneshot_mods_state);
    ret = false;
  }

  // TAP(_OGUI)
  else if (keycode == _OGUI && record->event.pressed && record->tap.count > 0) {
    set_oneshot_mods(MOD_BIT(KC_LGUI) | oneshot_mods_state);
    ret = false;
  }

  else if (keycode == XMOD) {
    if (record->event.pressed) {
      layer_on(ACT);
      set_oneshot_layer(ACT, ONESHOT_START);
    } else {
      set_oneshot_layer(ACT, ONESHOT_PRESSED);
    }

    ret = false;
  }

  // TAP(_OALT)
  else if (keycode == _OALT && record->event.pressed && record->tap.count > 0) {
    set_oneshot_mods(MOD_BIT(KC_LALT) | oneshot_mods_state);
    ret = false;
  }

  // TAP(_OCTL)
  else if (keycode == _OCTL && record->event.pressed && record->tap.count > 0) {
    set_oneshot_mods(MOD_BIT(KC_LCTL) | oneshot_mods_state);
    ret = false;
  }

  // SYM: DTIL
  else if (keycode == _S_TIL && record->event.pressed && record->tap.count > 0) {
    tap_code16(_DTIL);
    layer_off(SYM);
    ret = false;
  }

  // SYM: ACUT
  else if (keycode == _G_ACU && record->event.pressed && record->tap.count > 0) {
    tap_code16(_ACUT);
    layer_off(SYM);
    ret = false;
  }

  // SYM: DCIR
  else if (keycode == _A_CIR && record->event.pressed && record->tap.count > 0) {
    tap_code16(_DCIR);
    layer_off(SYM);
    ret = false;
  }

  // SYM: DGRV
  else if (keycode == _C_GRV && record->event.pressed && record->tap.count > 0) {
    tap_code16(_DGRV);
    layer_off(SYM);
    ret = false;
  }

  // SYM: PIPE
  else if (keycode == _PIPE && record->event.pressed) {
    tap_code16(KC_PIPE);
    tap_code16(KC_RABK);
    ret = false;
  }

  // _ARROW
  else if (keycode == _ARROW && record->event.pressed) {
    tap_code(KC_MINS);
    tap_code16(KC_RABK);
    ret = false;
  }

  // _ARROW2
  else if (keycode == _ARROW2 && record->event.pressed) {
    tap_code16(KC_EQL);
    tap_code16(KC_RABK);
    ret = false;
  }

  // _CURDIR
  else if (keycode == _CURDIR && record->event.pressed) {
    tap_code16(KC_DOT);
    tap_code16(KC_SLSH);
    ret = false;
  }

  // _HOMDIR
  else if (keycode == _HOMDIR && record->event.pressed) {
    tap_code16(KC_TILD);
    tap_code16(KC_SLSH);
    ret = false;
  }

  // _PRVDIR
  else if (keycode == _PRVDIR && record->event.pressed) {
    tap_code16(KC_DOT);
    tap_code16(KC_DOT);
    tap_code16(KC_SLSH);
    ret = false;
  }

  return ret;
}


// --- TAPPING OVERRIDES ---


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
