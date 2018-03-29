#define _POSIX_C_SOURCE 200809L

#include <dirent.h>
#include <stdio.h>

void ls0() {
    DIR *directory = opendir(".");
    if (directory == NULL) { perror(""); }
    for (struct dirent *child = readdir(directory);
         child != NULL;
         child = readdir(directory)) {
        printf("%s\n", child->d_name);
    }
    if (closedir(directory) == -1) { perror(""); }
}

int main() {
    ls0();
    return 0;
}
