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

#ifndef __MCP2515_H__
#define __MCP2515_H__

#include <furi_hal_spi.h>
#include <furi_hal_spi_config.h>

#include <can.h>

/*
 *  Speed 8M
 */
#define MCP_8MHz_1000kBPS_CFG1 (0x00)
#define MCP_8MHz_1000kBPS_CFG2 (0x80)
#define MCP_8MHz_1000kBPS_CFG3 (0x80)

#define MCP_8MHz_500kBPS_CFG1 (0x00)
#define MCP_8MHz_500kBPS_CFG2 (0x90)
#define MCP_8MHz_500kBPS_CFG3 (0x82)

#define MCP_8MHz_250kBPS_CFG1 (0x00)
#define MCP_8MHz_250kBPS_CFG2 (0xB1)
#define MCP_8MHz_250kBPS_CFG3 (0x85)

#define MCP_8MHz_200kBPS_CFG1 (0x00)
#define MCP_8MHz_200kBPS_CFG2 (0xB4)
#define MCP_8MHz_200kBPS_CFG3 (0x86)

#define MCP_8MHz_125kBPS_CFG1 (0x01)
#define MCP_8MHz_125kBPS_CFG2 (0xB1)
#define MCP_8MHz_125kBPS_CFG3 (0x85)

#define MCP_8MHz_100kBPS_CFG1 (0x01)
#define MCP_8MHz_100kBPS_CFG2 (0xB4)
#define MCP_8MHz_100kBPS_CFG3 (0x86)

#define MCP_8MHz_80kBPS_CFG1 (0x01)
#define MCP_8MHz_80kBPS_CFG2 (0xBF)
#define MCP_8MHz_80kBPS_CFG3 (0x87)

#define MCP_8MHz_50kBPS_CFG1 (0x03)
#define MCP_8MHz_50kBPS_CFG2 (0xB4)
#define MCP_8MHz_50kBPS_CFG3 (0x86)

#define MCP_8MHz_40kBPS_CFG1 (0x03)
#define MCP_8MHz_40kBPS_CFG2 (0xBF)
#define MCP_8MHz_40kBPS_CFG3 (0x87)

#define MCP_8MHz_33k3BPS_CFG1 (0x47)
#define MCP_8MHz_33k3BPS_CFG2 (0xE2)
#define MCP_8MHz_33k3BPS_CFG3 (0x85)

#define MCP_8MHz_31k25BPS_CFG1 (0x07)
#define MCP_8MHz_31k25BPS_CFG2 (0xA4)
#define MCP_8MHz_31k25BPS_CFG3 (0x84)

#define MCP_8MHz_20kBPS_CFG1 (0x07)
#define MCP_8MHz_20kBPS_CFG2 (0xBF)
#define MCP_8MHz_20kBPS_CFG3 (0x87)

#define MCP_8MHz_10kBPS_CFG1 (0x0F)
#define MCP_8MHz_10kBPS_CFG2 (0xBF)
#define MCP_8MHz_10kBPS_CFG3 (0x87)

#define MCP_8MHz_5kBPS_CFG1 (0x1F)
#define MCP_8MHz_5kBPS_CFG2 (0xBF)
#define MCP_8MHz_5kBPS_CFG3 (0x87)

/*
 *  speed 16M
 */
#define MCP_16MHz_1000kBPS_CFG1 (0x00)
#define MCP_16MHz_1000kBPS_CFG2 (0xD0)
#define MCP_16MHz_1000kBPS_CFG3 (0x82)

#define MCP_16MHz_500kBPS_CFG1 (0x00)
#define MCP_16MHz_500kBPS_CFG2 (0xF0)
#define MCP_16MHz_500kBPS_CFG3 (0x86)

#define MCP_16MHz_250kBPS_CFG1 (0x41)
#define MCP_16MHz_250kBPS_CFG2 (0xF1)
#define MCP_16MHz_250kBPS_CFG3 (0x85)

#define MCP_16MHz_200kBPS_CFG1 (0x01)
#define MCP_16MHz_200kBPS_CFG2 (0xFA)
#define MCP_16MHz_200kBPS_CFG3 (0x87)

