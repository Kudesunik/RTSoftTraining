DIR = /lib/modules/$(shell uname -r)/build
PWD = $(shell pwd)

TARGET = module

obj-m += $(TARGET).o

all:
	make -C $(DIR) M=$(PWD) modules

clean:
	make -C $(DIR) M=$(PWD) clean
