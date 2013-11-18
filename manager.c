#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "err.h"

unsigned int licznik = 0;
unsigned int iloscWykonawcow = 0;
void tworzPotomka(int deskryptorOdczytuPotomka)
{
	if (licznik < iloscWykonawcow)
	{
		int pipe_nast[2];
		if (close (0) == -1)            syserr("child, close (0)");
		if (dup (deskryptorOdczytuPotomka) != 0)    syserr("child, dup (deskryptorOdczytuPotomka)");
		if (close (deskryptorOdczytuPotomka) == -1) syserr("child, close (deskryptorOdczytuPotomka)])");
		
		if (pipe (pipe_nast) == -1) syserr("Error in pipe\n");
		
		
		if (close (1) == -1)            syserr("child, close (0)");
		if (dup (pipe_nast[1]) != 0)    syserr("child, dup (pipe_nast[1])");
		if (close (pipe_nast[1]) == -1) syserr("child, close (pipe_nast[1])])");
	
		++licznik;
		tworzPotomka(pipe_nast[1]);
	}
}

int main(int argc, char* argv[])
{
	
	if (argc != 4){
		fatal("NJEE\n");
	}
	
	int pipe_dsc [2];
	iloscWykonawcow = atoi(argv[1]);
	
	if (pipe (pipe_dsc) == -1) syserr("Error in pipe\n");
	
	int licznik = 0;
	for(licznik = 0; licznik < iloscWykonawcow; licznik++){
		switch (fork ())
		{
			case -1: 
				syserr("Error in fork\n");

			case 0:
				if (close (0) == -1)            syserr("child, close (0)");
				if (dup (pipe_dsc [0]) != 0)    syserr("child, dup (pipe_dsc [0])");
				if (close (pipe_dsc [0]) == -1) syserr("child, close (pipe_dsc [0])");
				if (close (pipe_dsc [1]) == -1) syserr("child, close (pipe_dsc [1])");
				
				execl("executor", "./executor", (char *) 0);
				syserr ("child, execvp");
				
			
		}
		
			
	}
	
	if (close (pipe_dsc [0]) == -1) syserr("parent, close (pipe_dsc [0])");
// 	if (write (pipe_dsc [1], message, sizeof(message) - 1) == -1)
// 		syserr("write");

	if (close (pipe_dsc [1]) == -1) syserr("parent, close (pipe_dsc [1])");

	if (wait (0) == -1) 
		syserr("wait");
	exit (0);
}