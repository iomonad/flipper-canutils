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

/**
 * ___________                    __
 * \_   _____/__  __ ____   _____/  |_
 *  |    __)_\  \/ // __ \ /    \   __\
 *  |        \\   /\  ___/|   |  \  |
 * /_______  / \_/  \___  >___|  /__|
 *         \/           \/     \/
 */

bool canutils_scene_on_event_main_menu(void* context, SceneManagerEvent event) {
    Application* app = (Application*)context;
    bool is_consumed = false;

    switch(event.type) {
    case SceneManagerEventTypeCustom: {
        switch(event.event) {
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
            scene_manager_next_scene(app->scene_manager, ViewScene_CanFdTest);
            is_consumed = true;
            break;
        case Event_CanProbe:
            scene_manager_next_scene(app->scene_manager, ViewScene_CanProbe);
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

/**
 * ___________      .__  __
 * \_   _____/__  __|__|/  |_
 *  |    __)_\  \/  /  \   __\
 *  |        \>    <|  ||  |
 * /_______  /__/\_ \__||__|
 *         \/      \/
 *
 */

void canutils_scene_on_exit_main_menu(void* context) {
    FURI_LOG_T(TAG, "canutils_scene_on_exit_main_menu");

    Application* app = (Application*)context;
    menu_reset(app->menu);
}

/**
 * ____   ____.__
 * \   \ /   /|__| ______  _  __
 *  \   Y   / |  |/ __ \ \/ \/ /
 *   \     /  |  \  ___/\     /
 *    \___/   |__|\___  >\/\_/
 *                    \/
 */

void canutils_scene_on_enter_main_menu(void* context) {
    Application* app = (Application*)context;

    menu_reset(app->menu);

    menu_add_item(
        app->menu,
        "Configuration",
        NULL,
        Select_Config,
        canutils_scene_main_menu_callback_handler,
        app);
    menu_add_item(
        app->menu,
        "CAN Dump",
        NULL,
        Select_CanDump,
        canutils_scene_main_menu_callback_handler,
        app);
    menu_add_item(
        app->menu,
        "CAN Player",
        NULL,
        Select_CanPlayer,
        canutils_scene_main_menu_callback_handler,
        app);
    menu_add_item(
        app->menu,
        "CAN Send",
        NULL,
        Select_CanSend,
        canutils_scene_main_menu_callback_handler,
        app);
    menu_add_item(
        app->menu, "CAN Gen", NULL, Select_CanGen, canutils_scene_main_menu_callback_handler, app);
    menu_add_item(
        app->menu,
        "CAN Sequence",
        NULL,
        Select_CanSequence,
        canutils_scene_main_menu_callback_handler,
        app);
    menu_add_item(
        app->menu,
        "CAN Sniffer",
        NULL,
        Select_CanSniffer,
        canutils_scene_main_menu_callback_handler,
        app);
    menu_add_item(
        app->menu,
        "CAN BusLoad",
        NULL,
        Select_CanBusLoad,
        canutils_scene_main_menu_callback_handler,
        app);
    menu_add_item(
        app->menu,
        "CAN CalcBitTiming",
        NULL,
        Select_CanCalcBitTiming,
        canutils_scene_main_menu_callback_handler,
        app);
    menu_add_item(
        app->menu,
        "CAN FdTest",
        NULL,
        Select_CanFdTest,
        canutils_scene_main_menu_callback_handler,
        app);
    menu_add_item(
        app->menu,
        "CAN Probe",
        NULL,
        Select_CanProbe,
        canutils_scene_main_menu_callback_handler,
        app);

    view_dispatcher_switch_to_view(app->view_dispatcher, ViewScene_Menu);
}
