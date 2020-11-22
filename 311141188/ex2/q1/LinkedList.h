#pragma once

#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include "ex2_q1_given.h"

struct LinkedList {
    struct Node* head;
    struct Node* tail;
};

int is_list_empty(struct LinkedList linkedList);
struct Node * create_node(struct polygon* polygonOfNewNode);
void add_data_to_linked_list(struct LinkedList * linkedList, struct polygon* polygonToAdd);
struct LinkedList create_empty_linked_list();
void free_list(struct LinkedList * linkedList);
char * get_string();
int get_num_of_points_by_polygon_type(enum POLY_TYPE polyType);
int get_num_of_numbers_to_read_by_polygon_type(enum POLY_TYPE polyType);
char* get_instruction_line(int* isFlagNOn, int* isFlagLOn, int* isFlagdOn, int* isFlagpOn, int* isFlagaOn, enum POLY_TYPE * polyType);
void free_polygon_pointer(struct polygon* poly);