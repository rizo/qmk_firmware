#include QMK_KEYBOARD_H


enum layers {
  EP_TY,
  EP_SY,
  EP_NM,
  EP_DO,
  EP_MD,
  EP_FN,
  EP_GM
};


// Custom keys.
enum keycodes {
  EP_DOSP_FAKE = SAFE_RANGE,
  EP_PLUS_FAKE,

  EP_SY_C_FAKE,
  EP_SY_A_FAKE,
  EP_SY_G_FAKE,
  EP_SY_S_FAKE,

  EP_OS_C,
  EP_OS_A,
  EP_OS_G,
  EP_OS_S,

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
  .trigger = EP_OS_C,
  .mod = MOD_BIT(KC_LCTL),
  .timer = 0,
};
oslm_state_t oslm_a = {
  .trigger = EP_OS_A,
  .mod = MOD_BIT(KC_LALT),
  .timer = 0,
};
oslm_state_t oslm_g = {
  .trigger = EP_OS_G,
  .mod = MOD_BIT(KC_LGUI),
  .timer = 0,
};
oslm_state_t oslm_s = {
  .trigger = EP_OS_S,
  // HACK: R is used to overcome the count>1 issue (see journal).
  .mod = MOD_BIT(KC_RSFT),
  .timer = 0,
};


// TY: thumb keys
#define EP_DOSP LT(EP_DO, EP_DOSP_FAKE)
#define EP_SYEN LT(EP_SY, KC_ENT)
#define EP_FNBS LT(EP_FN, KC_BSPC)
#define EP_LBRC LT(EP_DO, KC_LBRC)
#define EP_RBRC SFT_T(KC_RBRC)

// FN: one-shot keys
#define EP_FN_G OSM(MOD_LGUI)
#define EP_FN_A OSM(MOD_LALT)
#define EP_FN_C OSM(MOD_LCTL)
#define EP_FN_S OSM(MOD_LSFT)

// SY: mod tap
#define EP_SY_G GUI_T(EP_SY_G_FAKE)
#define EP_SY_A ALT_T(EP_SY_A_FAKE)
#define EP_SY_C CTL_T(EP_SY_C_FAKE)
#define EP_SY_S SFT_T(EP_SY_S_FAKE)

// DO: shortcuts
#define EP_UNDO C(KC_Z)
#define EP_REDO S(C(KC_Z))
#define EP_COPY C(KC_C)
#define EP_PSTE C(KC_V)
#define EP_CUT C(KC_X)
#define EP_BACK KC_WBAK
#define EP_FRWD KC_WFWD
#define EP_STAB S(KC_TAB)
#define EP_WDL C(KC_LEFT)
#define EP_WDR C(KC_RIGHT)
#define EP_FLUP C(KC_HOME)
#define EP_FLDW C(KC_END)
#define EP_LNLF KC_HOME
#define EP_LNRT KC_END

// International keys (linux)
#define EP_CEDL RALT(KC_COMM)
#define EP_GBP A(KC_3)
#define EP_EUR S(A(KC_2))

// International keys (macos)
/* #define EP_CEDL A(KC_C) */

// Dead accent keys (linux)
#define EP_DTIL RALT(S(KC_GRV))
#define EP_ACUT RALT(KC_QUOT)
#define EP_DCIR RALT(KC_6)
#define EP_DGRV RALT(KC_GRV)

// Dead accent keys (macos)
// #define EP_DTIL A(KC_N)
// #define EP_ACUT A(KC_E)
// #define EP_DCIR A(KC_I)
// #define EP_DGRV A(KC_GRV)

// KEYMAP
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [EP_TY] = LAYOUT(
       KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                      KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT,
       KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                      KC_H,    KC_N,    KC_E,    KC_I,    KC_O,
       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_EXLM,
                                        EP_DOSP, KC_LSFT,    EP_SYEN, EP_FNBS
  ),

  [EP_DO] = LAYOUT(
     REPEAT,  KC_ESC, EP_BACK, EP_FRWD, KC_WH_U,                      KC_PGUP, EP_STAB, KC_UP,   KC_TAB,  EP_FLUP,
    EP_OS_G, EP_OS_A, EP_OS_C, EP_OS_S, KC_WH_D,                      KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, EP_FLDW,
    EP_UNDO,  EP_CUT, EP_COPY, EP_PSTE, EP_REDO,                      XXXXXXX, EP_LNLF, KC_ESC,  EP_LNRT, XXXXXXX,
                                        _______, XXXXXXX,     KC_ENT, KC_BSPC
  ),

  [EP_MD] = LAYOUT(
       KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                      KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT,
       KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                      KC_H,    KC_N,    KC_E,    KC_I,    KC_O,
       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SCLN,
                                        _______, XXXXXXX,     KC_ENT, KC_SPC
  ),

  [EP_SY] = LAYOUT(
     KC_GRV,   KC_1,     KC_2,    KC_3,  KC_EQL,                      KC_ASTR, KC_LCBR, KC_DLR,  KC_RCBR, KC_CIRC,
       KC_0,   KC_4,     KC_5,    KC_6, KC_MINS,                      KC_PLUS, EP_SY_S, EP_SY_C, EP_SY_A, EP_SY_G,
    KC_BSLS,   KC_7,     KC_8,    KC_9, KC_SLSH,                      KC_PERC, KC_LABK, KC_PIPE, KC_RABK, KC_AMPR,
                                        EP_LBRC, EP_RBRC,    _______, XXXXXXX
  ),

  [EP_FN] = LAYOUT(
     KC_PWR,   KC_F1,   KC_F2,  KC_F3,   KC_F10,                      DM_REC1, KC_MUTE, KC_VOLD, KC_VOLU, TO(EP_GM),
    KC_PSCR,   KC_F4,   KC_F5,  KC_F6,   KC_F11,                      DM_RSTP, EP_FN_S, EP_FN_C, EP_FN_A, EP_FN_G,
     KC_INS,   KC_F7,   KC_F8,  KC_F9,   KC_F12,                      DM_PLY1, KC_MPRV, KC_MPLY, KC_MNXT, EP_CEDL,
                                         KC_SPC, KC_CAPS,    XXXXXXX, _______
  ),

  [EP_GM] = LAYOUT(
    KC_ESC,     KC_Q,    KC_W,   KC_E,     KC_R,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TO(EP_TY),
   KC_LSFT,     KC_A,    KC_S,   KC_D,     KC_F,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   KC_LCTL,     KC_Z,    KC_X,   KC_C,     KC_V,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                         KC_SPC,  KC_TAB,    XXXXXXX, XXXXXXX
  )
};


