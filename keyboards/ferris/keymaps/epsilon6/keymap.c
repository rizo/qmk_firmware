#include QMK_KEYBOARD_H

#define OSCTL OSM(MOD_BIT(KC_LCTL))
#define OSALT OSM(MOD_BIT(KC_LALT))
#define OSGUI OSM(MOD_BIT(KC_LGUI))
#define OSSFT OSM(MOD_BIT(KC_LSFT))

enum layers {
  ABC,
  ACT,
  NUM,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [ABC] = LAYOUT(
        KC_Q,    KC_W,    KC_E,     KC_R,     KC_T,                          KC_Y,     KC_U, KC_I,     KC_O,   KC_QUOT,
        KC_A,    KC_S,    KC_D,     KC_F,     KC_G,                          KC_H,     KC_J, KC_K,     KC_L,   KC_SCLN,
        KC_Z,    KC_X,    KC_C,     KC_V,     KC_B,                          KC_N,     KC_M, KC_COMMA, KC_DOT, KC_P,
                                           MO(ACT), KC_LSFT,         KC_SPC, MO(NUM)
  ),

    [ACT] = LAYOUT(
     XXXXXXX,  KC_ESC,  G(KC_LBRC), G(KC_RBRC), XXXXXXX,                       KC_PGUP, S(KC_TAB), KC_UP,   KC_TAB,   KC_HOME,
       OSGUI,   OSALT,       OSCTL,      OSSFT, XXXXXXX,                       KC_PGDN, KC_LEFT,   KC_DOWN, KC_RIGHT, KC_END,
     XXXXXXX, XXXXXXX,     XXXXXXX,    XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX,  XXXXXXX,
                                                _______, XXXXXXX,      KC_ENT, KC_BSPC
  ),

  [NUM] = LAYOUT(
        KC_BSLS, KC_1,    KC_2,    KC_3,  KC_SLSH,                     XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,
        KC_LBRC, KC_4,    KC_5,    KC_6,  KC_RBRC,                     XXXXXXX, KC_RSFT,  KC_RCTL, KC_RALT, KC_RGUI,
         KC_GRV, KC_7,    KC_8,    KC_9,     KC_0,                     XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, RESET,
                                          KC_MINS, KC_EQL,    XXXXXXX, _______
  )
};

