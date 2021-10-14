#include "unistd.h"
#include "stdio.h"
#include <string.h>

void toLower(char* buffer) {
    for (int i = 0; i < strlen(buffer); i++) {
        if(buffer[i] >= 'a' && buffer[i] <= 'z')
            buffer[i] = buffer[i] - 'a' + 'A';
    }
}

int main() {
    char buffer[256];
    while (1) {
        fgets(buffer, 256, stdin);
        toLower(buffer);
        printf("%s", buffer);
        fflush(stdout);
    }
    return 0;
}