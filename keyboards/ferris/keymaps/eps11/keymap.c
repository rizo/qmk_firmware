#include QMK_KEYBOARD_H

enum layers {
  EP_TY,
  EP_DO,
  EP_MD,
  EP_SY,
  EP_FN
};


// Custom keys.
enum keycodes {
  EP_DOSP_FAKE = SAFE_RANGE,
  EP_SYSF_FAKE,
  EP_PLUS_FAKE,

  EP_DOUN_FAKE,

  EP_SY_C_FAKE,
  EP_SY_A_FAKE,
  EP_SY_G_FAKE,
  EP_SY_S_FAKE,

  EP_OS_C,
  EP_OS_A,
  EP_OS_G,
  EP_OS_S,

  // SHORTCUTS
  EP_CURD, // ./
  EP_PARD, // ../
  EP_HOMD, // ~/

  EP_MENU,

  REPEAT,
};

// One-Shot Layer-Mod (OLSM)
// =========================
//
// **Faster access to alphas**
// No need to release the layer key to access alphas. Alphas are immediately
// available after tapping the OSLM key. Once the one-shot is fired, you're
// back to the layer. This allows for much faster activation of multiple
// consecutive mod shortcuts.
//
// **Easier activation**
// To activate multiple OLSM keys, they can be tapped quickly all at once, or
// they can be sequentially (and as slowly as desired) held and activated by
// tapping the last OSLM key. As long as the last OSLM key is tapped, all held
// OLSM keys will be activated as one-shot.
//
// **Hold OSLM for regular mods**
// Holding the OSLM key produces a regular modifier activation. This permits
// using OSLM keys for shortcuts on the layer they are placed on.
//
// **Consistent deactivation**
// When the layer key is released, all OSLM keys are released. There is no
// timer, no special cancelation key. Just release the layer key and the
// state is reset.

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


// DO: thumb keys
#define EP_DOSP LT(EP_DO, KC_SPC)
#define EP_SYEN LT(EP_SY, KC_ENT)
#define EP_SFEN SFT_T(KC_ENT)
#define EP_FNBS LT(EP_FN, KC_BSPC)

#define EP_LBRC LT(EP_DO, KC_LBRC)
#define EP_RBRC SFT_T(KC_RBRC)

// FN: one-shot mods
#define EP_FN_G OSM(MOD_RGUI)
#define EP_FN_A OSM(MOD_RALT)
#define EP_FN_C OSM(MOD_RCTL)
#define EP_FN_S OSM(MOD_RSFT)

// SY: mod tap placeholders
#define EP_SY_G GUI_T(EP_SY_G_FAKE)
#define EP_SY_A MT(MOD_RALT, EP_SY_A_FAKE)
#define EP_SY_C CTL_T(EP_SY_C_FAKE)
#define EP_SY_S SFT_T(EP_SY_S_FAKE)

// Shortcuts
#define EP_UNDO C(KC_Z)
#define EP_REDO S(C(KC_Z))
#define EP_COPY KC_COPY
#define EP_PSTE KC_PSTE
#define EP_CUT KC_CUT
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

// Dead accent keys (linux)
#define EP_DTIL RALT(S(KC_GRV))
#define EP_ACUT RALT(KC_QUOT)
#define EP_DCIR RALT(KC_6)
#define EP_DGRV RALT(KC_GRV)


// #define ENABLE_HOME_ROW_MODS

#ifdef ENABLE_HOME_ROW_MODS
#define EP_A GUI_T(KC_A)
#define EP_R ALT_T(KC_R)
#define EP_S CTL_T(KC_S)
#define EP_T SFT_T(KC_T)
#define EP_N SFT_T(KC_N)
#define EP_E CTL_T(KC_E)
#define EP_I ALT_T(KC_I)
#define EP_O GUI_T(KC_O)
#else
#define EP_A KC_A
#define EP_R KC_R
#define EP_S KC_S
#define EP_T KC_T
#define EP_N KC_N
#define EP_E KC_E
#define EP_I KC_I
#define EP_O KC_O
#endif

