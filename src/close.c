#include <myfsconfig.h>

#include <myfsapi.h>

bool myclose(MYFILE_HANDLE file)
{
    CloseHandle(file->hFile);

    free(file);

    myrefresh_pwd();

    return true;
}
