/**
 * @file rdm_identify.c
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

#include <stdint.h>

#include "util.h"
#include "irq_led.h"

static uint8_t rdm_identify_enabled = FALSE;	///<

/**
 *
 * @return
 */
const uint8_t rdm_identify_is_enabled(void)
{
	return rdm_identify_enabled;
}

/**
 *
 */
void rdm_identify_off(void)
{
	rdm_identify_enabled = FALSE;

	/*
	 * Replace below with user code
	 */
	ticks_per_second_set(1E6 / 2);
}

/**
 *
 */
void rdm_identify_on(void)
{
	rdm_identify_enabled = TRUE;

	/*
	 * Replace below with user code
	 */
	ticks_per_second_set(1E6 / 4);
}

/**
 *
 */
void rdm_identify(void)
{
	if (rdm_identify_enabled == FALSE)
		return;

	/*
	 * Add user code here
	 */
}
