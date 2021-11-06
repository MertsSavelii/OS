#include <stdio.h>
#include <unistd.h>

int main() {
    char c ;
    int clonein;
    dup2(clonein, 0);
    dup()
    close(0);
    c = getc(stdin);
    while (c != EOF) {
        printf("%c", c);
        c = getc(stdin);
    }
}