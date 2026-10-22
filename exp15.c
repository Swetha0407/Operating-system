#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
int main() {
    char mainDirectory[] = ".";
    char subDirectory[] = "os";
    char fileName[] = "example.txt";
    char mainDirPath[200];
    char filePath[200];
    if (mkdir(subDirectory, 0755) == -1) {
        struct stat st;
        if (stat(subDirectory, &st) == -1 || !S_ISDIR(st.st_mode)) {
            perror("Error creating directory");
            return 1;
        }
    }
    snprintf(mainDirPath, sizeof(mainDirPath), "%s/%s", mainDirectory, subDirectory);
    snprintf(filePath, sizeof(filePath), "%s/%s", mainDirPath, fileName);
    FILE *file = fopen(filePath, "w");
    if (file == NULL) {
        perror("Error creating file");
        return 1;
    }
    fprintf(file, "This is an example file content.");
    fclose(file);
    printf("File created successfully: %s\n", filePath);
    return 0;
}
