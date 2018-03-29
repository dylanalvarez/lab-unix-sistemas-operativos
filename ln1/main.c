#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <unistd.h>

void ln1(const char *original, const char *link_path) {
    if (link(original, link_path) == -1) { perror(""); }
}

int main(int argc, char *argv[]) {
    if (argc < 3) { return -1; }
    ln1(argv[1], argv[2]);
    return argc & 0;
}
