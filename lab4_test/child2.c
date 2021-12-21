#include <stdio.h>
#include "pipe_map.hpp"

void PrintChar(char c, pipe_map child2_parent) {
    pipe_map_write(&c, child2_parent.buffer, sizeof(char));
    fflush(stdout);
}


int main(int argc, char *argv[])
{
	pipe_map child1_child2;
	pipe_map child2_parent;

	if (pipe_map_connect("child1_child2", &child1_child2) ||
		pipe_map_connect("child2_parent", &child2_parent) )
	{
		printf("error: cannot connect to shared memory\n");
		return 1;
	}
	
	char c;
	pipe_map_read(child1_child2.buffer, &c, sizeof(char));
    while (c != EOF) {
        PrintChar(c, child2_parent);
        if (c == ' ') {
			pipe_map_read(child1_child2.buffer, &c, sizeof(char));
            while (c == ' ')
                PrintChar(0, child2_parent);
            PrintChar(c, child2_parent);
        }
		pipe_map_read(child1_child2.buffer, &c, sizeof(char));
    }
	return 0;
}
