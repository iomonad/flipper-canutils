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

#ifndef __CAN_H__
#define __CAN_H__

#include "mcp2518fd.h"

typedef unsigned char __u8;
typedef unsigned short __u16;
typedef unsigned long __u32;

/* special address description flags for the CAN_ID */
#define CAN_EFF_FLAG 0x80000000UL /* EFF/SFF is set in the MSB */
#define CAN_RTR_FLAG 0x40000000UL /* remote transmission request */
#define CAN_ERR_FLAG 0x20000000UL /* error message frame */

/* valid bits in CAN ID for frame formats */
#define CAN_SFF_MASK 0x000007FFUL /* standard frame format (SFF) */
#define CAN_EFF_MASK 0x1FFFFFFFUL /* extended frame format (EFF) */
#define CAN_ERR_MASK 0x1FFFFFFFUL /* omit EFF, RTR, ERR flags */

/*
 * Controller Area Network Identifier structure
 *
 * bit 0-28 : CAN identifier (11/29 bit)
 * bit 29   : error message frame flag (0 = data frame, 1 = error message)
 * bit 30   : remote transmission request flag (1 = rtr frame)
 * bit 31   : frame format flag (0 = standard 11 bit, 1 = extended 29 bit)
 */
typedef __u32 canid_t;

#define CAN_SFF_ID_BITS 11
#define CAN_EFF_ID_BITS 29

/* CAN payload length and DLC definitions according to ISO 11898-1 */
#define CAN_MAX_DLC 8
#define CAN_MAX_DLEN 8

struct can_frame {
    canid_t can_id; /* 32 bit CAN_ID + EFF/RTR/ERR flags */
    __u8 can_dlc; /* frame payload length in byte (0 .. CAN_MAX_DLEN) */
    __u8 data[CAN_MAX_DLEN] __attribute__((aligned(8)));
};

/* device holder structure */
typedef struct {
     mcp2518fd_device_t *driver;
} can_device_t;


/* primitive */

can_device_t *can_device_init();
void         can_device_deinit(can_device_t *device);

#endif // __CAN_H__
