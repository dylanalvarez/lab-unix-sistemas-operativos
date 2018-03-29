#define _POSIX_C_SOURCE 200809L
#define BUFFER_SIZE 100

#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

void tee0(const char *pathname) {
    int output = open(pathname, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    if (output == -1) {
        perror("");
        return;
    }

    ssize_t read_count = -1;
    char buffer[BUFFER_SIZE];

    while (read_count) {
        read_count = read(STDIN_FILENO, buffer, BUFFER_SIZE);
        if (read_count < 0) {
            perror("");
            if (close(output)) { perror(""); }
            return;
        }

        ssize_t file_written_count = 0;
        while (file_written_count < read_count) {
            file_written_count = write(output,
                                       buffer + file_written_count,
                                       (size_t) (read_count -
                                                 file_written_count));
            if (file_written_count < 0) {
                perror("");
                if (close(output)) { perror(""); }
                return;
            }
        }

        ssize_t stdout_written_count = 0;
        while (stdout_written_count < read_count) {
            stdout_written_count = write(STDOUT_FILENO,
                                         buffer + stdout_written_count,
                                         (size_t) (read_count -
                                                   stdout_written_count));
            if (stdout_written_count < 0) {
                perror("");
                if (close(output)) { perror(""); }
                return;
            }
        }
    }

    if (close(output)) { perror(""); }
}

int main(int argc, char *argv[]) {
    if (argc < 2) { return -1; }
    tee0(argv[1]);
    return argc & 0;
}
