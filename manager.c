#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "err.h"

char wiadomosc[] = "2 7 + 3 -\n";

unsigned int iloscWykonawcow = 0;
void tworzPotomka(int deskryptorOdczytuOdOjca, int deskryptorZapisuSyna)//zwraca deskryptor do odczytu z ostatniego pipe

{
	/*
	Jestem ojcem. Zamieniam standardowe wejscie obecnego potomka na 
	deskryptorOdczytuOdOjca, na który ojciec wypisuje różne rzeczy
	*/
		
			if (close (0) == -1)            syserr("child, close (0)");
			if (dup2 (deskryptorOdczytuOdOjca, 0) != 0)    syserr("child, dupa (deskryptorOdczytuPotomka)");
			if (close (deskryptorOdczytuOdOjca) == -1) syserr("child, close (deskryptorOdczytuPotomka)])");
			if (close (1) == -1)            syserr("child, close (0)");
			if (dup2 (deskryptorZapisuSyna, 1) != 0)    syserr("child, dups (pipe_nast[1])");
			if (close (deskryptorZapisuSyna) == -1) syserr("child, close (pipe_nast[1])])");
	/*
		Jestem dzieckiem. Podmieniam sobie standartowe wyjscie na moj deskryptor do odczytu.
		Tworze pipe'a dla siebie i podmieniam swoje standardowe
		wejscie na wyjscie ojca.
		*/
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
	
 	
	int licznik = 0;
	int poprz[2];
	for(licznik = 0; licznik < iloscWykonawcow; licznik++){
		
		int pipeTemp[2];
		if (licznik < iloscWykonawcow - 1 ){
			if (pipe (pipeTemp) == -1) syserr("Error in pipe\n");
			
		}
		switch (fork ())
		{
			case -1: 
				syserr("Error in fork\n");

			case 0:
			{	
				if (licznik == 0){
					if (iloscWykonawcow == 1){
						pipeTemp[0] = ostatniPipe[0];
						pipeTemp[1] = ostatniPipe[1];
					}
					if (close (1) == -1)            syserr("child, close (0)");
					if (dup (pipeTemp[1]) == -1)    syserr("child, dups (pipe_nast[1])");
					if (close (pipeTemp[0]) == -1) syserr("child, close (pipe_nast[1])])");
					if (close (pipeTemp[1]) == -1) syserr("child, close (pipe_nast[1])])");
					if (close (0) == -1)            syserr("child, close (0)");
					if (dup (pierwszyPipe[0]) == -1)    syserr("child, dupa (deskryptorOdczytuPotomka)");
					if (close (pierwszyPipe[0]) == -1) syserr("child, close (deskryptorOdczytuPotomka)])");
					if (close (pierwszyPipe[1]) == -1) syserr("child, close (deskryptorOdczytuPotomka)])");
					
				}
//TDO DLA DWOCH
				else if (licznik == iloscWykonawcow - 1)
					{
					if (close (1) == -1)            syserr("child, close (0)");
					if (dup (ostatniPipe[1]) == -1)    syserr("child, dups (pipe_nast[1])");
					if (close (ostatniPipe[0]) == -1) syserr("child, close (pipe_nast[1])])");
					if (close (ostatniPipe[1]) == -1) syserr("child, close (pipe_nast[1])])");
					if (close (0) == -1)            syserr("child, close (0)");
					if (dup (poprz[0]) == -1)    syserr("child, dupa (deyptorOdczytuPotomka)");
					if (close (poprz[0]) == -1) syserr("child, close (skr])");
					if (close (poprz[1]) == -1) syserr("child, close (deskryptorOdczytuPotomka)])");
					
				}
				else
				{	if (close (1) == -1)            syserr("child, close (0)");
					if (dup (pipeTemp[1]) == -1)    syserr("child, dups (pipe_nast[1])");
					if (close (pipeTemp[0]) == -1) syserr("child, close (pipe_nast[1])])");
					if (close (pipeTemp[1]) == -1) syserr("child, close (pipe_nast[1])])");
					if (close (0) == -1)            syserr("child, close (0)");
					if (dup(poprz[0]) == -1)    syserr("child, dupa (de)");
					if (close (poprz[0]) == -1) syserr("child, close (deskryptorOdczytuPotomka)])");
					if (close (poprz[1]) == -1) syserr("child, close (deskryptorOdczytuPotomka)])");
					
				}
				
				//printf("hejkaaa %i\n", licznik);
				
				execl("./executor", "executor", (char *) 0);
				syserr ("child, execvp");
			}
		}
		
		poprz[0] = pipeTemp[0];
		poprz[1] = pipeTemp[1];
	
	}
			
	
	if (close (pierwszyPipe [0]) == -1) syserr("parent, close (pipe_dsc [0])");
 	
	if (write (pierwszyPipe [1], wiadomosc, sizeof(wiadomosc) - 1) == -1)
 		syserr("write");
	//if (write (pierwszyPipe [1], wiadomosc, sizeof(wiadomosc) - 1) == -1)
 	//	syserr("write");
	
	if (write (pierwszyPipe [1], "*", 1) == -1)
 		syserr("write");

	if (close (pierwszyPipe [1]) == -1) syserr("parent, close (pipe_dsc [1])");

	int j = 0;
	
	for ( j = 0; j < iloscWykonawcow; j	++){
		if (wait (0) == -1) 
			syserr("wait");}
	char wiadomosci[]= "aaaaaa";
	 if (close (ostatniPipe [1]) == -1) syserr("parent, close (pipe_dsc [1])");
	
	if (read (ostatniPipe [0], wiadomosc, sizeof(wiadomosc) - 1) == -1)
		syserr("read");
	
	int i = 0;
	
	for (i = 0; i < sizeof(wiadomosc) && wiadomosc[i] != '\n'; i++)
	printf("%c", wiadomosc[i]);
	
// 	if (read (ostatniPipe [0], wiadomosc, sizeof(wiadomosc) - 1) == -1)
// 		syserr("read");
// 	
// 	for (i = 0; i < sizeof(wiadomosc) && wiadomosc[i] != '\n'; i++)
// 	printf("%c", wiadomosc[i]);
//      
	
	
	
}