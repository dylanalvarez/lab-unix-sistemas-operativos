#define _POSIX_C_SOURCE 200809L

#include <unistd.h>
#include <stdio.h>

const char *file_name(const char *pathname) {
    int file_name_position = 0;
    for (int i = 0; pathname[i]; i++) {
        if (pathname[i] == '/') { file_name_position = i + 1; }
    }
    return pathname + file_name_position;
}

void rm0(const char *pathname) {
    if (unlink(pathname) == -1) {
        fprintf(stderr, "rm: cannot remove '%s': ", file_name(pathname));
        perror("");
        return;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) { return -1; }
    rm0(argv[1]);
    return argc & 0;
}
