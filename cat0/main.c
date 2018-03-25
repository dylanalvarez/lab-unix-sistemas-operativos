#define _POSIX_C_SOURCE 200809L
#define BUFFER_SIZE 100

#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

void cat0(const char *pathname) {
    int file_descriptor = open(pathname, 0);
    if (file_descriptor == -1) {
        perror("");
        return;
    }

    ssize_t read_count = -1;
    char buffer[BUFFER_SIZE];

    while (read_count) {
        read_count = read(file_descriptor, buffer, BUFFER_SIZE);
        if (read_count < 0) {
            perror("");
            if (close(file_descriptor)) { perror(""); }
            return;
        }

        ssize_t written_count = 0;
        while (written_count < read_count) {
            written_count = write(STDOUT_FILENO,
                                  buffer + written_count,
                                  (size_t) (read_count - written_count));
            if (written_count < 0) {
                perror("");
                if (close(file_descriptor)) { perror(""); }
                return;
            }
        }
    }

    if (close(file_descriptor)) { perror(""); }
}

int main(int argc, char *argv[]) {
    cat0(argv[1]);
    return argc & 0;
}