#define MCP_16MHz_125kBPS_CFG1 (0x03)
#define MCP_16MHz_125kBPS_CFG2 (0xF0)
#define MCP_16MHz_125kBPS_CFG3 (0x86)

#define MCP_16MHz_100kBPS_CFG1 (0x03)
#define MCP_16MHz_100kBPS_CFG2 (0xFA)
#define MCP_16MHz_100kBPS_CFG3 (0x87)

#define MCP_16MHz_95kBPS_CFG1 (0x03)
#define MCP_16MHz_95kBPS_CFG2 (0xAD)
#define MCP_16MHz_95kBPS_CFG3 (0x07)

#define MCP_16MHz_83k3BPS_CFG1 (0x03)
#define MCP_16MHz_83k3BPS_CFG2 (0xBE)
#define MCP_16MHz_83k3BPS_CFG3 (0x07)

#define MCP_16MHz_80kBPS_CFG1 (0x03)
#define MCP_16MHz_80kBPS_CFG2 (0xFF)
#define MCP_16MHz_80kBPS_CFG3 (0x87)

#define MCP_16MHz_50kBPS_CFG1 (0x07)
#define MCP_16MHz_50kBPS_CFG2 (0xFA)
#define MCP_16MHz_50kBPS_CFG3 (0x87)

#define MCP_16MHz_40kBPS_CFG1 (0x07)
#define MCP_16MHz_40kBPS_CFG2 (0xFF)
#define MCP_16MHz_40kBPS_CFG3 (0x87)

#define MCP_16MHz_33k3BPS_CFG1 (0x4E)
#define MCP_16MHz_33k3BPS_CFG2 (0xF1)
#define MCP_16MHz_33k3BPS_CFG3 (0x85)

#define MCP_16MHz_20kBPS_CFG1 (0x0F)
#define MCP_16MHz_20kBPS_CFG2 (0xFF)
#define MCP_16MHz_20kBPS_CFG3 (0x87)

#define MCP_16MHz_10kBPS_CFG1 (0x1F)
#define MCP_16MHz_10kBPS_CFG2 (0xFF)
#define MCP_16MHz_10kBPS_CFG3 (0x87)

#define MCP_16MHz_5kBPS_CFG1 (0x3F)
#define MCP_16MHz_5kBPS_CFG2 (0xFF)
#define MCP_16MHz_5kBPS_CFG3 (0x87)

/*
 *  speed 20M
 */
#define MCP_20MHz_1000kBPS_CFG1 (0x00)
#define MCP_20MHz_1000kBPS_CFG2 (0xD9)
#define MCP_20MHz_1000kBPS_CFG3 (0x82)

#define MCP_20MHz_500kBPS_CFG1 (0x00)
#define MCP_20MHz_500kBPS_CFG2 (0xFA)
#define MCP_20MHz_500kBPS_CFG3 (0x87)

#define MCP_20MHz_250kBPS_CFG1 (0x41)
#define MCP_20MHz_250kBPS_CFG2 (0xFB)
#define MCP_20MHz_250kBPS_CFG3 (0x86)

#define MCP_20MHz_200kBPS_CFG1 (0x01)
#define MCP_20MHz_200kBPS_CFG2 (0xFF)
#define MCP_20MHz_200kBPS_CFG3 (0x87)

#define MCP_20MHz_125kBPS_CFG1 (0x03)
#define MCP_20MHz_125kBPS_CFG2 (0xFA)
#define MCP_20MHz_125kBPS_CFG3 (0x87)

#define MCP_20MHz_100kBPS_CFG1 (0x04)
#define MCP_20MHz_100kBPS_CFG2 (0xFA)
#define MCP_20MHz_100kBPS_CFG3 (0x87)

#define MCP_20MHz_83k3BPS_CFG1 (0x04)
#define MCP_20MHz_83k3BPS_CFG2 (0xFE)
#define MCP_20MHz_83k3BPS_CFG3 (0x87)

