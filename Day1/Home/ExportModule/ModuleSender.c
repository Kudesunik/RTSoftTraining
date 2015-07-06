#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/sched.h>

MODULE_AUTHOR("Nikita (Kunik) Kuznetsov");
MODULE_VERSION("1.0.0");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Sender module");

int pid = 0;

module_param(pid, int, 0);

extern void printProcessInfo(int);

static int __init module_sender_init(void)
{
	printk(KERN_ALERT "Sender module loaded...\n");

	if (pid) {
		printProcessInfo(pid);
	}

	return 0;
}

static void __exit module_sender_exit(void)
{
	printk(KERN_ALERT "Sender module unloaded!\n");
}

module_init(module_sender_init);
module_exit(module_sender_exit);
