#ifndef KEYCODE_C
#define KEYCODE_C
#include "keymap.h"
#include "Arduino.h"

extern const uint8_t row_pins[KEYBOARD_ROWS];
extern const uint8_t col_pins[KEYBOARD_COLS];
extern const uint8_t keymap[KEYBOARD_ROWS][KEYBOARD_COLS];

uint8_t get_keycode(uint8_t row, uint8_t col)
{
  return keymap[row][col];
}

uint16_t get_col_state()
{
  uint8_t col;
  uint16_t _state = 0;
  for (col = 0; col < KEYBOARD_COLS; col++)
  {
    _state |= ((uint16_t)digitalRead(col_pins[col])) << col;
  }
  return _state;
}


#endif