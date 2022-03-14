#include <stdio.h>
#include <string.h>

#include <logging/log.h>
LOG_MODULE_REGISTER(sensors, LOG_LEVEL_INF);
#include <zephyr.h>
#include <device.h>
#include <drivers/i2c.h>
#include <drivers/sensor.h>

#include "common.h"
#include "lcd.h"
#include "sensor.h"


const struct device *sensor_dev = NULL;
#define BMP388_DEV_NAME DT_LABEL(DT_NODELABEL(bmp388))

void sensors_init()
{
    sensor_dev = device_get_binding(BMP388_DEV_NAME);

    if ( sensor_dev == NULL ) {
        LOG_ERR("Device BMP388 not found.");
        return;
    }
    LOG_INF("Device BMP388 found.");
}

void sensors_read()
{
    struct sensor_value temp, press;

    if ( sensor_dev == NULL ) return;

	sensor_sample_fetch(sensor_dev);
	sensor_channel_get(sensor_dev, SENSOR_CHAN_AMBIENT_TEMP, &temp);
	sensor_channel_get(sensor_dev, SENSOR_CHAN_PRESS, &press);

	printk("temp: %d.%06d; press: %d.%06d;\n",
		      temp.val1, temp.val2, press.val1, press.val2);
}


