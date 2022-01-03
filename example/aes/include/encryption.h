//
// Created by Ezra on 8/11/2020.
//

#ifndef __ENCRYPTION__
#define __ENCRYPTION__

#include "aes_defs.h"

#include <sstream>
#include <string>

#include <myfsapi.h>

std::stringstream encryption(MYFILE_HANDLE file, std::string key);

#endif //__ENCRYPTION__