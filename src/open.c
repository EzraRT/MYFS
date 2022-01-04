#include <myfsconfig.h>

#include <myfsapi.h>
#include <stdio.h>

MYFILE_HANDLE myopen(const char* filename, char* mode)
{
    // TODO: implement permission check

    HANDLE hFile;
    DWORD dwDesiredAccess;
    DWORD dwShareMode;
    DWORD dwCreationDisposition;

    MYFILE_ATTIBUTE attr;
    bool file_exist = false;

    memset(&attr, 0, sizeof(attr));
    mystat(filename, &attr);
    if (strlen(attr.name) == 0) {
        file_exist = false;
    } else {
        file_exist = true;
    }

    uint8_t privillege = grant_privilege(&attr);

    if (strcmp(mode, "r") == 0) {
        if (!file_exist)
            return NULL;
        if (privillege & MYFS_FREAD) {
            dwDesiredAccess = GENERIC_READ;
            dwShareMode = FILE_SHARE_READ;
            dwCreationDisposition = OPEN_EXISTING;
        } else {
            printf("error: no privillege to read %s\n", filename);
            return NULL;
        }
    } else if (strcmp(mode, "w") == 0) {
        if (!file_exist) {
            strcpy(attr.name, filename);
            attr.uid = uid;
            attr.gid = gid;
            attr.owner = MYFS_FREAD | MYFS_FWRITE;
            attr.group = MYFS_FREAD | MYFS_FWRITE;
            attr.other = MYFS_FREAD;

            dwDesiredAccess = GENERIC_WRITE;
            dwShareMode = FILE_SHARE_WRITE;
            dwCreationDisposition = CREATE_ALWAYS;
        } else if (privillege & MYFS_FWRITE) {
            dwDesiredAccess = GENERIC_WRITE;
            dwShareMode = FILE_SHARE_WRITE;
            dwCreationDisposition = CREATE_ALWAYS;
        } else {
            printf("error: no privillege to write %s\n", filename);
            return NULL;
        }
    } else {
        printf("error: invalid mode:%s\n", mode);
        return NULL;
    }

    hFile = CreateFile(filename, dwDesiredAccess, dwShareMode, NULL, dwCreationDisposition, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile == INVALID_HANDLE_VALUE) {
        return NULL;
    }

    if (!file_exist) {
        FILE* attr_file = fopen("attr.info", "a");
        fprintf(attr_file, "%s %d %d %d\n", filename, attr.uid, attr.gid, attr.owner * 100 + attr.group * 10 + attr.other);
    }

    MYFILE_HANDLE file = (MYFILE_HANDLE)malloc(sizeof(MYFILE));
    file->hFile = hFile;

    myrefresh_pwd();

    return file;
}
