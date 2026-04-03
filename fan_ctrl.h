#include <linux/module.h>
#include <linux/init.h>
#include <linux/gpio/consumer.h>


#define IO_FAN      13
#define IO_OFFSET   512


int fan_ctrl_init(void);
void fan_ctrl_exit(void);