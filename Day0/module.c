#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/sched.h>

MODULE_AUTHOR("Nikita (Kunik) Kuznetsov");
MODULE_VERSION("1.0.0");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Task1");

struct task_struct *p;
struct task_struct *t;

int pid = 0;

module_param(pid, int, 0);

void print_pids(void) 
{
	for_each_process(p) {
		printk(KERN_INFO "Pid of %s process = %d\n", p -> comm, p -> pid);
	}
}

void print_threads_pid(void) 
{
	p = pid_task(find_get_pid(pid), PIDTYPE_PID);

	if(p != NULL) {
		for_each_thread(p, t) {
			printk(KERN_INFO "Pid of %s thread = %d\n", t -> comm, t -> pid);
		}
	}
	else {
		printk(KERN_INFO "Process with pid = %d not running!\n", pid);
	}
}


int __init module1_init(void)
{

	printk(KERN_INFO "Module 1 loaded...\n");

	if (pid) {
		print_threads_pid();
	}
	else {
		print_pids();
	}

	return 0;
}

void __exit module1_exit(void)
{
	printk(KERN_INFO "Module 1 unloaded!\n");
}

module_init(module1_init);
module_exit(module1_exit);
