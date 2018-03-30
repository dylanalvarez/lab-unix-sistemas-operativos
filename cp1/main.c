#define _POSIX_C_SOURCE 200809L

#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>


size_t file_size(int file_descriptor) {
    struct stat original_info;
    if (fstat(file_descriptor, &original_info) == -1) {
        return 0;
    }
    return (size_t) original_info.st_size;
}

long int min(long int a, long int b) {
    return a - b > 0 ? b : a;
}

void cp1(const char *original, const char *copy) {
    int original_fd = open(original, 0);
    if (original_fd == -1) {
        perror("");
        return;
    }

    int copy_fd = open(copy, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
    if (copy_fd == -1) {
        perror("");
        if (close(original_fd)) { perror(""); }
        return;
    }

    size_t size = file_size(original_fd);
    if (size == 0 || ftruncate(copy_fd, size) == -1) {
        perror("");
        if (close(original_fd)) { perror(""); }
        if (close(copy_fd)) { perror(""); }
    }

    long int iterations = 0;
    long int page_size = sysconf(_SC_PAGE_SIZE);

    while ((size_t) (iterations * page_size) < size) {
        long int bytes_to_transfer = min(page_size,
                                         size - (iterations * page_size));

        char *source = mmap(0, (size_t) bytes_to_transfer,
                            PROT_READ, MAP_SHARED,
                            original_fd, iterations * page_size);
        if (source == MAP_FAILED) {
            perror("");
            if (close(original_fd)) { perror(""); }
            if (close(copy_fd)) { perror(""); }
            return;
        }

        char *destination = mmap(0, (size_t) bytes_to_transfer,
                                 PROT_READ | PROT_WRITE, MAP_SHARED,
                                 copy_fd, iterations * page_size);
        if (destination == MAP_FAILED) {
            perror("");
            if (close(original_fd)) { perror(""); }
            if (close(copy_fd)) { perror(""); }
            return;
        }

        memcpy(destination, source, (size_t) bytes_to_transfer);
        iterations += 1;
    }

    if (close(original_fd)) { perror(""); }
    if (close(copy_fd)) { perror(""); }
    return;
}

int main(int argc, char *argv[]) {
    if (argc < 3) { return -1; }
    struct stat info1;
    stat(argv[1], &info1);
    struct stat info2;
    stat(argv[2], &info2);
    if (info1.st_dev == 0) {
        fprintf(stderr, "cp: '%s' doesn't exist", argv[1]);
        return 0;
    }
    if (info1.st_dev == info2.st_dev && info1.st_ino == info2.st_ino) {
        fprintf(stderr, "cp: '%s' and '%s' are the same file",
                argv[1], argv[2]);
        return 0;
    }
    cp1(argv[1], argv[2]);
    return argc & 0;
}
