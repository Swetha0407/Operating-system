#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
int main() {
    int fd, bytesRead;
    char buffer[100];
    fd = creat("sample.txt", S_IRWXU);
    if (fd == -1) {
        perror("create");
        exit(1);
    } else {
        printf("File 'sample.txt' created successfully.\n");
        close(fd);
    }
    fd = open("sample.txt", O_WRONLY | O_APPEND);
    if (fd == -1) {
        perror("open");
        exit(1);
    } else {
        printf("File 'sample.txt' opened for writing.\n");
    }
    write(fd, "Hello, World!\n", 14);
    printf("Data written to 'sample.txt'.\n");
    close(fd);
    fd = open("sample.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    } else {
        printf("File 'sample.txt' opened for reading.\n");
    }
    bytesRead = read(fd, buffer, sizeof(buffer));
    if (bytesRead == -1) {
        perror("read");
        exit(1);
    } else {
        printf("Data read from 'sample.txt':\n");
        write(STDOUT_FILENO, buffer, bytesRead);
    }
    close(fd);
    if (remove("sample.txt") == -1) {
        perror("remove");
        exit(1);
    } else {
        printf("File 'sample.txt' deleted.\n");
    }
    return 0;
}
