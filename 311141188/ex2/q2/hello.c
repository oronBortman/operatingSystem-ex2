#include "hello.h"

//-----------------------------------------------
void greet(char* name)
{
  printf("hello %s\n", name);
}
//-----------------------------------------------
void exit_msg(char* who, int count)
{
  fprintf(stderr, "pid=%d greeted %s %d times\n", getpid(), who, count);
  exit(count);
}
//-----------------------------------------------
int msleep(unsigned int tms) {
  return usleep(tms * 1000);
}
//------------------------------------------------
int main(int argc, char* argv[])
{
  if (argc != 4) 
    usage_err(argc);
  long howMuchTimesToGreet = strtol(argv[1], NULL, 10);
  char * name = argv[2];
  long timeToSleepBetweenGreets = strtol(argv[3], NULL, 10);
  for(int i = 0 ; i < howMuchTimesToGreet; i++)
  {
    greet(name);
    msleep(timeToSleepBetweenGreets);
  }
  exit_msg(name, howMuchTimesToGreet);

  exit(0);
}

//------------------------------------------------
void usage_err(int count)
{
  fprintf(stderr, "Expecting three arguments and got %d arguments\n", --count);
  fprintf(stderr, "The arguments should be:\n");
  fprintf(stderr, "1. How much times to greet\n");
  fprintf(stderr, "2. Name\n");
  fprintf(stderr, "3. How much time to sleep between greetings in mileseconds.\n");
  exit(1);
}





