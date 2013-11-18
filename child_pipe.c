#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "err.h"
#include <string.h>
#define BUF_SIZE                1024
int main (int argc, char *argv[])
{
  char a = 'a';
  int licznik = 0;
  while( a != '\n')
  {
    scanf("%c", &a);
    fprintf(stderr,"%c", a);
  }
  
}
