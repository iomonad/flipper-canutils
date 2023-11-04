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
#include <furi_hal_resources.h>
#include <furi_hal_spi.h>
#include <furi_hal_spi_types.h>
#include <furi_hal_spi_config.h>
#include <furi_hal_cortex.h>
#include <assert.h>

#include <mcp2515.h>
#include <canutils.h>

/** Read MCP2515 register through SPI
 *
 * @param      handle  - pointer to FuriHalSpiHandle | NULL for default preset
 *
 * @notes      https://github.com/flipperdevices/flipperzero-firmware/blob/dev/firmware/targets/f7/furi_hal/furi_hal_spi_config.c#L344C21-L344C53
 *             A6 -> MISO
 *             A7 -> MOSI
 *             B3 -> SCK
 *             A4 -> CS
 *
 *  FuriHalSpiBusHandle furi_hal_spi_bus_handle_external = {
 *     .bus = &furi_hal_spi_bus_r,
 *     .callback = furi_hal_spi_bus_handle_external_event_callback,
 *     .miso = &gpio_ext_pa6,
 *     .mosi = &gpio_ext_pa7,
 *     .sck = &gpio_ext_pb3,
 *     .cs = &gpio_ext_pa4
 *  };
 *
 *
 * @return     the actual handler instance
 */
FuriHalSpiBusHandle mcp2515_register_driver(FuriHalSpiBusHandle *handle) {

  FURI_LOG_I(TAG, "mcp2515_register_driver");

  /* Enable Board 5v */
  furi_hal_power_enable_otg();
  if (handle == NULL) {
    FURI_LOG_I(TAG, "mcp2515_register_driver - using default external preset");
    furi_hal_spi_bus_handle_init(&furi_hal_spi_bus_handle_external);
    furi_hal_spi_acquire(&furi_hal_spi_bus_handle_external);

    return furi_hal_spi_bus_handle_external;
  } else {
    FURI_LOG_I(TAG, "mcp2515_register_driver - using custom handle");
    furi_hal_spi_bus_handle_init(handle);
    furi_hal_spi_acquire(handle);

    return *handle;
  }
}

/** Release MCP2515 driver
 *
 * @param      handle  - pointer to FuriHalSpiHandle
 *
 * @return     boolean status
 */
bool mcp2515_release_driver(FuriHalSpiBusHandle *handle) {

  FURI_LOG_I(TAG, "mcp2515 driver cleanup %p", handle);

  /* Disable Board 5v */
  furi_hal_power_disable_otg();
  if (handle) {
    FURI_LOG_I(TAG, "mcp2515 driver cleanup");
    furi_hal_spi_release(handle);
    furi_hal_spi_bus_handle_deinit(handle);

    return true;
  }
  return false;
}


/** Thin wrapper around furi SPI trx API
 *
 * @param      handle  - pointer to FuriHalSpiHandle
 * @param      tx      - tx data
 * @param      rx      - rx data
 * @param      size    - data segment size
 *
 * @return     boolean status
 */
static bool mcp2515_spi_trx(FuriHalSpiBusHandle* handle,
			    const uint8_t* tx,
			    const uint8_t* rx,
			    const uint8_t size) {

  FuriHalCortexTimer timer = furi_hal_cortex_timer_get(MCP2515_TIMEOUT * 1000);

  FURI_LOG_D(TAG, "mcp2515 - spi trx data");

  while (furi_hal_gpio_read(handle->miso)) {
    if (furi_hal_cortex_timer_is_expired(timer)) {
      FURI_LOG_W(TAG, "mcp2515 - cortex timeout");
      return false;
    }
  }

  if (!furi_hal_spi_bus_trx(handle, (uint8_t*)tx, (uint8_t*)rx, size, MCP2515_TIMEOUT)) {

    FURI_LOG_W(TAG, "mcp2515 - SPI tx timeout");
    return false;
  }

  return true;
}


