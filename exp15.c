#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
int main() {
    char subDirectory[] = "os";
    char filePath[] = "./os/example.txt";
    if (mkdir(subDirectory, 0755) == -1) {
        if (errno != EEXIST) {
            perror("Error creating directory");
            return 1;
        }
        struct stat st;
        if (stat(subDirectory, &st) == -1 || !S_ISDIR(st.st_mode)) {
            printf("Error: 'os' exists but is not a directory.\n");
            return 1;
        }
    }
    FILE *file = fopen(filePath, "w");
    if (file == NULL) {
        perror("Error creating file");
        return 1;
    }
    if (fprintf(file, "This is an example file content.") < 0) {
        perror("Error writing to file");
        fclose(file);
        return 1;
    }
    if (fclose(file) == EOF) {
        perror("Error closing file");
        return 1;
    }
    printf("File created successfully: %s\n", filePath);
    return 0;
}
