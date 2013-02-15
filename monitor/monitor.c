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

long (*k_setaffinity)(pid_t, const struct cpumask*);
	
static int __init monitor(void)
{
	
	// get cpu mask of bootstrap core (core 0 is safe assumption)
	const struct cpumask  *mask =  get_cpu_mask(0);	
	long monitor_affinity;
 
	/*
	 To get sched_setaffinity(pid, cpumask) to work in kernel mode, we have 2 options:
		1- Export Symbol and re-compile kernel
		2- Use function pointer of sched_setaffinity from System.map file
	*/

	printk(KERN_INFO "Monitor Kernel Module Started\n");
	printk(KERN_INFO "Monitoring process %d\n", PID); 

	/* 	
	  Testing approach 2 : Export sched_setaffinity address from System.map 	
	  We defined the function pointer k_setaffinity (i.e. kernel set affinity) 
	  and point it to the (local machine) address where the kernel function sched_setaffinity is located
	  We can find that address in /boot/System.map . This value is static as it is after the kernel is compiled
	*/
	k_setaffinity = 0xc1055f90;		

	// kernel module level core affinity setting for PID
	//monitor_affinity = k_setaffinity(PID,mask); // set this process to this cpu 
	
	monitor_affinity = k_setaffinity(0,mask); // set this process to this cpu 
	printk(KERN_INFO "Testing function pointer %d\n", monitor_affinity);

	return 0;



}


//exit call
static void __exit leave_monitor(void)
{
	printk(KERN_INFO "Monitor Kernel Module Stopped\n"); 
	
}


//module registation
module_init(monitor); 
module_exit(leave_monitor); 


//misc info
//MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jerry B. Backer");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Monitor sys calls of process with id PID");
