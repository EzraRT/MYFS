#include <myfsconfig.h>

#include <myfsapi.h>

void mychdir(const char* path)
{
    if (!SetCurrentDirectory(path)) {
        printf("error: %s not exist\n", path);
        return;
    }

    myrefresh_pwd();
}
