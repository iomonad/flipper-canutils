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

#ifndef __MCP2518FD_H__
#define __MCP2518FD_H__

#include <stdbool.h>

#include <furi.h>
#include <furi_hal_spi.h>
#include <furi_hal_spi_types.h>
#include <furi_hal_spi_config.h>

typedef struct {
     bool initialized;
     FuriHalSpiBusHandle handle;
} mcp2518fd_device_t;

/* primitive */
mcp2518fd_device_t *mcp25158fd_register_driver(FuriHalSpiBusHandle *handle);
bool mcp25158fd_release_driver(mcp2518fd_device_t *device);

#endif /* __MCP2518FD_H__ */
