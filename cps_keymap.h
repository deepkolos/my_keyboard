#ifndef CPS_KEYMAP
#define CPS_KEYMAP

int composite_key_len;

#include "cps_key.h"

#define KC_0_9_WASD_SET_LEN 16
#define KC_0_9_WASD_SET {KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_CAPS, KC_LSFT, KC_W, KC_A, KC_S, KC_D}
#define KC_0_TO_9_SET_LEN 10
#define KC_0_TO_9_SET {KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0}
#define KC_WASD_KEY_LEN 7
#define KC_WASD_KEY {KC_LSFT, KC_CAPS, KC_W, KC_A, KC_S, KC_D, KC_R}

composite_key_t composite_keymap[] = {
    // home + wasd start
    {{KC_HOME, KC_W},       2,
     {KC_UP},               1,
     KC_WASD_KEY,           KC_WASD_KEY_LEN,
     DEFAULT_CPS_BASE},

    {{KC_HOME, KC_A},       2,
     {KC_LEFT},             1,
     KC_WASD_KEY,           KC_WASD_KEY_LEN,
     DEFAULT_CPS_BASE},

    {{KC_HOME, KC_S},       2,
     {KC_DOWN},             1,
     KC_WASD_KEY,           KC_WASD_KEY_LEN,
     DEFAULT_CPS_BASE},

    {{KC_HOME, KC_D},       2,
     {KC_RIGHT},            1,
     KC_WASD_KEY,           KC_WASD_KEY_LEN,
     DEFAULT_CPS_BASE},
     // home + wasd end
     
     // shift + bs -> enter
     {{KC_CAPS, KC_TAB},    2,
     {KC_ENT},              1,
    { KC_LSFT, KC_CAPS, 
      KC_W, KC_A, KC_S, 
      KC_D, KC_HOME},       7,
     true, 0, 0, false},
     
     // home + r -> win + r
     {{KC_HOME, KC_R},      2,
     {KC_LGUI, KC_R},       2,
     KC_WASD_KEY,           KC_WASD_KEY_LEN,
     DEFAULT_CPS_BASE},

     // home + spc -> win + r
     {{KC_HOME, KC_SPC},    2,
     {KC_LGUI, KC_R},       2,
     KC_WASD_KEY,           KC_WASD_KEY_LEN,
     DEFAULT_CPS_BASE},

     // win + n start
     {{KC_HOME, KC_1},      2,
     {KC_LGUI, KC_1},       2,
     KC_0_9_WASD_SET,       KC_0_9_WASD_SET_LEN,
     DEFAULT_CPS_BASE},

     {{KC_HOME, KC_2},      2,
     {KC_LGUI, KC_2},       2,
     KC_0_9_WASD_SET,       KC_0_9_WASD_SET_LEN,
     DEFAULT_CPS_BASE},

     {{KC_HOME, KC_3},      2,
     {KC_LGUI, KC_3},       2,
     KC_0_9_WASD_SET,       KC_0_9_WASD_SET_LEN,
     DEFAULT_CPS_BASE},

     {{KC_HOME, KC_4},      2,
     {KC_LGUI, KC_4},       2,
     KC_0_9_WASD_SET,       KC_0_9_WASD_SET_LEN,
     DEFAULT_CPS_BASE},

     {{KC_HOME, KC_5},      2,
     {KC_LGUI, KC_5},       2,
     KC_0_9_WASD_SET,       KC_0_9_WASD_SET_LEN,
     DEFAULT_CPS_BASE},

     {{KC_HOME, KC_6},      2,
     {KC_LGUI, KC_6},       2,
     KC_0_9_WASD_SET,       KC_0_9_WASD_SET_LEN,
     DEFAULT_CPS_BASE},

     {{KC_HOME, KC_7},      2,
     {KC_LGUI, KC_7},       2,
     KC_0_9_WASD_SET,       KC_0_9_WASD_SET_LEN,
     DEFAULT_CPS_BASE},

     {{KC_HOME, KC_8},      2,
     {KC_LGUI, KC_8},       2,
     KC_0_9_WASD_SET,       KC_0_9_WASD_SET_LEN,
     DEFAULT_CPS_BASE},
     
     {{KC_HOME, KC_9},      2,
     {KC_LGUI, KC_9},       2,
     KC_0_9_WASD_SET,       KC_0_9_WASD_SET_LEN,
     DEFAULT_CPS_BASE},
     // win + n end

     // home + esc -> alt + f4
     {{KC_HOME, KC_ESC},    2,
     {KC_LALT, KC_F4},      2,
     KC_WASD_KEY,           KC_WASD_KEY_LEN,
     DEFAULT_CPS_BASE},
    
     // home + tab -> alt + tab
     {{KC_HOME, KC_LCTL},   2,
     {KC_LALT, KC_LCTL},    2,
     KC_WASD_KEY,           KC_WASD_KEY_LEN,
     DEFAULT_CPS_BASE},

     // esc + n -> fn start
     {{KC_ESC, KC_1},       2,
     {KC_F1},               1,
     KC_0_TO_9_SET,         KC_0_TO_9_SET_LEN,
     DEFAULT_CPS_BASE},

     {{KC_ESC, KC_2},       2,
     {KC_F2},               1,
     KC_0_TO_9_SET,         KC_0_TO_9_SET_LEN,
     DEFAULT_CPS_BASE},

     {{KC_ESC, KC_3},       2,
     {KC_F3},               1,
     KC_0_TO_9_SET,         KC_0_TO_9_SET_LEN,
     DEFAULT_CPS_BASE},

     {{KC_ESC, KC_4},       2,
     {KC_F4},               1,
     KC_0_TO_9_SET,         KC_0_TO_9_SET_LEN,
     DEFAULT_CPS_BASE},

     {{KC_ESC, KC_5},       2,
     {KC_F5},               1,
     KC_0_TO_9_SET,         KC_0_TO_9_SET_LEN,
     DEFAULT_CPS_BASE},

     {{KC_ESC, KC_6},       2,
     {KC_F6},               1,
     KC_0_TO_9_SET,         KC_0_TO_9_SET_LEN,
     DEFAULT_CPS_BASE},

     {{KC_ESC, KC_7},       2,
     {KC_F7},               1,
     KC_0_TO_9_SET,         KC_0_TO_9_SET_LEN,
     DEFAULT_CPS_BASE},

     {{KC_ESC, KC_8},       2,
     {KC_F8},               1,
     KC_0_TO_9_SET,         KC_0_TO_9_SET_LEN,
     DEFAULT_CPS_BASE},

     {{KC_ESC, KC_9},       2,
     {KC_F9},               1,
     KC_0_TO_9_SET,         KC_0_TO_9_SET_LEN,
     DEFAULT_CPS_BASE},

     {{KC_ESC, KC_0},       2,
     {KC_F10},              1,
     KC_0_TO_9_SET,         KC_0_TO_9_SET_LEN,
     DEFAULT_CPS_BASE},

     {{KC_ESC, KC_MINS},    2,
     {KC_F11},              1,
     KC_0_TO_9_SET,         KC_0_TO_9_SET_LEN,
     DEFAULT_CPS_BASE},

     {{KC_ESC, KC_EQL},     2,
     {KC_F12},              1,
     KC_0_TO_9_SET,         KC_0_TO_9_SET_LEN,
     DEFAULT_CPS_BASE}
     // esc + n -> fn end
    
};

void init_cps_key () {
  composite_key_len = sizeof(composite_keymap)/sizeof(composite_key_t);
}

#endif