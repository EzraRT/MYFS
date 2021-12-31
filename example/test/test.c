#include <myfsapi.h>
#include <string.h>
#include <time.h>

int main(int argc, char const* argv[])
{
    uid = 0;
    gid = 0;

    mychdir("fmlnb");
    MYFILE_HANDLE file = myopen("test.txt", "r");
    if (file == NULL) {
        printf("open failed\n");
        return -1;
    }

    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    size_t read_size = myread(file, buffer, sizeof(char), 1024);
    printf("read_size: %llu\n", read_size);
    printf("buffer:\n%s\n", buffer);

    myclose(file);

    MYFILE_HANDLE file2write = myopen("testoutput.txt", "w");
    if (file2write == NULL) {
        printf("open failed\n");
        return -1;
    }

    memset(buffer, 0, sizeof(buffer));

    sprintf(buffer, "hello world!\n%llu\n", time(NULL));

    size_t write_size = mywrite(file2write, buffer, sizeof(char), strlen(buffer));

    write_size = mywrite(file2write, buffer, sizeof(char), strlen(buffer));

    myclose(file2write);

    // mychdir("fmlnb");

    // STARTUPINFO si;
    // memset(&si, 0, sizeof(si));
    // si.cb = sizeof(si);
    // PROCESS_INFORMATION pi;
    // memset(&pi, 0, sizeof(pi));
    // if (!CreateProcess(NULL, "aes-tool.exe output.txt -p fmlnb!!!", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
    //     printf("CreateProcess %s failed.\n", "aes-tool.exe");
    //     return;
    // }

    return 0;
}
