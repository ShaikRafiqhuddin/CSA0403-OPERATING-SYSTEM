/*
 * EXP-2: Copy the content of one file to another using
 * open(), read(), write() and close() system calls.
 */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
    int src_fd, dst_fd;
    ssize_t n;
    char buffer[BUF_SIZE];
    char source[100], destination[100];

    if (argc == 3) {
        strcpy(source, argv[1]);
        strcpy(destination, argv[2]);
    } else {
        printf("Enter source file name: ");
        scanf("%s", source);
        printf("Enter destination file name: ");
        scanf("%s", destination);
    }

    src_fd = open(source, O_RDONLY);
    if (src_fd < 0) {
        perror("Error opening source file");
        exit(1);
    }

    dst_fd = open(destination, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dst_fd < 0) {
        perror("Error opening/creating destination file");
        close(src_fd);
        exit(1);
    }

    while ((n = read(src_fd, buffer, BUF_SIZE)) > 0) {
        if (write(dst_fd, buffer, n) != n) {
            perror("Write error");
            break;
        }
    }

    close(src_fd);
    close(dst_fd);

    printf("File copied successfully from %s to %s\n", source, destination);
    return 0;
}
