#define _POSIX_C_SOURCE 200809L
#define BUFFER_SIZE 100

#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>


void cp0(const char *original, const char *copy) {
    int original_fd = open(original, 0);
    if (original_fd == -1) {
        perror("");
        return;
    }

    int copy_fd = open(copy, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    if (copy_fd == -1) {
        perror("");
        if (close(original_fd)) { perror(""); }
        return;
    }

    ssize_t read_count = -1;
    char buffer[BUFFER_SIZE];

    while (read_count) {
        read_count = read(original_fd, buffer, BUFFER_SIZE);
        if (read_count < 0) {
            perror("");
            if (close(original_fd)) { perror(""); }
            if (close(copy_fd)) { perror(""); }
            return;
        }

        ssize_t written_count = 0;
        while (written_count < read_count) {
            written_count = write(copy_fd,
                                  buffer + written_count,
                                  (size_t) (read_count - written_count));
            if (written_count < 0) {
                perror("");
                if (close(original_fd)) { perror(""); }
                if (close(copy_fd)) { perror(""); }
                return;
            }
        }
    }

    if (close(original_fd)) { perror(""); }
    if (close(copy_fd)) { perror(""); }
}

int main(int argc, char *argv[]) {
    if (argc < 3) { return -1; }
    struct stat info1;
    stat(argv[1], &info1);
    struct stat info2;
    stat(argv[2], &info2);
    if (info1.st_dev == info2.st_dev && info1.st_ino == info2.st_ino) {
        fprintf(stderr, "cp: '%s' and '%s' are the same file",
                argv[1], argv[2]);
    }
    cp0(argv[1], argv[2]);
    return argc & 0;
}
