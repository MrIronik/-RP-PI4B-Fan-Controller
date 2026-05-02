#ifndef FAN_CTRL_H
#define FAN_CTRL_H

#include <linux/module.h>
#include <linux/init.h>
#include <linux/gpio/consumer.h>

int fan_ctrl_init(void);
void fan_ctrl_exit(void);

#endif  /* FAN_CTRL_H */