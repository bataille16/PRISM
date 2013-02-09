/*
02/08/2012
bataille16@gmail.com

Linux Kernel module that receives pid from launcher process
and monitors sys calls made by pid

*/

#undef __KERNEL__
#define __KERNEL__

#undef MODULE
#define MODULE

#include <linux/types.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

// start 


// initialization call
static int __init monitor(void)
{

	printk(KERN_INFO "Monitor Kernel Module Started\n");
	return 0;
}


//exit call
static void __exit leave_monitor(void)
{
	printk(KERN_INFO "Monitor Kernel Module Ended\n"); 
	
}


//module registation
module_init(monitor); 
module_exit(leave_monitor); 
