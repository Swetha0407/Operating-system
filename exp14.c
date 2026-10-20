#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define BUFFER_SIZE 4096
const char *sourcefile = "sasi.txt";
const char *destination_file = "sk.txt";
void create() {
    FILE *fp = fopen(sourcefile, "w");
    if (fp == NULL) {
        perror("File creation failed");
        return;
    }
    fclose(fp);
    printf("File created successfully.\n");
}
void copy() {
    int source_fd = open(sourcefile, O_RDONLY);
    if (source_fd == -1) {
        perror("Error opening source file");
        return;
    }
    int dest_fd = open(destination_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (dest_fd == -1) {
        perror("Error opening destination file");
        close(source_fd);
        return;
    }
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead, bytesWritten;
    while ((bytesRead = read(source_fd, buffer, BUFFER_SIZE)) > 0) {
        ssize_t totalWritten = 0;
        while (totalWritten < bytesRead) {
            bytesWritten = write(dest_fd, buffer + totalWritten, bytesRead - totalWritten);
            if (bytesWritten == -1) {
                perror("Error writing file");
                close(source_fd);
                close(dest_fd);
                return;
            }
            totalWritten += bytesWritten;
        }
    }
    if (bytesRead == -1)
        perror("Error reading source file");
    else
        printf("File copied successfully.\n");
    close(source_fd);
    close(dest_fd);
}
void delete() {
    if (remove(sourcefile) == 0)
        printf("File deleted successfully.\n");
    else
        perror("File deletion failed");
}
int main() {
    int n;
    printf("1. Create  2. Copy  3. Delete\n");
    printf("Enter your choice: ");
    scanf("%d", &n);
    switch (n) {
        case 1:
            create();
            break;
        case 2:
            copy();
            break;
        case 3:
            delete();
            break;
        default:
            printf("Invalid choice.\n");
    }
    return 0;
}
