#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) 

{

  int pid;

  pid = fork(); //fork () returns value to pid
		//zero in case of child   OR
	       //Positive integer greater than zero incase if parent
	
  if (pid==0)
  {
	  printf("\nCHILD HERE\n");
		
  }//ending if()
  else
  {
	  printf("\nPARENT HERE\n");
		
  }//ending else
  
  return 0;

}//ending main ()
