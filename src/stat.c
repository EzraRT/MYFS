#include <myfsconfig.h>

#include <myfsapi.h>

MYFILE_ATTRIBUTE* get_file_attribute(const char* filename)
{
    MYFILE_ATTRIBUTE* attr;
    link_node* node = current_dir_attribute_head;
    while (node != NULL) {
        attr = (MYFILE_ATTRIBUTE*)(node->data);
        if (strcmp(attr->name, filename) == 0) {
            return attr;
        }
        node = node->next;
    }
    return NULL;
}

void mystat(const char* filename, MYFILE_ATTRIBUTE* attr)
{
    MYFILE_ATTRIBUTE* result = get_file_attribute(filename);
    if (result == NULL) {
        return;
    }
    memcpy(attr, result, sizeof(MYFILE_ATTRIBUTE));
}