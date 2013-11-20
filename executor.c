#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "err.h"
#include <string.h>
#include <stdbool.h>
#define BUF_SIZE                1024

char operatory[] = "*+-/";
int wyliczonaLiczba = 0;

int wykonajDzialanie(char a[], char b[], char operator[]){
	
	int i, j;
	i = atoi(a);
	j = atoi(b);
	fprintf(stderr, "%s %i %s %i\n", a, i, b, j);
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

int znajdzIndeksZnaku(int dlugoscPoprzedniego){
	char nic[] = "nic";
	char liczba1[2], liczba2[2], liczba3[2];
	strcpy(liczba1, nic);
	strcpy(liczba2, nic);
	strcpy(liczba3, nic);
	
	int i;
	bool warunekPetli = true;
	while (warunekPetli)
	{
		scanf("%s", liczba3);
		i = strcspn(liczba3, operatory);
	//	fprintf(stderr, "%s %i %i\n", liczba3, strlen(liczba3), i);
		if (i < strlen(liczba3) && strlen(liczba3) < 2){
			if (strcmp(liczba2, nic) == 0){
				strcpy(liczba1, nic);
			}
			else{
				//strcpy(liczba2, liczba3);
				warunekPetli = false;
			}
		}
		else{
			if (strcmp(liczba1, nic) == 0){
				strcpy(liczba1, liczba3);
	//			fprintf(stderr, "XD%s %s \n", liczba1,liczba3);
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
		
	}
	int j;
	//fprintf(stderr, "%s %s \n", liczba1,liczba2);
	
	i = atoi(liczba1);
	j = atoi(liczba2);
	//fprintf(stderr, "%s %i %s %i\n", liczba1, i, liczba2, j);
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
	
	long int pozycja = ftell(stdin);
	return pozycja - strlen(liczba1) - strlen(liczba2) - strlen(liczba3) - 3;
	
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
	int pozycja = znajdzIndeksZnaku(0);
	char slowo[10];
	int i = 0;
	rewind(stdin);
	while ( ftell(stdin) < pozycja){
		scanf("%s", slowo);
		fprintf(stderr,"%s ", slowo);
	}
	fprintf(stderr,"%i ", wyliczonaLiczba);
	scanf("%s", slowo);
	scanf("%s", slowo);
	scanf("%s", slowo);
	while(!feof(stdin)){
		scanf("%s", slowo);
		fprintf(stderr,"%s ", slowo);
	}
	return 0;
}
