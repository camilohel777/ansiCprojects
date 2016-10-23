/*
Camilo Rivera
Camilo Riviere
 */
/* Operating Systems course, Fall 2016: Creating a module and printing at Linux Ubuntu kernel level*/
#include <linux/module.h>

static int hello_init(void)
{
 printk("Hello world, this is Camilo Rivera\n");
 printk("Hello world 2, this is Camilo Rivera\n");
 printk("Hello world 3, this is Camilo Rivera\n");
 return 0;
}

static void hello_exit(void)
{
 printk("This is Camilo Rivera, Goodbye world\n");
 printk("This is Camilo Rivera 2, Goodbye world\n");
 printk("This is Camilo Rivera 3, Goodbye world\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_AUTHOR("Camilo Rivera");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Hello World");
