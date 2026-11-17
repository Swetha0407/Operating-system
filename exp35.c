#include <stdio.h>
#include <stdlib.h>
struct Block {
    int blockNumber;
    char data[256];
};
int main() {
    FILE *file;
    struct Block block;
    int blockNumber;
    long indexBlock[100] = {-1};
    file = fopen("indexed_file.txt", "wb");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }
    printf("Enter blocks (Enter '0' as block number to exit):\n");
    while (1) {
        printf("Block Number: ");
        scanf("%d", &block.blockNumber);
        if (block.blockNumber == 0) {
            break;
        }
        if (block.blockNumber < 1 || block.blockNumber >= 100) {
            printf("Invalid block number. Use 1 to 99.\n");
            continue;
        }
        printf("Data: ");
        scanf(" %255[^\n]", block.data);
        long position = ftell(file);
        if (fwrite(&block, sizeof(struct Block), 1, file) != 1) {
            printf("Error writing block.\n");
            fclose(file);
            return 1;
        }
        indexBlock[block.blockNumber] = position;
    }
    fclose(file);
    file = fopen("indexed_file.txt", "rb");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }
    while (1) {
        printf("Enter the block number to read (0 to exit): ");
        scanf("%d", &blockNumber);
        if (blockNumber == 0) {
            break;
        }
        if (blockNumber < 1 || blockNumber >= 100 || indexBlock[blockNumber] == -1) {
            printf("Block not found.\n");
        } else {
            fseek(file, indexBlock[blockNumber], SEEK_SET);
            if (fread(&block, sizeof(struct Block), 1, file) == 1) {
                printf("Block Number: %d\n", block.blockNumber);
                printf("Data: %s\n", block.data);
            } else {
                printf("Error reading block.\n");
            }
        }
    }
    fclose(file);
    return 0;
}
