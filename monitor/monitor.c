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
#include <linux/sched.h>
// start 

// add pid parameter
static int PID =0;
module_param(PID,int, 0);
MODULE_PARM_DESC(PID, "Process id to be monitored");
// initialization call


static int monitor_process(pid_t pid)
{
	
	pid_t c_pid = current->pid;
	printk(KERN_INFO "Current Process is %i\n", c_pid);
	return 0; 

}

static int __init monitor(void)
{

	printk(KERN_INFO "Monitor Kernel Module Started\n");
	printk(KERN_INFO "Monitoring process %d\n", PID); 
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
