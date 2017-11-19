#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>


void main(int argc, char *argv[])
{    
	if (argc == 3)
	{
		int fd1,fd2,LineRead,x;
		struct stat statbuf;
		
		stat(argv[1], &statbuf);
		x=statbuf.st_size;
		
		char buf[x];

		fd1 = open(argv[1], O_RDONLY);		
		fd2 = open(argv[2], O_CREAT | O_WRONLY, S_IRWXU|S_IRWXG|S_IRWXO);

		while ((LineRead = read(fd1, buf, x)) > 0) //it will read line by line so if no line is present numRead value will be less than 1
		{
			write(fd2, buf, LineRead);
		}//ending while()
	}//ending if()	
	
	else
	{
		printf("Number of parameters inserted is not correct\n");
	}//ending else
}//ending main ()
