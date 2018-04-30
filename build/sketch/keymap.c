#ifndef KEYMAP_C
#define KEYMAP_C

#include "stdint.h"
#include "keymap.h"
#include "keyboard.h"

extern uint8_t keymap[KEYBOARD_ROWS][KEYBOARD_COLS];
uint16_t curr_col_state[KEYBOARD_ROWS];
uint16_t prev_col_state[KEYBOARD_ROWS];
uint16_t temp_col_state[KEYBOARD_ROWS];

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

uint8_t debounce = 0;
void update_curr_col_state()
{
  uint8_t row;
  uint16_t _col_state;
  for (row = 0; row < KEYBOARD_ROWS; row++)
  {
    // 扫描行
    digitalWrite(row_pins[row], LOW);
    _col_state = ~get_col_state();

    if (temp_col_state[row] != _col_state)
    {
      // 检测到变化, 开始防抖, 延迟curr_col_state生效
      temp_col_state[row] = _col_state;
      debounce = DEBOUNCE;
    }
    digitalWrite(row_pins[row], HIGH);
  }

  if (debounce)
  {
    if (--debounce)
    {
      delay(1);
    }
    else
    {
      for (row = 0; row < KEYBOARD_ROWS; row++)
      {
        curr_col_state[row] = temp_col_state[row];
      }
    }
  }
}

#endif