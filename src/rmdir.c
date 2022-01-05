#include <myfsconfig.h>

#include <myfsapi.h>

bool MYFS_EXPORT myrmdir(const char* pathname)
{
    bool result = false;
    MYFILE_ATTRIBUTE attr;

    memset(&attr, 0, sizeof(attr));
    mystat(pathname, &attr);
    if (strlen(attr.name) == 0 || !attr.is_dir) {
        // not exist
        printf("error: folder '%s' not found\n", pathname);
        return false;
    } else {
        if (grant_privilege(&attr) & MYFS_FWRITE) {
            SHFILEOPSTRUCT FileOp;

            memset(&FileOp, 0, sizeof(FileOp));
            FileOp.hwnd = NULL;
            FileOp.wFunc = FO_DELETE; // 删除
            FileOp.pFrom = pathname; // 非空目录的路径
            FileOp.pTo = NULL;
            FileOp.fFlags = FOF_SIMPLEPROGRESS | FOF_ALLOWUNDO | FOF_NOCONFIRMATION;
            result = !SHFileOperation(&FileOp);
        } else {
            printf("error: permission denied\n");
            return false;
        }
    }

    char buffer[1024], filename_buffer[80];

    if (result) {
        FILE* attr_file = fopen("attr.info", "r+");
        memset(buffer, 0, sizeof(buffer));
        long lastr = 0, lastw = 0;

        while (fgets(buffer, sizeof(buffer), attr_file) != NULL) {
            memset(filename_buffer, 0, sizeof(filename_buffer));

            sscanf(buffer, "%s", filename_buffer);
            printf("'%s'\n", pathname);
            printf("'%s'\n", filename_buffer);
            if (strcmp(filename_buffer, pathname) == 0) {
                printf("%d %d\n", ftell(attr_file), strlen(buffer));
                lastw = ftell(attr_file) - strlen(buffer) - 1;
                break;
            }
            memset(buffer, 0, sizeof(buffer));
        }

        printf("%d\n", lastw);

        if (!lastw) {
            printf("error: %s not found\n", pathname);
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
