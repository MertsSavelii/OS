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

	if (pipe_map_create("parent_child1.txt", &parent_child1) == -1 ||
		pipe_map_create("child1_child2.txt", &child1_child2) == -1 ||
		pipe_map_create("child2_parent.txt", &child2_parent) == -1 )
	{
		printf("error: cannot create shared memory\n");
		return 1;
	}

	if (Spawning_Child_Processes("./child1") == -1 ||
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

	pipe_destroy(&parent_child1);
	pipe_destroy(&child1_child2);
	pipe_destroy(&child2_parent);
	//remove("parent_child1.txt");
	remove("child1_child2.txt");
	remove("child2_parent.txt");
	return 0;
}
