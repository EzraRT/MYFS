#include <myfsapi.h>

bool myclose(MYFILE_HANDLE file)
{
    CloseHandle(file->hFile);

    free(file);

    return true;
}
