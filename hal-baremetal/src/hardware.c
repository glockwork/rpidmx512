/**
 * @file hardware.c
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

#include <time.h>

#include "bcm2835.h"
#include "bcm2835_vc.h"
#include "bcm2835_led.h"
#include "bcm2835_wdog.h"
#include "mcp7941x.h"

#include "hardware.h"
#include "sys_time.h"

static const uint8_t FIRMWARE_COPYRIGHT[] = "Copyright (c) 2012 Broadcom";								///<
static const uint8_t FIRMWARE_COPYRIGHT_LENGTH = (sizeof(FIRMWARE_COPYRIGHT) / sizeof(uint8_t)) - 1;	///<

struct _hardware_led
{
	void (*init)(void);								///< Pointer to function for LED ACCT init (GPIO FSEL OUTPUT)
	void (*set)(const int);							///< Pointer to function for LED ACCT on/off
} static _hardware_led_f = {led_init, led_set};

#define MAX_NAME_LENGTH 20

struct _hardware_revision_code
{
	uint32_t value;
	const uint8_t name[MAX_NAME_LENGTH];
} const board_version[] = {
		{0x000000, "Model Unknown       "},
		{0x000002, "Model B R1 256MB    "},
		{0x000003, "Model B R1 256MB    "},
		{0x000004, "Model B R2 256MB    "},
		{0x000005, "Model B R2 256MB    "},
		{0x000006, "Model B R2 256MB    "},
		{0x000007, "Model A 256MB       "},
		{0x000008, "Model A 256MB       "},
		{0x000009, "Model A 256MB       "},
		{0x00000d, "Model B R2 512MB    "},
		{0x00000e, "Model B R2 512MB    "},
		{0x00000f, "Model B R2 512MB    "},
		{0x000010, "Model B+ 512MB      "},
		{0x000011, "Compute Module 512MB"},
		{0x000012, "Model A+ 256MB      "},
		{0xa01041, "Pi 2 Model B 1GB    "},
};

extern void fb_init(void);

static volatile uint64_t hardware_init_startup_micros = 0;	///<

/**
 *
 * @return
 */
const uint64_t hardware_uptime_seconds(void)
{
	return (((bcm2835_st_read() - hardware_init_startup_micros) / 1E6));
}

/**
 *
 * @return
 */
const uint32_t hardware_get_firmware_revision(void)
{
	return bcm2835_vc_get_get_firmware_revision();
}

/**
 *
 * @return
 */
const uint8_t *hardware_get_firmware_copyright(void)
{
	return FIRMWARE_COPYRIGHT;
}

/**
 *
 * @return
 */
const uint8_t hardware_get_firmware_copyright_length(void)
{
	return FIRMWARE_COPYRIGHT_LENGTH;
}

/**
 *
 * @return
 */
const uint32_t hardware_get_board_model_id(void)
{
	return bcm2835_vc_get_get_board_revision();
}

/**
 *
 * @return
 */
const uint8_t *hardware_get_board_model(void)
{
	const uint8_t array_length = sizeof(board_version) / sizeof(board_version[0]);
	const uint32_t revision_code = bcm2835_vc_get_get_board_revision();

	if (revision_code <= 0)
		return board_version[0].name;

	int i;
	for (i = 1; i < array_length ; i++)
	{
		if (revision_code == board_version[i].value)
			return board_version[i].name;
	}

	return board_version[0].name;
}

/**
 *
 * @return
 */
const uint8_t hardware_get_board_model_length(void)
{
	return MAX_NAME_LENGTH;
}

/**
 *
 */
void hardware_led_init(void)
{
	_hardware_led_f.init();
}

/**
 *
 * @param state
 */
void hardware_led_set(const int state)
{
	_hardware_led_f.set(state);
}

/**
 *
 * @param tm_hw
 */
void hardware_rtc_set(const struct hardware_time *tm_hw)
{
	struct rtc_time tm_rtc;

	tm_rtc.tm_hour = tm_hw->hour;
	tm_rtc.tm_min = tm_hw->minute;
	tm_rtc.tm_sec = tm_hw->second;
	tm_rtc.tm_mday = tm_hw->day;
	//tm_rtc.tm_wday = // TODO
	tm_rtc.tm_mon = tm_hw->month;
	tm_rtc.tm_year = tm_hw->year - 2000;	// RTC stores 2 digits only

	if (mcp7941x_start(0x00) != MCP7941X_ERROR)
	{
		mcp7941x_set_date_time(&tm_rtc);
	}

	struct tm tmbuf;

	tmbuf.tm_hour = tm_rtc.tm_hour;
	tmbuf.tm_min = tm_rtc.tm_min;
	tmbuf.tm_sec = tm_rtc.tm_sec;
	tmbuf.tm_mday = tm_rtc.tm_mday;
	tmbuf.tm_wday = tm_rtc.tm_wday;
	tmbuf.tm_mon = tm_rtc.tm_mon;
	tmbuf.tm_year = tm_rtc.tm_year;
	tmbuf.tm_isdst = 0;

	sys_time_set(&tmbuf);
}

/**
 *
 */
void hardware_init(void)
{
	hardware_init_startup_micros = bcm2835_st_read();
	sys_time_init();
	fb_init();

	const uint32_t revision_code = bcm2835_vc_get_get_board_revision();

	if (revision_code > 0x00000f)
	{
		_hardware_led_f.init = led_new_pi_init;
		_hardware_led_f.set = led_new_pi_set;
	}

	hardware_led_init();
	hardware_led_set(1);
}

/**
 *
 */
void hardware_reboot(void)
{
	hardware_led_set(1);
	watchdog_init();
	for(;;);
}
