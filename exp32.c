#include <stdio.h>
#define MAX_FRAMES 3
void printFrames(int frames[], int n) {
    for (int i = 0; i < n; i++) {
        if (frames[i] == -1) {
            printf(" - ");
        } else {
            printf(" %d ", frames[i]);
        }
    }
    printf("\n");
}
int main() {
    int frames[MAX_FRAMES];
    int lastUsed[MAX_FRAMES] = {0};
    int pageFaults = 0, pageHits = 0;
    int counter = 0;
    int referenceString[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(referenceString) / sizeof(referenceString[0]);
    for (int i = 0; i < MAX_FRAMES; i++) {
        frames[i] = -1;
    }
    printf("Reference String: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", referenceString[i]);
    }
    printf("\n\nPage Replacement Order:\n");
    for (int i = 0; i < n; i++) {
        int page = referenceString[i];
        int pageFound = 0;
        counter++;
        for (int j = 0; j < MAX_FRAMES; j++) {
            if (frames[j] == page) {
                pageFound = 1;
                lastUsed[j] = counter;
                break;
            }
        }
        if (pageFound) {
            pageHits++;
            printf("Page %d -> HIT ", page);
            printFrames(frames, MAX_FRAMES);
        } else {
            pageFaults++;
            int lruIndex = -1;
            for (int j = 0; j < MAX_FRAMES; j++) {
                if (frames[j] == -1) {
                    lruIndex = j;
                    break;
                }
                if (lruIndex == -1 || lastUsed[j] < lastUsed[lruIndex]) {
                    lruIndex = j;
                }
            }
            if (frames[lruIndex] == -1) {
                printf("Page %d -> FAULT (Empty frame) ", page);
            } else {
                printf("Page %d -> FAULT (Replace %d) ", page, frames[lruIndex]);
            }
            frames[lruIndex] = page;
            lastUsed[lruIndex] = counter;
            printFrames(frames, MAX_FRAMES);
        }
    }
    printf("\nTotal Page Hits: %d\n", pageHits);
    printf("Total Page Faults: %d\n", pageFaults);
    return 0;
}
