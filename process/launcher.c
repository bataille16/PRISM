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

int main()
{

 	int exec_val;
	pid_t pID;

	char *envp[] = { NULL };
 	char *argv[] = { "./dummy.o", "hello", "there", NULL };
 
	pID = fork();
	
	switch(pID)
	{
		case 0:
			printf("pID 1 is %d\n", pID); 
			exec_val = execve("./dummy.o", argv,envp);
		default:
			printf("pID 2 is %d\n", pID); 	
			if( waitpid(pID, &exec_val, 0) <0)
			{
				printf("pID 3 is %d\n", pID);	
				printf("error\n");
				exit(-1);
			}
	}
	
	printf("pID is  %d\n", pID);	
	//exec_val = execve("./dummy.o", argv,envp);
		
		
	return 0 ;
}
