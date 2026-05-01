#ifndef FAN_HW_H
#define FAN_HW_H

#include <linux/kernel.h>

#include <linux/gpio/consumer.h>

#define IO_FAN      13
#define IO_OFFSET   512

#define SET_FAN_ON  1
#define SET_FAN_OFF 0


int fan_gpio_init(void);

int fan_gpio_on(void);

int fan_gpio_off(void);

#endif  /* FAN_HW_H */