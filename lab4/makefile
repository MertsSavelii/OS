CC = gcc
CFLAGS = -pedantic -pthread -lrt

build:
	$(CC) $(CFLAGS) parent.c -o parent && $(CC) $(CFLAGS) child1.c -o child1 && $(CC) $(CFLAGS) child2.c -o child2


clean:
	rm $(PROG_PARENT)

