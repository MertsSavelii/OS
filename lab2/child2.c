#include <unistd.h>
#include <stdio.h>

void PrintChar(char x) {
    printf("%c", x);
    fflush(stdout);
}

int main() {
    char c;
    while ((c = getchar()) != EOF) {
        PrintChar(c);
        if (c == ' ') {
            while ((c = getchar()) == ' ')
                PrintChar(0);
            PrintChar(c);
        }
    }
    return 0;
}