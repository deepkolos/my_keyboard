#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include "keymap.h"
#include "keycode.c"
#include "mHID-Project/HID-Project.h"
#include "mHID-Project/HID-Settings.h"

uint16_t curr_col_state[KEYBOARD_ROWS];
uint16_t prev_col_state[KEYBOARD_ROWS];
uint16_t temp_col_state[KEYBOARD_ROWS];
uint8_t key_press_stack[KEYBOARD_COLS * KEYBOARD_ROWS] = {};
uint8_t key_release_stack[KEYBOARD_COLS * KEYBOARD_ROWS] = {};
uint8_t key_pressed_num = 0;
uint8_t key_released_num = 0;

void init_keyboard () {
    Consumer.begin();
    NKROKeyboard.begin();
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

void send_key(uint8_t keycode, bool pressed)
{
  // 不需要使用表, 把类分好来就可以的了

  uint16_t _code;
  switch (keycode)
  {
  case KC_A ... KC_EXSEL:
  case KC_LCTRL ... KC_RGUI:
    if (pressed)
    {
      NKROKeyboard.press((KeyboardKeycode)keycode);
    }
    else
    {
      NKROKeyboard.release((KeyboardKeycode)keycode);
    }
    break;
  case KC_SYSTEM_POWER ... KC_SYSTEM_WAKE:
    _code = KEYCODE2SYSTEM(keycode);
    if (pressed)
    {
      System.press((SystemKeycode)_code);
    }
    else
    {
      System.release();
    }
    break;
  case KC_AUDIO_MUTE ... KC_BRIGHTNESS_DOWN:
    _code = KEYCODE2CONSUMER(keycode);
    if (pressed)
    {
      Consumer.press((ConsumerKeycode)_code);
    }
    else
    {
      Consumer.release((ConsumerKeycode)_code);
    }
    break;
  case KC_MS_UP ... KC_MS_ACCEL2:
    if (pressed)
    {
      NKROKeyboard.press(keycode);
    }
    else
    {
      NKROKeyboard.release(keycode);
    }
    break;
  case KC_TRNS:
    break;
  case KC_BOOTLOADER:
    break;
  default:
    break;
  }
}
#endif