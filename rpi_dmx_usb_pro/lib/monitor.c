/**
 * @file monitor.c
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

#include <stdio.h>

#include "dmx.h"
#include "widget.h"
#include "widget_params.h"
#include "console.h"
#include "monitor.h"
#include "sniffer.h"
#include "util.h"

static uint32_t dmx_packets_previous = 0;

/**
 * @ingroup monitor
 */
void monitor_update(void)
{
	char dir[3][10] =
	{ "Idle", "Output", "Input" };
	struct _widget_params widget_params;

	widget_params_get(&widget_params);

	monitor_time_uptime(1);

	const uint8_t widget_mode = widget_mode_get();

	if (widget_mode == MODE_RDM_SNIFFER)
	{
		monitor_dmx_data(3, dmx_data);

		const struct _total_statistics *total_statistics = total_statistics_get();
		const uint32_t total_packets = total_statistics->dmx_packets + total_statistics->rdm_packets;

		console_clear_line(7);
		printf("Packets : %ld, DMX %ld, RDM %ld\n\n", total_packets, total_statistics->dmx_packets, total_statistics->rdm_packets);

		const struct _rdm_statistics *rdm_statistics = rdm_statistics_get();

		printf("Discovery          : %ld\n", rdm_statistics->discovery_packets);
		printf("Discovery response : %ld\n", rdm_statistics->discovery_response_packets);
		printf("GET Requests       : %ld\n", rdm_statistics->get_requests);
		printf("SET Requests       : %ld\n", rdm_statistics->set_requests);

		const uint16_t dmx_updates_per_second = total_statistics->dmx_packets - dmx_packets_previous;

		console_clear_line(14);
		console_clear_line(17);
		printf("DMX updates/sec %d  \n", dmx_updates_per_second);
		if (dmx_updates_per_second)
		{
			printf("Slots in packet %d  \n", (uint16_t)dmx_get_slots_in_packet());
			printf("Slot to slot    %d  \n", (uint16_t)dmx_get_slot_to_slot());
			printf("Break to break  %ld\n", dmx_get_break_to_break());
		}
		else
		{
			printf("Slots in packet -- \n");
			printf("Slot to slot    -- \n");
			printf("Break to break  --\n");
		}
		dmx_packets_previous = total_statistics->dmx_packets;
	} else
	{
		console_clear_line(2);

		printf("FW %d.%d BreakTime %d(%d) MaBTime %d(%d) RefreshRate %d(%d)\n",
				widget_params.firmware_msb, widget_params.firmware_lsb,
				widget_params.break_time, (int) dmx_get_output_break_time(),
				widget_params.mab_time, (int) dmx_get_output_mab_time(),
				widget_params.refresh_rate, (int)(1E6 / dmx_get_output_period()));

		console_clear_line(3);

		if (DMX_PORT_DIRECTION_INP == dmx_get_port_direction())
			printf("Input [%s]\n", receive_dmx_on_change_get() == SEND_ALWAYS ? "SEND_ALWAYS" : "SEND_ON_DATA_CHANGE_ONLY");
		else
		{
			printf("%s\n", dir[dmx_get_port_direction()]);
		}

		// line 4 LABEL
		// line 5 Info

		monitor_dmx_data(8, dmx_data);

		// line 11 RDM Data
	}
}
