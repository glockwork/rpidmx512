/**
 * @file rdm_device_const.h
 */
/* Copyright (C) 2015 by Arjan van Vught <pm @ http://www.raspberrypi.org/forum/>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef RDM_DEVICE_CONST_H_
#define RDM_DEVICE_CONST_H_

#include <stdint.h>

#include "rdm.h"

static const uint8_t  DEVICE_LABEL[] = "Raspberry Pi DMX USB Pro";
static const uint8_t  DEVICE_MANUFACTURER_NAME[] = "AvV";
static const uint8_t  DEVICE_MANUFACTURER_ID[] = {0x7F, 0xF0};	///< 0x7F, 0xF0 : RESERVED FOR PROTOTYPING/EXPERIMENTAL USE ONLY
static const uint8_t  DEVICE_SUPPORTED_LANGUAGE[] = "en";
static const uint8_t  DEVICE_SOFTWARE_VERSION[] = "1.0";
static const uint32_t DEVICE_SOFTWARE_VERSION_ID = 0x20150321;

#define DEFAULT_DMX_START_ADDRESS		1
#define DEFAULT_CURRENT_PERSONALITY		1
#define DMX_FOOTPRINT					512

static const struct _rdm_personality rdm_personalities[] = {
		{ DMX_FOOTPRINT, "Raspberry Pi DMX USB Pro" }
		};

#endif /* RDM_DEVICE_CONST_H_ */
