#define _POSIX_C_SOURCE 200809L

#include <stdio.h>

void mv0(const char *old_name, const char *new_name) {
    if (rename(old_name, new_name) == -1) { perror(""); }
}

int main(int argc, char *argv[]) {
    mv0(argv[1], argv[2]);
    return argc & 0;
}
