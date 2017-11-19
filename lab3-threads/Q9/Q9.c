#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int IsPrime = 1;
int Golba_N = 0; // the value to check prime
int Global_P = 0; // the number of threads
int SubSetLen = 0;   // sub length to check by thread 
int RemainedThread = 0;  
/*
here we divided SubSetLen = Golba_N/Global_P; to find the length of compution by each thread
*/

pthread_mutex_t mutexsum;

void *CheckPrime(void *threadid)
{
	int taskId, i=0;
	taskId = (int)threadid;
	
	int startIndex = (SubSetLen * taskId);  // the offset to startIndex   
	if(taskId == 0) i=2; // the first task must skip 1,2
	/*
	(Golba_N/2) >= (startIndex + i) to avoid over computation when we reach to the N/2
	(startIndex + i) != 1; when the length is 1 all the time Golba_N % 1 = 0 then the computation ahead on wrong way  
	*/
	for(; i<SubSetLen && (Golba_N/2) >= (startIndex + i) && (startIndex + i) != 1; i++ ) 
	{
		if(Golba_N % (startIndex + i) == 0)
		{
			pthread_mutex_lock(&mutexsum);
			IsPrime = 0;
			printf("taskId:%d ,\tIsnot Prime: %d/%d=0\n",taskId,Golba_N,(startIndex + i));
			pthread_mutex_unlock(&mutexsum);return;
			pthread_exit(NULL);
		}
	}
		
	/*// other semaphor to count the number of processses because when the number isnot prime, we can find the end of computation*/
	pthread_mutex_lock(&mutexsum);   
	RemainedThread--;
	printf("taskId:%d ,\tRemainedThread = %d \n",taskId,RemainedThread);
	pthread_mutex_unlock(&mutexsum);

	pthread_exit(NULL);
}

void main(int argc, char *argv[])
{	
	if(argc != 3){	printf("\nInput arrguments are not correct Global_P Golba_N ...\n");	return; }
	Global_P = atoi(argv[1]);
	RemainedThread = Global_P;	
	Golba_N = atoi(argv[2]);

	SubSetLen = Golba_N/Global_P; // tool subset har thread
	if(SubSetLen == 0)
	{ 
		printf("\nThe number of threads are more than N, Global_P must be less than Golba_N because it is impossible to divid the elements among threads\n");
		return;
	}

	pthread_t threads[Global_P];
	pthread_attr_t attr;
	int rc, t;
	
	pthread_mutex_init(&mutexsum, NULL);

	for(t=0; t < Global_P; t++) 
	{
		printf("Creating thread : %d\n", t);

		rc = pthread_create(&threads[t], NULL, CheckPrime, (void *)t);
		if (rc) {	printf("ERROR; return code from pthread_create() is %d\n", rc);	exit(-1);	}
	}

	/*the unlimited loop up to the time one of threads changes the value of IsPrime = 0 Or one of threads remained
	Isprime checked by main thread continuosly */
	while(1 ) //  ta zamanike yeki az thread ha IsPrime ra 0 kond ya hanooz threadei baghi mandeh bashad 
	{
		if (IsPrime == 0) // Is not prime
		{ 
			printf("\n\nMain Function: Golba_N = %d isnot prime \n", Golba_N);
			pthread_mutex_destroy(&mutexsum); 
			pthread_exit(NULL);
			return;
		}
		
		if(RemainedThread == 0) 	// no one of threads changed the value of IsPrime and all of them terminated compeletly
		{ 
			printf("\n\nMain Function: Golba_N = %d is prime \n", Golba_N);
			pthread_mutex_destroy(&mutexsum); 
			pthread_exit(NULL);
			return;
		}		
	}
}
