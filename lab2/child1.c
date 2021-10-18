#include "unistd.h"
#include "stdio.h"
#include <string.h>
#include <ctype.h>

void toUpper(char* buffer) {
    for (int i = 0; i < strlen(buffer); i++)
    {
        buffer[i] = toupper(buffer[i]);
    }
    
}

int main() {
    char buffer[256];
    
        fgets(buffer, 256, stdin);
        toUpper(buffer);
        printf("%s", buffer);
        fflush(stdout);
    
    return 0;
}