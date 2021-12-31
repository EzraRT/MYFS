#include "myshellapi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void shell_cat(const char* filename)
{
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    MYFILE_HANDLE file = myopen(filename, "r");

    if (file == NULL) {
        printf("open failed\n");
        return;
    }

    while (myread(file, buffer, sizeof(char), 1024) != 0) {
        printf("%s", buffer);
        memset(buffer, 0, sizeof(buffer));
    }

    myclose(file);
    printf("\n");
}
