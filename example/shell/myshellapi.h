#ifndef __SHELLAPI_H__
#define __SHELLAPI_H__

#include <myfsapi.h>

void shell_cat(const char* filename);

void shell_ls();

void shell_ll(const char* filename);

void shell_cd(const char* path);

void shell_pwd();

#endif // __SHELLAPI_H__