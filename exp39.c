#include <stdio.h>
#include <stdlib.h>
int main() {
    int n, head, diskSize, seek_time = 0;
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);
    if (n <= 0) {
        printf("Invalid number of requests.\n");
        return 1;
    }
    int request_queue[n];
    printf("Enter the disk request queue:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &request_queue[i]);
    }
    printf("Enter the initial position of the disk head: ");
    scanf("%d", &head);
    printf("Enter the disk size (number of cylinders): ");
    scanf("%d", &diskSize);
    if (diskSize <= 0 || head < 0 || head >= diskSize) {
        printf("Invalid disk size or head position.\n");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        if (request_queue[i] < 0 || request_queue[i] >= diskSize) {
            printf("Invalid disk request.\n");
            return 1;
        }
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (request_queue[i] > request_queue[j]) {
                int temp = request_queue[i];
                request_queue[i] = request_queue[j];
                request_queue[j] = temp;
            }
        }
    }
    printf("\nSCAN (Elevator) Disk Scheduling:\n");
    printf("Head Movement Sequence: %d", head);
    int i = 0;
    while (i < n && request_queue[i] < head) {
        i++;
    }
    for (int j = i; j < n; j++) {
        seek_time += abs(head - request_queue[j]);
        head = request_queue[j];
        printf(" -> %d", head);
    }
    if (head != diskSize - 1) {
        seek_time += abs(head - (diskSize - 1));
        head = diskSize - 1;
        printf(" -> %d", head);
    }
    for (int j = i - 1; j >= 0; j--) {
        seek_time += abs(head - request_queue[j]);
        head = request_queue[j];
        printf(" -> %d", head);
    }
    printf("\nTotal Seek Time: %d\n", seek_time);
    printf("Average Seek Time: %.2f\n", (float)seek_time / n);
    return 0;
}
