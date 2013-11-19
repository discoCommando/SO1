#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "err.h"

char wiadomosc[] = "Hello from your parent!\n";

unsigned int iloscWykonawcow = 0;
void tworzPotomka(int deskryptorOdczytuOdOjca, int licznik, int deskryptorZapisuManagera)//zwraca deskryptor do odczytu z ostatniego pipe

{
	int pipeNast[2];
	/*
	Jestem ojcem. Zamieniam standardowe wejscie obecnego potomka na 
	deskryptorOdczytuOdOjca, na który ojciec wypisuje różne rzeczy
	*/
		
	if (close (0) == -1)            syserr("child, close (0)");
	if (dup (deskryptorOdczytuOdOjca) != 0)    syserr("child, dup (deskryptorOdczytuPotomka)");
	if (close (deskryptorOdczytuOdOjca) == -1) syserr("child, close (deskryptorOdczytuPotomka)])");

	if (licznik < iloscWykonawcow)
	{	
		
		switch(fork())
		{
			case -1:
				syserr("Error in fork, tworzpotomka\n");
			case 0:
				/*
				Jestem dzieckiem. Podmieniam sobie standartowe wyjscie na moj deskryptor do odczytu.
				Tworze pipe'a dla siebie i podmieniam swoje standardowe
				wejscie na wyjscie ojca.
				*/
				if (licznik == iloscWykonawcow - 1)
				{
					if (close (2) == -1)            syserr("child, close (0)");
					if (dup (deskryptorZapisuManagera) != 0)    syserr("child, du (pipe_nast[1])");
					if (close (deskryptorZapisuManagera) == -1) syserr("child, close (pipe_nast[1])])");
				}
				else if (licznik < iloscWykonawcow - 1) {
					if (pipe (pipeNast) == -1) syserr("Error in pipe\n");
					if (close (2) == -1)            syserr("child, close (0)");
					if (dup (pipeNast[1]) != 0)    syserr("child, dup (pipe_nast[1])");
					if (close (pipeNast[1]) == -1) syserr("child, close (pipe_nast[1])])");
					tworzPotomka(pipeNast[1], ++licznik, deskryptorZapisuManagera);
				}
				execl("executor", "./executor", (char *) 0);
				syserr ("child, execvp");
			
			}
	}
}

int main(int argc, char* argv[])
{
	/*
	if (argc != 4){
		fatal("NJEE\n");
	}
	*/
	int pierwszyPipe [2];
	iloscWykonawcow = atoi(argv[1]);
	
	int ostatniPipe [2];
	
	if (pipe (pierwszyPipe) == -1) syserr("Error in pipe\n");
	if (pipe (ostatniPipe) == -1) syserr("Error in pipe\n");
	
	if (close (ostatniPipe [1]) == -1) syserr("parent, close (pipe_dsc [0])");
 	
	
	
	switch (fork ())
	{
		case -1: 
			syserr("Error in fork\n");

		case 0:
			tworzPotomka(pierwszyPipe[0], 1, ostatniPipe[1]);
			execl("executor", "./executor", (char *) 0);
			syserr ("child, execvp");
			
		
	}
		
			
	
	if (close (pierwszyPipe [0]) == -1) syserr("parent, close (pipe_dsc [0])");
 	
	if (write (pierwszyPipe [1], wiadomosc, sizeof(wiadomosc) - 1) == -1)
 		syserr("write");

	if (close (pierwszyPipe [1]) == -1) syserr("parent, close (pipe_dsc [1])");

	int j = 0;
	for ( j = 0; j < iloscWykonawcow - 1; j++){
		if (wait (0) == -1) 
			syserr("wait");}
	
char wiadomosci[] = "aaaaaaaaaaaaaaaaaaaaaaa\n";
	if (read (ostatniPipe [0], wiadomosci, sizeof(wiadomosci) - 1) == -1)
		syserr("read");
	int i = 0;
	
	for (i = 0; i < sizeof(wiadomosci) && wiadomosci[i] != '\n'; i++)
	printf("%c", wiadomosci[i]);
     
	
	exit (0);
}