/** Read MCP2515 register through SPI
 *
 * @param      handle  - pointer to FuriHalSpiHandle
 * @param      reg     - register to read
 * @param      results - point to write data from
 *
 * @return     mcp2515 results call
 */
mcp_results_t mcp2515_reg_read(FuriHalSpiBusHandle* handle,
			       const mcp_register_t reg,
			       uint8_t *results) {
  uint8_t tx[3] = { INSTRUCTION_READ , reg, 0 };
  mcp_results_t rx[2] = {0};

  FURI_LOG_I(TAG, "mcp2515 - register read %d", reg);

  if (!mcp2515_spi_trx(handle, tx, (uint8_t*)rx, 3)) {
    FURI_LOG_D(TAG, "mcp2515 - SPI write failure");
  }

  assert(rx[0].CHIP_RDYn | rx[1].CHIP_RDYn == 0x0);
  *results = *(uint8_t*)&rx[1];

  FURI_LOG_D(TAG, "mcp2515 - register read %d - %d",
	     rx[0].FIFO_BYTES_AVAILABLE,
	     rx[1].FIFO_BYTES_AVAILABLE);
  return rx[0];
}


/** Write MCP2515 register through SPI
 *
 * @param      handle  - pointer to FuriHalSpiHandle
 * @param      reg     - register
 * @param      data    - data to write
 *
 * @return     mcp2515 results call
 */
mcp_results_t mcp2515_reg_write(FuriHalSpiBusHandle* handle,
				const mcp_register_t reg,
				const uint8_t data) {

  uint8_t tx[3] = { INSTRUCTION_WRITE, reg, data};
  mcp_results_t rx[2] = {0};

  FURI_LOG_D(TAG, "mcp2515 - register write");
  if (!mcp2515_spi_trx(handle, tx, (uint8_t*)rx, 3)) {
    FURI_LOG_D(TAG, "mcp2515 - SPI write failure");
  }

  assert((rx[0].CHIP_RDYn | rx[1].CHIP_RDYn) == 0x0);
  return rx[1];
}


/** Modify MCP2515 register through SPI
 *
 * @param      handle  - pointer to FuriHalSpiHandle
 * @param      reg     - register
 * @param      mask    - mask to apply
 * @param      data    - data to write
 *
 * @return     mcp2515 results call
 */
mcp_results_t mcp2515_reg_modify(FuriHalSpiBusHandle* handle,
				 const mcp_register_t reg,
				 const uint8_t mask,
				 const uint8_t data) {

  uint8_t tx[4] = { INSTRUCTION_BITMOD, reg, mask, data };
  mcp_results_t rx[2] = {0};

  FURI_LOG_D(TAG, "mcp2515 - register modify");
  while (furi_hal_gpio_read(handle->miso))
    ;

  furi_hal_spi_bus_trx(handle, tx, (uint8_t*)rx, 2, MCP2515_TIMEOUT);
  assert((rx[0].CHIP_RDYn | rx[1].CHIP_RDYn) == 0x0);

  return rx[1];
}


/** Modify MCP2515 mode
 *
 * @param      handle  - pointer to FuriHalSpiHandle
 * @param      mode    - mode to switch to (see `mcp_canctrl_reqop_mode_t`)
 *
 * @return     mcp2515 results call
 */
mcp_results_t mcp2515_set_mode(FuriHalSpiBusHandle* handle,
			       const mcp_canctrl_reqop_mode_t mode) {
  return mcp2515_reg_modify(handle, MCP_CANCTRL, CANCTRL_REQOP, mode);
}


/** Enter MCP2515 in CONFIG mode
 *
 * @param      handle  - pointer to FuriHalSpiHandle
 *
 * @return     mcp2515 results call
 */
mcp_results_t mcp2525_set_config_mode(FuriHalSpiBusHandle* handle) {
  return mcp2515_set_mode(handle, CANCTRL_REQOP_CONFIG);
}


