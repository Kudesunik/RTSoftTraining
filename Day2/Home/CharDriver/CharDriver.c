#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/ioctl.h>
#include <linux/slab.h>
#include <asm/uaccess.h>

MODULE_AUTHOR("Nikita (Kunik) Kuznetsov");
MODULE_VERSION("1.0.0");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Char driver with ioctl");

#define SUCCESS 0;

char deviceName[] = "TestDevice";

static int majorNumber;

char *messageBuffer;

int indexIn = 0;
int indexOut = 0;

static int device_open(struct inode *inode, struct file *file)
{
	printk(KERN_ALERT "Device opened!\n");

	messageBuffer = "Test message for userspace program";

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

	if (*messageBuffer == 0) {
		return 0;
	}

	while (length && *messageBuffer) {
		put_user(*(messageBuffer++), buffer++);
		length--;
		bytesRead++;
	}

	return bytesRead;
}

static ssize_t device_write(struct file *filp, const char *buffer, size_t length, loff_t *offset)
{
	int bytesWrite = 0;
	printk(KERN_ALERT "Start writing...\n");

	return bytesWrite;
}

static long device_unlocked_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	printk(KERN_INFO "Ioctl message received!\n");
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

