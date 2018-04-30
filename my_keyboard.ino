#include "mHID-Project/HID-Project.h"
#include "mHID-Project/HID-Settings.h"

#include "set.h"
#include "keycode.h"
#include "keymap.h"

#define KEYBOARD_ROWS 5
#define KEYBOARD_COLS 13
#define DEBOUNCE 5

const uint8_t row_pins[KEYBOARD_ROWS] = {1, 0, 2, 3, 4};
const uint8_t col_pins[KEYBOARD_COLS] = {};

const uint8_t keymap[KEYBOARD_ROWS][KEYBOARD_COLS] =
    KEYMAP(
        ESC, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, MINS, EQL, GRV,
        TAB, Q, W, E, R, T, Y, U, I, O, P, LBRC, RBRC,
        CAPS, A, S, D, F, G, H, J, K, L, SCLN, QUOT,
        LSFT, Z, X, C, V, B, N, M, COMM, DOT, SLSH,
        LCTL, LALT, DEL, LGUI, RGUI, SPC, RCTL, RSFT, BSLS);

uint16_t curr_col_state[KEYBOARD_ROWS];
uint16_t prev_col_state[KEYBOARD_ROWS];
uint16_t temp_col_state[KEYBOARD_ROWS];
uint8_t key_press_stack[KEYBOARD_COLS * KEYBOARD_ROWS] = {};
uint8_t key_release_stack[KEYBOARD_COLS * KEYBOARD_ROWS] = {};
uint8_t key_pressed_num = 0;
uint8_t key_released_num = 0;
Set press_trigger_key_set;
Set blocked_press_key_set;

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

// 函数定义
void key_event(uint8_t row, uint8_t col, bool pressed);
uint8_t get_keycode(uint8_t row, uint8_t col);
void trigger_composite_key(uint8_t keycode, bool pressed);

void setup()
{
  Consumer.begin();
  NKROKeyboard.begin();

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

bool check_in_allow_insert_key_list(composite_key_t *cps_key, uint8_t keycode)
{
  uint8_t i;
  for (i = 0; i < cps_key->key_allow_insert_len; i++)
    if (cps_key->key_allow_insert[i] == keycode)
      return true;
  return false;
}

void trigger_composite_key(uint8_t keycode, bool pressed)
{
  uint8_t i, j;
  bool block = false;
  bool is_short_recover_key = false;

  composite_key_t *cps_key;
  for (i = 0; i < composite_key_len; i++)
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
