#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


long GlobalSumValues = 0;
int GlobalX = 0;
pthread_mutex_t mutexsum;

void *Xpower2I(void *threadid)
{
	int taskId;
	taskId = (int)threadid;
	

	long i=0, tmepvalue = 1; 
	int LocalPower=0;

	for (i =0; i < taskId; i++)	// compute the 2^i by each thread
	{
		tmepvalue *= GlobalX;
	}
	
	pthread_mutex_lock(&mutexsum);  // tyrs to add to the globl sum
	GlobalSumValues += tmepvalue;
	printf("\ntaskId:%d ,\tLocalSumValue = %ld,\tGlobalSumValues = %ld ",taskId,tmepvalue, GlobalSumValues);
	pthread_mutex_unlock(&mutexsum);
	

	pthread_exit(NULL);
}

void main(int argc, char *argv[])
{	
	if(argc != 3){	printf("\nInput arrguments are not correct....\n");	return; }
	GlobalX = atoi(argv[1]);	
	int NUM_THREADS = atoi(argv[2]);	

	pthread_t threads[NUM_THREADS];
	pthread_attr_t attr;
	void *status;
	int rc, t;
	
	pthread_mutex_init(&mutexsum, NULL);
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	for(t=0;t<NUM_THREADS;t++) 
	{
		printf("Creating thread : %d\n", t);

		rc = pthread_create(&threads[t], &attr, Xpower2I, (void *)t);
		if (rc) {	printf("ERROR; return code from pthread_create() is %d\n", rc);	exit(-1);	}
	  }

	pthread_attr_destroy(&attr);
	for(t=0;t<NUM_THREADS;t++)
	{
		rc = pthread_join(threads[t], &status); 
		if (rc){	printf("ERROR return code from pthread_join() is %d\n", rc);	 exit(-1);	}
	}
	
	printf("\n\n\nGlobalSumValues = %ld \n",GlobalSumValues);

	pthread_mutex_destroy(&mutexsum);
	pthread_exit(NULL);
}
