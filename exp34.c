#include <stdio.h>
#include <stdlib.h>
struct Record {
    int recordNumber;
    char data[256];
};
int main() {
    FILE *file;
    struct Record record;
    int recordNumber;
    file = fopen("sequential_file.txt", "wb");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }
    printf("Enter records (Enter '0' as record number to exit):\n");
    while (1) {
        printf("Record Number: ");
        scanf("%d", &record.recordNumber);
        if (record.recordNumber == 0) {
            break;
        }
        printf("Data: ");
        scanf(" %255[^\n]", record.data);
        fwrite(&record, sizeof(struct Record), 1, file);
    }
    fclose(file);
    file = fopen("sequential_file.txt", "rb");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }
    while (1) {
        printf("Enter the record number to read (0 to exit): ");
        scanf("%d", &recordNumber);
        if (recordNumber == 0) {
            break;
        }
        int found = 0;
        while (fread(&record, sizeof(struct Record), 1, file) == 1) {
            if (record.recordNumber == recordNumber) {
                printf("Record Number: %d\n", record.recordNumber);
                printf("Data: %s\n", record.data);
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("Record not found.\n");
        }
        rewind(file);
    }
    fclose(file);
    return 0;
}
