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

/*
 * MAIN MENU
 */

static void canutils_scene_on_enter_main_menu(void *context) {
  Application *app = (Application*)context;

  menu_reset(app->menu);
  menu_add_item(app->menu, "CAN Dump", NULL, Select_CanDump, canutils_scene_main_menu_callback_handler, app);
  menu_add_item(app->menu, "CAN Player", NULL, Select_CanPlayer, canutils_scene_main_menu_callback_handler, app);
  menu_add_item(app->menu, "CAN Send", NULL, Select_CanSend, canutils_scene_main_menu_callback_handler, app);
  menu_add_item(app->menu, "CAN Gen", NULL, Select_CanGen, canutils_scene_main_menu_callback_handler, app);
  menu_add_item(app->menu, "CAN Sequence", NULL, Select_CanSequence, canutils_scene_main_menu_callback_handler, app);
  menu_add_item(app->menu, "CAN Sniffer", NULL, Select_CanSniffer, canutils_scene_main_menu_callback_handler, app);
  menu_add_item(app->menu, "CAN BusLoad", NULL, Select_CanBusLoad, canutils_scene_main_menu_callback_handler, app);
  menu_add_item(app->menu, "CAN CalcBitTiming", NULL, Select_CanCalcBitTiming, canutils_scene_main_menu_callback_handler, app);
  menu_add_item(app->menu, "CAN FdTest", NULL, Select_CanFdTest, canutils_scene_main_menu_callback_handler, app);

  view_dispatcher_switch_to_view(app->view_dispatcher, ViewScene_Menu);
}

/* DEFAULT VIEW */
void unimplemented_view(void* context) {
  Application *app = (Application*)context;

  popup_reset(app->popup);
  popup_set_context(app->popup, app);

  popup_set_header(app->popup, "Unimplemented", 64, 10, AlignCenter, AlignTop);
  popup_set_icon(app->popup, 10, 10, &I_cvc_36x36);
  popup_set_text(app->popup, "Unimplemented", 64, 20, AlignLeft, AlignTop);
  view_dispatcher_switch_to_view(app->view_dispatcher, View_Popup);
}


void (*const canutils_scene_on_enter_handlers[])(void*) = {
  canutils_scene_on_enter_main_menu,
  unimplemented_view, // CanDump
  unimplemented_view, // CanPlayer
  unimplemented_view, // CanSend
  unimplemented_view, // CanGen
  unimplemented_view, // CanSequence
  unimplemented_view, // CanSniffer
  unimplemented_view, // CanBusLoad
  unimplemented_view, // CanCalcBitTiming
  unimplemented_view, // CanFdTest
};
