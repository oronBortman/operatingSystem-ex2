#pragma once

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <signal.h>

  char * prog_name = "hello";
// *****   declarations of types and constants   *****
char* out_msg = "Hello Standard Output\n";
char* err_msg = "Hello Standard Error\n";

// *****   declarations of function prototypes   *****

//-----------------------------------------------
void write_messages();
//-----------------------------------------------
int open_file(char* name);
//-----------------------------------------------
void usage_err(int count);
//-----------------------------------------------
void restore_fd(int temp_stdout);




