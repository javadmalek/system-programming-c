#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/shm.h>
#define SHMSIZE 4 

void semaphore_init (int* sw)
{
	if (pipe(sw) == -1) 
	{
		printf ("init() process error\n");
		exit (-1); 
	}//ending if()
}//ending void semaphore_init()

void semaphore_wait (int* sw)
{
	char buffer;
	if (read(sw[0],&buffer,1) != 1) {
		printf ("Buffer value is %c. Error in wait()\n", buffer);
		exit (-1);
	}//ending if()
}//ending void semaphore_wait()

void semaphore_signal (int* sw)
{
	if (write(sw[1],"X",1) != 1) {
		printf ("Error in signal()\n");
		exit (-1);
	}//ending if()
}//ending semaphore_signal()

int main(void) 
{	
	int mutex[2],full[2],empty[2],buffer[2],sem_in[2],n,shmid,read,write;
	int fork_result,N=4,i;
	char *shmPtr;
	
	semaphore_init (mutex);
	semaphore_init (full);
	semaphore_init (empty);
	semaphore_init (sem_in);
	
	pipe(buffer);
	
	semaphore_signal(mutex);
	for( i=1 ; i<=4 ; i++)
	{
		semaphore_signal(empty);
	}//ending for()

	printf("Enter number of letters to read (max 4) = ");
	scanf("%d",&read);
   
	printf("Enter number of letters to write (max 4) = ");
	scanf("%d",&write);
   
	fork_result = fork();
	
	if (fork_result == 0) 
	{
		shmid=shmget(2041, SHMSIZE, 0666 | IPC_CREAT);
		shmPtr=shmat(shmid, 0, 0); 
		   
		int y=1,out=0,r,q;
		char x;
		
		while(y<=read)
			{
				semaphore_wait(full);
				semaphore_wait(mutex);
			
				printf("\nI am consumer, mutex, out is %d, character read from shared memory is %c",out,shmPtr[out]);
				printf("\n");
				out=(out+1)%N;
				
				semaphore_signal(mutex);
				semaphore_signal(empty);
			
			y++;
			sleep(2);
		}//ending while()
	}//ending if()
	else 
	{   
		int y=1,in=0,r,q;
		
		shmid=shmget(2041, SHMSIZE, 0666 | IPC_CREAT);
		shmPtr=shmat(shmid, 0, 0);
		
		while(y<=write)
			{
				semaphore_wait(empty);
				semaphore_wait(mutex);

				shmPtr[in]='a'+in;
				printf("\nI am Producer, mutex, is in %d, character written in shared memory is %c",in,shmPtr[in]);
				printf("\n");
					in=(in+1)%N;
				
				semaphore_signal(mutex);
				semaphore_signal(full);
			
		y++;
		sleep(2);
		}//ending while()
	}//ending else
	return 0;
}//ending main ()
