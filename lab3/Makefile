obj-m += tsulab.o
KERNELDIR ?= /usr/src/linux-headers-$(shell uname -r)
PWD := $(CURDIR)

all:
    $(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
    $(MAKE) -C $(KERNELDIR) M=$(PWD) clean