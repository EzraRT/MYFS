#include <myfsconfig.h>

#include <myfsapi.h>

#include <io.h>

#include <windows.h>

bool myremove(const char* filename)
{
    MYFILE_ATTIBUTE* attr;
    bool file_exist = false;
    link_node* node = current_dir_attribute_head;
    while (node != NULL) {
        attr = (MYFILE_ATTIBUTE*)(node->data);
        if (strcmp(attr->name, filename) == 0) {
            file_exist = true;
            break;
        }
        node = node->next;
    }

    if (!file_exist) {
        printf("'%s' not found\n", filename);
        return false;
    }

    uint8_t privilege = grant_privilege(attr);

    if (!(privilege & MYFS_FWRITE)) {
        printf("Permission denied\n");
        return false;
    }

    bool result = DeleteFile(filename);
    char buffer[1024], filename_buffer[80];

    if (result) {
        FILE* attr_file = fopen("attr.info", "r+");
        memset(buffer, 0, sizeof(buffer));
        long lastr = 0, lastw = 0;

        while (fgets(buffer, sizeof(buffer), attr_file) != NULL) {
            memset(filename_buffer, 0, sizeof(filename_buffer));

            sscanf(buffer, "%s", filename_buffer);
            if (strcmp(filename_buffer, filename) == 0) {
                lastw = ftell(attr_file) - strlen(buffer) - 1;
                break;
            }
        }

        if (!lastw) {
            printf("error: %s not found\n", filename);
            return false;
        }

        while (fgets(buffer, sizeof(buffer), attr_file) != NULL) {
            lastr = ftell(attr_file);
            fseek(attr_file, lastw, SEEK_SET);
            fputs(buffer, attr_file);
            lastw = ftell(attr_file);
            memset(buffer, 0, sizeof(buffer));
            fseek(attr_file, lastr, SEEK_SET);
        }

        chsize(fileno(attr_file), lastw);

        fclose(attr_file);
    }

    myrefresh_pwd();

    return result;
}