// KEYMAP
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [EP_TY] = LAYOUT(
       KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                   KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT,
       EP_A,    EP_R,    EP_S,    EP_T,    KC_D,                   KC_H,    EP_N,    EP_E,    EP_I,    EP_O,
       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                   KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_EXLM,
                                        EP_DOSP, EP_SYEN, EP_SFEN, EP_FNBS
  ),

  [EP_DO] = LAYOUT(
     REPEAT,  KC_ESC, EP_BACK, EP_FRWD, KC_WH_U,                   KC_PGUP, EP_WDL,  KC_UP,   EP_WDR,  EP_FLUP,
    EP_OS_G, EP_OS_A, EP_OS_C, EP_OS_S, KC_WH_D,                   EP_LNLF, KC_LEFT, KC_DOWN, KC_RGHT, EP_LNRT,
    EP_UNDO,  EP_CUT, EP_COPY, EP_PSTE, EP_REDO,                   KC_PGDN, EP_STAB, KC_ESC,  KC_TAB,  EP_FLDW,
                                        _______, _______, KC_ENT,  KC_BSPC
  ),

  [EP_MD] = LAYOUT(
       KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                   KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT,
       KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                   KC_H,    KC_N,    KC_E,    KC_I,    KC_O,
       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                   KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SCLN,
                                        _______, XXXXXXX, KC_ENT,  KC_BSPC
  ),

  [EP_SY] = LAYOUT(
    KC_CIRC, KC_HASH, KC_LCBR, KC_RCBR, KC_ASTR,                      KC_EQL,  KC_1,    KC_2,    KC_3,    KC_GRV,
    EP_SY_G, EP_SY_A, EP_SY_C, EP_SY_S, KC_PLUS,                      KC_MINS, KC_4,    KC_5,    KC_6,    KC_0,
    KC_AMPR, KC_PIPE, KC_LABK, KC_RABK, KC_PERC,                      KC_SLSH, KC_7,    KC_8,    KC_9,    KC_BSLS,
                                        _______, _______,    EP_LBRC, EP_RBRC
  ),

  [EP_FN] = LAYOUT(
     KC_PWR,   KC_F1,   KC_F2,   KC_F3,  KC_F10,                   DM_REC1, KC_MUTE, KC_VOLD, KC_VOLU, KC_CAPS,
     KC_INS,   KC_F4,   KC_F5,   KC_F6,  KC_F11,                   DM_RSTP, EP_FN_S, EP_FN_C, EP_FN_A, EP_FN_G,
    QK_BOOT,   KC_F7,   KC_F8,   KC_F9,  KC_F12,                   DM_PLY1, KC_MPRV, KC_MPLY, KC_MNXT, EP_CEDL,
                                         KC_SPC, KC_PSCR, XXXXXXX, _______
  )
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

