#include <unistd.h>
#include "stdio.h"
#include <string.h>

int main() {
    while ((c = getc(stdin)) != EOF) {
        if(c == ' ')
            while ((s = getc(stdin)) == ' ' && (s != EOF || s != '\n'));
        printf("%c", c);
        if(s >= 'a' && s <= 'A')
            printf("%c", s);
        fflush(stdout);
    }
    return 0;
}