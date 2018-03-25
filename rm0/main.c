#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

void rm0(const char *pathname) {
    unlink(pathname);
    if (errno) {
        printf("%s", strerror(errno));
        return;
    }
}

int main(int argc, char *argv[]) {
    rm0(argv[1]);
    return argc & 0;
}
