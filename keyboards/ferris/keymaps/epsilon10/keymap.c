#include QMK_KEYBOARD_H


enum layers {
  ABC,
  SYM,
  NUM,
  ACT,
  MOD,
  FUN,
};


// Custom keys.
enum keycodes {
  SYM_FAKE = SAFE_RANGE,

  EP_AC_C_FAKE,
  EP_AC_A_FAKE,
  EP_AC_G_FAKE,
  EP_AC_S_FAKE,

  NUM_C_FAKE,
  NUM_A_FAKE,
  NUM_G_FAKE,
  NUM_S_FAKE,

  OSLM_C,
  OSLM_A,
  OSLM_G,
  OSLM_S,

  // SHORTCUTS
  EP_PIPB, // <|
  EP_PIPF, // |>
  EP_ARR1, // ->
  EP_ARR2, // =>
  EP_CURD, // ./
  EP_PARD, // ../
  EP_HOMD, // ~/
  
  EP_MENU,

  REPEAT,
};


typedef struct {
  uint16_t trigger;
  uint16_t mod;
  uint16_t timer;
} oslm_state_t;

oslm_state_t oslm_c = {
  .trigger = OSLM_C,
  .mod = MOD_BIT(KC_LCTL),
  .timer = 0,
};
oslm_state_t oslm_a = {
  .trigger = OSLM_A,
  .mod = MOD_BIT(KC_LALT),
  .timer = 0,
};
oslm_state_t oslm_g = {
  .trigger = OSLM_G,
  .mod = MOD_BIT(KC_LGUI),
  .timer = 0,
};
oslm_state_t oslm_s = {
  .trigger = OSLM_S,
  // HACK: R is used to overcome the count>1 issue (see journal).
  .mod = MOD_BIT(KC_RSFT),
  .timer = 0,
};


// Thumb keys
#define ACT_SPC LT(ACT, KC_SPC)
#define NUM_SFT LT(NUM, KC_NO)
#define SYM_ENT LT(SYM, KC_ENT)
#define FUN_BSP LT(FUN, KC_BSPC)

#define EP_OS_C OSM(MOD_LCTL)
#define EP_OS_A OSM(MOD_LALT)
#define EP_OS_G OSM(MOD_LGUI)
#define EP_OS_S OSM(MOD_LSFT)

// ACT keys
#define UNDO G(KC_Z)
#define REDO S(G(KC_Z))
#define COPY G(KC_C)
#define PASTE G(KC_V)
#define CUT G(KC_X)
#define EP_BACK G(KC_LBRC)
#define EP_FRWD G(KC_RBRC)
#define EP_STAB S(KC_TAB)


// Mods with accent keys
#define EP_AC_C CTL_T(EP_AC_C_FAKE)
#define EP_AC_A ALT_T(EP_AC_A_FAKE)
#define EP_AC_G GUI_T(EP_AC_G_FAKE)
#define EP_AC_S SFT_T(EP_AC_S_FAKE)


// NUM intl keys
#define EP_CEDL A(KC_C)
#define EP_GBP A(KC_3)
#define EP_EUR S(A(KC_2))


// Dead accent keys
#define EP_DTIL A(KC_N)
#define EP_ACUT A(KC_E)
#define EP_DCIR A(KC_I)
#define EP_DGRV A(KC_GRV)

// Nav
#define EP_WDL A(KC_LEFT)
#define EP_WDR A(KC_RIGHT)
#define EP_LNL G(KC_LEFT)
#define EP_LNR G(KC_RIGHT)


