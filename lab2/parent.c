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

    if (pipe(pipe1) == -1) 
        printf("Pipe1 error!");
    if (pipe(pipe2) == -1) 
        printf("Pipe2 error!");
    if (pipe(pipe3) == -1) 
        printf("Pipe3 error!");
    
    /*if (Spawning_Child_Processes("./child1", pipe1[0], pipe2[1])) {
        perror("fork error");
		return -1;
    }*/
    if (Spawning_Child_Processes("./child2", pipe2[0], pipe3[1])) {
        perror("fork error");
		return -1;
    }

    printf("Enter string:\n");
    char in, out;
    while ((in = getc(stdin)) != EOF) {
        write(pipe2[1], &in, 1);
        read(pipe3[0], &out, 1);
        if (out != "\0")
            printf("%c", out);
        fflush(stdout);
    }
    return 0;
}