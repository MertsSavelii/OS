#include <stdio.h>
#include "pipe_map.h"

int Spawning_Child_Processes (char *fname) {
    switch (fork()) {
        case -1:
            return -1;
        case 0:
        {
            char *args[] = {NULL};
            if(execv(fname, args) == -1)
                printf("execv error!");
            return 0;
        } 
        default:
            break;
    }
    return 0;
}

int main()
{
	pipe_map parent_child1;
	pipe_map child1_child2;
	pipe_map child2_parent;

	if (pipe_map_create("parent_child1", &parent_child1) == -1 ||
		pipe_map_create("child1_child2", &child1_child2) == -1 ||
		pipe_map_create("child2_parent", &child2_parent) == -1 )
	{
		printf("error: cannot create shared memory\n");
		return 1;
	}

	if (Spawning_Child_Processes("./child1") == -1 |
		Spawning_Child_Processes("./child2") == -1 )
	{
		perror("fork error");
		return -1;
	}

	printf("Enter string:\n");
	char c;
	while ((c = getchar()) != EOF) {
		pipe_map_write(&c, parent_child1.buffer, sizeof(char));
		pipe_map_read(child2_parent.buffer, &c, sizeof(char));
		printf("%c ", c);
		fflush(stdout);
	}
	return 0;
}
