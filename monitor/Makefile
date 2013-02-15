#
#02/08/2012
# Makefile for monitor kernel module


obj-m := malware_monitor.o
#ccflags-y := -Iinclude

#monitor-y := monitor_syscalls.o

malware_monitor-objs := monitor_syscalls.o monitor.o


.PHONY: all clean 


KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
EXTRA_CFLAGS +=-I$(PWD)/include

all:
	$(MAKE) $(EXTRA_CFLAGS) -C $(KDIR) M=$(PWD) modules
 
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
