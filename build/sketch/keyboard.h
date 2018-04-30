#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "stdint.h"
#include "keymap.h"

#define KEYBOARD_COLS 13
#define KEYBOARD_ROWS 5
#define DEBOUNCE 5

const uint8_t col_pins[] = {5, 6, 7, 8, 9, 10, 16, 14, 15, 18, 19, 20, 21};
const uint8_t row_pins[] = {1, 0, 2, 3, 4};

// 先是简单的一维数组
uint8_t keymap[KEYBOARD_ROWS][KEYBOARD_COLS] =
    KEYMAP(ESC, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, MINS, EQL,
           TAB, Q, W, E, R, T, Y, U, I, O, P, LBRC, RBRC,
           CAPS, A, S, D, F, G, H, J, K, L, SCLN, QUOT, GRV,
           LSFT, Z, X, C, V, B, N, M, COMM, DOT, SLSH,
           LCTRL, LALT, DEL, LGUI, RGUI, SPC, RCTRL, RSFT, BSLS);

#endif