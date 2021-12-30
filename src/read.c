#include <myfsapi.h>

size_t myread(MYFILE_HANDLE file, void* buffer, size_t size, size_t count)
{
    DWORD dwRead;
    printf("read: %llu\n", size * count);
    if (!ReadFile(file->hFile, buffer, size * count, &dwRead, NULL)) {
        return 0;
    }
    return dwRead;
}
