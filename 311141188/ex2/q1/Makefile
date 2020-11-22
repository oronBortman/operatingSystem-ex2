# Makefile for ex2-q1 winter 2020A
CFLAGS = -g -Wall
LDFLAGS = -lm # not really needed for this exercise
#CC = gcc -std=c99
CC = gcc
ECHO = echo "going to compile for target $@"
PROG = ex2_q1

all: $(PROG) ex2_q1_helper test

$(PROG): ex2_q1.o LinkedList.o ex2_q1_given.o
	$(CC) $(CFLAGS) LinkedList.o ex2_q1.o -o $(PROG) $(LDFLAGS)

ex2_q1_helper:  ex2_q1_helper.o LinkedList.o ex2_q1_given.o
	$(CC) $(CFLAGS) LinkedList.o ex2_q1_helper.o ex2_q1_given.o -o ex2_q1_helper $(LDFLAGS)

test:
	# make sure you have input file in.txt.
	# so the following command works
	./$(PROG) < in.txt
	#./$(PROG)
ex2_q1.o:  ex2_q1.h ex2_q1.c
	$(CC) $(CFLAGS) -c ex2_q1.c $(LDFLAGS)

ex2_q1_given.o:  ex2_q1_given.h ex2_q1_given.c
	$(CC) $(CFLAGS) -c ex2_q1_given.c $(LDFLAGS)

ex2_q1_helper.o:  ex2_q1_helper.h ex2_q1_helper.c
	$(CC) $(CFLAGS) -c ex2_q1_helper.c $(LDFLAGS)

LinkedList.o:  LinkedList.h LinkedList.c 
	$(CC) $(CFLAGS) -c LinkedList.c $(LDFLAGS)

clean: 
	$(RM) *.o *~ $(PROG) *.tmp