#define MCP_20MHz_80kBPS_CFG1 (0x04)
#define MCP_20MHz_80kBPS_CFG2 (0xFF)
#define MCP_20MHz_80kBPS_CFG3 (0x87)

#define MCP_20MHz_50kBPS_CFG1 (0x09)
#define MCP_20MHz_50kBPS_CFG2 (0xFA)
#define MCP_20MHz_50kBPS_CFG3 (0x87)

#define MCP_20MHz_40kBPS_CFG1 (0x09)
#define MCP_20MHz_40kBPS_CFG2 (0xFF)
#define MCP_20MHz_40kBPS_CFG3 (0x87)

#define MCP_20MHz_33k3BPS_CFG1 (0x0B)
#define MCP_20MHz_33k3BPS_CFG2 (0xFF)
#define MCP_20MHz_33k3BPS_CFG3 (0x87)

typedef enum {
  MCP_20MHZ,
  MCP_16MHZ,
  MCP_8MHZ
} can_clock_t;

typedef enum {
  CAN_5KBPS,
  CAN_10KBPS,
  CAN_20KBPS,
  CAN_31K25BPS,
  CAN_33KBPS,
  CAN_40KBPS,
  CAN_50KBPS,
  CAN_80KBPS,
  CAN_83K3BPS,
  CAN_95KBPS,
  CAN_100KBPS,
  CAN_125KBPS,
  CAN_200KBPS,
  CAN_250KBPS,
  CAN_500KBPS,
  CAN_1000KBPS
} mcp_can_speed_t;

typedef enum {
  CLKOUT_DISABLE = -1,
  CLKOUT_DIV1 = 0x0,
  CLKOUT_DIV2 = 0x1,
  CLKOUT_DIV4 = 0x2,
  CLKOUT_DIV8 = 0x3,
} can_clkout_t;

typedef enum {
  ERROR_OK        = 0,
  ERROR_FAIL      = 1,
  ERROR_ALLTXBUSY = 2,
  ERROR_FAILINIT  = 3,
  ERROR_FAILTX    = 4,
  ERROR_NOMSG     = 5
} mcp_error_t;

typedef struct {
  uint8_t FIFO_BYTES_AVAILABLE : 4;
  mcp_error_t STATE : 3;
  bool        CHIP_RDYn : 1;
} mcp_results_t;

typedef enum {
  MASK0,
  MASK1
} mcp_mask_t;

typedef enum {
  RXF0 = 0,
  RXF1 = 1,
  RXF2 = 2,
  RXF3 = 3,
  RXF4 = 4,
  RXF5 = 5
} mcp_rxf_t;

typedef enum {
  RXB0 = 0,
  RXB1 = 1
} mcp_rxbn_t;

typedef enum {
  TXB0 = 0,
  TXB1 = 1,
  TXB2 = 2
} mcp_txbn_t;

typedef enum canintf_t {
  canintf_t_RX0IF = 0x01,
  canintf_t_RX1IF = 0x02,
  canintf_t_TX0IF = 0x04,
  canintf_t_TX1IF = 0x08,
  canintf_t_TX2IF = 0x10,
  canintf_t_ERRIF = 0x20,
  canintf_t_WAKIF = 0x40,
  canintf_t_MERRF = 0x80
} canintf_t;

typedef enum {
  EFLG_RX1OVR = (1<<7),
  EFLG_RX0OVR = (1<<6),
  EFLG_TXBO   = (1<<5),
  EFLG_TXEP   = (1<<4),
  EFLG_RXEP   = (1<<3),
  EFLG_TXWAR  = (1<<2),
  EFLG_RXWAR  = (1<<1),
  EFLG_EWARN  = (1<<0)
} mcp_eflg_t;

static const uint8_t CANCTRL_REQOP = 0xE0;
static const uint8_t CANCTRL_ABAT = 0x10;
static const uint8_t CANCTRL_OSM = 0x08;
static const uint8_t CANCTRL_CLKEN = 0x04;
static const uint8_t CANCTRL_CLKPRE = 0x03;

