#include "unistd.h"
#include "stdio.h"
#include <string.h>
#include <ctype.h>

void Double_space_to_Single (char* buffer){
    int j =1;
    int i;
    for(i=0;i<=strlen(buffer);i++)
        if((buffer[i]==' ') && (buffer[i+1]==' ') && (buffer[i+2]==' ') )
        {
            for(j=i;j<=strlen(buffer);j++)
                buffer[j]=buffer[j+3];
            i=i-3;
        }
}

int main() {
    char buffer[256];
    fgets(buffer, 256, stdin);
    Double_space_to_Single(buffer);
    printf("%s", buffer);
    fflush(stdout);
    return 0;
}