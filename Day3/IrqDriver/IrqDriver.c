#include <linux/gpio.h>
#include <linux/irq.h>
#include <linux/interrupt.h>

MODULE_AUTHOR("Nikita (Kunik) Kuznetsov");
MODULE_VERSION("1.0.0");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Irq driver");

#define GPIO_NUM 67
#define GPIO_NAME "InterruptLine"
#define IRQ_NAME "GPIO IRQ"

static int gpio_irq_num = 0;

irqreturn_t irq_handler(int irq, void *notused)
{
	printk("IRQ both handled\n");
	return IRQ_HANDLED;
}

static int __init irq_driver_init(void)
{
	printk(KERN_INFO "Irq driver loaded...\n");
	
	if (gpio_request(GPIO_NUM, GPIO_NAME)) {
		printk(KERN_ALERT "Gpio request error!\n");
	}
	if ((gpio_irq_num = gpio_to_irq(GPIO_NUM)) < 0) {
		printk(KERN_ALERT "Gpio irq num error!\n");
	}
	if (request_irq(gpio_irq_num, irq_handler, 0, IRQ_NAME, NULL)) {
		printk(KERN_ALERT "Request irq error!\n");
	}

	irq_set_irq_type(gpio_irq_num, IRQ_TYPE_EDGE_BOTH);

	return 0;
}

static void __exit irq_driver_exit(void)
{
	free_irq(gpio_irq_num, NULL);
	gpio_free(GPIO_NUM);

	printk(KERN_INFO "Irq driver unloaded!\n");
}

module_init(irq_driver_init);
module_exit(irq_driver_exit);
