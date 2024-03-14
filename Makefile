obj-m += usb_drv.o
$pcie_drv-objs := pcie_drv.c
KERN_DIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

EXTRA_CFLAGS += -Wall

CFLAGS += -I$(KERN_DIR)/include/generated
all:
	$(MAKE) -C $(KERN_DIR) M=$(PWD)
clean:
	$(MAKE) -C $(KERN_DIR) M=$(PWD) clean
