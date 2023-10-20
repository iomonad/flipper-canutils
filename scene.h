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

#ifndef __SCENE_H__
#define __SCENE_H__

#include <gui/gui.h>
#include <gui/icon_i.h>
#include <gui/view_dispatcher.h>
#include <gui/scene_manager.h>
#include <gui/modules/menu.h>
#include <gui/modules/popup.h>

#include "views.h"
#include "events.h"

typedef enum {
  ViewScene_Menu = 0x0,

  ViewScene_CanDump,
  ViewScene_CanPlayer,
  ViewScene_CanSend,
  ViewScene_CanGen,
  ViewScene_CanSequence,
  ViewScene_CanSniffer,
  ViewScene_CanBusLoad,
  ViewScene_CanCalcBitTiming,
  ViewScene_CanFdTest,

  ViewScene_Total
} ApplicationScene;


typedef enum {
  View_Menu,
  View_Popup
} ApplicationView;


typedef struct {
  SceneManager   *scene_manager;
  ViewDispatcher *view_dispatcher;
  Menu           *menu;
  Popup          *popup;
} Application;


typedef enum {
  Event_CanDump,
  Event_CanPlayer,
  Event_CanSend,
  Event_CanGen,
  Event_CanSequence,
  Event_CanSniffer,
  Event_CanBusLoad,
  Event_CanCalcBitTiming,
  Event_CanFdTest,
} ApplicationEvents;


typedef enum {
  Select_CanDump,
  Select_CanPlayer,
  Select_CanSend,
  Select_CanGen,
  Select_CanSequence,
  Select_CanSniffer,
  Select_CanBusLoad,
  Select_CanCalcBitTiming,
  Select_CanFdTest
} ApplicationSelection;

const SceneManagerHandlers ev_handler = {
  .on_enter_handlers = canutils_scene_on_enter_handlers,
  .on_event_handlers = canutils_scene_on_event_handlers,
  .on_exit_handlers  = canutils_scene_on_exit_handlers,
  .scene_num         = ViewScene_Total};

/* PROTO */

void canutils_scene_main_menu_callback_handler(void *context, const uint32_t index);
void canutils_scene_manager_init(Application *app);
void canutils_view_dispatcher_init(Application *app);

#endif // __SCENE_H__
