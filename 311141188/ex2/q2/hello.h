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
#include "ex2_q2.h"


// *****   declarations of types and constants   *****

// *****   declarations of function prototypes   *****

//-----------------------------------------------
void greet(char* name);
//-----------------------------------------------
void exit_msg(char* who, int count);
//-----------------------------------------------
int msleep(unsigned int tms);
//-----------------------------------------------
