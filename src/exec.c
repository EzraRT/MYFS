#include <myfsconfig.h>

#include <myfsapi.h>

MYFS_EXPORT void myexec(const MYFILE_ATTIBUTE* file, const* command)
{
    uint8_t privillege = grant_privilege(file);
    if (privillege & MYFS_FEXEC) {
        char cmd[1024];
        memset(cmd, 0, sizeof(cmd));

        if (command) {
            sprintf(cmd, "%s %s", file->name, command);
        } else {
            sprintf(cmd, "%s", file->name);
        }

        puts(cmd);

        STARTUPINFO si;
        memset(&si, 0, sizeof(si));
        si.cb = sizeof(si);
        PROCESS_INFORMATION pi;
        memset(&pi, 0, sizeof(pi));
        if (!CreateProcess(NULL, cmd, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
            printf("CreateProcess %s failed.\n", file->name);
            return;
        }

        WaitForSingleObject(pi.hProcess, INFINITE);
    } else {
        printf("error: no privillege to exec %s\n", file->name);
        return;
    }
}
