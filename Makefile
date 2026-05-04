.PHONY: all clean

obj-m += fan_ctrl_drv.o

fan_ctrl_drv-objs := fan_ctrl.o fan_hw.o fan_chr.o


all:
	make -C /lib/modules/${shell uname -r}/build M=${PWD} modules

clean:
	make -C /lib/modules/${shell uname -r}/build M=${PWD} clean