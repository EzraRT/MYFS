#include <myfsconfig.h>

#include <myfsapi.h>

size_t mywrite(MYFILE_HANDLE file, void* buffer, size_t size, size_t count)
{
    DWORD dwWritten;
    printf("%llu\n", size * count);
    if (!WriteFile(file->hFile, buffer, size * count, &dwWritten, NULL)) {
        return 0;
    }

    return dwWritten;
}