typedef enum {
  CANCTRL_REQOP_NORMAL     = 0x00,
  CANCTRL_REQOP_SLEEP      = 0x20,
  CANCTRL_REQOP_LOOPBACK   = 0x40,
  CANCTRL_REQOP_LISTENONLY = 0x60,
  CANCTRL_REQOP_CONFIG     = 0x80,
  CANCTRL_REQOP_POWERUP    = 0xE0
} mcp_canctrl_reqop_mode_t;

static const uint8_t CANSTAT_OPMOD = 0xE0;
static const uint8_t CANSTAT_ICOD = 0x0E;

static const uint8_t CNF3_SOF = 0x80;

static const uint8_t TXB_EXIDE_MASK = 0x08;
static const uint8_t DLC_MASK       = 0x0F;
static const uint8_t RTR_MASK       = 0x40;

static const uint8_t RXBnCTRL_RXM_STD    = 0x20;
static const uint8_t RXBnCTRL_RXM_EXT    = 0x40;
static const uint8_t RXBnCTRL_RXM_STDEXT = 0x00;
static const uint8_t RXBnCTRL_RXM_MASK   = 0x60;
static const uint8_t RXBnCTRL_RTR        = 0x08;
static const uint8_t RXB0CTRL_BUKT       = 0x04;
static const uint8_t RXB0CTRL_FILHIT_MASK = 0x03;
static const uint8_t RXB1CTRL_FILHIT_MASK = 0x07;
static const uint8_t RXB0CTRL_FILHIT = 0x00;
static const uint8_t RXB1CTRL_FILHIT = 0x01;

static const uint8_t MCP_SIDH = 0;
static const uint8_t MCP_SIDL = 1;
static const uint8_t MCP_EID8 = 2;
static const uint8_t MCP_EID0 = 3;
static const uint8_t MCP_DLC  = 4;
static const uint8_t MCP_DATA = 5;

typedef enum {
  STAT_RX0IF = (1<<0),
  STAT_RX1IF = (1<<1)
} mcp_stat_t;

static const uint8_t mcp_stat_rxif_mask
= STAT_RX0IF | STAT_RX1IF;

enum TXBnCTRL {
  TXB_ABTF   = 0x40,
  TXB_MLOA   = 0x20,
  TXB_TXERR  = 0x10,
  TXB_TXREQ  = 0x08,
  TXB_TXIE   = 0x04,
  TXB_TXP    = 0x03
};

static const uint8_t mcp_eflg_errormask_t =
  EFLG_RX1OVR
  | EFLG_RX0OVR
  | EFLG_TXBO
  | EFLG_TXEP
  | EFLG_RXEP;

typedef enum {
  INSTRUCTION_WRITE       = 0x02,
  INSTRUCTION_READ        = 0x03,
  INSTRUCTION_BITMOD      = 0x05,
  INSTRUCTION_LOAD_TX0    = 0x40,
  INSTRUCTION_LOAD_TX1    = 0x42,
  INSTRUCTION_LOAD_TX2    = 0x44,
  INSTRUCTION_RTS_TX0     = 0x81,
  INSTRUCTION_RTS_TX1     = 0x82,
  INSTRUCTION_RTS_TX2     = 0x84,
  INSTRUCTION_RTS_ALL     = 0x87,
  INSTRUCTION_READ_RX0    = 0x90,
  INSTRUCTION_READ_RX1    = 0x94,
  INSTRUCTION_READ_STATUS = 0xA0,
  INSTRUCTION_RX_STATUS   = 0xB0,
  INSTRUCTION_RESET       = 0xC0
} mcp_instruction_t;

