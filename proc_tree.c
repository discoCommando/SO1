#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "err.h"

char message[1024] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n";

int main (int argc, char *argv[])
{
  int pipe_dsc [2];
  
  int pipe_dsc2 [2];
  if (pipe (pipe_dsc) == -1) syserr("Error in pipe\n");
if (pipe (pipe_dsc2) == -1) syserr("Error in pipe\n");

  

  switch (fork ()) {
    case -1: 
      syserr("Error in fork\n");

    case 0:
	    
      
	if (close (2) == -1)            syserr("child, close (0)");
      if (dup(pipe_dsc[1]) == -1) syserr("sdas");
      if (close (pipe_dsc [0]) == -1) syserr("child, close (pipe_dsc [0])");
      //if (close (pipe_dsc [1]) == -1) syserr("child, close (pipe_dsc [1])");
      
      if (close (0) == -1)            syserr("child, close (0)");
      if (dup (pipe_dsc2 [0]) != 0)    syserr("child, dup (pipe_dsc [0])");
      if (close (pipe_dsc2 [0]) == -1) syserr("child, close (pipe_dsc [0])");
      if (close (pipe_dsc2 [1]) == -1) syserr("child, close (pipe_dsc [1])");
      if (argc >= 2) {
        /* argv + 1 is equivalent to argv array without its first element, *
	 * this element is the name of the program: "parent_dup"           */
	execvp (argv[1], argv + 1);
	syserr ("child, execvp");
      }
      exit (0);

    default:
	  
      //if (close (pipe_dsc [0]) == -1) syserr("parent, close (pipe_dsc [0])");

      if (close (pipe_dsc2 [0]) == -1) syserr("parent, close (pipe_dsc [0])");
	
      if (write (pipe_dsc2 [1], message, sizeof(message) - 1) == -1)
	syserr("write");

      if (close (pipe_dsc2 [1]) == -1) syserr("parent, close (pipe_dsc [1])");

      
      
      if (wait (0) == -1) 
	syserr("wait");
      if (close (pipe_dsc [1]) == -1) syserr("parent, close (pipe_dsc [1])");
	
      
      if (read (pipe_dsc [0], message, sizeof(message) - 1) == -1)
	syserr("read");
      int i = 0;
      for (i = 0; i < sizeof(message) && message[i] != '\n'; i++)
      printf("%c", message[i]);
     
  
      exit (0);
  } /* switch (fork ()) */
}
