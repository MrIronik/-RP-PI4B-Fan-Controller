#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>

#include "fan_ctrl.h"
#include "fan_hw.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mikołaj Majewski");
MODULE_DESCRIPTION("Simple driver to turn on RP Pis fan on GPIO13");

static int major;

static int fan_ctrl_init(void)
{
    int status;

    status = fan_gpio_init();

    return status;
}

static void fan_ctrl_exit(void)
{
    fan_gpio_off();
}

module_init(fan_ctrl_init);
module_exit(fan_ctrl_exit);