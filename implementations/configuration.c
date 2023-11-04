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

#include <views.h>
#include <scene.h>
#include <canutils.h>
#include <mcp2515.h>

static char* mcp_speed_names[] =
  {"5k",
   "10k",
   "20k",
   "31.25k",
   "33k",
   "40k",
   "50k",
   "80k",
   "83.3k",
   "95k",
   "100k",
   "125k",
   "200k",
   "250k",
   "500k",
   "1000k"
  };

static char *mcp_clock_names[] =
  {"20Mhz",
   "16Mhz",
   "8Mhz"
  };

/* Configuration Updater */

static void option_speed_change(VariableItem* item) {
  Application* app = variable_item_get_context(item);
  uint8_t index = variable_item_get_current_value_index(item);
  variable_item_set_current_value_text(item, mcp_speed_names[index]);

  FURI_LOG_T(TAG, "models changed");

  can_preferences_t* model = view_get_model(app->conf_model);
  model->speed = index;
}

static void option_clock_change(VariableItem* item) {
  Application* app = variable_item_get_context(item);
  uint8_t index = variable_item_get_current_value_index(item);
  variable_item_set_current_value_text(item, mcp_clock_names[index]);

  FURI_LOG_T(TAG, "models changed");

  can_preferences_t* model = view_get_model(app->conf_model);
  model->clock = index;
}


/* View Setup */
void canutils_scene_on_enter_configuration(void *context) {
  Application *app = (Application*)context;
  can_preferences_t* model = view_get_model(app->conf_model);
  VariableItem* item = NULL;

  variable_item_list_reset(app->variable_item_list);
  variable_item_list_add(app->variable_item_list, "MCP2515 Configuration", 0, NULL, NULL);

  /* SPEED SETUP */
  item = variable_item_list_add(app->variable_item_list,
					      "Bitrate",
					      COUNT_OF(mcp_speed_names),
					      option_speed_change,
					      app);
  uint8_t setting_speed_index = model->speed;
  variable_item_set_current_value_index(item, setting_speed_index);
  variable_item_set_current_value_text(item, mcp_speed_names[setting_speed_index]);

  /* CLOCK SETUP */
  item = variable_item_list_add(app->variable_item_list,
				"Clock",
				COUNT_OF(mcp_clock_names),
				option_clock_change,
				app);

  uint8_t setting_clock_index = model->clock;
  variable_item_set_current_value_index(item, setting_clock_index);
  variable_item_set_current_value_text(item, mcp_clock_names[setting_clock_index]);

  view_dispatcher_switch_to_view(app->view_dispatcher, View_VariableItemList);
}
