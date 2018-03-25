#define _POSIX_C_SOURCE 200809L

#include <unistd.h>
#include <stdio.h>

void rm0(const char *pathname) {
    if (unlink(pathname) == -1) {
        perror("");
        return;
    }
}

int main(int argc, char *argv[]) {
    rm0(argv[1]);
    return argc & 0;
}
