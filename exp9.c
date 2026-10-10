#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SHM_SIZE 1024
int main() {
    key_t key = ftok("shmfile", 65);
    if (key == -1) {
        perror("ftok");
        return 1;
    }
    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        return 1;
    }
    char *shm_ptr = (char *)shmat(shmid, NULL, 0);
    if (shm_ptr == (char *)-1) {
        perror("shmat");
        shmctl(shmid, IPC_RMID, NULL);
        return 1;
    }
    strcpy(shm_ptr, "Hello, shared memory!");
    printf("Data written to shared memory: %s\n", shm_ptr);
    if (shmdt(shm_ptr) == -1) {
        perror("shmdt");
        shmctl(shmid, IPC_RMID, NULL);
        return 1;
    }
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        return 1;
    }
    return 0;
}
