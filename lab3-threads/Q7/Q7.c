#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS	10
#define LEN_ARRAY_THREADS	10
int GlobalGeneratedValues[LEN_ARRAY_THREADS*NUM_THREADS];
pthread_mutex_t mutexsum;

void *GenerateValues(void *threadid)
{
	int taskId;
	taskId = (int)threadid;
	//printf("\taskId ,  %d\n", taskId);

	int i=0, tmepvalue; 
	int LocalThreadGeneratedValues[NUM_THREADS];

	for (i =0; i <= LEN_ARRAY_THREADS; i++)	 // generates the random values and put in the local array in side the thread
	{
		tmepvalue = rand() % 11; // between 0 and 10 
		while (tmepvalue == 0 ) 
			tmepvalue = rand() % 11;	
		LocalThreadGeneratedValues[i] = tmepvalue;
	}
	
	int SegmentNo = (LEN_ARRAY_THREADS*taskId); // buliding the index offset of each thread to work with array
	pthread_mutex_lock (&mutexsum);          // starting the critical section 
	for(i=0; i < LEN_ARRAY_THREADS; i++)
	{
		GlobalGeneratedValues[SegmentNo + i] = LocalThreadGeneratedValues[i];
		printf("\ntaskId:%d , GlobalGeneratedValues[%d] = %d \t",taskId,i, LocalThreadGeneratedValues[i]);
	}
	pthread_mutex_unlock (&mutexsum);
	
	pthread_exit(NULL);
}

void main(int argc, char *argv[])
{
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

		rc = pthread_create(&threads[t], &attr, GenerateValues, (void *)t);
		if (rc) {	printf("ERROR; return code from pthread_create() is %d\n", rc);	exit(-1);	}
	  }

	pthread_attr_destroy(&attr);
	for(t=0;t<NUM_THREADS;t++)
	{
		rc = pthread_join(threads[t], &status); 
		if (rc){	printf("ERROR return code from pthread_join() is %d\n", rc);	 exit(-1);	}
	}
	
	int sum = 0;        // make the summation at the end, when all the threads have been finished
	for(int i=0; i<LEN_ARRAY_THREADS*NUM_THREADS; i++)
	{
		printf("\nGlobalGeneratedValues[%d] = %d \t Sum = %d",i, GlobalGeneratedValues[i], sum);
		sum += GlobalGeneratedValues[i];
	}
	printf("\n\n\n\n The sum of all generated value numbers by threads is : %d",sum);

	pthread_mutex_destroy(&mutexsum);
	pthread_exit(NULL);
}
