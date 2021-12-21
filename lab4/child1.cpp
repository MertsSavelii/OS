#include <stdio.h>
#include "pipe_map.hpp"

char toUpper(char c) {
    if (c >= 'a' && c <= 'z')
        return c - ('a' - 'A');
    return c;
}

int main(int argc, char *argv[])
{
	pipe_map parent_child1;
	pipe_map child1_child2;

	if (pipe_map_connect("parent_child1", &parent_child1) ||
		pipe_map_connect("child1_child2", &child1_child2) )
	{
		printf("error: cannot connect to shared memory\n");
		return 1;
	}

	char c;
	pipe_map_read(parent_child1.buffer, &c, sizeof(char));
	while(c  != EOF)
	{
		toUpper(c);
		pipe_map_write(&c, child1_child2.buffer, sizeof(char));
		fflush(stdout);
		pipe_map_read(parent_child1.buffer, &c, sizeof(char));
	}
	return 0;
}
