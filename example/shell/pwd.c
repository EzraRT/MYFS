#include "myshellapi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void shell_pwd()
{
    myrefresh_pwd();
    printf("%s\n", current_dir_buffer);
}
