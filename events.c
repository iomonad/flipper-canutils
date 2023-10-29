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

#include <scene.h>
#include <canutils.h>

/* MAIN MENU*/

bool canutils_scene_on_event_main_menu(void *context, SceneManagerEvent event) {
  Application *app = (Application*)context;
  bool is_consumed = false;

  switch (event.type) {
  case SceneManagerEventTypeCustom: {
    switch (event.event) {
    case Event_Config:
      scene_manager_next_scene(app->scene_manager, ViewScene_Configuration);
      is_consumed = true;
      break;
    case Event_CanDump:
      scene_manager_next_scene(app->scene_manager, ViewScene_CanDump);
      is_consumed = true;
      break;
    case Event_CanPlayer:
      scene_manager_next_scene(app->scene_manager, ViewScene_CanPlayer);
      is_consumed = true;
      break;
    case Event_CanSend:
      scene_manager_next_scene(app->scene_manager, ViewScene_CanSend);
      is_consumed = true;
      break;
    case Event_CanGen:
      scene_manager_next_scene(app->scene_manager, ViewScene_CanGen);
      is_consumed = true;
      break;
    case Event_CanSequence:
      scene_manager_next_scene(app->scene_manager, ViewScene_CanSequence);
      is_consumed = true;
      break;
    case Event_CanSniffer:
      scene_manager_next_scene(app->scene_manager, ViewScene_CanSniffer);
      is_consumed = true;
      break;
    case Event_CanBusLoad:
      scene_manager_next_scene(app->scene_manager, ViewScene_CanBusLoad);
      is_consumed = true;
      break;
    case Event_CanCalcBitTiming:
      scene_manager_next_scene(app->scene_manager, ViewScene_CanCalcBitTiming);
      is_consumed = true;
      break;
    case Event_CanFdTest:
      scene_manager_next_scene(app->scene_manager, ViewScene_CanDump);
      is_consumed = true;
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

  Application* app = (Application*)context;
  menu_reset(app->menu);
}

/* UNIMPLEMENTED */

static bool unimplemented_on_event(void *context,
				   SceneManagerEvent event) {
  Application* app = (Application*)context;

  UNUSED(app);
  UNUSED(context);
  UNUSED(event);


  return false;
}

static void unimplemented_on_exit(void *context) {
  Application* app = (Application*)context;

  UNUSED(app);
  popup_reset(app->popup);
}


/* Implementations */


bool (*const canutils_scene_on_event_handlers[])(void*, SceneManagerEvent) = {
  canutils_scene_on_event_main_menu,
  unimplemented_on_event, // Configuration
  unimplemented_on_event, // CanDump
  unimplemented_on_event, // CanPlayer
  unimplemented_on_event, // CanSend
  unimplemented_on_event, // CanGen
  unimplemented_on_event, // CanSequence
  unimplemented_on_event, // CanSniffer
  unimplemented_on_event, // CanBusLoad
  unimplemented_on_event, // CanCalcBitTiming
  unimplemented_on_event, // CanFdTest
};


void (*const canutils_scene_on_exit_handlers[])(void*) = {
  canutils_scene_on_exit_main_menu,
  unimplemented_on_exit, // Configuration
  unimplemented_on_exit, // CanDump
  unimplemented_on_exit, // CanPlayer
  unimplemented_on_exit, // CanSend
  unimplemented_on_exit, // CanGen
  unimplemented_on_exit, // CanSequence
  unimplemented_on_exit, // CanSniffer
  unimplemented_on_exit, // CanBusLoad
  unimplemented_on_exit, // CanCalcBitTiming
  unimplemented_on_exit, // CanFdTest
};