typedef enum {
  MCP_RXF0SIDH = 0x00,
  MCP_RXF0SIDL = 0x01,
  MCP_RXF0EID8 = 0x02,
  MCP_RXF0EID0 = 0x03,
  MCP_RXF1SIDH = 0x04,
  MCP_RXF1SIDL = 0x05,
  MCP_RXF1EID8 = 0x06,
  MCP_RXF1EID0 = 0x07,
  MCP_RXF2SIDH = 0x08,
  MCP_RXF2SIDL = 0x09,
  MCP_RXF2EID8 = 0x0A,
  MCP_RXF2EID0 = 0x0B,
  MCP_CANSTAT  = 0x0E,
  MCP_CANCTRL  = 0x0F,
  MCP_RXF3SIDH = 0x10,
  MCP_RXF3SIDL = 0x11,
  MCP_RXF3EID8 = 0x12,
  MCP_RXF3EID0 = 0x13,
  MCP_RXF4SIDH = 0x14,
  MCP_RXF4SIDL = 0x15,
  MCP_RXF4EID8 = 0x16,
  MCP_RXF4EID0 = 0x17,
  MCP_RXF5SIDH = 0x18,
  MCP_RXF5SIDL = 0x19,
  MCP_RXF5EID8 = 0x1A,
  MCP_RXF5EID0 = 0x1B,
  MCP_TEC      = 0x1C,
  MCP_REC      = 0x1D,
  MCP_RXM0SIDH = 0x20,
  MCP_RXM0SIDL = 0x21,
  MCP_RXM0EID8 = 0x22,
  MCP_RXM0EID0 = 0x23,
  MCP_RXM1SIDH = 0x24,
  MCP_RXM1SIDL = 0x25,
  MCP_RXM1EID8 = 0x26,
  MCP_RXM1EID0 = 0x27,
  MCP_CNF3     = 0x28,
  MCP_CNF2     = 0x29,
  MCP_CNF1     = 0x2A,
  MCP_CANINTE  = 0x2B,
  MCP_canintf_t  = 0x2C,
  MCP_EFLG     = 0x2D,
  MCP_TXB0CTRL = 0x30,
  MCP_TXB0SIDH = 0x31,
  MCP_TXB0SIDL = 0x32,
  MCP_TXB0EID8 = 0x33,
  MCP_TXB0EID0 = 0x34,
  MCP_TXB0DLC  = 0x35,
  MCP_TXB0DATA = 0x36,
  MCP_TXB1CTRL = 0x40,
  MCP_TXB1SIDH = 0x41,
  MCP_TXB1SIDL = 0x42,
  MCP_TXB1EID8 = 0x43,
  MCP_TXB1EID0 = 0x44,
  MCP_TXB1DLC  = 0x45,
  MCP_TXB1DATA = 0x46,
  MCP_TXB2CTRL = 0x50,
  MCP_TXB2SIDH = 0x51,
  MCP_TXB2SIDL = 0x52,
  MCP_TXB2EID8 = 0x53,
  MCP_TXB2EID0 = 0x54,
  MCP_TXB2DLC  = 0x55,
  MCP_TXB2DATA = 0x56,
  MCP_RXB0CTRL = 0x60,
  MCP_RXB0SIDH = 0x61,
  MCP_RXB0SIDL = 0x62,
  MCP_RXB0EID8 = 0x63,
  MCP_RXB0EID0 = 0x64,
  MCP_RXB0DLC  = 0x65,
  MCP_RXB0DATA = 0x66,
  MCP_RXB1CTRL = 0x70,
  MCP_RXB1SIDH = 0x71,
  MCP_RXB1SIDL = 0x72,
  MCP_RXB1EID8 = 0x73,
  MCP_RXB1EID0 = 0x74,
  MCP_RXB1DLC  = 0x75,
  MCP_RXB1DATA = 0x76
} mcp_register_t;

#define DEFAULT_SPI_CLOCK = 10000000; // 10MHz
#define MCP2515_TIMEOUT 500
#define N_TXBUFFERS 3
#define N_RXBUFFERS 2

typedef struct {
  mcp_register_t CTRL;
  mcp_register_t SIDH;
  mcp_register_t DATA;
} mcp_txbn_regs_t;


typedef struct {
  mcp_register_t CTRL;
  mcp_register_t SIDH;
  mcp_register_t DATA;
  canintf_t      RXnIF;
} mcp_rxbn_regs_t;

static const mcp_txbn_regs_t TXB[N_TXBUFFERS];
static const mcp_rxbn_regs_t RXB[N_RXBUFFERS];

#endif // __MCP2515_H__