// KEY OVERRIDES

// S(EP_FNBS) -> KC_UNDS
const key_override_t unds_ko = ko_make_basic(MOD_BIT(KC_LSFT), EP_FNBS, KC_UNDS);

// S(EP_SYEN) -> KC_AT
const key_override_t at_ko = ko_make_basic(MOD_BIT(KC_LSFT), EP_SYEN, KC_AT);

// S(KC_COMMA) -> KC_SCLN
const key_override_t scln_ko = ko_make_basic(MOD_BIT(KC_LSFT), KC_COMMA, KC_SCLN);

// S(KC_DOT) -> KC_COLN
const key_override_t coln_ko = ko_make_basic(MOD_BIT(KC_LSFT), KC_DOT, KC_COLN);

// S(KC_EXLM) -> KC_QUES
const key_override_t ques_ko = ko_make_basic(MOD_BIT(KC_LSFT), KC_EXLM, KC_QUES);

// S(KC_BSPC) -> KC_DEL
const key_override_t sbsp_ko = _ko_make_strict_negmods(MOD_BIT(KC_RSFT), KC_BSPC, KC_DEL, MOD_BIT(KC_LGUI));

// A(KC_DEL) -> C(KC_K)
const key_override_t c_k_ko = _ko_make_strict(MOD_BIT(KC_LALT), KC_DEL, C(KC_K));

const key_override_t **key_overrides = (const key_override_t *[]) {
  &unds_ko,
  &at_ko,
  &scln_ko,
  &coln_ko,
  &ques_ko,
  &c_k_ko,
  &sbsp_ko,
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
    // clear held mod
    unregister_mods(oslm_state->mod);

    // released: check if it's a tap
    if (timer_elapsed(oslm_state->timer) < TAPPING_TERM) {
      // tap: keep all current mods and set oneshot layer
      set_oneshot_mods(mods);
      set_oneshot_layer(EP_MD, ONESHOT_START);
    }
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
    case EP_DOSP:
      if (record->event.pressed && record->tap.count > 0) {
        tap_code16(KC_SPC);
      }
      // Intercept hold release to clear OSM/OSLM state.
      else if (!record->event.pressed && record->tap.count == 0) {
        layer_clear();
        clear_oneshot_mods();
        unregister_mods(mods_state);
        ret = true;
      } else {
        ret = true;
      }
      break;

    // DO: OS_C
    case EP_OS_C:
      process_osml(&oslm_c, keycode, record);
      break;

    // DO: OS_A
    case EP_OS_A:
      process_osml(&oslm_a, keycode, record);
      break;

    // DO: OS_G
    case EP_OS_G:
      process_osml(&oslm_g, keycode, record);
      break;

    // DO: OS_S
    case EP_OS_S:
      process_osml(&oslm_s, keycode, record);
      break;

    // BEGIN SY MT
    case EP_SY_S:
      if (record->event.pressed && record->tap.count > 0) {
        tap_code16(KC_LPRN);
      } else {
        ret = true;
      }
      break;

    case EP_SY_C:
      if (record->event.pressed && record->tap.count > 0) {
        tap_code16(KC_HASH);
      } else {
        ret = true;
      }
      break;

    case EP_SY_A:
      if (record->event.pressed && record->tap.count > 0) {
        tap_code16(KC_RPRN);
      } else {
        ret = true;
      }
      break;

    case EP_SY_G:
      if (record->event.pressed && record->tap.count > 0) {
        tap_code16(KC_TILD);
      } else {
        ret = true;
      }
      break;
    // END SY MT

    // BEGIN FN MT
    case EP_FN_S:
      if (record->event.pressed && record->tap.count > 0) {
        tap_code16(EP_DTIL);
        layer_clear();
      } else {
        ret = true;
      }
      break;

    case EP_FN_C:
      if (record->event.pressed && record->tap.count > 0) {
        tap_code16(EP_ACUT);
        layer_clear();
      } else {
        ret = true;
      }
      break;

    case EP_FN_A:
      if (record->event.pressed && record->tap.count > 0) {
        tap_code16(EP_DCIR);
        layer_clear();
      } else {
        ret = true;
      }
      break;

    case EP_FN_G:
      if (record->event.pressed && record->tap.count > 0) {
        tap_code16(EP_DGRV);
        layer_clear();
      } else {
        ret = true;
      }
      break;
    // END FN MT

    // BEGIN SYMBOL SHORTCUTS
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
    // END SYMBOL SHORTCUTS

    default:
      // Clear current OSLM layer state.
      if (IS_LAYER_ON(EP_MD) && record->event.pressed) {
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
    // case EP_SYSP: return 200;
    default: return 0;
  }
}