// KEYMAP
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [ABC] = LAYOUT(
       KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                      KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT,
       KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                      KC_H,    KC_N,    KC_E,    KC_I,    KC_O,
       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_EXLM,
                                        ACT_SPC, NUM_SFT,    SYM_ENT, FUN_BSP
  ),

  [ACT] = LAYOUT(
    EP_MENU,  KC_ESC, EP_BACK, EP_FRWD, KC_WH_U,                      KC_PGUP, EP_STAB, KC_UP,   KC_TAB, KC_HOME,
     OSLM_C,  OSLM_A,  OSLM_G,  OSLM_S, KC_WH_D,                      KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,
       UNDO,     CUT,    COPY,   PASTE,    REDO,                      XXXXXXX, XXXXXXX, REPEAT,  XXXXXXX, XXXXXXX,
                                        _______, XXXXXXX,     KC_ENT, KC_BSPC
  ),

  [MOD] = LAYOUT(
       KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                      KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT,
       KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                      KC_H,    KC_N,    KC_E,    KC_I,    KC_O,
       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_EXLM,
                                        ACT_SPC, NUM_SFT,     KC_ENT, KC_SPC
  ),

  [NUM] = LAYOUT(
    EP_PIPB, EP_PIPF, EP_ARR1, EP_ARR2, EP_HOMD,                      KC_PLUS, KC_1,    KC_2,    KC_3,    KC_CIRC,
    KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, EP_CURD,                      KC_MINS, KC_4,    KC_5,    KC_6,    KC_0,
    XXXXXXX,  EP_GBP, EP_CEDL,  EP_EUR, EP_PARD,                      KC_ASTR, KC_7,    KC_8,    KC_9,    KC_SLSH,
                                        XXXXXXX, _______,    KC_EQL,  KC_SPC
  ),

  [SYM] = LAYOUT(
     KC_GRV,   KC_AT, KC_LCBR, KC_RCBR, KC_HASH,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_TILD, KC_PIPE, KC_LPRN, KC_RPRN, KC_PERC,                      XXXXXXX, EP_AC_S, EP_AC_G, EP_AC_A, EP_AC_C,
    KC_BSLS,  KC_DLR, KC_LBRC, KC_RBRC, KC_AMPR,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                        KC_LABK, KC_RABK,    _______, XXXXXXX
  ),

  [FUN] = LAYOUT(
      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                      DM_REC1, KC_MUTE, KC_VOLD, KC_VOLU, QK_RBT,
      KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,                      DM_RSTP, EP_OS_S, EP_OS_G, EP_OS_A, EP_OS_C,
     KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,                      DM_PLY1, KC_MPRV, KC_MPLY, KC_MNXT, QK_BOOT,
                                         KC_SPC,  KC_PWR,    XXXXXXX, _______
  )
};


// KEY OVERRIDES

// S(FUN_BSP) -> KC_UNDS
const key_override_t unds_key_override = ko_make_basic(MOD_BIT(KC_LSFT), FUN_BSP, KC_UNDS);
const key_override_t unds2_key_override = ko_make_basic(MOD_BIT(KC_LSFT), KC_SPC, KC_UNDS);

// S(SYM_ENT) -> KC_EQL
const key_override_t eql_key_override = ko_make_basic(MOD_BIT(KC_LSFT), SYM_ENT, KC_EQL);
const key_override_t eql2_key_override = ko_make_basic(MOD_BIT(KC_LSFT), KC_ENT, KC_EQL);

// S(KC_COMMA) -> KC_SCLN
const key_override_t scln_key_override = ko_make_basic(MOD_BIT(KC_LSFT), KC_COMMA, KC_SCLN);

// S(KC_DOT) -> KC_COLN
const key_override_t coln_key_override = ko_make_basic(MOD_BIT(KC_LSFT), KC_DOT, KC_COLN);

// S(KC_EXLM) -> KC_QUES
const key_override_t ques_key_override = ko_make_basic(MOD_BIT(KC_LSFT), KC_EXLM, KC_QUES);

// S(KC_BSPC) -> KC_DEL
const key_override_t sbsp_key_override = _ko_make_strict_negmods(MOD_BIT(KC_RSFT), KC_BSPC, KC_DEL, MOD_BIT(KC_LGUI));

// G(S(KC_BSPC)) -> C(KC_K)
const key_override_t gsbsp_key_override = _ko_make_strict(MOD_BIT(KC_LGUI) | MOD_BIT(KC_RSFT), KC_BSPC, C(KC_K));

// G(KC_DEL) -> C(KC_K)
const key_override_t gdel_key_override = _ko_make_strict(MOD_BIT(KC_LGUI), KC_DEL, C(KC_K));

