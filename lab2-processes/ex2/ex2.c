#include<stdio.h>
#include<dirent.h> 
//The <dirent.h> header defines the DIR data type through typedef
//DIR is a type representing a directory stream.
//It also defines the structure dirent

void main(int argc, char *argv[])
{
	if (argc == 2)
	{
		DIR *directory;
		struct dirent *dir;
		
		directory = opendir(argv[1]);
			
		while (dir = readdir(directory))
		{
			printf("%s\n",dir->d_name);
		}//ending while()
	}//ending if()	
	
	else
	{
		printf("\n Incorrect Parameters, write the absolute path! \n");
	}//ending else

}//ending main ()
