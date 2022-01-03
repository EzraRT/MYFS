//
// Created by Ezra on 8/11/2020.
//

#ifndef __DECRYPTION__
#define __DECRYPTION__

#include "aes_defs.h"

#include <sstream>
#include <string>

#include <myfsapi.h>

std::stringstream decryption(MYFILE_HANDLE file, std::string key);

#endif //__DECRYPTION__