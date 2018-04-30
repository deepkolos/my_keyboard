# 1 "d:\\DEV\\Github\\hardware\\my_keyboard\\my_keyboard.ino"
# 1 "d:\\DEV\\Github\\hardware\\my_keyboard\\my_keyboard.ino"
// #include "mHID-Project/HID-Project.h"
// #include "mHID-Project/HID-Settings.h"

# 5 "d:\\DEV\\Github\\hardware\\my_keyboard\\my_keyboard.ino" 2
# 6 "d:\\DEV\\Github\\hardware\\my_keyboard\\my_keyboard.ino" 2
# 7 "d:\\DEV\\Github\\hardware\\my_keyboard\\my_keyboard.ino" 2
# 8 "d:\\DEV\\Github\\hardware\\my_keyboard\\my_keyboard.ino" 2
# 9 "d:\\DEV\\Github\\hardware\\my_keyboard\\my_keyboard.ino" 2

extern uint16_t curr_col_state[5];
extern uint16_t prev_col_state[5];
extern uint16_t temp_col_state[5];
uint8_t key_press_stack[13 * 5] = {};
uint8_t key_release_stack[13 * 5] = {};
uint8_t key_pressed_num = 0;
uint8_t key_released_num = 0;
Set press_trigger_key_set;
Set blocked_press_key_set;

// 函数定义
void key_event(uint8_t row, uint8_t col, bool pressed);
uint8_t get_keycode(uint8_t row, uint8_t col);
void trigger_composite_key(uint8_t keycode, bool pressed);

void setup()
{
  Consumer.begin();
  NKROKeyboard.begin();

  uint8_t row, col, keycode;
  for (row = 0; row < 5; row++)
  {
    curr_col_state[row] = 0;
    prev_col_state[row] = 0;
    temp_col_state[row] = 0;
    pinMode(row_pins[row], 0x1);
    digitalWrite(row_pins[row], 0x1);
  }

  for (col = 0; col < 13; col++)
  {
    pinMode(col_pins[col], 0x2);
  }

  // 初始化的时候, unpress所有按钮
  for (keycode = KC_A; keycode <= KC_RGUI; keycode++)
  {
    NKROKeyboard.release(keycode);
  }
}

void loop()
{
  update_curr_col_state();
  // 检测变化

  uint8_t row, col;
  uint16_t changed_col;
  for (row = 0; row < 5; row++)
  {
    if (curr_col_state[row] != prev_col_state[row])
    {
      // 触发事件
      // 提取出该行哪列变化
      // 变化就是不同通过异或运算来取得
      changed_col = curr_col_state[row] ^ prev_col_state[row];

      for (col = 0; col < 13; col++)
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

void trigger_composite_key(uint8_t keycode, bool pressed)
{
  uint8_t i, j;
  bool block = false;
  bool is_short_recover_key = false;

  composite_key_t *cps_key;
  for (i = 0; i < 1; i++)
  {
    cps_key = &composite_keymap[i];

    if (pressed)
    {
      if (cps_key->scan_keys[cps_key->matched] == keycode)
      {
        cps_key->matched++;
        // 阻塞该默认
        block = true;
        blocked_press_key_set.add(keycode);
        // 判断时候打到触发条件
        if (cps_key->matched == cps_key->scan_key_len && cps_key->unmatched == 0)
        {
          // 触发组合键, 一次性按下所有的按键
          for (j = 0; j < cps_key->trigger_key_len; j++)
            if (press_trigger_key_set.add(cps_key->trigger_keys[j]))
              send_key(cps_key->trigger_keys[j], pressed);

          cps_key->has_triggered = true;
        }
      }

      // 非scan_key和insert_key
      else if (!check_in_allow_insert_key_list(cps_key, keycode))
      {
        cps_key->unmatched++;
        // 现在组合键处于未触发状态, 则释放被阻塞的按钮, 会重复触发, 不该在这里触发
        if (cps_key->matched != cps_key->trigger_key_len)
          for (j = 0; j < cps_key->unmatched; j++)
            // 把已经match, 那些被阻塞的, 取消阻塞
            // press home (block home) -> press g (unblock home press home press g)
            if (blocked_press_key_set.remove(cps_key->scan_keys[i]))
              send_key(cps_key->scan_keys[i], true);
      }
    }
    else // release
    {
      // 检测是否属于组合键的扫描键
      if (cps_key->scan_keys[cps_key->matched - 1] == keycode)
      {
        cps_key->matched--;
        block = true;
        blocked_press_key_set.remove(keycode);

        // 当已经触发过的时候
        if (cps_key->has_triggered)
        {
          // 慢释放
          // 需要释放的keycode
          j = cps_key->trigger_key_len - (cps_key->scan_key_len - cps_key->matched);
          if (j >= 0 && press_trigger_key_set.remove(cps_key->trigger_keys[j]))
            send_key(cps_key->trigger_keys[j], false);

          // 当没有键被按下的话, 把所有剩下的key都释放
          if (cps_key->matched == 0)
            for (j = 0; j < cps_key->trigger_key_len - cps_key->scan_key_len; j++)
              if (press_trigger_key_set.remove(cps_key->trigger_keys[j]))
                send_key(cps_key->trigger_keys[j], false);
        }

        // 未触发的时候释放了中间状态
        // 仅仅触发了一个的时候
        else if (key_pressed_num == 1)
          is_short_recover_key = true;
      }

      // 非scan_key和非insert key
      else if (!check_in_allow_insert_key_list(cps_key, keycode))
      {
        cps_key->unmatched--;

        // 如果减去之后会恢复match的阻塞状态
        if (cps_key->unmatched == 0)
          for (j = 0; j < cps_key->matched; j++)
            if (blocked_press_key_set.add(cps_key->scan_keys[j]))
              send_key(cps_key->scan_keys[j], false);
      }
    }
  }

  if (!block)
  {
    send_key(keycode, pressed);
  }

  if (is_short_recover_key)
  {
    send_key(keycode, true);
    delay(20);
    send_key(keycode, false);
  }
}

bool check_in_allow_insert_key_list(composite_key_t *cps_key, uint8_t keycode)
{
  uint8_t i;
  for (i = 0; i < cps_key->key_allow_insert_len; i++)
    if (cps_key->key_allow_insert[i] == keycode)
      return true;
  return false;
}
