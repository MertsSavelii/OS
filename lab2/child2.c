#include "unistd.h"
#include "stdio.h"
#include <string.h>
#include <ctype.h>

void Double_space_to_Single (char* buffer, char* dupl){
    int j = 1;
    dupl[0] = buffer[0];
    int i;
    for (i = 1; i<strlen(buffer) ; i++) {
        if (buffer[i] == ' ' && dupl[j-1] == ' ')
            continue;
        dupl[j] = buffer[i];
        j++;
    }
}

int main() {
    char buffer[256];
    char dupl[256];
    while (1) {
        fgets(buffer, 256, stdin);
        Double_space_to_Single(buffer, dupl);
        printf("%s", dupl);
        fflush(stdout);
    }
    return 0;
}