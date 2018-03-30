#define _POSIX_C_SOURCE 200809L
#define BUFFER_SIZE 100

#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

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

bool is_number(char *name) {
    bool result = true;
    int position = 0;
    while (name[position] != 0) {
        result = result && isdigit(name[position]);
        position++;
    }
    return result;
}

void ps0() {
    DIR *directory = opendir("/proc");
    if (directory == NULL) { perror(""); }
    for (struct dirent *child = readdir(directory);
         child != NULL;
         child = readdir(directory)) {
        if (is_number(child->d_name)) {
            ssize_t name_length = strlen(child->d_name);
            ssize_t written_count = 0;
            while (written_count < name_length) {
                written_count = write(STDOUT_FILENO,
                                      child->d_name + written_count,
                                      (size_t) (name_length - written_count));
            }
            write(STDOUT_FILENO, " ", 1);
            char path[BUFFER_SIZE];
            strcpy(path, "/proc/");
            strcat(path, child->d_name);
            strcat(path, "/comm");
            cat0(path);
        }
    }
    if (closedir(directory) == -1) { perror(""); }
}

int main() {
    ps0();
    return 0;
}
