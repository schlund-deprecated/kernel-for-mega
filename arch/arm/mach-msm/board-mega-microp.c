/* arch/arm/mach-msm/board-buzz-microp.c
 * Copyright (C) 2009 HTC Corporation.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
*/
#ifdef CONFIG_MICROP_COMMON
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/platform_device.h>
#include <mach/atmega_microp.h>
#include <mach/drv_callback.h>

#include "board-mega.h"

static struct i2c_client *buzz_microp_client;

static int buzz_microp_function_init(struct i2c_client *client)
{
	struct microp_i2c_platform_data *pdata;
	struct microp_i2c_client_data *cdata;
	uint8_t data[20];
	int i, j;
	int ret;

	buzz_microp_client = client;
	pdata = client->dev.platform_data;
	cdata = i2c_get_clientdata(client);

	/* Headset remote key */
	ret = microp_function_check(client, MICROP_FUNCTION_REMOTEKEY);
	if (ret >= 0) {
		i = ret;
		pdata->function_node[MICROP_FUNCTION_REMOTEKEY] = i;
		cdata->int_pin.int_remotekey =
			pdata->microp_function[i].int_pin;

		for (j = 0; j < 6; j++) {
			data[j] = (uint8_t)(pdata->microp_function[i].levels[j] >> 8);
			data[j + 6] = (uint8_t)(pdata->microp_function[i].levels[j]);
		}
		ret = microp_i2c_write(MICROP_I2C_WCMD_REMOTEKEY_TABLE,
				data, 12);
		if (ret)
			goto exit;
	}

	/* Reset button interrupt */
	ret = microp_write_interrupt(client, (1<<8), 1);
	if (ret)
		goto exit;
	/* OJ interrupt */
	ret = microp_function_check(client, MICROP_FUNCTION_OJ);
	if (ret >= 0) {
		i = ret;
		cdata->int_pin.int_oj = pdata->microp_function[i].int_pin;

		ret = microp_write_interrupt(client, cdata->int_pin.int_oj, 1);
		if (ret)
			goto exit;
	}
	return 0;

exit:
	return ret;
}

static struct microp_ops ops = {
	.init_microp_func = buzz_microp_function_init,
};

void __init buzz_microp_init(void)
{
	microp_register_ops(&ops);
}

#endif
