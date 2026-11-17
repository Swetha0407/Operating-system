#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Block {
    char data[256];
    struct Block *next;
};
int main() {
    struct Block *firstBlock = NULL;
    struct Block *lastBlock = NULL;
    struct Block *currentBlock;
    int blockCount = 0;
    int blockNumber;
    char data[256];
    char choice;
    printf("Linked Allocation Simulation\n");
    while (1) {
        printf("Enter 'W' to write a block, 'R' to read a block, or 'Q' to quit: ");
        scanf(" %c", &choice);
        if (choice == 'Q' || choice == 'q') {
            break;
        }
        if (choice == 'W' || choice == 'w') {
            printf("Enter data for the block: ");
            scanf(" %255[^\n]", data);
            struct Block *newBlock = malloc(sizeof(struct Block));
            if (newBlock == NULL) {
                printf("Memory allocation failed.\n");
                break;
            }
            strcpy(newBlock->data, data);
            newBlock->next = NULL;
            if (blockCount == 0) {
                firstBlock = newBlock;
                lastBlock = newBlock;
            } else {
                lastBlock->next = newBlock;
                lastBlock = newBlock;
            }
            blockCount++;
            printf("Block %d written successfully.\n", blockCount);
        } else if (choice == 'R' || choice == 'r') {
            if (blockCount == 0) {
                printf("No blocks available to read.\n");
                continue;
            }
            printf("Enter the block number to read (1-%d): ", blockCount);
            scanf("%d", &blockNumber);
            if (blockNumber < 1 || blockNumber > blockCount) {
                printf("Invalid block number. The valid range is 1-%d.\n", blockCount);
            } else {
                currentBlock = firstBlock;
                for (int i = 1; i < blockNumber; i++) {
                    currentBlock = currentBlock->next;
                }
                printf("Block %d Data: %s\n", blockNumber, currentBlock->data);
            }
        } else {
            printf("Invalid choice.\n");
        }
    }
    currentBlock = firstBlock;
    while (currentBlock != NULL) {
        struct Block *nextBlock = currentBlock->next;
        free(currentBlock);
        currentBlock = nextBlock;
    }
    printf("Memory released successfully.\n");
    return 0;
}
