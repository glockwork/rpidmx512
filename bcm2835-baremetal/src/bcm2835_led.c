/**
 * @file bcm2835_led.c
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
#include "bcm2835.h"
#include "bcm2835_gpio.h"

#define NEW_PI_PIN		47

#ifdef NEW_PI
#define PIN		NEW_PI_PIN
#else
#define PIN		16
#endif


/**
 * @ingroup Led
 *
 * @param state \ref HIGH sets the led on and \ref LOW sets the led off.
 */
void led_set(const int state)
{
#ifdef NEW_PI
	if (state)
		BCM2835_GPIO->GPSET1 = 1 << (NEW_PI_PIN % 32);
	else
		BCM2835_GPIO->GPCLR1 = 1 << (NEW_PI_PIN % 32);
#else
	if (!state)
		BCM2835_GPIO->GPSET0 = 1 << PIN;
	else
		BCM2835_GPIO->GPCLR0 = 1 << PIN;
#endif
}

/**
 * @ingroup Led
 *
 * Set the GPIO pin for the led to output.
 *
 */
void led_init(void)
{
#ifdef NEW_PI
	uint32_t value = BCM2835_GPIO->GPFSEL4;
	value &= ~(7 << 21);
	value |= BCM2835_GPIO_FSEL_OUTP << 21;
	BCM2835_GPIO->GPFSEL4 = value;
#else
	uint32_t value = BCM2835_GPIO->GPFSEL1;
	value &= ~(7 << 18);
	value |= BCM2835_GPIO_FSEL_OUTP << 18;
	BCM2835_GPIO->GPFSEL1 = value;
#endif
}

/**
 * @ingroup Led
 *
 * @param state \ref HIGH sets the led on and \ref LOW sets the led off.
 */
void led_new_pi_set(const int state)
{
	if (state)
		BCM2835_GPIO->GPSET1 = 1 << (NEW_PI_PIN % 32);
	else
		BCM2835_GPIO->GPCLR1 = 1 << (NEW_PI_PIN % 32);
}

/**
 * @ingroup Led
 *
 * Set the GPIO pin for the led to output.
 *
 */
void led_new_pi_init(void)
{
	uint32_t value = BCM2835_GPIO->GPFSEL4;
	value &= ~(7 << 21);
	value |= BCM2835_GPIO_FSEL_OUTP << 21;
	BCM2835_GPIO->GPFSEL4 = value;
}