const key_override_t **key_overrides = (const key_override_t *[]) {
  &unds_key_override,
  &unds2_key_override,
  &eql_key_override,
  &eql2_key_override,
  &scln_key_override,
  &coln_key_override,
  &ques_key_override,
  &sbsp_key_override,
  &gsbsp_key_override,
  &gdel_key_override,
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

// OSLM

void process_osml(oslm_state_t *oslm_state, uint16_t keycode, keyrecord_t *record) {
  static uint16_t mods = 0;
  if (record->event.pressed) {
    // init: init timer, register trigger mod
    oslm_state->timer = timer_read();
    register_mods(oslm_state->mod);
    // get mods at the time of pressed event.
    mods = get_mods();
  } else {
    // released: check if it's a tap or hold
    if (timer_elapsed(oslm_state->timer) < TAPPING_TERM) {
      // tap: keep all current mods and set oneshot layer
      set_oneshot_mods(mods);
      set_oneshot_layer(MOD, ONESHOT_START);
    }

    // clear mod
    unregister_mods(oslm_state->mod);
  }
}


// PROCESS KEYS

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
  uprintf("%u, %u: k=0x%04X #%u l=%u p=%b m=0x%02X M=0x%02X\n",
    record->event.key.row,
    record->event.key.col,
    keycode,
    record->tap.count,
    get_highest_layer(layer_state),
    record->event.pressed,
    get_mods(),
    get_oneshot_mods()
  );
#endif
  bool ret = false;

  mods_state = get_mods();
  oneshot_mods_state = get_oneshot_mods();

  switch (keycode) {
    // Intercept hold release to clear OSM/OSLM state.
    case ACT_SPC:
      if (record->tap.count == 0 && !record->event.pressed) {
        clear_oneshot_mods();
        layer_clear();
      }
      ret = true;
      break;

    case OSLM_C:
      process_osml(&oslm_c, keycode, record);
      break;

    case OSLM_A:
      process_osml(&oslm_a, keycode, record);
      break;

    case OSLM_G:
      process_osml(&oslm_g, keycode, record);
      break;

    case OSLM_S:
      process_osml(&oslm_s, keycode, record);
      break;

    case NUM_SFT:
      if (record->tap.count == 0) {
        ret = true;
      } else if (record->tap.count == 1) {
        if (record->event.pressed) {
          set_oneshot_mods(MOD_BIT(KC_LSFT));
        }
      } else {
        if (record->event.pressed) {
          clear_oneshot_mods();
          layer_on(MOD);
          register_mods(MOD_BIT(KC_LSFT));
        } else {
          unregister_mods(MOD_BIT(KC_LSFT));
          layer_off(MOD);
        }
      }
      break;

    case EP_AC_C:
      if (record->event.pressed && record->tap.count > 0) {
        tap_code16(EP_DGRV);
        layer_clear();
      }
      break;

    case EP_AC_A:
      if (record->event.pressed && record->tap.count > 0) {
        tap_code16(EP_DCIR);
        layer_clear();
      }
      break;

    case EP_AC_G:
      if (record->event.pressed && record->tap.count > 0) {
        tap_code16(EP_ACUT);
        layer_clear();
      }
      break;

    case EP_AC_S:
      if (record->event.pressed && record->tap.count > 0) {
        tap_code16(EP_DTIL);
        layer_clear();
      }
      break;

    case EP_PIPB:
      if (record->event.pressed) {
        SEND_STRING("<|");
      }
      break;

    case EP_PIPF:
      if (record->event.pressed) {
        SEND_STRING("|>");
      }
      break;

    case EP_ARR1:
      if (record->event.pressed) {
        SEND_STRING("->");
      }
      break;

    case EP_ARR2:
      if (record->event.pressed) {
        SEND_STRING("=>");
      }
      break;

    case EP_CURD:
      if (record->event.pressed) {
        SEND_STRING("./");
      }
      break;

    case EP_PARD:
      if (record->event.pressed) {
        SEND_STRING("../");
      }
      break;

    case EP_HOMD:
      if (record->event.pressed) {
        SEND_STRING("~/");
      }
      break;

    case EP_MENU:
      if (record->event.pressed) {
        tap_code16(C(KC_F2));
        tap_code(KC_RIGHT);
        tap_code(KC_DOWN);
      }
      break;

    default:
      // Clear current OSLM state.
      if (IS_LAYER_ON(MOD) && record->event.pressed) {
        clear_oneshot_layer_state(ONESHOT_PRESSED);
      }

      ret = true;
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


// Prevent tap key repeat on second quick tap.
// https://docs.qmk.fm/#/tap_hold?id=quick-tap-term
uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case NUM_SFT: return 200;
    default: return 0;
  }
}
