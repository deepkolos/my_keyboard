#ifndef CPS_KEYMAP_H
#define CPS_KEYMAP_H

#include "stdint.h"
#include "keycode.h"

typedef struct
{
  uint8_t scan_keys[5];
  uint8_t scan_key_len;
  uint8_t trigger_keys[5];
  uint8_t trigger_key_len;
  uint8_t key_allow_insert[8];
  uint8_t key_allow_insert_len;
  uint8_t matched;
  uint8_t unmatched;
  bool has_triggered;
} composite_key_t;

#define DEFAULT_CPS_BASE .matched = 0,   \
                         .unmatched = 0, \
                         .has_triggered = false

#define COMMON_INSERT_KEY_LEN 8
#define COMMON_INSERT_KEY                                            \
  {                                                                  \
    KC_LCTRL, KC_RCTRL, KC_LSHIFT, KC_RSHIFT, KC_W, KC_A, KC_S, KC_D \
  }

#define composite_key_len 4
composite_key_t composite_keymap[composite_key_len] = {
    {.scan_keys = {KC_HOME, KC_W},
     .scan_key_len = 2,
     .trigger_keys = {KC_UP},
     .trigger_key_len = 1,
     .key_allow_insert = COMMON_INSERT_KEY,
     .key_allow_insert_len = COMMON_INSERT_KEY_LEN,
     DEFAULT_CPS_BASE},

    {.scan_keys = {KC_HOME, KC_A},
     .scan_key_len = 2,
     .trigger_keys = {KC_LEFT},
     .trigger_key_len = 1,
     .key_allow_insert = COMMON_INSERT_KEY,
     .key_allow_insert_len = COMMON_INSERT_KEY_LEN,
     DEFAULT_CPS_BASE},

    {.scan_keys = {KC_HOME, KC_S},
     .scan_key_len = 2,
     .trigger_keys = {KC_DOWN},
     .trigger_key_len = 1,
     .key_allow_insert = COMMON_INSERT_KEY,
     .key_allow_insert_len = COMMON_INSERT_KEY_LEN,
     DEFAULT_CPS_BASE},

    {.scan_keys = {KC_HOME, KC_D},
     .scan_key_len = 2,
     .trigger_keys = {KC_RIGHT},
     .trigger_key_len = 1,
     .key_allow_insert = COMMON_INSERT_KEY,
     .key_allow_insert_len = COMMON_INSERT_KEY_LEN,
     DEFAULT_CPS_BASE}};

#endif