#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(int argc, char *argv[]) 
{
	int data_processed, file_pipes[2], fd1, file_read, numread, finalread=0, x, fork_result, wrote;
	struct stat statbuf;
	
	stat(argv[1], &statbuf);
	printf("Size of file: %lu\n", statbuf.st_size);
    
	x=statbuf.st_size;
    
    char buffer[x];
    char buffer2[x];
    
    fd1 = open(argv[1],O_RDONLY);
    
    if (pipe(file_pipes) == 0)
    {
        fork_result = fork();
		
		if (fork_result==-1)
		{
			printf("Fork Failed\n");
		}//ending if()

    	else if (fork_result == 0) 
		{   
			close(file_pipes[1]); 
			numread = read(file_pipes[0], buffer2, x);
			printf("Child read %d bytes \n",numread);
			exit(0);
		}//ending else if()
		else 
		{    
			close(file_pipes[0]); 
			file_read = read(fd1, buffer, x);
			wrote=write(file_pipes[1], buffer, file_read);
			printf("Parent Wrote %d bytes\n",wrote);			
			close(fd1);
			wait();
		}//ending else
    }//ending if ()
    return 0;
}//ending main ()
