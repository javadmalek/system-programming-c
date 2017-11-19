#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdbool.h> //for using bool type variables
#include<fcntl.h> //for using the system calls such as open(), close(), unlink(), read(), write()

void main (int argc, char *argv[])
{
	bool check_prime(int); 
	
	if (argc == 3)
	{
		struct stat statbuf;
		stat(argv[1], &statbuf);
		int filesize=statbuf.st_size;
			
		int fd1,fd2,check,i,input;
		bool result;
		char buf[filesize];
			
		
		fd1 = open(argv[1],O_RDONLY);
		fd2 = open(argv[2],O_RDWR|O_CREAT,S_IRWXU|S_IRWXG|S_IRWXO);
		
		do 
		{		
			i = 0;
				do 
				{
					check=read(fd1, buf+i, 1);
					i++;

				}//ending do while ()
				while(check != 0 && buf[i-1] != '\n');

			buf[i-1] = '\0';
			sscanf(buf, "%d", &input);
			
			result = check_prime(input);
			
			i=0;		
				if (result == 1)
				{
					do
					{
						write(fd2,buf+i,1);
						i++;
					}//ending do while ()
					while(buf[i] != '\0');
			
					write(fd2,"\n",1);

				}//ending if(result == 1)

		}//ending do while()
		while(check != 0);

		close(fd1);
		close(fd2);		
		
	}//ending if (argc == 3)
	else
		printf("\n !Entered Paramenters Are Not Correct! \n");
	


}//ending main (int)


bool check_prime(int input)
{
	bool flag = 0; 
	int remainder = 0, i;

	for(i=2; i<input; i++)
	{
		remainder = input % i;
		
		if(remainder == 0)
		{
			flag = 0;
			break;
		}//ending if(remainder ==0)
		else
		{	
			flag = 1;
			continue;
		}//ending else		
	}//ending for(int i=1;)
	
	return(flag);

}//ending check_prime()
