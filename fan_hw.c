#include <linux/kernel.h>
#include <linux/thermal.h>
#include <linux/gpio/consumer.h>

#include "fan_hw.h"

static struct gpio_desc *fan;
static struct thermal_zone_device *tmp;

/* Static Functions Prototypes*/

static int fan_gpio_init(void);
static int fan_init_tmp(void);

static int fan_on(void);
static int fan_off(void);

static int fan_get_tmp(void);



int fan_init(void)
{
    int status;

    status = fan_gpio_init();
    if (status != 0) {
        pr_err("fan_ctrl_drv - gpio Error");
        return status;
    }

    status = fan_init_tmp();
    if (status != 0) {
        return status;
    }

    return status;
}

int fan_deinit(void)
{
    // GPIO autamaticly deinit after removing module from Kernel
    
    fan_off();
    pr_alert("fan_ctrl_drv - Module removed form kernel\n");

    return 0;
}

void fan_run(void)
{
    int temperature;
    static int mode = FAN_OFF;

    temperature = fan_get_tmp();

    if (temperature > THRESHOLD_ON_TEMPERATURE && mode == FAN_OFF) {
        fan_on();
        mode = FAN_ON;
    } else if (temperature < THRESHOLD_OFF_TEMPERATURE && mode == FAN_ON) {
        fan_off();
        mode = FAN_OFF;
    }

    // pr_alert("fan_ctrl_drv - Current tmp %d°C\n", temperature);
}


/* Static Functions */

static int fan_gpio_init(void)
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

static int fan_init_tmp(void)
{
    tmp = thermal_zone_get_zone_by_name("cpu-thermal");
    if (IS_ERR(tmp)) {
        pr_err("fan_ctrl_drv - tmp init error\n");
        return PTR_ERR(tmp);
    }

    return 0;
}

static int fan_on(void)
{
    gpiod_set_value(fan, FAN_ON);
    pr_info("fan_ctrl_drv - Fan turn ON\n");

    return 0;
}

static int fan_off(void)
{
    gpiod_set_value(fan, FAN_OFF);
    pr_info("fan_ctrl_drv - Fan turn OFF\n");

    return 0;
}

static int fan_get_tmp(void) 
{
    int ctemp = 0;

    thermal_zone_get_temp(tmp, &ctemp);

    ctemp = ctemp / 1000;       // Convert from °C * 1000 to normal

    return ctemp;
}