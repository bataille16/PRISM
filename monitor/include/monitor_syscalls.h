/*

PRISM Project
02/15/2012
bataille16@gmail.com

Header files describing the overriden system calls
*/



#ifndef MONITOR_SYSCALLS_H
#define MONITOR_SYSCALLS_H




extern int PID;
extern void **sys_call_table; // pointer to system call table on machine
// change memory page read/write options

// save/set and reset sys calls
void save_originals(void);
void load_monitor_syscalls(void);
void cleanup(void);

// open (0x5)
//asmlinkage int (*original_open) (const char *, int, int);
asmlinkage int monitor_open(const char *, int, int);

#endif //MONITOR_SYSCALLS_H
