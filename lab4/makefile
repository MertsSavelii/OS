CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -g -pthread
SRC_PARENT = parent.c
PROG_PARENT = parent

build:
	$(CC) $(CFLAGS) $(SRC_PARENT) -o $(PROG_PARENT) && $(CC) $(CFLAGS) child1.c -o child1 && $(CC) $(CFLAGS) child2.c -o child2

clean:
	rm $(PROG_PARENT)
