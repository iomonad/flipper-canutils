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
#include <furi_hal_power.h>
#include <furi_hal_usb.h>
#include <furi_hal_spi.h>
#include <furi_hal_spi_types.h>
#include <furi_hal_spi_config.h>

#include "mcp2518fd.h"

#define TAG "mcp2518fd"

int8_t mcp2518fd_read_byte(mcp2518fd_device_t *device,
			   uint16_t address, uint8_t *rxd) {
     furi_hal_spi_acquire(&device->handle);

     uint8_t txbuff[64];
     txbuff[0] =
	  (uint8_t)((cINSTRUCTION_READ << 4) + ((address >> 8) & 0xF));
     txbuff[1] = (uint8_t)(address & 0xFF);
     txbuff[2] = 0;

     if (furi_hal_spi_bus_trx(&device->handle, txbuff, rxd, 1, 10000)) {
	  return 0;
     } else {
	  return 1;
     }

     furi_hal_spi_release(&device->handle);

     return 0;
}

/* int8_t mcp2518fd_write_byte(mcp2518fd_device_t *device, */
/* 			    uint16_t address, uint8_t txd) { */
/*      return ; */
/* } */

/* uint8_t mcp2518fd_read_word(mcp2518fd_device_t *device, */
/* 			    uint16_t address, uint32_t *rxd) { */
/*      return ; */
/* } */

/* uint8_t mcp2518fd_write_word(mcp2518fd_device_t *device, */
/* 			     uint16_t address, uint32_t txd) { */
/*      return ; */
/* } */

/* uint8_t mcp2518fd_read_halfword(mcp2518fd_device_t *device, */
/* 				uint16_t address, uint16_t *rxd) { */
/*      return ; */
/* } */

/* uint8_t mcp2518fd_write_halfword(mcp2518fd_device_t *device, */
/* 				 uint16_t address, uint16_t txd) { */
/*      return ; */
/* } */

/* uint8_t mcp2518fd_read_bytearray(mcp2518fd_device_t *device, */
/* 				 uint16_t address, uint8_t *rxd, uint16_t count) { */
/*      return ; */
/* } */

/* uint8_t mcp2518fd_write_bytearray(mcp2518fd_device_t *device, */
/* 				  uint16_t address, uint8_t *txd, uint16_t count) { */
/*      return ; */
/* } */



/* uint8_t mcp2518fd_enable_ecc(mcp2518fd_device_t *device) { */
/*      int8_t spi_status = 0; */
/*      uint8_t d = 0; */

/*      if ((spi_status = mcp2518fd_read_byte(device, cREGADDR_ECCCON, &d))) { */
/* 	       return -1; */
/*      } */

/*      FURI_LOG_I(TAG, "ECC acquired"); */
/*      d |= 0x01; */

/*      if ((spi_status = mcp2518fd_write_byte(device, cREGADDR_ECCCON, d))) { */
/* 	  return -2; */
/*      } */

/*      FURI_LOG_I(TAG, "ECC updated"); */
/*      return 0; */
/* } */



uint8_t mcp2518fd_initialize(mcp2518fd_device_t *device) {
     (void)device;
     return 0;
}

/* Lifecycle */

bool mcp25158fd_release_driver(mcp2518fd_device_t *device) {
     if (device == NULL) {
	  return false;
     }

     if (device->initialized) {
	  furi_hal_spi_bus_handle_deinit(&device->handle);
	  device->initialized = false;
     }

     free(device);
     return true;
}

uint8_t mcp2518fd_reset(mcp2518fd_device_t *device) {
     (void) device;

     return 0;
}

mcp2518fd_device_t *mcp25158fd_register_driver(FuriHalSpiBusHandle *handle) {
     mcp2518fd_device_t *device = NULL;

     if ((device = (mcp2518fd_device_t*)malloc(sizeof(mcp2518fd_device_t))) == NULL) {
	  FURI_LOG_I(TAG, "error allocating mcp2518fd_device_t device");

	  return NULL;
     }

     device->initialized = false;

     if (handle == NULL) {
	  furi_hal_spi_bus_handle_init(&furi_hal_spi_bus_handle_external);
	  device->handle = furi_hal_spi_bus_handle_external;
     } else {
	  furi_hal_spi_bus_handle_init(handle);
	  device->handle = *handle;
     }

     device->initialized = true;

     return device;
}
