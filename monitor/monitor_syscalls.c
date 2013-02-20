/*

PRISM Project
02/15/2012
bataille16@gmail.com

Implementation of overidden syscalls

*/

#undef __KERNEL__
#define __KERNEL__

#undef MODULE
#define MODULE


#include <linux/unistd.h>
#include <linux/moduleparam.h>	
#include <linux/kernel.h>	/* We're doing kernel work */
#include <linux/module.h>	/* Specifically, a module, */
#include <linux/moduleparam.h>	/* which will have params */
#include <linux/unistd.h>	/* The list of system calls */
#include <linux/sched.h>
#include "include/monitor_syscalls.h"

//extern void *sys_call_table[]; // pointer to system call table on machine
void ** sys_call_table = (void*) 0xc1832320;
//extern void **sys_call_table = 0xc1832320; // pointer to system call table on machine
asmlinkage int (*original_open) (const char *, int, int);




void save_originals(void)
{

	//sys_call_table = (void*) 0xc1832320;
	original_open = sys_call_table[__NR_open];
}

void load_monitor_syscalls(void)
{

	sys_call_table[__NR_open] = monitor_open;
}


void cleanup(void)
{
	sys_call_table[__NR_open] = original_open;
}



//asmlinkage int (*original_open) (const char *, int, int);
// open (0x5)
asmlinkage int monitor_open(const char *filename, int flags, int mode)
{

	if (PID == current->pid)
		//pause core and perform analysis
		printk(KERN_INFO "HEY, this opened\n");
	
	return original_open(filename, flags, mode);

}


