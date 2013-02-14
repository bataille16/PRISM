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
#include<linux/unistd.h>
#include <linux/cpumask.h>
//#include <linux/cpuidle.h>  --> modify cpuidle to get the work done
// start 

// add pid parameter
static int PID =0;
module_param(PID,int, 0);
MODULE_PARM_DESC(PID, "Process id to be monitored");

/*
static int monitor_process(pid_t pid)
{



	const struct cpumask  *mask =  get_cpu_mask(0);
	pid_t c_pid = current->pid;
	printk(KERN_INFO "Current Process is %i\n", c_pid);
	return 0; 

}

*/
static int __init monitor(void)
{
	
	// get cpu mask of bootstrap core (core 0 is safe assumption)
	const struct cpumask  *mask =  get_cpu_mask(0);	
	long monitor_affinity;
	long (*k_setaffinity)(pid_t, const struct cpumask*);
	 
	/*
	 To get sched_setaffinity(pid, cpumask) to work in kernel mode, we have 2 options:
		1- Export Symbol and re-compile kernel
		2- Use function pointer of sched_setaffinity from System.map file
	*/



	printk(KERN_INFO "Monitor Kernel Module Started\n");
	printk(KERN_INFO "Monitoring process %d\n", PID); 


	// Testing approach 2 : Export sched_setaffinity address from System.map 	
	k_setaffinity = 0xc1055a40;	
	monitor_affinity = k_setaffinity(PID,mask);
	//printk(KERN_INFO "Testing function pointer %d\n", monitor_affinity);



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


//misc info
MODULE_AUTHOR("Jerry B. Backer");
MODULE_DESCRIPTION("Monitor sys calls of process with id PID");
