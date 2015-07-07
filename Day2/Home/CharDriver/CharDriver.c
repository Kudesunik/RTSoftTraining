#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <asm/uaccess.h>

#include "CharDriverIoctl.h"

MODULE_AUTHOR("Nikita (Kunik) Kuznetsov");
MODULE_VERSION("1.0.0");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Char driver with ioctl");

#define SUCCESS 0;

char deviceName[] = "TestDevice";

static int majorNumber;

char *messageBuffer;

int messageBufferSize = 128;
int messageBufferMask = 127;
int indexWrite = 0;
int indexRead = 0;

static int device_open(struct inode *inode, struct file *file)
{
	printk(KERN_ALERT "Device opened!\n");
	return SUCCESS;
}

static int device_release(struct inode *inode, struct file *file)
{
	printk(KERN_ALERT "Device closed!\n");
	return SUCCESS;
}

static ssize_t device_read(struct file *filp, char *buffer, size_t length, loff_t *offset)
{
	int bytesRead = 0;
	printk(KERN_ALERT "Start reading...\n");

	if (indexWrite == indexRead) {
		return 0;
	}

	while (length && (indexWrite != indexRead)) {
		printk(KERN_INFO "Reading char: %c on index = %d\n", messageBuffer[indexRead], indexRead);
		put_user(messageBuffer[indexRead++], buffer++);
		length--;
		indexRead &= messageBufferMask;
		bytesRead++;
	}

	return bytesRead;
}

static ssize_t device_write(struct file *filp, const char *buffer, size_t length, loff_t *offset)
{
	int bytesWrite = 0;
	int index = length - 1;
	printk(KERN_ALERT "Start writing...\n");

	while (length > 0) {
		printk(KERN_INFO "Writing char: %c on index = %d\n", buffer[index], indexWrite);
		messageBuffer[indexWrite++] = buffer[index--];
		length--;
		indexWrite &= messageBufferMask;
		bytesWrite++;
	}

	return bytesWrite;
}

static long device_unlocked_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	printk(KERN_INFO "Ioctl message received!\n");

	switch(cmd) {
		case IOCTL_GET_MSG:
			printk(KERN_INFO "IOCTL_GET_MSG message received! Arg = %d\n", (int) arg);
			messageBuffer = kmalloc(((int) arg) * sizeof(char), GFP_KERNEL);
			messageBufferSize = ((int) arg);
			messageBufferMask = messageBufferSize - 1;
			indexWrite = 0;
			indexRead = 0;
			break;
	}

	return SUCCESS;
}

struct file_operations fops = {
		.owner = THIS_MODULE,
		.open = device_open,
		.release = device_release,
		.read = device_read,
		.write = device_write,
		.unlocked_ioctl = device_unlocked_ioctl
};

static int __init device_init(void)
{
	printk(KERN_ALERT "Char driver loaded...\n");

	messageBuffer = kmalloc(128 * sizeof(char), GFP_KERNEL);

	majorNumber = register_chrdev(0, deviceName, &fops);

	if (majorNumber < 0) {
		printk(KERN_ALERT "Registering char device failed with error # %d\n", majorNumber);
		return majorNumber;
	}

	printk(KERN_INFO "Driver registered. Major number = %d\n", majorNumber);
	printk(KERN_INFO "Don't forget to exec 'mknod /dev/%s c %d 0'\n", deviceName, majorNumber);

	return SUCCESS;
}

static void __exit device_exit(void)
{
	unregister_chrdev(majorNumber, deviceName);
	printk(KERN_ALERT "Char driver unloaded!\n");
}

module_init(device_init);
module_exit(device_exit);
