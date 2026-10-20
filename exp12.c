#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define NUM_PHILOSOPHERS 5
#define ROUNDS 3
pthread_mutex_t chopsticks[NUM_PHILOSOPHERS];
void* philosopherLifeCycle(void* arg) {
    int id = *((int*)arg);
    int left_chopstick = id;
    int right_chopstick = (id + 1) % NUM_PHILOSOPHERS;
    for (int i = 0; i < ROUNDS; i++) {
        printf("Philosopher %d is thinking...\n", id);
        int first = left_chopstick < right_chopstick ? left_chopstick : right_chopstick;
        int second = left_chopstick < right_chopstick ? right_chopstick : left_chopstick;
        pthread_mutex_lock(&chopsticks[first]);
        pthread_mutex_lock(&chopsticks[second]);
        printf("Philosopher %d is eating...\n", id);
        sleep(1);
        pthread_mutex_unlock(&chopsticks[second]);
        pthread_mutex_unlock(&chopsticks[first]);
    }
    return NULL;
}
int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        pthread_mutex_init(&chopsticks[i], NULL);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL,
                       philosopherLifeCycle, &philosopher_ids[i]);
    }
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        pthread_join(philosophers[i], NULL);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        pthread_mutex_destroy(&chopsticks[i]);
    printf("All philosophers have finished.\n");
    return 0;
}
