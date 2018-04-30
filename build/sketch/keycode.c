#ifndef KEYCODE_C
#define KEYCODE_C

#include "mHID-Project/HID-Project.h"
#include "mHID-Project/HID-Settings.h"

#include "stdint.h"
#include "keycode.h"

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