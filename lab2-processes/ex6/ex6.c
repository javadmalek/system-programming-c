#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>



int main(void)
{
  	int fda[2],x,i;
	int mydup2(int,int);	  
  	pipe(fda);
  
	switch (fork()) 
	{
		case -1:
			printf("Fork Failed\n");
		break;
    
		case 0:                
			i=mydup2(fda[1],1); 
			printf("I am child, Return of mydup2 %d\n",i);
			close(fda[1]);
			close(fda[0]);  
			execlp("ls","ls",(char *)0);
		break;
	  
		default:
			i=mydup2(fda[0],0);
			printf("I am parent, Return of mydup2 %d\n",i);
			close(fda[0]);
			close(fda[1]);
			execlp("wc","wc","-w",(char *)0);
			wait();
		break;
	}//ending switch() 
	return 0;
}//ending main()

int mydup2(int fda, int for_closing)
{
	int i, r;

	close(for_closing);
	
	int x[100],j=0;
	
	while((x[j]=dup(fda)) != for_closing && j < 100) 
	{
			j++;
	}//ending while()
	
	for(r=0;r<=j-1;r++)
	{
		close(x[r]);		
	}//ending for()

	return x[j];	
}//ending mydup2()
