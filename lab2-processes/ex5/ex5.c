#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>

void main(int argc, char *argv[])
{	
	int pid_ 1 = fork(), pid_2 = fork();

	if (pid_1 < 0)
	{
		printf("Fork Failed\n");
	
	}//ending if()
	
	else if (pid_1 > 0)
	{
		wait();	
		execlp("cat","cat","mypasswd",NULL);	
	}//ending else

	else
	{
		pid_2 = fork();

		if (pid_2 > 0)
		{
			wait();
			execlp("sort","sort","passwd","-o","mypasswd",NULL);
		}//ending if()
		
		else
		{
			execlp("cp","cp","/etc/passwd",".",NULL);
			exit(0);
		}//ending else
		
		exit(0);
	}//ending else
}//ending main ()
