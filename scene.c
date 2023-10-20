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

static void

/*
 * @desc TODO
 */
void canutils_scene_main_menu_callback_handler(void *context,
					       const uint32_t index) {
  FURI_LOG_T(TAG, "canutils_main_menu");

  const Application *app = (Application*)context;

  switch (index) {
  case Select_CanDump:
    scene_manager_handle_custom_event(app->scene_manager, Event_CanDump);
    break;
  case Select_CanPlayer:
    scene_manager_handle_custom_event(app->scene_manager, Event_CanPlayer);
    break;
  case Select_CanSend:
    scene_manager_handle_custom_event(app->scene_manager, Event_CanSend);
    break;
  case Select_CanGen:
    scene_manager_handle_custom_event(app->scene_manager, Event_CanGen);
    break;
  case Select_CanSequence:
    scene_manager_handle_custom_event(app->scene_manager, Event_CanSequence);
    break;
  case Select_CanSniffer:
    scene_manager_handle_custom_event(app->scene_manager, Event_CanSniffer);
    break;
  case Select_CanBusLoad:
    scene_manager_handle_custom_event(app->scene_manager, Event_CanBusLoad);
    break;
  case Select_CanCalcBitTiming:
    scene_manager_handle_custom_event(app->scene_manager, Event_CanCalcBitTiming);
    break;
  case Select_CanFdTest:
    scene_manager_handle_custom_event(app->scene_manager, Event_CanFdTest);
    break;
  default:
    /* Fallback? */
    scene_manager_handle_custom_event(app->scene_manager, Event_CanDump);
    break;
  }
}

void canutils_scene_manager_init(Application *app) {
  FURI_LOG_T(TAG, "scene setup");
  app->scene_manager = scene_manager_alloc(&ev_handler, app);

  return ;
}

void canutils_view_dispatcher_init(Application *app) {

  app->view_dispatcher = view_dispatcher_alloc();
  view_dispatcher_enable_queue(app->view_dispatcher);

  app->menu = menu_alloc();
  app->popup = popup_alloc();

  /* Handler to implement */
  return ;
}
