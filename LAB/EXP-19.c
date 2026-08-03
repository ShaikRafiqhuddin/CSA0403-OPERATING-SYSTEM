/*
 * EXP-19: Process Synchronization using Mutex Locks.
 * Two threads increment a shared counter; mutex prevents race condition.
 * Compile with: gcc EXP-19.c -o EXP-19 -lpthread
 */
#include <stdio.h>
#include <pthread.h>

#define ITERATIONS 100000

long counter = 0;
pthread_mutex_t lock;

void *increment(void *arg) {
    for (int i = 0; i < ITERATIONS; i++) {
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_mutex_init(&lock, NULL);

    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final value of counter (expected %d) = %ld\n", 2 * ITERATIONS, counter);

    pthread_mutex_destroy(&lock);
    return 0;
}
