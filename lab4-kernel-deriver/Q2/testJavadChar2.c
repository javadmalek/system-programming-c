#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include <pthread.h>

#define BUF_LEN 256

char msg[BUF_LEN];
int fd;
pthread_mutex_t mutex;


int  ReadingThreads()
{
	printf("\n\n********************\nStarting device reading by TaskID: %d \nReading from the device...\n",pthread_self());

	pthread_mutex_lock(&mutex);

	int ret = read(fd, msg, BUF_LEN);        // Read the response from the LKM
	printf("The received message is: [%s]\n", msg);

	pthread_mutex_unlock(&mutex);

	if (ret < 0){
		perror("Failed to read the message from the device.");
		return errno;
	}

	pthread_exit(NULL);
}


int WritingThread()
{

	printf("\n\n********************\nStarting device by means of Writing by TaskID: %d \n");
	printf("Type in a short string to send to the kernel module:\n",pthread_self());

	pthread_mutex_lock(&mutex);

	scanf("%[^\n]%*c", msg);                // Read in a string (with spaces)
	int ret = write(fd, msg, strlen(msg)); // Send the string to the LKM
	printf("Done Writing.\tMessage to the device [%s].\n", msg);	

	pthread_mutex_unlock(&mutex);

	if (ret < 0){
		perror("Failed to write the message to the device.\n");
		return errno;
	}

	pthread_exit(NULL);
}

void main()
{
	pthread_t Threads[16];
	pthread_mutex_init(&mutex,NULL);
	

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	int i;

	printf("\n\n********************\nStarting device test code example...\nOpening the file descriptor as a share variable\n");
	fd = open("/dev/JavadChar", O_RDWR);             // Open the device with read/write access
	if (fd < 0){
		perror("Failed to open the device...");
		return errno;
	}

	
	for(i = 0; i<4; i++)
	{
		pthread_create(&Threads[4*i+0], &attr, WritingThread,NULL);
	
		pthread_create(&Threads[4*i+1], &attr, ReadingThreads,NULL);
		pthread_create(&Threads[4*i+2], &attr, ReadingThreads,NULL);
		pthread_create(&Threads[4*i+3], &attr, ReadingThreads,NULL);

		printf("Threads Created\n");
	}

	pthread_attr_destroy(&attr);
	for(int j = 0; j < 16; j++)
		pthread_join(Threads[j], NULL);


	pthread_mutex_destroy(&mutex);
	close(fd);
	printf("End of the program\n");
}
