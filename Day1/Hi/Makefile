DIR = /home/kunik/Programming/am335x-evm/board-support/linux-3.14.26-g2489c02
PWD = $(shell pwd)

TARGET = Hi

obj-m += $(TARGET).o

all:
	make -C $(DIR) M=$(PWD) modules
clean:
	make -C $(DIR) M=$(PWD) clean
