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
 * Copyright (c) iomonad <iomonad@riseup.net>
 */

#ifndef __MCP_CAN_H__
#define __MCP_CAN_H__

/* Status Code */

#define CAN_OK              (0)
#define CAN_FAILINIT        (1)
#define CAN_FAILTX          (2)
#define CAN_MSGAVAIL        (3)
#define CAN_NOMSG           (4)
#define CAN_CTRLERROR       (5)
#define CAN_GETTXBFTIMEOUT  (6)
#define CAN_SENDMSGTIMEOUT  (7)
#define CAN_FAIL            (0xff)

/* Clock */

typedef enum {
     MCP_CLOCK_NO_MHz,
     /* apply to MCP2515 */
     MCP_CLOCK_16MHz,
     MCP_CLOCK_12MHz,
     MCP_CLOCK_8MHz,
     /* apply to MCP2518FD */
     MCP2518FD_CLOCK_40MHz = MCP_CLOCK_16MHz,
     MCP2518FD_CLOCK_20MHz,
     MCP2518FD_CLOCK_10MHz,
} mcp_clock_t;

/* Bitrate */

typedef enum {
     CAN_BITRATE_NOBPS,
     CAN_BITRATE_5KBPS,
     CAN_BITRATE_10KBPS,
     CAN_BITRATE_20KBPS,
     CAN_BITRATE_25KBPS,
     CAN_BITRATE_31K25BPS,
     CAN_BITRATE_33KBPS,
     CAN_BITRATE_40KBPS,
     CAN_BITRATE_50KBPS,
     CAN_BITRATE_80KBPS,
     CAN_BITRATE_83K3BPS,
     CAN_BITRATE_95KBPS,
     CAN_BITRATE_95K2BPS,
     CAN_BITRATE_100KBPS,
     CAN_BITRATE_125KBPS,
     CAN_BITRATE_200KBPS,
     CAN_BITRATE_250KBPS,
     CAN_BITRATE_500KBPS,
     CAN_BITRATE_666KBPS,
     CAN_BITRATE_800KBPS,
     CAN_BITRATE_1000KBPS
} mcp_bitrate_t;

#endif	/* __MCP_CAN_H__ */
