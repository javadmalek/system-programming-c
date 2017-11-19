#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

/*
the only a semaphore is not enugth to protect the mutex because the turn is important , hence the conditional variable is necessary to protect that
*/
pthread_mutex_t condition_mutex = PTHREAD_MUTEX_INITIALIZER;  // a semaphor for mutex
pthread_cond_t  condition_cond  = PTHREAD_COND_INITIALIZER; 
/* a conditional variable (because at the first time when a thread comes and it isnot its turn, this thread must release the mutex and wait for other thread to do its job)*/
int turn=0;
long Counter = 0;

void *Conter()
{
	while(1)
	{
		pthread_mutex_lock( &condition_mutex ); // choon momken hast meghdari baraye khoondan nabashad
		if(turn==0) pthread_cond_wait( &condition_cond, &condition_mutex );
	
		turn=1;
		Counter++;  // changes the shared variable

		pthread_cond_signal( &condition_cond );
		pthread_mutex_unlock( &condition_mutex );
	}
}

void *Printer()
{
	while(1)
	{
		pthread_mutex_lock( &condition_mutex );
		if(turn==1) pthread_cond_wait( &condition_cond, &condition_mutex );	

		turn=1;
		printf("Counter2 = %ld\n", Counter);
		sleep(1);	

		pthread_cond_signal( &condition_cond );
		pthread_mutex_unlock( &condition_mutex );
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
