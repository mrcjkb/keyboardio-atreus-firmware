/* -*- mode: c++ -*-
 * Atreus -- Chrysalis-enabled Sketch for the Keyboardio Atreus
 * Copyright (C) 2018, 2019  Keyboard.io, Inc
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "MrcJkb's firmware version 1.1.0"
#endif

#include "Kaleidoscope.h"
#include "Kaleidoscope-EEPROM-Settings.h"
#include "Kaleidoscope-EEPROM-Keymap.h"
#include "Kaleidoscope-FocusSerial.h"
#include "Kaleidoscope-TapDance.h"
#include "Kaleidoscope-Macros.h"
#include "Kaleidoscope-Qukeys.h"
#include "Key-Definitions.h"

enum {
  MACRO_QWERTY,
  MACRO_VERSION_INFO
};

enum {
  QWERTY,
  FUN,
  UPPER_0,
  UPPER_1
};

// List of tap dance indices:
#define TD_A 0
#define TD_O 1
#define TD_U 2
#define TD_S 3
#define TD_E 4

/* *INDENT-OFF* */
KEYMAPS(
  [QWERTY] = KEYMAP_STACKED
  (
       Key_Q   ,Key_W   ,Key_E       ,Key_R         ,Key_T
      ,Key_A   ,Key_S   ,Key_D       ,Key_F         ,Key_G
      ,Key_Z   ,Key_X   ,Key_C       ,Key_V         ,Key_B, Key_Backtick
      ,Key_Esc ,Key_Tab ,Key_LeftGui ,Key_LeftShift ,Key_Backspace ,Key_LeftControl

                     ,Key_Y     ,Key_U      ,Key_I     ,Key_O      ,Key_P
                     ,Key_H     ,Key_J      ,Key_K     ,Key_L      ,Key_Semicolon
       ,Key_Backslash,Key_N     ,Key_M      ,Key_Comma ,Key_Period ,Key_Slash
       ,Key_LeftAlt  ,Key_Space ,ShiftToLayer(FUN)    ,Key_Minus ,Key_Quote  ,Key_Enter
  ),

  [FUN] = KEYMAP_STACKED
  (
       Key_Exclamation ,Key_At           ,Key_UpArrow   ,Key_Dollar           ,Key_Percent
      ,Key_LeftParen   ,Key_LeftArrow    ,Key_DownArrow ,Key_RightArrow       ,Key_RightParen
      ,Key_LeftBracket ,Key_RightBracket ,Key_Hash      ,Key_LeftCurlyBracket ,Key_RightCurlyBracket ,Key_Caret
      ,LockLayer(UPPER_0)       ,Key_Insert       ,Key_LeftGui   ,Key_LeftShift        ,Key_Delete         ,Key_LeftControl

                   ,Key_PageUp   ,Key_7 ,Key_8      ,Key_9 ,Key_Backspace
                   ,Key_PageDown ,Key_4 ,Key_5      ,Key_6 ,___
      ,Key_And     ,Key_Star     ,Key_1 ,Key_2      ,Key_3 ,Key_Plus
      ,Key_LeftAlt ,Key_Space    ,___   ,Key_Period ,Key_0 ,Key_Equals
   ),

  [UPPER_0] = KEYMAP_STACKED
  (
       Key_Insert            ,Key_Home                 ,Key_UpArrow   ,Key_End        ,Key_PageUp
      ,Key_Delete            ,Key_LeftArrow            ,Key_DownArrow ,Key_RightArrow ,Key_PageDown
      ,M(MACRO_VERSION_INFO) ,Consumer_VolumeIncrement ,Consumer_Mute           ,Consumer_DisplayBrightnessDecrement            ,Consumer_DisplayBrightnessIncrement ,___
      ,LockLayer(UPPER_1)   ,Consumer_VolumeDecrement ,___           ,___            ,___ ,___

                ,Key_UpArrow   ,Key_F7              ,Key_F8          ,Key_F9         ,Key_F10
                ,Key_DownArrow ,Key_F4              ,Key_F5          ,Key_F6         ,Key_F11
      ,___      ,XXX           ,Key_F1              ,Key_F2          ,Key_F3         ,Key_F12
      ,___      ,___           ,MoveToLayer(QWERTY) ,Key_PrintScreen ,Key_ScrollLock ,Consumer_PlaySlashPause
   ),

  [UPPER_1] = KEYMAP_STACKED
  (
       ___            ,___                 ,TD(TD_E)   ,___        ,___
      ,TD(TD_A)            ,TD(TD_S)            ,___ ,___ ,___
      ,___ ,___ ,___           ,___            ,___ ,___
      ,MoveToLayer(QWERTY)   ,___ ,___           ,___            ,___ ,___

                ,___   ,TD(TD_U)              ,___          ,TD(TD_O)         ,___
                ,___ ,___              ,___          ,___         ,___
      ,___      ,___           ,___              ,___          ,___         ,___
      ,___      ,___           ,MoveToLayer(UPPER_0) ,___ ,___ ,___
   )
)
/* *INDENT-ON* */

KALEIDOSCOPE_INIT_PLUGINS(
  EEPROMSettings,
  EEPROMKeymap,
  Focus,
  FocusEEPROMCommand,
  FocusSettingsCommand,
  Qukeys,
  TapDance,
  Macros
);

const macro_t *macroAction(uint8_t macroIndex, uint8_t keyState) {
  switch (macroIndex) {
    case MACRO_QWERTY:
      // This macro is currently unused, but is kept around for compatibility
      // reasons. We used to use it in place of `MoveToLayer(QWERTY)`, but no
      // longer do. We keep it so that if someone still has the old layout with
      // the macro in EEPROM, it will keep working after a firmware update.
      Layer.move(QWERTY);
      break;
    case MACRO_VERSION_INFO:
      if (keyToggledOn(keyState)) {
        return Macros.type(PSTR("Keyboardio Atreus - Kaleidoscope "), PSTR(BUILD_INFORMATION));
      }
      break;
    default:
      break;
  }

  return MACRO_NONE;
}

void tapDanceAction(uint8_t tap_dance_index, KeyAddr key_addr, uint8_t tap_count, kaleidoscope::plugin::TapDance::ActionType tap_dance_action) {
  switch (tap_dance_index) {
    case TD_A:
      return tapDanceActionKeys(tap_count, tap_dance_action, Key_aUml, Key_AUml);
    case TD_O:
      return tapDanceActionKeys(tap_count, tap_dance_action, Key_oUml, Key_OUml);
    case TD_U:
      return tapDanceActionKeys(tap_count, tap_dance_action, Key_uUml, Key_UUml);
    case TD_E:
      return tapDanceActionKeys(tap_count, tap_dance_action, Key_Eur, Key_eGrave);
    case TD_S:
      return tapDanceActionKeys(tap_count, tap_dance_action, Key_de_SS, Key_Paragraph);
  } 
}

void setup() {
  TapDance.time_out = 180;
  Kaleidoscope.setup();
  //EEPROMKeymap.setup(10);
}

void loop() {
  Kaleidoscope.loop();
}
