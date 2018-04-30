#ifndef KEYMAP_H
#define KEYMAP_H

#include "keycode.h"
#include "stdint.h"

#define KEYMAP( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K0D, \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, \
    K40, K41, K42, K43, K44,      K45,      K46, K47, K48  \
) { \
    { KC_##K00, KC_##K01, KC_##K02, KC_##K03, KC_##K04, KC_##K05, KC_##K06, KC_##K07, KC_##K08, KC_##K09, KC_##K0A, KC_##K0B, KC_##K0C }, \
    { KC_##K10, KC_##K11, KC_##K12, KC_##K13, KC_##K14, KC_##K15, KC_##K16, KC_##K17, KC_##K18, KC_##K19, KC_##K1A, KC_##K1B, KC_##K1C }, \
    { KC_##K20, KC_##K21, KC_##K22, KC_##K23, KC_##K24, KC_##K25, KC_##K26, KC_##K27, KC_##K28, KC_##K29, KC_##K2A, KC_##K2B, KC_##K0D }, \
    { KC_##K30, KC_##K31, KC_##K32, KC_##K33, KC_##K34, KC_##K35, KC_##K36, KC_##K37, KC_##K38, KC_##K39, KC_##K3A, KC_NO,    KC_NO    }, \
    { KC_##K40, KC_##K41, KC_##K42, KC_##K43, KC_##K44, KC_##K45, KC_##K46, KC_##K47, KC_##K48, KC_NO,    KC_NO,    KC_NO,    KC_NO    }  \
}

#define KEYBOARD_ROWS 5
#define KEYBOARD_COLS 13
#define DEBOUNCE 5

const uint8_t row_pins[KEYBOARD_ROWS] = {1, 0, 2, 3, 4};
const uint8_t col_pins[KEYBOARD_COLS] = {5, 6, 7, 8, 9, 10, 16, 14, 15, 18, 19, 20, 21};

const uint8_t keymap[KEYBOARD_ROWS][KEYBOARD_COLS] =
    KEYMAP(
        ESC, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, MINS, EQL, GRV,
        TAB, Q, W, E, R, T, Y, U, I, O, P, LBRC, RBRC,
        CAPS, A, S, D, F, G, H, J, K, L, SCLN, QUOT,
        LSFT, Z, X, C, V, B, N, M, COMM, DOT, SLSH,
        LCTL, LALT, DEL, LGUI, RGUI, SPC, RCTL, RSFT, BSLS);
#endif