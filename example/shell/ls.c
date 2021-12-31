#include "myshellapi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void shell_ls()
{
    mychdir(".");
    link_node* node = current_dir_attribute_head;
    while (node) {
        MYFILE_ATTIBUTE* attr = (MYFILE_ATTIBUTE*)node->data;
        printf("%s  ", attr->name);
        node = node->next;
    }

    printf("\n");
}

void shell_ll(const char* path)
{
    mychdir(".");
    size_t max_size = 1, max_strlen = 1;

    link_node* node = current_dir_attribute_head;

    MYFILE_ATTIBUTE* attr;

    while (node) {
        attr = (MYFILE_ATTIBUTE*)(node->data);
        if (attr->size > max_size) {
            max_size = attr->size;
        }
        if (strlen(attr->name) > max_strlen) {
            max_strlen = strlen(attr->name);
        }

        node = node->next;
    }
    char line[128];

    node = current_dir_attribute_head;

    int max_size_len;
    for (max_size_len = 1; max_size_len < 21; max_size_len++) {
        if (max_size / 10 == 0) {
            break;
        }
        max_size /= 10;
    }

    char format[80] = "%2llu  %2llu  %";
    sprintf(format + strlen(format), "%d", max_size_len);
    sprintf(format + strlen(format), "llu  %s %s", "%s", "%s");

    while (node) {
        MYFILE_ATTIBUTE* attr = (MYFILE_ATTIBUTE*)(node->data);
        line[0] = attr->is_dir ? 'd' : '-';
        line[1] = attr->owner & MYFS_FREAD ? 'r' : '-';
        line[2] = attr->owner & MYFS_FWRITE ? 'w' : '-';
        line[3] = attr->owner & MYFS_FEXEC ? 'x' : '-';
        line[4] = attr->group & MYFS_FREAD ? 'r' : '-';
        line[5] = attr->group & MYFS_FWRITE ? 'w' : '-';
        line[6] = attr->group & MYFS_FEXEC ? 'x' : '-';
        line[7] = attr->other & MYFS_FREAD ? 'r' : '-';
        line[8] = attr->other & MYFS_FWRITE ? 'w' : '-';
        line[9] = attr->other & MYFS_FEXEC ? 'x' : '-';
        line[10] = ' ';
        line[11] = ' ';

        char time_str[20];
        memset(time_str, 0, sizeof(time_str));

        SYSTEMTIME Info = attr->last_write;
        memcpy(&Info, &(attr->last_write), sizeof(SYSTEMTIME));

        sprintf(
            time_str,
            "%4u.%02u.%02u,%02u:%02u:%02u",
            Info.wYear,
            Info.wMonth, Info.wDay,
            Info.wHour,
            Info.wSecond,
            Info.wMinute);

        sprintf(line + 12, format, attr->uid, attr->gid, attr->size, time_str, attr->name);
        puts(line);
        node = node->next;
    }
}
