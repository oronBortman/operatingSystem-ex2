# Makefile for ex1-q1 winter 2020A
CFLAGS = -g -Wall
LDFLAGS = -lm # not really needed for this exercise
//CC = gcc -std=c99
ECHO = echo "going to compile for target $@"
PROG = ex2_q2

all: $(PROG) hello test

$(PROG): ex2_q2.o
	$(CC) $(CFLAGS) ex2_q2.o  -o $(PROG) $(LDFLAGS)

test:
	# make sure you have input file in.txt.
	# so the following command works
	./$(PROG) 5 300 ali beni gadi

ex2_q2.o:  ex2_q2.h ex2_q2.c
	$(CC) $(CFLAGS) -c ex2_q2.c $(LDFLAGS)

hello.o:  hello.h hello.c 
	$(CC) $(CFLAGS) -c hello.c $(LDFLAGS)

clean: 
	$(RM) *.o *~ $(PROG) *.log
