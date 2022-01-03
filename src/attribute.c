#include <myfsconfig.h>

#include <myfsapi.h>
#include <stdlib.h>

HANDLE hListFile;

WIN32_FIND_DATA FindFileData;

char buffer[1024];

char current_dir_buffer[1024];

link_node* current_dir_attribute_head = NULL;

MYFILE_ATTIBUTE* get_file_attribute(const char* filename)
{
    MYFILE_ATTIBUTE* attr;
    link_node* node = current_dir_attribute_head;
    while (node != NULL) {
        attr = (MYFILE_ATTIBUTE*)(node->data);
        if (strcmp(attr->name, filename) == 0) {
            return attr;
        }
        node = node->next;
    }
    return NULL;
}

void mystat(const char* filename, MYFILE_ATTIBUTE* attr)
{
    MYFILE_ATTIBUTE* result = get_file_attribute(filename);
    if (result == NULL) {
        return;
    }
    memcpy(attr, result, sizeof(MYFILE_ATTIBUTE));
}

void myrefresh_pwd()
{
    int privilege;
    MYFILE_ATTIBUTE* attr = (MYFILE_ATTIBUTE*)malloc(sizeof(MYFILE_ATTIBUTE));
    memset(attr, 0, sizeof(MYFILE_ATTIBUTE));

    GetCurrentDirectory(1024, current_dir_buffer);
    while (current_dir_attribute_head != NULL) {
        current_dir_attribute_head = delete_node(current_dir_attribute_head);
    }

    hListFile = FindFirstFile("attr.info", &FindFileData);
    if (hListFile == INVALID_HANDLE_VALUE) {
        printf("Crashed or Unsupported PATH\n");
        return;
    }

    FILE* attr_file = fopen("attr.info", "r");
    memset(buffer, 0, sizeof(buffer));

    while (fgets(buffer, sizeof(buffer), attr_file) != NULL) {

        sscanf(buffer, "%s %llu %llu %u", attr->name, &(attr->uid), &(attr->gid), &privilege);

        attr->other = privilege % 10;
        attr->group = (privilege / 10) % 10;
        attr->owner = (privilege / 100) % 10;

        hListFile = FindFirstFile(attr->name, &FindFileData);

        attr->size = FindFileData.nFileSizeHigh;
        attr->size = attr->size << 32;
        attr->size += FindFileData.nFileSizeLow;

        FileTimeToSystemTime(&FindFileData.ftLastWriteTime, &attr->last_write);

        attr->is_dir = FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;

        current_dir_attribute_head = push_data(current_dir_attribute_head, attr);

        attr = (MYFILE_ATTIBUTE*)malloc(sizeof(MYFILE_ATTIBUTE));
        memset(attr, 0, sizeof(MYFILE_ATTIBUTE));
    };

    free(attr);
}

void mypwd()
{
    myrefresh_pwd();
    printf("%s\n", current_dir_buffer);
}