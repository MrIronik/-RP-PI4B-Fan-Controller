#include <linux/module.h>
#include <linux/init.h>
#include <linux/workqueue.h>

#include "fan_ctrl.h"
#include "fan_hw.h"
#include "fan_chr.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mikołaj Majewski");
MODULE_DESCRIPTION("Simple driver to turn on RP Pis fan on GPIO13");

static struct delayed_work fan_work;

static void fan_work_task(struct work_struct *work)
{
    fan_run();

    schedule_delayed_work(&fan_work, msecs_to_jiffies(1000));
}

int fan_ctrl_init(void)
{
    int status;

    status = fan_init();

    INIT_DELAYED_WORK(&fan_work, fan_work_task);
    schedule_delayed_work(&fan_work, msecs_to_jiffies(1000));

    return status;
}

void fan_ctrl_exit(void)
{
    cancel_delayed_work_sync(&fan_work);    
    fan_deinit();
}

module_init(fan_ctrl_init);
module_exit(fan_ctrl_exit);