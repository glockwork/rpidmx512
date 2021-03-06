/**
 * @file rdm_sub_devices.h
 *
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

#ifndef RDM_SUB_DEVICES_H_
#define RDM_SUB_DEVICES_H_

#include "rdm.h"
#include "rdm_device_info.h"

struct _rdm_sub_devices_info
{
	uint16_t dmx_footprint;
	uint8_t current_personality;
	uint8_t personality_count;
	uint16_t dmx_start_address;
	uint8_t sensor_count;
	uint8_t device_label[DEVICE_LABEL_MAX_LENGTH];
	uint8_t device_label_length;
	const struct _rdm_personality *rdm_personalities;
};

extern const uint16_t rdm_sub_devices_get_footprint(const uint16_t);

extern const uint16_t rdm_sub_devices_get_dmx_start_address(const uint16_t);
extern void rdm_sub_devices_set_dmx_start_address(const uint16_t, const uint16_t);

extern const uint8_t * rdm_sub_devices_get_label(const uint16_t);
extern void rdm_sub_devices_set_label(const uint16_t, const uint8_t *, uint8_t);
extern const uint8_t rdm_sub_devices_get_label_length(const uint16_t);

extern const struct _rdm_sub_devices_info *rdm_sub_devices_info_get(const uint16_t);
extern void rdm_sub_devices_info_set(const uint16_t , const struct _rdm_sub_devices_info *);

extern const uint8_t rdm_sub_devices_get_personality_current(const uint16_t);
extern void rdm_sub_devices_set_personality_current(const uint16_t, const uint8_t);

extern const char *rdm_sub_devices_get_personality_description(const uint16_t, const uint8_t);

extern const uint16_t rdm_sub_devices_get_personality_slots(const uint16_t, const uint8_t);

extern const uint16_t rdm_sub_devices_get(void);

#endif /* RDM_SUB_DEVICES_H_ */
