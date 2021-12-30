#ifndef __MYFSDEF_H__
#define __MYFSDEF_H__

#include <myfsconfig.h>
#include <windows.h>

#define O_RDONLY    00
#define O_WRONLY    01
#define O_RDWR      02

typedef struct {
    HANDLE hFile;
    uint8_t mode;
}  MYFILE, * MYFILE_HANDLE;

#endif // __MYFSDEF_H__