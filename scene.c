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

/*
 * @desc TODO
 */
void canutils_scene_main_menu_callback_handler(void *context,
					       const uint32_t index) {
  FURI_LOG_T(TAG, "canutils_main_menu");

  const Application *app = (Application*)context;

  switch (index) {
  case Select_Config:
    scene_manager_handle_custom_event(app->scene_manager, Event_Config);
    break;
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
  case Select_CanProbe:
    scene_manager_handle_custom_event(app->scene_manager, Event_CanProbe);
    break;
  default:
    /* Fallback? */
    scene_manager_handle_custom_event(app->scene_manager, Event_Config);
    break;
  }
}

static bool canutils_scene_manager_custom_event_callback(void* context,
							 uint32_t custom_event) {
    furi_assert(context);
    Application* app = (Application*)context;

    FURI_LOG_T(TAG, "canutils_scene_event_callback_setup");
    return scene_manager_handle_custom_event(app->scene_manager, custom_event);
}

static bool canutils_scene_manager_navigation_event_callback(void* context) {
  furi_assert(context);
  Application* app = (Application*)context;

  FURI_LOG_T(TAG, "canutils_scene_manager_callback_setup");
  return scene_manager_handle_back_event(app->scene_manager);
}


/* Setup */

void canutils_scene_manager_init(Application *app) {
  FURI_LOG_T(TAG, "canutils_scene_manager_setup");
  app->scene_manager = scene_manager_alloc(&ev_handler, app);
}

void canutils_view_dispatcher_init(Application *app) {

  FURI_LOG_T(TAG, "canutils_view_dispatcher_setup");
  app->view_dispatcher = view_dispatcher_alloc();

  if (app->view_dispatcher == NULL) {
    FURI_LOG_W(TAG, "dispatcher allocation failure");
  }

  view_dispatcher_enable_queue(app->view_dispatcher);

  app->menu = menu_alloc();
  app->popup = popup_alloc();
  app->submenu = submenu_alloc();
  app->widget = widget_alloc();
  app->text_input = text_input_alloc();
  app->variable_item_list = variable_item_list_alloc();
  app->conf_model = view_alloc();

  view_dispatcher_set_event_callback_context(app->view_dispatcher, app);
  view_dispatcher_set_custom_event_callback(app->view_dispatcher,
					    canutils_scene_manager_custom_event_callback);
  view_dispatcher_set_navigation_event_callback(app->view_dispatcher,
						canutils_scene_manager_navigation_event_callback);

  /* View Dispatcher */
  view_dispatcher_add_view(app->view_dispatcher, View_Menu,  menu_get_view(app->menu));
  view_dispatcher_add_view(app->view_dispatcher, View_Popup, popup_get_view(app->popup));
  view_dispatcher_add_view(app->view_dispatcher, View_SubMenu, submenu_get_view(app->submenu));
  view_dispatcher_add_view(app->view_dispatcher, View_Widget, widget_get_view(app->widget));
  view_dispatcher_add_view(app->view_dispatcher, View_TextInput, text_input_get_view(app->text_input));
  view_dispatcher_add_view(app->view_dispatcher, View_VariableItemList,
			   variable_item_list_get_view(app->variable_item_list));

  view_dispatcher_add_view(app->view_dispatcher, View_Models, app->conf_model);
}
