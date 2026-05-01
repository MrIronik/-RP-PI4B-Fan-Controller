#include <linux/kernel.h>

#include <linux/gpio/consumer.h>

#include "fan_hw.h"

static struct gpio_desc *fan;

int fan_gpio_init(void)
{
    int status;

    fan = gpio_to_desc(IO_FAN + IO_OFFSET);
    if (!fan) {
        printk("fan_ctrl - Error getting pin 13\n");
        return -ENODEV;
    }

    status = gpiod_direction_output(fan, 0);
    if (status) {
        printk("fan_ctrl - Error setting pin 13 to output\n");
        return status;
    }

    return 0;
}

int fan_gpio_on(void)
{
    gpiod_set_value(fan, SET_FAN_ON);
}

int fan_gpio_off(void)
{
    gpiod_set_value(fan, SET_FAN_OFF);
}