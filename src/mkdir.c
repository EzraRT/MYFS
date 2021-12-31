#include <myfsconfig.h>

#include <myfsapi.h>

bool MYFS_EXPORT mymkdir(const char* pathname)
{
    bool result = false;
    MYFILE_ATTIBUTE attr;

    memset(&attr, 0, sizeof(attr));
    mystat(pathname, &attr);
    if (strlen(attr.name) == 0) {
        // not exist
        result = CreateDirectory(pathname, NULL);
    } else {
        // already exist
        printf("error: %s already exist\n", pathname);
    }

    if (result) {
        FILE* attr_file = fopen("attr.info", "a");
        fprintf(attr_file, "%s %d %d %d\n", pathname, uid, gid, 775);
        fclose(attr_file);
        chdir(pathname);
        attr_file = fopen("attr.info", "w");
        fclose(attr_file);
        mychdir("..");
    }

    return result;
}