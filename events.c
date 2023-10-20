/*
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * (C) Author: iomonad <iomonad@riseup.net>
 */

#include "scene.h"
#include "canutils.h"

/* MAIN MENU*/

bool canutils_scene_on_event_main_menu(void *context, SceneManagerEvent event) {
  Application *app = (Application*)context;
  bool is_consumed = false;

  switch (event.type) {
  case SceneManagerEventTypeCustom: {
    switch (event.event) {
    case Event_CanDump:
      break;
    case Event_CanPlayer:
      break;
    case Event_CanSend:
      break;
    case Event_CanGen:
      break;
    case Event_CanSequence:
      break;
    case Event_CanSniffer:
      break;
    case Event_CanBusLoad:
      break;
    case Event_CanCalcBitTiming:
      break;
    case Event_CanFdTest:
      break;
    }
    break;
  }
  default:
    is_consumed = false;
    break;
  }
  return is_consumed;
}


void canutils_scene_on_exit_main_menu(void* context) {
  FURI_LOG_T(TAG, "canutils_scene_on_exit_main_menu");

  Application* app = context;
  menu_reset(app->menu);
}


bool (*const canutils_scene_on_event_handlers[])(void*, SceneManagerEvent) = {
  canutils_scene_on_event_main_menu,
};


void (*const canutils_scene_on_exit_handlers[])(void*) = {
  canutils_scene_on_exit_main_menu,
};
