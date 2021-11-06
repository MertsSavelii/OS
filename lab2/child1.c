#include <unistd.h>
#include <stdio.h>
#include <string.h>

char toUpper(char c) {
    if (c >= 'a' && c <= 'z')
        return c - ('a' - 'A');
    return c;
}

int main() {
    char c;
    while ((c = fgetc(stdin)) != EOF) {
        printf("%c", toUpper(c));
        fflush(stdout);
    }
    return 0;
}