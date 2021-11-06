#include <unistd.h>
#include <stdio.h>
#include <string.h>

<<<<<<< Updated upstream
void toUpper(char* buffer) {
    for (int i = 0; i < strlen(buffer); i++)
        if(buffer[i] >= 'a' && buffer[i] <= 'z')
            buffer[i] = buffer[i] - 'a' + 'A';
    
}

int main() {
    char buffer[256];
    fgets(buffer, 256, stdin);
    toUpper(buffer);
    printf("%s", buffer);
    fflush(stdout);
=======
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
>>>>>>> Stashed changes
    return 0;
}