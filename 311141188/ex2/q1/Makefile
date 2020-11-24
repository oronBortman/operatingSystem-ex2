# Makefile for ex2-q1 winter 2020A
CFLAGS = -g -Wall
LDFLAGS = -lm # not really needed for this exercise
#CC = gcc -std=c99
CC = gcc
ECHO = echo "going to compile for target $@"
PROG1 = ex2_q1
PROG2 = ex2_q1_helper
PROGS = $(PROG1) $(PROG2)

all: $(PROGS) test

$(PROG1): ex2_q1.o common_functions.o ex2_q1_given.o
	$(CC) $(CFLAGS) common_functions.o ex2_q1.o -o $(PROG1) $(LDFLAGS)

$(PROG2):  ex2_q1_helper.o common_functions.o ex2_q1_given.o
	$(CC) $(CFLAGS) common_functions.o ex2_q1_helper.o ex2_q1_given.o -o $(PROG2) $(LDFLAGS)

test: $(PROGS)
	# make sure you have input file in.txt.
	# so the following command works
	./$(PROG1) < in.txt

ex2_q1.o:  ex2_q1.h ex2_q1.c
	$(CC) $(CFLAGS) -c ex2_q1.c $(LDFLAGS)

ex2_q1_given.o:  ex2_q1_given.h ex2_q1_given.c
	$(CC) $(CFLAGS) -c ex2_q1_given.c $(LDFLAGS)

ex2_q1_helper.o:  ex2_q1_helper.h ex2_q1_helper.c
	$(CC) $(CFLAGS) -c ex2_q1_helper.c $(LDFLAGS)

common_functions.o:  common_functions.h common_functions.c 
	$(CC) $(CFLAGS) -c common_functions.c $(LDFLAGS)

clean: 
	$(RM) *.o *~ $(PROGS) *.tmp
