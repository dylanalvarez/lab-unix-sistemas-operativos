#define _POSIX_C_SOURCE 200809L

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

void touch0(const char *pathname) {
    int file_descriptor = open(pathname, O_CREAT, S_IRWXU);
    if (file_descriptor == -1) {
        perror("");
        return;
    }
    if (close(file_descriptor)) { perror(""); }
}

int main(int argc, char *argv[]) {
    if (argc < 2) { return -1; }
    touch0(argv[1]);
    return argc & 0;
}
