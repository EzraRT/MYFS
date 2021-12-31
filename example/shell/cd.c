#include "myshellapi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void shell_cd(const char* path)
{
    mychdir(path);
}
