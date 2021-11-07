#include <unistd.h>
#include "stdio.h"
#include <string.h>

int main() {
    char c;
    while ((c = getc(stdin)) != EOF) {
        printf("%c", c);
        if (c == ' ') {
            while ((c = getc(stdin)) == ' ')
                printf("\0");
            printf("%c", c);
        }
    }
    return 0;
}