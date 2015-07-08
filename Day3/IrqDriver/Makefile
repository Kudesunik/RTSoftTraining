SOURCES = IrqDriver
TARGET = $(SOURCES:=.o)
DIR = /home/user/ti-processor-sdk-linux-am335x-evm-01.00.00.00/board-support/linux-3.14.26-g2489c02
PWD = $(shell pwd)

obj-m += $(TARGET)

all:
	make -C $(DIR) M=$(PWD) modules
clean:
	make -C $(DIR) M=$(PWD) clean
