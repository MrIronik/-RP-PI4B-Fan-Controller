#ifndef FAN_HW_H
#define FAN_HW_H

#include <linux/kernel.h>

#include <linux/gpio/consumer.h>

#define IO_FAN      13
#define IO_OFFSET   512

#define FAN_ON  1
#define FAN_OFF 0

#define THRESHOLD_ON_TEMPERATURE    60
#define THRESHOLD_OFF_TEMPERATURE   55


int fan_init(void);
int fan_deinit(void);

void fan_run(void);

#endif  /* FAN_HW_H */