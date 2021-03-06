#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "err.h"
#include <string.h>
#include <stdbool.h>
#define BUF_SIZE                1024

char operatory[] = "*+-/";
int wyliczonaLiczba = 0;
char bufor[BUF_SIZE];
int indeksZnaku = 0;
int indeksPierwszejLiczby = 0;

int wykonajDzialanie(char a[], char b[], char operator[]){
	
	long int i, j;
	i = atol(a);
	j = atol(b);
	fprintf(stderr,"%li %li\n", i, j);
	if (strcmp(operator, "*") == 0){
		return i*j;
	}
	if (strcmp(operator, "/") == 0){
		return i/j;
	}
	if (strcmp(operator, "+") == 0){
		return i+j;
	}
	return i-j;
	
}

void znajdzIndeksZnaku(int dlugoscPoprzedniego){
	char nic[] = "nic";
	char liczba1[2], liczba2[2], liczba3[2];
	strcpy(liczba1, nic);
	strcpy(liczba2, nic);
	strcpy(liczba3, nic);
	
	int i;
	bool warunekPetli = true;
	int indeks = 0;
	while (warunekPetli)
	{
		sscanf(bufor + indeks, "%s", liczba3);
		//printf("%s\n", liczba3);
		i = strcspn(liczba3, operatory);
		if (i < strlen(liczba3) && strlen(liczba3) < 2){
			if (strcmp(liczba2, nic) == 0){
				strcpy(liczba1, nic);
			}
			else{
				warunekPetli = false;
			}
		}
		else{
			if (strcmp(liczba1, nic) == 0){
				strcpy(liczba1, liczba3);
			}
			else if (strcmp(liczba2, nic) == 0){
				strcpy(liczba2, liczba3);
			}
			else{
				strcpy(liczba1, liczba2);
				strcpy(liczba2, liczba3);
			}
			warunekPetli = true;
		}
		indeks += 1 + strlen(liczba3);
		
	}
	int j;
	i = atoi(liczba1);
	j = atoi(liczba2);
	if (strcmp(liczba3, "*") == 0){
		wyliczonaLiczba = i*j;
	}
	else if (strcmp(liczba3, "/") == 0){
		wyliczonaLiczba = i/j;
	}
	else if (strcmp(liczba3, "+") == 0){
		wyliczonaLiczba = i+j;
	}
	else wyliczonaLiczba = i-j;
	
	indeksZnaku = indeks;
	indeksPierwszejLiczby = indeks - strlen(liczba1) - strlen(liczba2) - strlen(liczba3) - 3;
	
	
}

int main (int argc, char *argv[])
{	
	
	
	/*
	char a[10];
	while ( strcmp(a, "*") != 0){
	int licznik = 0;
	printf("Hi");
	
	scanf("%s", &a);
	printf("%s", a);
		
	}
	printf("*");
	*/
  /*
	int liczba = 1;
  
	char slowo[10];
		
		scanf("%s", slowo);
		printf("%s\n", slowo);
	*/
	
	fgets(bufor, sizeof(bufor), stdin);
	znajdzIndeksZnaku(0);
	int pozycja = 0;
	char slowo[10];
	int i = 0;
	char litera = 'a';
	while ( pozycja < indeksPierwszejLiczby){
		litera = bufor[pozycja];	
		printf("%c", litera);
		pozycja++;
	}
	//printf("%s", bufor + (-2));
	printf("%i", wyliczonaLiczba);
	if (strlen(bufor) - 1 > indeksZnaku)
		printf(" %s", bufor + indeksZnaku);
	printf("\n");
	/*scanf("%s", slowo);
	scanf("%s", slowo);
	scanf("%s", slowo);
	
	while(litera != '\n'){
		scanf("%c", &litera);
		if (litera == 'a'){
			litera = '\n';}
		else 
			printf("%c", litera);
	}
	*//*
	pid_t pid = getpid();
	fprintf(stderr, "%i", pid);
	return 0;*/
}
