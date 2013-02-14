/*
02/08/2012
bataille16@gmail.com

User-level process launcher.
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#ifndef __USE_GNU
#define __USE_GNU
#endif
#include <sched.h>
#include<linux/sched.h>
int main()
{

	cpu_set_t mask; 
 	int exec_val;
	pid_t pID;

	char *envp[] = { NULL };
 	char *argv[] = { "./dummy.o", "hello", "there", NULL };
 
	pID = fork();
	// setting cpu mask
	CPU_ZERO(&mask);
	CPU_SET(1, &mask);

	if (sched_setaffinity(pID, sizeof(cpu_set_t), &mask)!=0)
		printf("Warning: Could not set core affinity\n");	
	printf("Process id is %d\n", pID);

	switch(pID)
	{
		case 0:
			printf("pID 1 is %d\n", pID); 
			exec_val = execve("./dummy.o", argv,envp);
		default:
			if( waitpid(pID, &exec_val, 0) <0)
			{
				printf("error\n");
				exit(-1);
			}
	}
	
	//exec_val = execve("./dummy.o", argv,envp);
		
		
	return 0 ;
}
