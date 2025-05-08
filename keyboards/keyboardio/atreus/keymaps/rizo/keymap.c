// Copyright (C) 2019, 2020  Keyboard.io, Inc
//
// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H

enum layer_names {
    _TX,
    _DO,
    _NM,
    _SY,
};

#define AT_STAB S(KC_TAB)
#define AT_WDLF C(KC_LEFT)
#define AT_WDRT C(KC_RIGHT)
#define AT_CHOM C(KC_HOME)
#define AT_CEND C(KC_END)

#define AT_DOEN LT(_DO, KC_ENT)
#define AT_SFTB SFT_T(KC_TAB)
#define AT_SFES SFT_T(KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_TX] = LAYOUT(
    KC_Q,       KC_W,    KC_F,    KC_P,    KC_G,                   KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT,
    KC_A,       KC_R,    KC_S,    KC_T,    KC_D,                   KC_H,    KC_N,    KC_E,    KC_I,    KC_O,
    KC_Z,       KC_X,    KC_C,    KC_V,    KC_B, KC_ESC,  KC_TAB,  KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
    KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL,  KC_SPC, AT_SFES, AT_SFTB, AT_DOEN, KC_BSPC, KC_RALT, KC_RGUI, KC_RSFT
  ),

  [_DO] = LAYOUT(
       KC_Q,    KC_1,    KC_2,    KC_3, KC_WH_U,                   KC_PGUP, AT_WDLF, KC_UP,   AT_WDRT, AT_CHOM,
       KC_0,    KC_4,    KC_5,    KC_6, KC_WH_D,                   KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,
       KC_Z,    KC_7,    KC_8,    KC_9,    KC_B,  KC_GRV, KC_UNDS, KC_PGDN, AT_STAB, KC_ESC,  KC_TAB,  AT_CEND,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  [_NM] = LAYOUT(
    KC_Q,       KC_W,    KC_E,    KC_R,    KC_T,                   KC_Y,    KC_1,    KC_2,    KC_3,    KC_P,
    KC_A,       KC_S,    KC_D,    KC_F,    KC_G,                   KC_H,    KC_4,    KC_5,    KC_6,    KC_0,
    KC_Z,       KC_X,    KC_C,    KC_V,    KC_B,  KC_GRV, KC_BSLS, KC_N,    KC_7,    KC_8,    KC_9,    KC_SLSH,
    KC_ESC,   KC_TAB, KC_LGUI, KC_LCTL, KC_LSFT, MO(_NM), _______, _______, _______, _______, _______, _______
  ),

  [_SY] = LAYOUT(
    KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,                   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    KC_A,     KC_S,    KC_D,    KC_F,    KC_G,                   KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
    KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,  KC_GRV, KC_BSLS, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
    KC_ESC, KC_TAB, KC_LGUI, KC_LCTL, KC_LSFT, MO(_NM), MO(_SY), KC_SPC,  MO(_DO), KC_MINS, KC_QUOT, KC_ENT
  ),
};
