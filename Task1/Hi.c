#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_AUTHOR("Nikita (Kunik) Kuznetsov");
MODULE_VERSION("1.0.0");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Hi");

static int __init module1_init(void)
{
	printk(KERN_ALERT "Hi RTSoft from Linux Kernel!\n");
	return 0;
}

static void __exit module1_exit(void)
{
	printk(KERN_ALERT "Go away...\n");
}

module_init(module1_init);
module_exit(module1_exit);