/** Enter MCP2515 in LISTEN_ONLY mode
 *
 * @param      handle  - pointer to FuriHalSpiHandle
 *
 * @return     mcp2515 results call
 */
mcp_results_t mcp2515_set_listen_only_mode(FuriHalSpiBusHandle* handle) {
  return mcp2515_set_mode(handle, CANCTRL_REQOP_LISTENONLY);
}


/** Enter MCP2515 in SLEEP mode
 *
 * @param      handle  - pointer to FuriHalSpiHandle
 *
 * @return     mcp2515 results call
 */
mcp_results_t mcp2515_set_sleep_mode(FuriHalSpiBusHandle* handle) {
  return mcp2515_set_mode(handle, CANCTRL_REQOP_SLEEP);
}


/** Enter MCP2515 in LOOPBACK mode
 *
 * @param      handle  - pointer to FuriHalSpiHandle
 *
 * @return     mcp2515 results call
 */
mcp_results_t mcp2515_set_loopback_mode(FuriHalSpiBusHandle* handle) {
  return mcp2515_set_mode(handle, CANCTRL_REQOP_LOOPBACK);
}


/** Enter MCP2515 in NORMAL mode
 *
 * @param      handle  - pointer to FuriHalSpiHandle
 *
 * @return     mcp2515 results call
 */
mcp_results_t mcp2515_set_normal_mode(FuriHalSpiBusHandle* handle) {
  return mcp2515_set_mode(handle, CANCTRL_REQOP_NORMAL);
}


/** Modify MCP2515 bitrate
 *
 * @param      handle  - pointer to FuriHalSpiHandle
 * @param      bitrate - bitrate to setup
 * @param      clock - bitrate clock (use NULL for default)
 *
 * @return     mcp2515 results call
 */
