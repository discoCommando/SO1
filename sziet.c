#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "err.h"

char message[1024] = "hejka\n";

int main (int argc, char *argv[])
{
  int ostatniPipe [2];
  
  int pierwszyPipe [2];
  
  if (pipe (ostatniPipe) == -1) syserr("Error in pipe\n");
if (pipe (pierwszyPipe) == -1) syserr("Error in pipe\n");


{  int poprz [2];
	if (pipe (poprz) == -1) syserr("Error in pipe\n");
switch (fork ()) {
    case -1: 
      syserr("Error in fork\n");

    case 0:
	    
      
	if (close (1) == -1)            syserr("child, close (0)");
      if (dup(poprz[1]) == -1) syserr("sdas");
      if (close (poprz [0]) == -1) syserr("child, close (pipe_dsc [0])");
      if (close (poprz [1]) == -1) syserr("child, close (pipe_dsc [1])");
      
      if (close (0) == -1)            syserr("child, close (0)");
      if (dup (pierwszyPipe [0]) != 0)    syserr("child, dup (pipe_dsc [0])");
      if (close (pierwszyPipe [0]) == -1) syserr("child, close (pipe_dsc [0])");
      if (close (pierwszyPipe [1]) == -1) syserr("child, close (pipe_dsc [1])");
      if (argc >= 2) {
        /* argv + 1 is equivalent to argv array without its first element, *
	 * this element is the name of the program: "parent_dup"           */
	execvp (argv[1], argv + 1);
	syserr ("child, execvp");
      }
      exit (0);

  }
  switch (fork ()) {
    case -1: 
      syserr("Error in fork\n");

    case 0:
	    
      
	if (close (1) == -1)            syserr("child, close (0)");
      if (dup(ostatniPipe[1]) == -1) syserr("sdas");
      if (close (ostatniPipe [0]) == -1) syserr("child, close (pipe_dsc [0])");
      if (close (ostatniPipe [1]) == -1) syserr("child, close (pipe_dsc [1])");
      
      if (close (0) == -1)            syserr("child, close (0)");
      if (dup (poprz [0]) != 0)    syserr("child, dup (pipe_dsc [0])");
      if (close (poprz [0]) == -1) syserr("child, close (pipe_dsc [0])");
      if (close (poprz [1]) == -1) syserr("child, close (pipe_dsc [1])");
      if (argc >= 2) {
        /* argv + 1 is equivalent to argv array without its first element, *
	 * this element is the name of the program: "parent_dup"           */
	execvp (argv[1], argv + 1);
	syserr ("child, execvp");
      }
      exit (0);
  }
  }
	  
      //if (close (pipe_dsc [0]) == -1) syserr("parent, close (pipe_dsc [0])");

      if (close (pierwszyPipe [0]) == -1) syserr("parent, close (pipe_dsc [0])");
	
      if (write (pierwszyPipe [1], message, sizeof(message) - 3) == -1)
	syserr("write");

      if (close (pierwszyPipe [1]) == -1) syserr("parent, close (pipe_dsc [1])");

      
      
      if (wait (0) == -1) 
	syserr("wait");
      if (wait (0) == -1) 
	syserr("wait");
      if (close (ostatniPipe [1]) == -1) syserr("parent, close (pipe_dsc [1])");
	
      
      if (read (ostatniPipe [0], message, sizeof(message) - 1) == -1)
	syserr("read");
      int i = 0;
      for (i = 0; i < sizeof(message) && message[i] != '\n'; i++)
      printf("%c", message[i]);
     
  
    /* switch (fork ()) */
}
