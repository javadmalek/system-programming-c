#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#include <sys/stat.h>

/*
this is the Writer&Reader problem because there is a common buffer to read and write, 
here I assumed the limit for the length of file 
and reader starts to read first then the writer will start its jobs
*/
int length=0;
char buffer[10000];

void *Reader(void *argv_ReadFileStr)
{
	int file;
	file = open(argv_ReadFileStr, O_RDONLY);
	length = read(file,buffer, 10000);
	printf("\nlength: %d\n",length);

}

void *Writer(void *argv_WriteFileStr)
{
	int file;
	file = open(argv_WriteFileStr, O_WRONLY|O_CREAT, 0644);
	write(file,buffer, length);
}


void main(int argc, char *argv[]) 
{
	if(argc != 3) {
		printf("Error in input data (Read file, write file name)");
		return;
	}

	pthread_t ReaderThrd,WriterThrd; 

	pthread_create(&ReaderThrd, NULL, Reader, (void *)argv[1]); // calling the reader thread to read from file
	pthread_join( ReaderThrd, NULL); // the main thread wait for child thread to complete the its job
	
	pthread_create(&WriterThrd, NULL, Writer, (void *)argv[2]); //calling the writer thread to write into second file
	pthread_join( WriterThrd, NULL);
}
