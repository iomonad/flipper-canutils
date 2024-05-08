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

bool canutils_scene_on_event_can_dump(void* context, SceneManagerEvent event) {
    UNUSED(context);
    UNUSED(event);

    return false;
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

void canutils_scene_on_exit_can_dump(void* context) {
    Application* app = (Application*)context;

    popup_reset(app->popup);
}

/**
 * ____   ____.__
 * \   \ /   /|__| ______  _  __
 *  \   Y   / |  |/ __ \ \/ \/ /
 *   \     /  |  \  ___/\     /
 *    \___/   |__|\___  >\/\_/
 *                    \/
 */

void canutils_scene_on_enter_can_dump(void* context) {
    Application* app = (Application*)context;

    popup_reset(app->popup);
    popup_set_context(app->popup, app);

    popup_set_header(app->popup, "can_dump", 64, 10, AlignCenter, AlignTop);

    view_dispatcher_switch_to_view(app->view_dispatcher, View_Popup);
}
