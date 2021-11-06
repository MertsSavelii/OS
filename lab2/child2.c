#include <unistd.h>
#include "stdio.h"
#include <string.h>

int main() {
<<<<<<< Updated upstream
    char buffer[256];
    fgets(buffer, 256, stdin);
    Double_space_to_Single(buffer);
    printf("%s", buffer);
    fflush(stdout);
=======
    char c,s;
    while ((c = getc(stdin)) != EOF) {
        if(c == ' ')
            while ((s = getc(stdin)) == ' ' && (s != EOF || s != '\n'));
        printf("%c", c);
        if(s >= 'a' && s <= 'A')
            printf("%c", s);
        fflush(stdout);
    }
>>>>>>> Stashed changes
    return 0;
}