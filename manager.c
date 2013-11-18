#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "err.h"

int main(int argc, char* argv[])
{
	
	if (argc != 4){
		fatal("NJEE\n");
	}
	
	int pipe_dsc [2];
	int iloscWykonawcow = atoi(argv[1]);
	
	if (pipe (pipe_dsc) == -1) syserr("Error in pipe\n");
	
	
	for(int licznik = 0; licznik < iloscWykonawcow; licznik++){
		switch (fork ())
		{
			case -1: 
				syserr("Error in fork\n");

			case 0:
				if (close (0) == -1)            syserr("child, close (0)");
				if (dup (pipe_dsc [0]) != 0)    syserr("child, dup (pipe_dsc [0])");
				if (close (pipe_dsc [0]) == -1) syserr("child, close (pipe_dsc [0])");
				if (close (pipe_dsc [1]) == -1) syserr("child, close (pipe_dsc [1])");
				
				execl("./executor", "executor", (char *) 0);
				syserr ("child, execvp");
				
			
		}
		
			
	}
	
	if (close (pipe_dsc [0]) == -1) syserr("parent, close (pipe_dsc [0])");
	if (write (pipe_dsc [1], message, sizeof(message) - 1) == -1)
		syserr("write");

	if (close (pipe_dsc [1]) == -1) syserr("parent, close (pipe_dsc [1])");

	if (wait (0) == -1) 
		syserr("wait");
	exit (0);
}