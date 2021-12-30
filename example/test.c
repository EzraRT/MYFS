#include <myfsapi.h>
#include <string.h>
#include <time.h>

int main(int argc, char const* argv[])
{
    MYFILE_HANDLE file = myopen("test.txt", "r");
    if (file == NULL) {
        printf("open failed\n");
        return -1;
    }

    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    size_t read_size = myread(file, buffer, 1024, sizeof(char));
    printf("read_size: %llu\n", read_size);
    printf("buffer:\n%s\n", buffer);

    myclose(file);

    MYFILE_HANDLE file2write = myopen("output.txt", "w");
    if (file2write == NULL) {
        printf("open failed\n");
        return -1;
    }

    memset(buffer, 0, sizeof(buffer));

    sprintf(buffer, "hello world!\n%llu\n", time(NULL));

    size_t write_size = mywrite(file2write, buffer, sizeof(char), strlen(buffer));

    write_size = mywrite(file2write, buffer, sizeof(char), strlen(buffer));

    myclose(file2write);
    return 0;
}
