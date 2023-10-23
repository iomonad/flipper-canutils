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

#include <furi.h>
#include <furi_hal_spi.h>
#include <furi_hal_spi_config.h>

#include <canutils_icons.h>

#include "scene.h"
#include "canutils.h"

static Application *canutils_context_setup(void) {
  FURI_LOG_T(TAG, "canutils_context_setup");

  Application *app = (Application*)malloc(sizeof(Application));
  if (app == NULL) {
    FURI_LOG_W(TAG, "allocation failed");
  }

  canutils_scene_manager_init(app);
  canutils_view_dispatcher_init(app);
  return app;
}

static void canutils_context_free(Application *app) {
  if (app->scene_manager) {
    scene_manager_free(app->scene_manager);
  }

  view_dispatcher_remove_view(app->view_dispatcher, View_Menu);
  view_dispatcher_remove_view(app->view_dispatcher, View_Popup);

  view_dispatcher_free(app->view_dispatcher);

  if (app->menu) {
    menu_free(app->menu);
  }

  if (app->popup) {
    popup_free(app->popup);
  }

  free(app);
}

int32_t canutils_app(void* p) {
  UNUSED(p);

  FURI_LOG_I(TAG, "context setup");
  Application *app = canutils_context_setup();
  Gui         *gui = furi_record_open(RECORD_GUI);

  FURI_LOG_I(TAG, "dispatcher setup");
  view_dispatcher_attach_to_gui(app->view_dispatcher, gui, ViewDispatcherTypeFullscreen);

  FURI_LOG_I(TAG, "scene manager next scene");
  scene_manager_next_scene(app->scene_manager, ViewScene_Menu);
  FURI_LOG_I(TAG, "run view dispatcher");
  view_dispatcher_run(app->view_dispatcher);

  FURI_LOG_I(TAG, "context cleanup");
  furi_record_close(RECORD_GUI);
  canutils_context_free(app);
  return 0;
}
