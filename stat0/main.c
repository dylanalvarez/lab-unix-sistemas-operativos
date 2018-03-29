#define _POSIX_C_SOURCE 200809L

#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>

const char *file_name(const char *pathname) {
    int file_name_position = 0;
    for (int i = 0; pathname[i]; i++) {
        if (pathname[i] == '/') { file_name_position = i + 1; }
    }
    return pathname + file_name_position;
}

void stat0(const char *pathname) {
    struct stat info;
    if (stat(pathname, &info) == -1) {
        perror("");
        return;
    }
    printf("Size: %d\nFile: %s\nType: %s",
           (int) info.st_size,
           file_name(pathname),
           S_ISREG(info.st_mode) ? "regular file" : "directory");
}

int main(int argc, char *argv[]) {
    if (argc < 2) { return -1; }
    stat0(argv[1]);
    return argc & 0;
}
