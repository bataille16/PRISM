/*

PRISM Project
02/15/2012
bataille16@gmail.com

Implementation of overidden syscalls

*/
#include <linux/unistd.h> 
#include "include/monitor_syscalls.h"



extern void *sys_call_table[]; // pointer to system call table on machine


int monitored_sys_open(void)
{

	return -23;
}


