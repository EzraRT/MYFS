#include "myshellapi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t get_pos_of_first_space(const char* str)
{
    size_t pos = 0;
    while (str[pos] != ' ' && str[pos] != '\0') {
        ++pos;
    }

    return pos;
}

size_t get_pos_of_first_last_space(const char* str)
{
    size_t pos = 0;
    while (str[pos] != ' ' && str[pos] != '\0') {
        ++pos;
    }
    while (str[pos] == ' ') {
        ++pos;
    }

    return pos;
}

size_t get_pos_of_first_not_space(const char* str)
{
    size_t pos = 0;
    while (str[pos] == ' ' && str[pos] != '\0') {
        ++pos;
    }

    return pos;
}

int main(int argc, char const* argv[])
{
    uid = 0;
    gid = 0;
    mychdir("fmlnb");
    // freopen("input.txt", "r", stdin);
    char command_buffer[1024], filename_buffer[1024];
    memset(command_buffer, 0, sizeof(command_buffer));
    memset(filename_buffer, 0, sizeof(filename_buffer));

    while (true) {
        memset(command_buffer, 0, sizeof(command_buffer));
        memset(filename_buffer, 0, sizeof(filename_buffer));
        printf("%s $ ", current_dir_buffer);
        gets(command_buffer);

        const char* cmd = command_buffer + get_pos_of_first_not_space(command_buffer);

        if (strcmp(cmd, "exit") == 0) {
            break;
        } else if (strncmp(cmd, "cat ", 4) == 0) {
            size_t pos = get_pos_of_first_last_space(cmd);
            const char* filename = cmd + pos;
            shell_cat(filename);
        } else if (strncmp(cmd, "ls ", 3) == 0 || strncmp(cmd, "ls", 3) == 0) {
            size_t pos = get_pos_of_first_last_space(cmd);
            const char* pathname = cmd + pos;
            shell_ls(pathname);
        } else if (strncmp(cmd, "ll ", 3) == 0 || strncmp(cmd, "ll", 3) == 0) {
            size_t pos = get_pos_of_first_last_space(command_buffer);
            const char* pathname = cmd + pos;
            shell_ll(pathname);
        } else if (strncmp(cmd, "cd ", 3) == 0) {
            size_t pos = get_pos_of_first_last_space(cmd);
            shell_cd(cmd + pos);
        } else if (strncmp(cmd, "pwd", 4) == 0) {
            shell_pwd();
        } else if (strncmp(cmd, "mkdir ", 6) == 0) {
            size_t pos = get_pos_of_first_last_space(cmd);
            const char* pathname = cmd + pos;
            mymkdir(pathname);
        } else if (strlen(cmd) == 0) {
            continue;
        } else {
            int pos = get_pos_of_first_space(cmd);
            strncpy(filename_buffer, cmd, pos);
            MYFILE_ATTIBUTE attr;
            memset(&attr, 0, sizeof(attr));
            mystat(filename_buffer, &attr);
            if (strlen(attr.name) == 0 || attr.is_dir) {
                printf("error: no such file named %s\n", filename_buffer);
                continue;
            }
            myexec(&attr, cmd + get_pos_of_first_last_space(cmd));
        }
    }

    printf("bye");
    return 0;
}
