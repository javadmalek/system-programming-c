#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

/* if you dont want to manage the errors and execption you can reboot your PC, (also you cannot print the result of yyour computaion) 
I prefer to control this logical error and produce the result of my programm at time of error
*/
void *PrintHello(void *threadid)
{
   pthread_exit(NULL);
}

void main() 
{
	int pid1, pid2, rc;
	int countrProcesses=2, countrThreads=2;

	struct timeval start, end;
	long mtime, seconds, useconds;    
	gettimeofday(&start, NULL);
	
	printf("\n *************** Starting to Fork And Execute ************ \n\n");
	pid1 = fork();
	switch(pid1) 
	{
		case -1:
			printf("Error in forck Function\n\n\n");
			break;
		case 0: // First Child of Fork 2 counts processes
			//int countrProcesses=2; // parent and current child
			while(1) // Infint loop to fork new processes by First Child
			{
				pid2 = fork();
				switch(pid2)
				{
					case -1:  // printing the result when it is impossible to create new processe (because it is over) 
						gettimeofday(&end, NULL);
						seconds  = end.tv_sec  - start.tv_sec;
						useconds = end.tv_usec - start.tv_usec;
						mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5; // computing the time diffrence at beging of program up the time of last process
						printf("Processes Elapsed time: %ld milliseconds\n\n", mtime);
						printf("MAX CHILD ID IS :%ld\n\n",sysconf(_SC_CHILD_MAX));

						printf("countrProcesses = %d\n\n\n\n\n",countrProcesses);
						return;
					case 0: // Doing somthing in second child 
						exit(0);
						break;					
					default: // counting the number of processes 
						countrProcesses++;
						break;
				};
			} // End Of Processes While
			break;

		default: // First Parent 2 counts Threads
			//int countrThreads=2; // parent and current child
			while(1) 
			{
				pthread_t tmpThrd; int i;
				rc = pthread_create(&tmpThrd, NULL, PrintHello, (void *)i);
				if (rc)	{
					gettimeofday(&end, NULL);
					seconds  = end.tv_sec  - start.tv_sec;
					useconds = end.tv_usec - start.tv_usec;
					mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
					printf("Threads Elapsed time: %ld milliseconds\n", mtime);

					printf("countrThreads = %d\n\n\n\n\n",countrThreads);
					pthread_exit(NULL);
					return;
				}
				else countrThreads++;

			}// End Of Threads While			
			break;
	}
}
