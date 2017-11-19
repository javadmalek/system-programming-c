#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>


/*
int Counter = 0;
it had the concurrency problem when the CounterThread thread tried to change Counter and the solution is to use the mutex
*/

long Counter = 0;
void *Conter() //infinit increament function for increament thread
{
	while(1)
	{
		Counter++;
		//printf("Counter1 = %ld\t", Counter);
	}
}

void *Printer() // printing the value of counter in the infinit loop by a second sleep
{
	while(1)
	{
		printf("Counter2 = %ld\n", Counter);
		sleep(1);	
	}		
}


void main() 
{
	int pid1, pid2, rc1, rc2;
	pthread_t ConterThrd,PrinterThrd; 

	rc1 = pthread_create(&ConterThrd, NULL, Conter, NULL);
	if (rc1)	{		
		printf("Error:unable to create thread, error no: %d", rc1);
		return;
	}
	rc2 = pthread_create(&PrinterThrd, NULL, Printer, NULL);
	if (rc2)	{		
		printf("Error:unable to create thread, error no: %d", rc2);
		return;
	}

	pthread_join( ConterThrd, NULL);
	pthread_join( PrinterThrd, NULL); 
}
