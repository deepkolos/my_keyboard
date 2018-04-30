#ifndef CPS_KEYMAP
#define CPS_KEYMAP

const int composite_key_len = 6;

#include "cps_key.h"

composite_key_t composite_keymap[] = {
    // home + wasd start
    {{KC_HOME, KC_W},       2,
     {KC_UP},               1,
     COMMON_INSERT_KEY,     COMMON_INSERT_KEY_LEN,
     DEFAULT_CPS_BASE},

    {{KC_HOME, KC_A},       2,
     {KC_LEFT},             1,
     COMMON_INSERT_KEY,     COMMON_INSERT_KEY_LEN,
     DEFAULT_CPS_BASE},

    {{KC_HOME, KC_S},       2,
     {KC_DOWN},             1,
     COMMON_INSERT_KEY,     COMMON_INSERT_KEY_LEN,
     DEFAULT_CPS_BASE},

    {{KC_HOME, KC_D},       2,
     {KC_RIGHT},            1,
     COMMON_INSERT_KEY,     COMMON_INSERT_KEY_LEN,
     DEFAULT_CPS_BASE},
     // home + wasd end
     
     // shift + bs -> enter
    //  {{KC_LSFT, KC_TAB},    2,
    //  {KC_RIGHT},            1,
    //  {},                    0,
    //  DEFAULT_CPS_BASE},
     
     // home + r -> win + r
    //  {{KC_HOME, KC_R},      2,
    //  {KC_LGUI, KC_R},       2,
    //  {},                    0,
    //  DEFAULT_CPS_BASE},

     // win + n start
     {{KC_HOME, KC_1},      2,
     {KC_LGUI, KC_1},       2,
     {},                    0,
     DEFAULT_CPS_BASE},

     {{KC_HOME, KC_2},      2,
     {KC_LGUI, KC_2},       2,
     {},                    0,
     DEFAULT_CPS_BASE}

    //  {{KC_HOME, KC_3},      2,
    //  {KC_LGUI, KC_3},       2,
    //  {},                    0,
    //  DEFAULT_CPS_BASE},

    //  {{KC_HOME, KC_4},      2,
    //  {KC_LGUI, KC_4},       2,
    //  {},                    0,
    //  DEFAULT_CPS_BASE},

    //  {{KC_HOME, KC_5},      2,
    //  {KC_LGUI, KC_5},       2,
    //  {},                    0,
    //  DEFAULT_CPS_BASE},

    //  {{KC_HOME, KC_6},      2,
    //  {KC_LGUI, KC_6},       2,
    //  {},                    0,
    //  DEFAULT_CPS_BASE},

    //  {{KC_HOME, KC_7},      2,
    //  {KC_LGUI, KC_7},       2,
    //  {},                    0,
    //  DEFAULT_CPS_BASE},

    //  {{KC_HOME, KC_8},      2,
    //  {KC_LGUI, KC_8},       2,
    //  {},                    0,
    //  DEFAULT_CPS_BASE},
     
    //  {{KC_HOME, KC_9},      2,
    //  {KC_LGUI, KC_9},       2,
    //  {},                    0,
    //  DEFAULT_CPS_BASE}
     // win + n end
};

#endif