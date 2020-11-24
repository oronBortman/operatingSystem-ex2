#pragma once

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <math.h>
#include "common_functions.h"

// *****   declarations of types and constants   *****

#define llu unsigned long long
#define TRUE 1
#define FALSE 0
#define  emptyLine "L\n"

// *****   declarations of function prototypes   *****
void sleep_for_nano();

// *****   declarations of input functions prototypes   *****
struct point * get_verticles(enum POLY_TYPE polyType);

// *****   declarations of print functions prototypes   *****
void write_empty_line(int fileToWrite);

// *****   declarations of file functions prototypes   *****
int open_file(char* name);
void get_verticles_and_write_to_file(enum POLY_TYPE polyType, int fileToWriteTo);
void write_empty_lines_to_files(enum POLY_TYPE polyType, int quadIn, int hexIn, int octIn, int isFlagNOn);
int get_file_to_write_by_type(enum POLY_TYPE polyType, int quadIn, int hexIn, int octIn);
void write_instruction_to_file(int fileToWrite, char* instructionLine, int intructionLineSize);
void setFilesToIgnore(enum POLY_TYPE polyType, int * firstFileToIgnore, int * secondFileToIgnore, int quadIn, int hexIn, int octIn);
void get_input_and_write_to_files(int quadIn, int hexIn, int octIn);
int open_file_by_polygon_type(enum POLY_TYPE polyType);
void open_all_files(int* quadIn, int* hexIn, int* octIn);
void close_all_files(int quadIn, int hexIn, int octIn);

// *****   declarations of signal functions prototypes   *****
void set_sig_handlers();
void sending_signal_SIGUSR1_to_process(int i, int* pids);
void handle_char_signals(int * pids);
void send_SIGUSR2_to_all_processes(int* pids);
void wait_to_all_processes(int* pids);
void call_to_all_helpers(int * pids);
void call_to_certian_helper(char* prog_name, enum POLY_TYPE polyType);
