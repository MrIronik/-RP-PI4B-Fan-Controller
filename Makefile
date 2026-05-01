obj-m += fan_ctrl

fan_ctrl-objs := fan_ctrl.o fan_hw.o

all:
	make -C /lib/modules/${shell uname -r}/build M=${PWD} modules

clean:
	make -C /lib/modules/${shell uname -r}/build M=${PWD} clean