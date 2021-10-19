#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int Spawning_Child_Processes (char *fname, int read, int write) {
    switch (fork())
    {
        case -1:
            return -1;
        case 0:
        {
            char *args[] = {NULL};
            dup2(read, 0);
            dup2(write, 1);
            execv(fname, args);
            return 0;
        } 
        default:
            break;
    }
    return 0;
}

int main() {

    int pipe1[2], pipe2[2], pipe3[2];

    if (pipe(pipe1) == -1)
        printf("Pipe1 error!");
    if (pipe(pipe2) == -1) 
        printf("Pipe2 error!");
    if (pipe(pipe3) == -1) 
        printf("Pipe3 error!");
    
    if (Spawning_Child_Processes("./child1", pipe1[0], pipe2[1])) {
        perror("fork error");
		return -1;
    }
    if (Spawning_Child_Processes("./child2", pipe2[0], pipe3[1])) {
        perror("fork error");
		return -1;
    }

    printf("Enter string:\n");
    char buffer[256];
	fgets(buffer, 256, stdin);
	write(pipe1[1], buffer, strlen(buffer));
	read(pipe3[0], buffer, 256);

	for(int i = 0; i < strlen(buffer); i++)
        if(buffer[i] != '\n')
            printf("%c", buffer[i]);
        else
            break;
    printf("\n");
	fflush(stdout);
    return 0;
}