#include <myfsapi.h>
#include <stdio.h>

MYFILE_HANDLE myopen(const char* filename, char* mode)
{
    // TODO: implement permission check

    HANDLE hFile;
    DWORD dwDesiredAccess;
    DWORD dwShareMode;
    DWORD dwCreationDisposition;

    if (strcmp(mode, "r") == 0) {
        dwDesiredAccess = GENERIC_READ;
        dwShareMode = FILE_SHARE_READ;
        dwCreationDisposition = OPEN_EXISTING;
    }
    else if (strcmp(mode, "w") == 0) {
        dwDesiredAccess = GENERIC_WRITE;
        dwShareMode = FILE_SHARE_WRITE;
        dwCreationDisposition = OPEN_ALWAYS;
    }
    else {
        return NULL;
    }

    hFile = CreateFile(filename, dwDesiredAccess, dwShareMode, NULL, dwCreationDisposition, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile == INVALID_HANDLE_VALUE) {
        FILE* log_file = fopen(myfs_logfile, "w");
        fprintf(log_file, "open failed\n");
        fclose(log_file);
        return NULL;
    }

    MYFILE_HANDLE file = (MYFILE_HANDLE)malloc(sizeof(MYFILE));
    file->hFile = hFile;

    if (strcmp(mode, "r") == 0) {
        file->mode = O_RDONLY;
    }
    else if (strcmp(mode, "w") == 0) {
        file->mode = O_WRONLY;
    }

    return file;
}
