obj-m := tsu.o

KDIR := /lib/modules/$(shell uname -r)/build

PWD := $(shell pwd)

all: run test clean
sudo dmesg | tail -n 4
run:
$(MAKE) -C $(KDIR) M=$(PWD) modules
sudo insmod tsu.ko

test:
cat /proc/tsulab

clean:
sudo rmmod tsu
$(MAKE) -C $(KDIR) M=$(PWD) clean