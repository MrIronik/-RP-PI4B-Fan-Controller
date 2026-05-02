#include <linux/kernel.h>
#include <linux/gpio/consumer.h>

#include "fan_hw.h"

static struct gpio_desc *fan;

int fan_init(void)
{
    int status;

    fan = gpio_to_desc(IO_FAN + IO_OFFSET);
    if (!fan) {
        pr_err("fan_ctrl_drv - Error getting pin 13\n");
        return -ENODEV;
    }

    status = gpiod_direction_output(fan, 0);
    if (status) {
        pr_err("fan_ctrl_drv - Error setting pin 13 to output\n");
        return status;
    }

    pr_info("fan_ctrl_drv - Successful init\n");

    return 0;
}

int fan_deinit(void)
{
    // GPIO autamaticly deinit after removing module from Kernel
    
    fan_off();
    pr_alert("fan_ctrl_drv - Module removed form kernel\n");

    return 0;
}

int fan_on(void)
{
    gpiod_set_value(fan, SET_FAN_ON);
    pr_info("fan_ctrl_drv - Fan turn ON\n");

    return 0;
}

int fan_off(void)
{
    gpiod_set_value(fan, SET_FAN_OFF);
    pr_info("fan_ctrl_drv - Fan turn OFF\n");

    return 0;
}