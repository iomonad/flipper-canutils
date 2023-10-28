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
 * Copyright (c) 2013 Seeed Technology Inc. Copyright (c) 2016 Dmitry
 * (C) Author: iomonad <iomonad@riseup.net>
 */

#include <furi.h>
#include <furi_hal_resources.h>
#include <furi_hal_spi.h>
#include <furi_hal_spi_types.h>
#include <furi_hal_spi_config.h>

#include <canutils.h>
#include <mcp2515.h>

/** Read MCP2515 register through SPI
 *
 * @param      handle  - pointer to FuriHalSpiHandle | NULL for default preset
 *
 * @notes      https://github.com/flipperdevices/flipperzero-firmware/blob/dev/firmware/targets/f7/furi_hal/furi_hal_spi_config.c#L344C21-L344C53
 *             A6 -> MISO
 *             A7 -> MOSI
 *             B3 -> SCK
 *             A6 -> CS
 *
 * @return     the actual handler instance
 */
FuriHalSpiBusHandle mcp2515_register_driver(FuriHalSpiBusHandle *handle) {

  FURI_LOG_I(TAG, "mcp2515_register_driver");
  if (handle == NULL) {
    FURI_LOG_I(TAG, "mcp2515_register_driver - using default external preset");
    furi_hal_spi_bus_handle_init(&furi_hal_spi_bus_handle_external);
    furi_hal_spi_acquire(&furi_hal_spi_bus_handle_external);
    return (furi_hal_spi_bus_handle_external);
  } else {
    FURI_LOG_I(TAG, "mcp2515_register_driver - using custom handle");
    furi_hal_spi_bus_handle_init(handle);
    furi_hal_spi_acquire(handle);
    return (furi_hal_spi_bus_handle_external);
  }
}

/** Read MCP2515 register through SPI
 *
 * @param      handle  - pointer to FuriHalSpiHandle
 * @param      reg     - register to read
 *
 * @return     void
 */
void mcp2515_reg_read(FuriHalSpiBusHandle* handle,
		      const mcp_register_t reg) {

  while (furi_hal_gpio_read(handle->miso)) { }

  UNUSED(handle);
  UNUSED(reg);
}

/** Write WCP2515 register through SPI
 *
 * @param      handle  - pointer to FuriHalSpiHandle
 * @param      reg     - register
 * @param      data    - data to write
 *
 * @return     void
 */
void mcp2515_reg_write(FuriHalSpiBusHandle* handle,
		       const mcp_register_t reg,
		       uint8_t *values) {
  while (furi_hal_gpio_read(handle->miso)) { }

  UNUSED(reg);
  UNUSED(values);
}
