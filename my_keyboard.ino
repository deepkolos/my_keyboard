#include "keycode.c"
#include "cps_keymap.h"

extern const uint8_t row_pins[KEYBOARD_ROWS];
extern const uint8_t col_pins[KEYBOARD_COLS];
extern uint16_t curr_col_state[KEYBOARD_ROWS];
extern uint16_t prev_col_state[KEYBOARD_ROWS];
extern uint16_t temp_col_state[KEYBOARD_ROWS];
extern uint8_t key_press_stack[KEYBOARD_COLS * KEYBOARD_ROWS];
extern uint8_t key_release_stack[KEYBOARD_COLS * KEYBOARD_ROWS];
extern uint8_t key_pressed_num;
extern uint8_t key_released_num;

void setup()
{
  init_cps_key();
  init_keyboard();

  uint8_t row, col, keycode;
  for (row = 0; row < KEYBOARD_ROWS; row++)
  {
    curr_col_state[row] = 0;
    prev_col_state[row] = 0;
    temp_col_state[row] = 0;
    pinMode(row_pins[row], OUTPUT);
    digitalWrite(row_pins[row], HIGH);
  }

  for (col = 0; col < KEYBOARD_COLS; col++)
  {
    pinMode(col_pins[col], INPUT_PULLUP);
  }

  // 初始化的时候, unpress所有按钮
  for (keycode = KC_A; keycode <= KC_RGUI; keycode++)
  {
    NKROKeyboard.release(keycode);
  }
}

// 函数定义
void key_event(uint8_t row, uint8_t col, bool pressed);

void loop()
{
  update_curr_col_state();
  // 检测变化

  uint8_t row, col;
  uint16_t changed_col;
  for (row = 0; row < KEYBOARD_ROWS; row++)
  {
    if (curr_col_state[row] != prev_col_state[row])
    {
      // 触发事件
      // 提取出该行哪列变化
      // 变化就是不同通过异或运算来取得
      changed_col = curr_col_state[row] ^ prev_col_state[row];

      for (col = 0; col < KEYBOARD_COLS; col++)
      {
        // 当包含了当前列
        if (changed_col & 1UL << col)
        {
          // 触发事件, 参数: row, col, press/release
          bool pressed = curr_col_state[row] & 1UL << col;
          key_event(row, col, pressed);

          prev_col_state[row] = curr_col_state[row];
        }
      }
    }
  }
}

void key_event(uint8_t row, uint8_t col, bool pressed)
{
  // 获取物理键盘对应按钮的键码
  uint8_t keycode = get_keycode(row, col);
  if (pressed)
  {
    key_press_stack[key_pressed_num] = keycode;
    key_pressed_num++;
  }
  else
  {
    key_release_stack[key_released_num] = keycode;
    key_released_num++;
  }

  trigger_composite_key(keycode, pressed);

  // 当key_pressed_num和key_released_num相等的时候就清0
  if (key_pressed_num == key_released_num)
  {
    key_pressed_num = key_released_num = 0;
  }
}