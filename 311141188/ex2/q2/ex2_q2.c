#include "ex2_q2.h"

//------------------------------------------------
void write_messages()
{
  static int n = 1;
  char str[20];
  sprintf(str, "(%d pid=%d) ", n++, getpid());
  write(1, str, strlen(str));  
  write(1, out_msg, strlen(out_msg));
  write(2, str, strlen(str));  
  write(2, err_msg, strlen(err_msg));
}

//------------------------------------------------
int open_file(char* name)
{
  int fd;
  fd = open(name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
  if (fd < 0)  // open failed
  {
    fprintf(stderr, "ERROR: open \"%s\" failed (%d). Exiting\n", name, fd);
    exit(2);
  }
  //fprintf(stderr, "opened file %s, file descriptor is: %d\n",name, fd);
  return(fd);
}

//------------------------------------------------
int main(int argc, char* argv[])
{
  if (argc < 4) 
    usage_err(argc);
  //long howMuchTimesToGreet = strtol(argv[1], NULL, 10);
  //long timeToSleepBetweenGreets = strtol(argv[2], NULL, 10);
  int i = 3;
  int child_count=0;
  int temp_std_out;

  while(argv[i] != NULL)
  {
    temp_std_out = dup(1);
    char* my_argv[5];
    my_argv[0] = prog_name;
    my_argv[1] = argv[1];
    my_argv[2] = argv[i];
    my_argv[3] = argv[2];
    my_argv[4] = NULL;

    if (fork() == 0)
    {
      char logFileName[1000];
      strcpy(logFileName, my_argv[2]);
      strcat(logFileName,".log");
      close(1);
      open_file(logFileName);
      execve(prog_name, my_argv, NULL);
      fprintf(stderr, "*** ERROR: *** EXEC of %s FAILED\n", prog_name);
      exit(1);
    } 
    wait(NULL);
    restore_fd(temp_std_out);
    i++;
    child_count++;
  }
  fprintf(stderr, "program: %s - %d child processes terminated\n", argv[0], child_count);

  exit(0);
}

//------------------------------------------------

void restore_fd(int temp_stdout)
{
	close(1);
	dup(temp_stdout);
}
//------------------------------------------------
void usage_err(int count)
{
  fprintf(stderr, "Expecting three arguments and got %d arguments\n", --count);
  fprintf(stderr, "The arguments should be:\n");
  fprintf(stderr, "1. How much times to greet\n");
  fprintf(stderr, "2. How much time to sleep between greetings in mileseconds.\n");
  fprintf(stderr, "3. List of names\n");

  exit(1);
}

//*********************************
// use the following line of code in the main of ex2_q2.c:
// child_count is the number of child processes which it created.
/*
  fprintf(stderr, "program: %s - %d child processes terminated\n", 
          argv[0], child_count);
*/





