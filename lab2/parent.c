#include <stdio.h>
#include <unistd.h>

int Spawning_Child_Processes (char *fname, int read, int write) {
    switch (fork()) {
        case -1:
            return -1;
        case 0: //child
        {
            char *args[] = {NULL};
            if(dup2(read, 0) == -1)
                printf("dup2 error!");
            if(dup2(write, 1) == -1)
                printf("dup2 error!");
            if(execv(fname, args) == -1)
                printf("execv error!");
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
    char c;
    while ((c = getchar()) != EOF) {
        write(pipe1[1], &c, 1);
        read(pipe3[0], &c, 1);
        printf("%c", c);
        fflush(stdout);
    }
    return 0;
}