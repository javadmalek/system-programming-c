#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


int GlobalCounter = 0, NewNumber = 0;;
pthread_mutex_t mutexsum;

void *Func1(void *threadid)   // for first thread to take value and starting the programm, other threads MUST WAITE for initializing
{
	int taskId;
	taskId = (int)threadid;
	
	pthread_mutex_lock (&mutexsum);		
	printf("\n\nThread 1: Enter New Number To be added the Counter (0: Terminate the process)\n");
	scanf("%d",&NewNumber);
	GlobalCounter += NewNumber;
	printf("taskId: %d ,\tThread 1: GlobalCounter is %d\n", taskId,GlobalCounter);
	pthread_mutex_unlock (&mutexsum);
	
	pthread_exit(NULL);
}

void *Func234(void *threadid)
{
	int taskId;
	taskId = (int)threadid;
	int TID = pthread_self();	

	while (GlobalCounter == 0);// printf("\nwait please...");;  
/*	this is a busy waiting and the solution is conditional variable (there is turn problem and initalization problem at first-
 it is possible for other 3rd threads to read when the value has no correct value)*/

 	pthread_mutex_lock (&mutexsum);		
	while(GlobalCounter > 0)
	{
		GlobalCounter--;
		printf("taskId: %d ,\tThread ID: %d ,\t GlobalCounter is %d\n", taskId,TID, GlobalCounter);
		sleep(1);
	}
	pthread_mutex_unlock (&mutexsum);
	
	pthread_exit(NULL);
}

void main(int argc, char *argv[])
{
	pthread_t threads[4];
	pthread_attr_t attr;
	void *status;
	int rc, t;

	pthread_mutex_init(&mutexsum, NULL);
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	t = 0;	printf("Creating thread : %d\n",t); 
	pthread_create(&threads[t], &attr, Func1, (void *)t);

	t = 1;	printf("Creating thread : %d\n",t); 
	pthread_create(&threads[t], &attr, Func234, (void *)t);

	t = 2;	printf("Creating thread : %d\n",t); 
	pthread_create(&threads[t], &attr, Func234, (void *)t);

	t = 3;	printf("Creating thread : %d\n",t); 
	pthread_create(&threads[t], &attr, Func234, (void *)t);

	pthread_attr_destroy(&attr);
	for(t=0;t<4;t++)
		pthread_join(threads[t], &status); 

	pthread_mutex_destroy(&mutexsum);
	pthread_exit(NULL);
}
