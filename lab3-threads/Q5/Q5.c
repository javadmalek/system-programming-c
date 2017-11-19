#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

/*
int shareValue = 10;
it had the concurrency problem when each thread tried to change shareValue and the solution is to use the mutex
*/
int shareValue = 10;
void *F1() // for the second child to call for its threads
{
	printf("\n\nin PID=%d 1st shareValue = %d",getpid(),shareValue);	
	//shareValue = 1;
	printf("\t new shareValue = %d\n",shareValue);	
	pthread_exit(NULL);
}
void *F2()// for the first child to call for its threads
{
	printf("\n\nin PID=%d 2st shareValue = %d",getpid(),shareValue);	
	//shareValue = 2;
	printf("\t PID=%d new shareValue = %d\n",shareValue);	
	pthread_exit(NULL);
}
void *F3()// for the main process to call for its threads
{
	printf("\n\nin PID=%d 3st shareValue = %d",getpid(),shareValue);	
	//shareValue = 3;
	printf("\t PID=%d new shareValue = %d\n",shareValue);	
	pthread_exit(NULL);
}

void main() 
{
	int pid1, pid2;
	pthread_t T1,T2,T3; 
	
	shareValue=0;

	pid1 = fork();
	switch(pid1) 
	{
		case -1:
			printf("Error in forck Function\n\n\n");
			break;
		case 0: 
			//execl("/bin/ls","bin/ls -l",(char *)0,0); 
			/* runs the command but the other processes terminated!? */
			pid2 = fork();
			//execl("/bin/ls","bin/ls -l",(char *)0,0);
			switch(pid2)
			{
				case -1: 
					printf("Error in forck Function\n\n\n");
					exit(0);
				case 0: //second child
					//execl("/bin/ls","bin/ls -l",(char *)0,0);
					/* runs the command but sometimes the other processes terminated! and sometimes they runned */
					pthread_create(&T1, NULL, F1, NULL);
					pthread_create(&T2, NULL, F1, NULL);
					pthread_create(&T3, NULL, F1, NULL);
					//execl("/bin/ls","bin/ls -l",(char *)0,0);
					pthread_join( T1, NULL);
					pthread_join( T2, NULL);
					pthread_join( T3, NULL);
					exit(0);
					break;					
				default: //first child
					pthread_create(&T1, NULL, F2, NULL);
					pthread_create(&T2, NULL, F2, NULL);
					pthread_create(&T3, NULL, F2, NULL);
					pthread_join( T1, NULL);
					pthread_join( T2, NULL);
					pthread_join( T3, NULL);
					break;
			}
			break;

		default: //father
			pthread_create(&T1, NULL, F3, NULL);
			pthread_create(&T2, NULL, F3, NULL);
			pthread_create(&T3, NULL, F3, NULL);
			pthread_join( T1, NULL);
			pthread_join( T2, NULL);
			pthread_join( T3, NULL);
					
			break;
	}
}
