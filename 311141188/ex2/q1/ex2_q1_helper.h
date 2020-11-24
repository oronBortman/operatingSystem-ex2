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

// *****   declarations of function prototypes   *****
void my_exception(int line, const char* function, char* msg);
struct polygon * copy_polygon(struct polygon polygonOfNewNode);

// *****   declarations of input prototypes   *****
void get_verticles(enum POLY_TYPE polyType, struct point * vertices);
int get_coordinate_from_number(unsigned long long number);
struct LinkedList read_polygons_and_add_to_list();

// *****   declarations of print prototypes   *****
void print_poloygon(struct polygon polygonToPrint);
void print_polygon_points(size_t sizeOfVerticlesArr, struct point * verticles);
void print_point(struct point pt);
void print_polygon_list();

// *****   declarations of signal prototypes   *****
void SIGUSR1_handler(int sig_num);
void SIGUSR2_handler(int sig_num);
void set_sig_handlers();


