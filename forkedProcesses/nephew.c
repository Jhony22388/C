#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main (int argc, char **argv)
{ 
  int waiting=atoi(argv[1]); 
  printf("This is %s\n", argv[0]);
  printf("my process id is %i\n", getpid());
  printf("Popeye\'s process id or my parent process id is %i\n", getppid());
  printf("I finished my race in %i seconds.\n",waiting);
  sleep(waiting);
  exit (0);
}
