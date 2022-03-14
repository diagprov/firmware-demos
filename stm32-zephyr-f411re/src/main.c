/*
 * Copyright (c) 2019 Jan Van Winkel <jan.van_winkel@dxplore.eu>
 *
 * Based on ST7789V sample:
 * Copyright (c) 2019 Marc Reilly
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <stdio.h>
#include <string.h>

#include <logging/log.h>
LOG_MODULE_REGISTER(node, LOG_LEVEL_INF);
#include <zephyr.h>
#include <device.h>

#include "common.h"
#include "lcd.h"
#include "sensor.h"


void main(void)
{
	LOG_INF("FIRMWARE SETUP");
    //sensors_init();
    display_render();

    while (1) {
	    LOG_INF("FIRMWARE LOOP ITERATON");
        //sensors_read();
        //display_update();

		k_msleep(1000);
	}
    

	RETURN_FROM_MAIN(0);
}