mcp_results_t mcp2515_set_bitrate(FuriHalSpiBusHandle* handle,
				  const mcp_can_speed_t bitrate,
				  const can_clock_t *clock) {

  mcp_results_t results = mcp2515_set_normal_mode(handle);

  if (clock == NULL) {

    can_clock_t default_clock = MCP_16MHZ;

    return mcp2515_set_bitrate(handle, bitrate, &default_clock);
  }

  uint8_t set = 1, cfg1, cfg2, cfg3;

  switch (*clock) {
  case (MCP_8MHZ):
    switch (bitrate) {
    case (CAN_5KBPS):                                               //   5KBPS
      cfg1 = MCP_8MHz_5kBPS_CFG1;
      cfg2 = MCP_8MHz_5kBPS_CFG2;
      cfg3 = MCP_8MHz_5kBPS_CFG3;
      break;

    case (CAN_10KBPS):                                              //  10KBPS
      cfg1 = MCP_8MHz_10kBPS_CFG1;
      cfg2 = MCP_8MHz_10kBPS_CFG2;
      cfg3 = MCP_8MHz_10kBPS_CFG3;
      break;

    case (CAN_20KBPS):                                              //  20KBPS
      cfg1 = MCP_8MHz_20kBPS_CFG1;
      cfg2 = MCP_8MHz_20kBPS_CFG2;
      cfg3 = MCP_8MHz_20kBPS_CFG3;
      break;

    case (CAN_31K25BPS):                                            //  31.25KBPS
      cfg1 = MCP_8MHz_31k25BPS_CFG1;
      cfg2 = MCP_8MHz_31k25BPS_CFG2;
      cfg3 = MCP_8MHz_31k25BPS_CFG3;
      break;

    case (CAN_33KBPS):                                              //  33.333KBPS
      cfg1 = MCP_8MHz_33k3BPS_CFG1;
      cfg2 = MCP_8MHz_33k3BPS_CFG2;
      cfg3 = MCP_8MHz_33k3BPS_CFG3;
      break;

    case (CAN_40KBPS):                                              //  40Kbps
      cfg1 = MCP_8MHz_40kBPS_CFG1;
      cfg2 = MCP_8MHz_40kBPS_CFG2;
      cfg3 = MCP_8MHz_40kBPS_CFG3;
      break;

    case (CAN_50KBPS):                                              //  50Kbps
      cfg1 = MCP_8MHz_50kBPS_CFG1;
      cfg2 = MCP_8MHz_50kBPS_CFG2;
      cfg3 = MCP_8MHz_50kBPS_CFG3;
      break;

    case (CAN_80KBPS):                                              //  80Kbps
      cfg1 = MCP_8MHz_80kBPS_CFG1;
      cfg2 = MCP_8MHz_80kBPS_CFG2;
      cfg3 = MCP_8MHz_80kBPS_CFG3;
      break;

    case (CAN_100KBPS):                                             // 100Kbps
      cfg1 = MCP_8MHz_100kBPS_CFG1;
      cfg2 = MCP_8MHz_100kBPS_CFG2;
      cfg3 = MCP_8MHz_100kBPS_CFG3;
      break;

    case (CAN_125KBPS):                                             // 125Kbps
      cfg1 = MCP_8MHz_125kBPS_CFG1;
      cfg2 = MCP_8MHz_125kBPS_CFG2;
      cfg3 = MCP_8MHz_125kBPS_CFG3;
      break;

    case (CAN_200KBPS):                                             // 200Kbps
      cfg1 = MCP_8MHz_200kBPS_CFG1;
      cfg2 = MCP_8MHz_200kBPS_CFG2;
      cfg3 = MCP_8MHz_200kBPS_CFG3;
      break;

    case (CAN_250KBPS):                                             // 250Kbps
      cfg1 = MCP_8MHz_250kBPS_CFG1;
      cfg2 = MCP_8MHz_250kBPS_CFG2;
      cfg3 = MCP_8MHz_250kBPS_CFG3;
      break;

    case (CAN_500KBPS):                                             // 500Kbps
      cfg1 = MCP_8MHz_500kBPS_CFG1;
      cfg2 = MCP_8MHz_500kBPS_CFG2;
      cfg3 = MCP_8MHz_500kBPS_CFG3;
      break;

    case (CAN_1000KBPS):                                            //   1Mbps
      cfg1 = MCP_8MHz_1000kBPS_CFG1;
      cfg2 = MCP_8MHz_1000kBPS_CFG2;
      cfg3 = MCP_8MHz_1000kBPS_CFG3;
      break;

    default:
      set = 0;
      break;
    }
    break;

  case (MCP_16MHZ):
    switch (bitrate) {
    case (CAN_5KBPS):                                               //   5Kbps
      cfg1 = MCP_16MHz_5kBPS_CFG1;
      cfg2 = MCP_16MHz_5kBPS_CFG2;
      cfg3 = MCP_16MHz_5kBPS_CFG3;
      break;

    case (CAN_10KBPS):                                              //  10Kbps
      cfg1 = MCP_16MHz_10kBPS_CFG1;
      cfg2 = MCP_16MHz_10kBPS_CFG2;
      cfg3 = MCP_16MHz_10kBPS_CFG3;
      break;

    case (CAN_20KBPS):                                              //  20Kbps
      cfg1 = MCP_16MHz_20kBPS_CFG1;
      cfg2 = MCP_16MHz_20kBPS_CFG2;
      cfg3 = MCP_16MHz_20kBPS_CFG3;
      break;

    case (CAN_33KBPS):                                              //  33.333Kbps
      cfg1 = MCP_16MHz_33k3BPS_CFG1;
      cfg2 = MCP_16MHz_33k3BPS_CFG2;
      cfg3 = MCP_16MHz_33k3BPS_CFG3;
      break;

    case (CAN_40KBPS):                                              //  40Kbps
      cfg1 = MCP_16MHz_40kBPS_CFG1;
      cfg2 = MCP_16MHz_40kBPS_CFG2;
      cfg3 = MCP_16MHz_40kBPS_CFG3;
      break;

    case (CAN_50KBPS):                                              //  50Kbps
      cfg1 = MCP_16MHz_50kBPS_CFG1;
      cfg2 = MCP_16MHz_50kBPS_CFG2;
      cfg3 = MCP_16MHz_50kBPS_CFG3;
      break;

    case (CAN_80KBPS):                                              //  80Kbps
      cfg1 = MCP_16MHz_80kBPS_CFG1;
      cfg2 = MCP_16MHz_80kBPS_CFG2;
      cfg3 = MCP_16MHz_80kBPS_CFG3;
      break;

    case (CAN_83K3BPS):                                             //  83.333Kbps
      cfg1 = MCP_16MHz_83k3BPS_CFG1;
      cfg2 = MCP_16MHz_83k3BPS_CFG2;
      cfg3 = MCP_16MHz_83k3BPS_CFG3;
      break;

    case (CAN_95KBPS):                                              //  95Kbps
      cfg1 = MCP_16MHz_95kBPS_CFG1;
      cfg2 = MCP_16MHz_95kBPS_CFG2;
      cfg3 = MCP_16MHz_95kBPS_CFG3;
      break;

    case (CAN_100KBPS):                                             // 100Kbps
      cfg1 = MCP_16MHz_100kBPS_CFG1;
      cfg2 = MCP_16MHz_100kBPS_CFG2;
      cfg3 = MCP_16MHz_100kBPS_CFG3;
      break;

    case (CAN_125KBPS):                                             // 125Kbps
      cfg1 = MCP_16MHz_125kBPS_CFG1;
      cfg2 = MCP_16MHz_125kBPS_CFG2;
      cfg3 = MCP_16MHz_125kBPS_CFG3;
      break;

    case (CAN_200KBPS):                                             // 200Kbps
      cfg1 = MCP_16MHz_200kBPS_CFG1;
      cfg2 = MCP_16MHz_200kBPS_CFG2;
      cfg3 = MCP_16MHz_200kBPS_CFG3;
      break;

    case (CAN_250KBPS):                                             // 250Kbps
      cfg1 = MCP_16MHz_250kBPS_CFG1;
      cfg2 = MCP_16MHz_250kBPS_CFG2;
      cfg3 = MCP_16MHz_250kBPS_CFG3;
      break;

    case (CAN_500KBPS):                                             // 500Kbps
      cfg1 = MCP_16MHz_500kBPS_CFG1;
      cfg2 = MCP_16MHz_500kBPS_CFG2;
      cfg3 = MCP_16MHz_500kBPS_CFG3;
      break;

    case (CAN_1000KBPS):                                            //   1Mbps
      cfg1 = MCP_16MHz_1000kBPS_CFG1;
      cfg2 = MCP_16MHz_1000kBPS_CFG2;
      cfg3 = MCP_16MHz_1000kBPS_CFG3;
      break;

    default:
      set = 0;
      break;
    }
    break;

  case (MCP_20MHZ):
    switch (bitrate) {
    case (CAN_33KBPS):                                              //  33.333Kbps
      cfg1 = MCP_20MHz_33k3BPS_CFG1;
      cfg2 = MCP_20MHz_33k3BPS_CFG2;
      cfg3 = MCP_20MHz_33k3BPS_CFG3;
      break;

    case (CAN_40KBPS):                                              //  40Kbps
      cfg1 = MCP_20MHz_40kBPS_CFG1;
      cfg2 = MCP_20MHz_40kBPS_CFG2;
      cfg3 = MCP_20MHz_40kBPS_CFG3;
      break;

    case (CAN_50KBPS):                                              //  50Kbps
      cfg1 = MCP_20MHz_50kBPS_CFG1;
      cfg2 = MCP_20MHz_50kBPS_CFG2;
      cfg3 = MCP_20MHz_50kBPS_CFG3;
      break;

    case (CAN_80KBPS):                                              //  80Kbps
      cfg1 = MCP_20MHz_80kBPS_CFG1;
      cfg2 = MCP_20MHz_80kBPS_CFG2;
      cfg3 = MCP_20MHz_80kBPS_CFG3;
      break;

    case (CAN_83K3BPS):                                             //  83.333Kbps
      cfg1 = MCP_20MHz_83k3BPS_CFG1;
      cfg2 = MCP_20MHz_83k3BPS_CFG2;
      cfg3 = MCP_20MHz_83k3BPS_CFG3;
      break;

    case (CAN_100KBPS):                                             // 100Kbps
      cfg1 = MCP_20MHz_100kBPS_CFG1;
      cfg2 = MCP_20MHz_100kBPS_CFG2;
      cfg3 = MCP_20MHz_100kBPS_CFG3;
      break;

    case (CAN_125KBPS):                                             // 125Kbps
      cfg1 = MCP_20MHz_125kBPS_CFG1;
      cfg2 = MCP_20MHz_125kBPS_CFG2;
      cfg3 = MCP_20MHz_125kBPS_CFG3;
      break;

    case (CAN_200KBPS):                                             // 200Kbps
      cfg1 = MCP_20MHz_200kBPS_CFG1;
      cfg2 = MCP_20MHz_200kBPS_CFG2;
      cfg3 = MCP_20MHz_200kBPS_CFG3;
      break;

    case (CAN_250KBPS):                                             // 250Kbps
      cfg1 = MCP_20MHz_250kBPS_CFG1;
      cfg2 = MCP_20MHz_250kBPS_CFG2;
      cfg3 = MCP_20MHz_250kBPS_CFG3;
      break;

    case (CAN_500KBPS):                                             // 500Kbps
      cfg1 = MCP_20MHz_500kBPS_CFG1;
      cfg2 = MCP_20MHz_500kBPS_CFG2;
      cfg3 = MCP_20MHz_500kBPS_CFG3;
      break;

    case (CAN_1000KBPS):                                            //   1Mbps
      cfg1 = MCP_20MHz_1000kBPS_CFG1;
      cfg2 = MCP_20MHz_1000kBPS_CFG2;
      cfg3 = MCP_20MHz_1000kBPS_CFG3;
      break;

    default:
      set = 0;
      break;
    }
    break;

  default:
    set = 0;
    break;
  }

  if (set) {
    mcp2515_reg_write(handle, MCP_CNF1, cfg1);
    mcp2515_reg_write(handle, MCP_CNF2, cfg2);
    mcp2515_reg_write(handle, MCP_CNF3, cfg3);

    results.STATE = ERROR_OK;
  } else {
    results.STATE = ERROR_FAIL;
  }
  return results;
}


/** Check BUS errors
 *
 * @param      handle  - pointer to FuriHalSpiHandle
 *
 * @return     boolean
 */
bool mcp2515_have_errors(FuriHalSpiBusHandle *handle) {

  uint8_t result;

  mcp2515_reg_read(handle, MCP_EFLG, &result);

  FURI_LOG_I(TAG, "reg read results %d", result);

  return result & MCP_EFLG_ERRORMASK
    ? true : false;
}

/** Read BUS Status
 *
 * @param      handle  - pointer to FuriHalSpiHandle
 *
 * @return     uint8_t status
 */
uint8_t mcp2515_read_status(FuriHalSpiBusHandle *handle) {

  uint8_t tx[2] = { INSTRUCTION_READ_STATUS, 0 };
  mcp_results_t rx[1];

  if (!mcp2515_spi_trx(handle, tx, (uint8_t*)rx, 2)) {
    FURI_LOG_D(TAG, "mcp2515 - SPI write failure");
  }

  return rx[0].FIFO_BYTES_AVAILABLE;
}
