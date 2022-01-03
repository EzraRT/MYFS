//
// Created by Ezra on 8/11/2020.
//

#include "decryption.h"
#include "encryption.h"
#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

string get_output_filename(string input_filename, bool is_decryption)
{
    if (is_decryption) {
        return input_filename + ".decrypted";
    }
    string result;
    auto pos = input_filename.rfind('.');
    if (pos == input_filename.npos) {
        //文件名无后缀
        result = input_filename.append(".bin");
    } else {
        result = input_filename.substr(0, pos).append(".bin");
    }
    return result;
}

void print_usage()
{
    cout << "usage :" << endl;
    cout << "aes-tool ${filename} [-p ${password}] [-d (if wanna decryption a file)]" << endl;
    cout << "[note] The default password is 12345678" << endl;
}

int main(int argc, char const* argv[])
{
    uid = 0;
    gid = 0;
    mypwd();
    char key_default[] = "12345678";
    char* key = key_default;
    bool is_decryption = false;

    if (argc < 2) {
        cerr << "Error, no input file." << endl;
        print_usage();
        return -1;
    }

    string file_name(argv[1]);
    // string file_name = "test.txt";
    MYFILE_HANDLE file = myopen(file_name.c_str(), "r");

    if (!file) {
        cerr << '\'' << file_name << "\' open failed." << endl;
        return -1;
    }

    if (argc >= 4) {
        // 指定了密码
        char* key_temp = key_default;
        if (!strcmp(argv[2], "-p")) {
            key_temp = (char*)calloc(strlen(argv[3]) + 1, sizeof(char));
            strcpy(key_temp, argv[3]);
        }
        key = key_temp;
    }

    cout << "use password as " << key << endl;

    if (argc <= 3) {
        if (!strncmp(argv[2], "-d", 3)) {
            is_decryption = true;
        }
    } else if (argc >= 5) {
        if (!strncmp(argv[4], "-d", 3)) {
            is_decryption = true;
        }
    }

    stringstream stream;
    if (is_decryption) {
        stream = decryption(file, key);
    } else {
        stream = encryption(file, key);
    }
    myclose(file);

    string output_filename = get_output_filename(file_name, is_decryption);
    MYFILE_HANDLE output = myopen(output_filename.c_str(), "w");
    if (!output) {
        cerr << '\'' << output_filename << "\' open failed." << endl;
        return -1;
    }
    char buf[1024];

    size_t length = stream.tellp();

    memset(buf, 0, sizeof(buf));
    do {
        stream.read(buf, 1024);
        mywrite(output, buf, sizeof(char), min(length, 1024));
        memset(buf, 0, sizeof(buf));
    } while (((long long)length - 1024ll > 0ll));

    myclose(output);

    if (key != key_default)
        free(key);

    cout << "Success! The result has been stored in " << output_filename << endl;
    return 0;
}
