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

#include <implementations.h>

void (*const canutils_scene_on_enter_handlers[])(void*) = {
    canutils_scene_on_enter_main_menu, // MainMenu
    canutils_scene_on_enter_configuration, // Configuration
    canutils_scene_on_enter_can_dump, // CanDump
    canutils_scene_on_enter_can_player, // CanPlayer
    canutils_scene_on_enter_can_send, // CanSend
    canutils_scene_on_enter_can_gen, // CanGen
    canutils_scene_on_enter_can_sequence, // CanSequence
    canutils_scene_on_enter_can_sniffer, // CanSniffer
    canutils_scene_on_enter_can_busload, // CanBusLoad
    canutils_scene_on_enter_can_calcbittiming, // CanCalcBitTiming
    canutils_scene_on_enter_can_fdtest, // CanFdTest
    canutils_scene_on_enter_can_probe, // CanProbe
};
