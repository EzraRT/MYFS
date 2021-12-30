#ifndef __MYFSAPI_H__
#define __MYFSAPI_H__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <myfsconfig.h>
#include <myfsdef.h>

extern const char* myfs_logfile;

MYFS_EXPORT MYFILE_HANDLE myopen(const char* filename, char* mode);

MYFS_EXPORT bool myclose(MYFILE_HANDLE file);

MYFS_EXPORT size_t myread(MYFILE_HANDLE file, void* buffer, size_t size, size_t count);

MYFS_EXPORT size_t mywrite(MYFILE_HANDLE file, void* buffer, size_t size, size_t count);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __MYFSAPI_H__