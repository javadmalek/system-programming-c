#include <sys/types.h>  //wait() is defined in sys/types.h header file
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) 

{

  int pid;
 
  pid = fork(); //The fork returns a value to pid
		//The Value zero is returned to the child's PID
		//The Process ID of the child is returned to the Parent's PID

  if (pid==0)
  {
	  printf("\nCHILD HERE\n and i have finished my work!");
	  exit(0);
  }//ending if()
  else
  {
	  wait(); //The wait() function compells the parent to let it wait for the child to finish its process. 
		 //Sometimes it happens that a parent goes off before its child ends. in that particular situation such child process become a semaphore. 
		//In such situation the child process without a parent is given under the control of init process. 

	  printf("\nPARENT HERE\n I waited for the child to finish its process.\n");
  }//ending else
  
  return 0;
}//edning main ()
