#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/sched.h>

MODULE_AUTHOR("Nikita (Kunik) Kuznetsov");
MODULE_VERSION("1.0.0");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Receiver module");

struct task_struct *p;

void printProcessInfo(int pid)
{
	p = pid_task(find_get_pid(pid), PIDTYPE_PID);
	printk(KERN_INFO "Process # %d info:\n", p -> pid);
	printk(KERN_INFO "Name: %s\n", p -> comm);
	printk(KERN_INFO "State: %ld\n", p -> state);
	printk(KERN_INFO "Parent process id: %d\n", p -> parent -> pid);
	printk(KERN_INFO "Thread group id: %d\n", p -> tgid);
}

static int __init module_receiver_init(void)
{
	printk(KERN_ALERT "Reciever module loaded...\n");
	return 0;
}

static void __exit module_receiver_exit(void)
{
	printk(KERN_ALERT "Reciever module unloaded!\n");
}

module_init(module_receiver_init);
module_exit(module_receiver_exit);

EXPORT_SYMBOL(printProcessInfo);
