#include <unistd.h>
#include <stdio.h>

char toUpper(char c) {
    if (c >= 'a' && c <= 'z')
        return c - ('a' - 'A');
    return c;
}

int main() {
    char c;
    while ((c = getchar()) != EOF) {
        printf("%c", toUpper(c));
        fflush(stdout);
    }
    return 0;
}