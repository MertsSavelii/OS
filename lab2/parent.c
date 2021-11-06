#include <stdio.h>
#include <unistd.h>
//#include <fcntl.h>
//#include <string.h>

int Spawning_Child_Processes (char *fname, int read, int write) {
    switch (fork())
    {
        case -1:
            return -1;
        case 0: //child
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

<<<<<<< Updated upstream
    int pipe1[2], pipe2[2], pipe3[2];

    if (pipe(pipe1) == -1)
=======
    if (pipe(pipe1) == -1) 
>>>>>>> Stashed changes
        printf("Pipe1 error!");
    if (pipe(pipe2) == -1) 
        printf("Pipe2 error!");
    if (pipe(pipe3) == -1) 
        printf("Pipe3 error!");
    
    if (Spawning_Child_Processes("./child1", pipe1[0], pipe2[1])) {
        perror("fork error");
		return -1;
    }
    /*if (Spawning_Child_Processes("./child2", pipe2[0], pipe3[1])) {
        perror("fork error");
		return -1;
    }*/

    printf("Enter string:\n");
<<<<<<< Updated upstream
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
=======
    char c;
    while ((c = getc(stdin)) != EOF) {
        write(pipe1[1], &c, 1);
        read(pipe2[0], &c, 1);
        printf("%c", c);
        fflush(stdout);
    }
>>>>>>> Stashed changes
    return 0;
}