// OSLM: process a OSLM key
void process_osml(oslm_state_t *oslm_state, uint16_t keycode, keyrecord_t *record) {
  static uint16_t mods = 0;
  if (record->event.pressed) {
    // init: init timer, register trigger mod
    oslm_state->timer = timer_read();
    register_mods(oslm_state->mod);
    // get mods at the time of pressed event.
    mods = get_mods();
  } else {
    // released: check if it's a tap
    if (timer_elapsed(oslm_state->timer) < TAPPING_TERM) {
      // tap: keep all current mods and set oneshot layer
      set_oneshot_mods(mods);
      set_oneshot_layer(EP_MD, ONESHOT_START);
    } else {
      // hold/release: clear held mod
      unregister_mods(oslm_state->mod);
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
  bool advance = true;

  mods_state = get_mods();
  oneshot_mods_state = get_oneshot_mods();

  switch (keycode) {
    case EP_DOSP:
      // Reset OSM/OSLM state.
      if (record->tap.count == 0) {
        // Clear all layers and mods on hold (press and release)
        layer_clear();
        clear_oneshot_mods();
        unregister_mods(mods_state);
        advance = true;
      } else if (record->event.pressed && record->tap.count == 1 && mods_state == MOD_BIT(KC_LSFT)) {
        tap_code16(KC_UNDS);
        advance = false;
      } else {
        advance = true;
      }
      break;

    // S(EP_SYEN) => KC_AT
    case EP_SYEN:
      if (record->event.pressed && record->tap.count == 1 && mods_state == MOD_BIT(KC_LSFT)) {
        tap_code16(KC_AT);
        advance = false;
      } else {
        advance = true;
      }
      break;

    // S(KC_DOT) => KC_SEMI
    case KC_DOT:
      if (record->event.pressed && mods_state == MOD_BIT(KC_LSFT)) {
        tap_code16(KC_COLON);
        advance = false;
      } else {
        advance = true;
      }
      break;

    // S(KC_COMM) => KC_SEMI
    case KC_COMM:
      if (record->event.pressed && mods_state == MOD_BIT(KC_LSFT)) {
        del_mods(MOD_BIT(KC_LSFT));
        tap_code16(KC_SCLN);
        add_mods(MOD_BIT(KC_LSFT));
        advance = false;
      } else {
        advance = true;
      }
      break;

    // S(KC_EXLM) => KC_QUES
    case KC_EXLM:
      if (record->event.pressed && mods_state == MOD_BIT(KC_LSFT)) {
        tap_code16(KC_QUES);
        advance = false;
      } else {
        advance = true;
      }
      break;

    // -- BEGIN OSLM KEYS ---
    // DO: OS_C
    case EP_OS_C:
      process_osml(&oslm_c, keycode, record);
      advance = false;
      break;

    // DO: OS_A
    case EP_OS_A:
      process_osml(&oslm_a, keycode, record);
      advance = false;
      break;

    // DO: OS_G
    case EP_OS_G:
      process_osml(&oslm_g, keycode, record);
      advance = false;
      break;

    // DO: OS_S
    case EP_OS_S:
      process_osml(&oslm_s, keycode, record);
      advance = false;
      break;

    // -- END OSLM KEYS ---

    // BEGIN SY MT
    case EP_SY_S:
      if (record->event.pressed && record->tap.count > 0) {
        tap_code16(KC_LPRN);
        advance = false;
      } else {
        advance = true;
      }
      break;

    case EP_SY_C:
      if (record->event.pressed && record->tap.count > 0) {
        tap_code16(KC_LPRN);
        advance = false;
      } else {
        advance = true;
      }
      break;

    case EP_SY_A:
      if (record->event.pressed && record->tap.count > 0) {
        tap_code16(KC_DLR);
        advance = false;
      } else {
        advance = true;
      }
      break;

    case EP_SY_G:
      if (record->event.pressed && record->tap.count > 0) {
        tap_code16(KC_TILD);
        advance = false;
      } else {
        advance = true;
      }
      break;
    // END SY MT

    // BEGIN FN MT
    case EP_FN_S:
      if (record->event.pressed && record->tap.count > 0) {
        tap_code16(EP_DTIL);
        layer_clear();
        advance = false;
      } else {
        advance = true;
      }
      break;

    case EP_FN_C:
      if (record->event.pressed && record->tap.count > 0) {
        tap_code16(EP_ACUT);
        layer_clear();
        advance = false;
      } else {
        advance = true;
      }
      break;

    case EP_FN_A:
      if (record->event.pressed && record->tap.count > 0) {
        tap_code16(EP_DCIR);
        layer_clear();
        advance = false;
      } else {
        advance = true;
      }
      break;

    case EP_FN_G:
      if (record->event.pressed && record->tap.count > 0) {
        tap_code16(EP_DGRV);
        layer_clear();
        advance = false;
      } else {
        advance = true;
      }
      break;
    // END FN MT

    // BEGIN SYMBOL SHORTCUTS

    case EP_CURD:
      if (record->event.pressed) {
        SEND_STRING("./");
        advance = false;
      }
      break;

    case EP_PARD:
      if (record->event.pressed) {
        SEND_STRING("../");
        advance = false;
      }
      break;

    case EP_HOMD:
      if (record->event.pressed) {
        SEND_STRING("~/");
        advance = false;
      }
      break;
    // END SYMBOL SHORTCUTS

    // S(KC_EQL): ../
    case KC_EQL:
      if (record->event.pressed && (mods_state == MOD_BIT(KC_LSFT))) {
        del_mods(MOD_BIT(KC_LSFT));
        SEND_STRING("../");
        add_mods(MOD_BIT(KC_LSFT));
        advance = false;
      } else {
        advance = true;
      }
      break;

    // S(KC_MINS): ./
    case KC_MINS:
      if (record->event.pressed && (mods_state == MOD_BIT(KC_LSFT))) {
        del_mods(MOD_BIT(KC_LSFT));
        SEND_STRING("./");
        add_mods(MOD_BIT(KC_LSFT));
        advance = false;
      } else {
        advance = true;
      }
      break;

    // S(KC_SLSH): ~/
    case KC_SLSH:
      if (record->event.pressed && (mods_state == MOD_BIT(KC_LSFT))) {
        del_mods(MOD_BIT(KC_LSFT));
        SEND_STRING("~/");
        add_mods(MOD_BIT(KC_LSFT));
        advance = false;
      } else {
        advance = true;
      }
      break;

    default:
      // OSLM: Clear current OSLM layer state after press.
      if (IS_LAYER_ON(EP_MD) && record->event.pressed) {
        clear_oneshot_layer_state(ONESHOT_PRESSED);
        unregister_mods(mods_state);
      }
      advance = true;
  }

  processrepeat_key(keycode, record);
  return advance;
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
    case EP_DOSP:
    case EP_SYEN:
    case EP_FNBS:
    case EP_SFEN:
        return 0;
    default:
        return QUICK_TAP_TERM;
  }
}


bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case EP_N:
        case EP_T:
            // Do not select the hold action when another key is tapped.
            return false;
        default:
            // Immediately select the hold action when another key is tapped.
            return true;
    }
}
