#define _POSIX_C_SOURCE 200809L
#include <unistd.h>

void rm0(const char *pathname) {
    unlink(pathname);
}

int main(int argc, char *argv[]) {
    rm0(argv[1]);
    return argc & 0;
}
