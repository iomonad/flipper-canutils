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

#include <canutils.h>

/* MAIN MENU */
bool canutils_scene_on_event_main_menu(void *context, SceneManagerEvent event);
void canutils_scene_on_exit_main_menu(void* context);

void canutils_scene_on_enter_main_menu(void *context);

/* CONFIGURATION */
bool canutils_scene_on_event_configuration(void *context, SceneManagerEvent event);
void canutils_scene_on_exit_configuration(void *context);
void canutils_scene_on_enter_configuration(void *context);

/* can_dump */
bool canutils_scene_on_event_can_dump(void *context, SceneManagerEvent event);
void canutils_scene_on_exit_can_dump(void *context);
void canutils_scene_on_enter_can_dump(void *context);

/* can_probe */
bool canutils_scene_on_event_can_probe(void *context, SceneManagerEvent event);
void canutils_scene_on_exit_can_probe(void *context);
void canutils_scene_on_enter_can_probe(void *context);

/* can_player */
bool canutils_scene_on_event_can_player(void *context, SceneManagerEvent event);
void canutils_scene_on_exit_can_player(void *context);
void canutils_scene_on_enter_can_player(void *context);

/* can_send */
bool canutils_scene_on_event_can_send(void *context, SceneManagerEvent event);
void canutils_scene_on_exit_can_send(void *context);
void canutils_scene_on_enter_can_send(void *context);

/* can_gen */
bool canutils_scene_on_event_can_gen(void *context, SceneManagerEvent event);
void canutils_scene_on_exit_can_gen(void *context);
void canutils_scene_on_enter_can_gen(void *context);

/* can_sequence */
bool canutils_scene_on_event_can_sequence(void *context, SceneManagerEvent event);
void canutils_scene_on_exit_can_sequence(void *context);
void canutils_scene_on_enter_can_sequence(void *context);

/* can_sniffer */
bool canutils_scene_on_event_can_sniffer(void *context, SceneManagerEvent event);
void canutils_scene_on_exit_can_sniffer(void *context);
void canutils_scene_on_enter_can_sniffer(void *context);

/* can_busload */
bool canutils_scene_on_event_can_busload(void *context, SceneManagerEvent event);
void canutils_scene_on_exit_can_busload(void *context);
void canutils_scene_on_enter_can_busload(void *context);

/* can_calcbittiming */
bool canutils_scene_on_event_can_calcbittiming(void *context, SceneManagerEvent event);
void canutils_scene_on_exit_can_calcbittiming(void *context);
void canutils_scene_on_enter_can_calcbittiming(void *context);

/* can_fdtest */
bool canutils_scene_on_event_can_fdtest(void *context, SceneManagerEvent event);
void canutils_scene_on_exit_can_fdtest(void *context);
void canutils_scene_on_enter_can_fdtest(void *context);

/* can_probe */
bool canutils_scene_on_event_can_probe(void *context, SceneManagerEvent event);
void canutils_scene_on_exit_can_probe(void *context);
void canutils_scene_on_enter_can_probe(void *context);
