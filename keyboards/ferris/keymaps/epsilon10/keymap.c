#include QMK_KEYBOARD_H


enum layers {
  ABC,
  SYM,
  ACT,
  FUN,
};


// Custom keys.
enum keycodes {
  FUN_C_FAKE = SAFE_RANGE,
  FUN_A_FAKE,
  FUN_G_FAKE,
  FUN_S_FAKE,

  SYM_C_FAKE,
  SYM_A_FAKE,
  SYM_G_FAKE,
  SYM_S_FAKE,

  REPEAT,
  RSTMOD,
};


// c, ç
#define MY_C LT(0, KC_C) // intercepted in process_record_user


// One-shot mods
#define OSCTL OSM(MOD_BIT(KC_LCTL))
#define OSALT OSM(MOD_BIT(KC_LALT))
#define OSGUI OSM(MOD_BIT(KC_LGUI))
#define OSSFT OSM(MOD_BIT(KC_LSFT))


// Thumb keys
#define ACT_SPC LT(ACT, KC_SPC)
#define SFT_SPC MT(MOD_LSFT, KC_SPC)
#define SYM_ENT LT(SYM, KC_ENT)
#define FUN_BSP LT(FUN, KC_BSPC)


// ACT keys
#define UNDO G(KC_Z)
#define REDO S(G(KC_Z))
#define COPY G(KC_C)
#define PASTE G(KC_V)
#define CUT G(KC_X)
#define VOLU KC__VOLUP
#define VOLD KC__VOLDOWN
#define MUTE KC__MUTE
#define BACK G(KC_LBRC)
#define FRWD G(KC_RBRC)
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


// KEYMAP
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [ABC] = LAYOUT(
       KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                      KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT,
       KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                      KC_H,    KC_N,    KC_E,    KC_I,    KC_O,
       KC_Z,    KC_X,    MY_C,    KC_V,    KC_B,                      KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_EXLM,
                                        ACT_SPC, KC_LSFT,    SYM_ENT, FUN_BSP
  ),

  [ACT] = LAYOUT(
     RSTMOD,  KC_ESC,    BACK,    FRWD, XXXXXXX,                      KC_PGUP, STAB,    KC_UP,   KC_TAB,  KC_HOME,
      OSCTL,   OSALT,   OSGUI,   OSSFT,  REPEAT,                      KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,
       UNDO,     CUT,    COPY,   PASTE,    REDO,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                        _______, XXXXXXX,     KC_ENT, KC_BSPC
  ),

  [SYM] = LAYOUT(
     KC_GRV,    KC_1,    KC_2,    KC_3, KC_PLUS,                      KC_HASH, KC_LCBR, KC_DLR,  KC_RCBR, KC_TILD,
       KC_0,    KC_4,    KC_5,    KC_6, KC_MINS,                      KC_ASTR, SYM_S,   SYM_G,   SYM_A,   SYM_C,
    KC_BSLS,    KC_7,    KC_8,    KC_9, KC_SLSH,                      KC_AMPR, KC_LT,   KC_PIPE, KC_GT,   KC_CIRC,
                                        KC_LBRC, KC_RBRC,    _______, XXXXXXX
  ),

  [FUN] = LAYOUT(
    XXXXXXX,   KC_F1,   KC_F2,   KC_F3,  KC_F10,                      DM_REC1, MUTE,    VOLD,    VOLU,   XXXXXXX,
     KC_PWR,   KC_F4,   KC_F5,   KC_F6,  KC_F11,                      DM_RSTP, FUN_S,   FUN_G,   FUN_A,   FUN_C,
      RESET,   KC_F7,   KC_F8,   KC_F9,  KC_F12,                      DM_PLY1, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX,
                                         KC_SPC, XXXXXXX,    XXXXXXX, _______
  )
};


// KEY OVERRIDES

// S(FUN_BSP) -> KC_UNDS
const key_override_t unds_key_override = ko_make_basic(MOD_MASK_SHIFT, FUN_BSP, KC_UNDS);

// S(FUN_BSP) -> KC_EQL
const key_override_t at_key_override = ko_make_basic(MOD_MASK_SHIFT, SYM_ENT, KC_EQL);

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


// REPEAT

// Used to extract the basic tapping keycode from a dual-role key.
// Example: GET_TAP_KC(MT(MOD_RSFT, KC_E)) == KC_E
#define GET_TAP_KC(dual_role_key) dual_role_key & 0xFF

uint16_t last_tap = KC_NO;
uint8_t last_modifier = 0;
uint8_t mods_state = 0;
uint8_t oneshot_mods_state = 0;

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


// PROCESS KEYS

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

  mods_state = get_mods();
  oneshot_mods_state = get_oneshot_mods();

  // RSTMOD
  if (keycode == RSTMOD && record->event.pressed) {
    clear_oneshot_mods();
    ret = false;
  }

  // MY_C
  else if (keycode == MY_C && record->event.pressed) {
    if (record->tap.count > 0) { // tap
      tap_code(KC_C);
    } else { // hold
      tap_code16(A(KC_C));
    }
    ret = false;
  }

  // FUN_S: ã
  else if (keycode == FUN_S && record->event.pressed && record->tap.count > 0) {
    tap_code16(DTIL);
    layer_off(FUN);
    ret = false;
  }

  // FUN_G: é
  else if (keycode == FUN_G && record->event.pressed && record->tap.count > 0) {
    tap_code16(ACUT);
    layer_off(FUN);
    ret = false;
  }

  // FUN_A: ô
  else if (keycode == FUN_A && record->event.pressed && record->tap.count > 0) {
    tap_code16(DCIR);
    layer_off(FUN);
    ret = false;
  }

  // FUN_C: à
  else if (keycode == FUN_C && record->event.pressed && record->tap.count > 0) {
    tap_code16(DGRV);
    layer_off(FUN);
    ret = false;
  }

  // SYM_C: ~
  else if (keycode == SYM_C && record->event.pressed && record->tap.count > 0) {
    tap_code16(KC_AT);
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

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        default:
            return true;
    }
}
