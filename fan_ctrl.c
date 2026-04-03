#include <linux/module.h>
#include <linux/init.h>
#include <linux/gpio/consumer.h>

#include "fan_ctrl.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mikołaj Majewski");
MODULE_DESCRIPTION("Simple driver to turn on RP Pis fan on GPIO13");

static struct gpio_desc *fan;

int fan_ctrl_init(void)
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

    gpiod_set_value(fan, 1);

    return 0;
}

void fan_ctrl_exit(void)
{
    gpiod_set_value(fan, 0);
}

module_init(fan_ctrl_init);
module_exit(fan_ctrl_exit);