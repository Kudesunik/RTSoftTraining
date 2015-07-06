SOURCES = ModuleSender ModuleReceiver
TARGET = $(SOURCES:=.o)
DIR = /lib/modules/$(shell uname -r)/build
PWD = $(shell pwd)

obj-m += $(TARGET)

all:
	make -C $(DIR) M=$(PWD) modules
clean:
	make -C $(DIR) M=$(PWD) clean
