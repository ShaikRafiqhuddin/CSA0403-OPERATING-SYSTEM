/*
 * EXP-12: Simulation of the Dining-Philosophers problem
 * using pthreads and mutexes (semaphores for forks).
 * Compile with: gcc EXP-12.c -o EXP-12 -lpthread
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define N 5
#define LEFT(i) ((i + N - 1) % N)
#define RIGHT(i) ((i + 1) % N)
#define THINKING 0
#define HUNGRY 1
#define EATING 2

int state[N];
pthread_mutex_t mutex;
pthread_cond_t cond_var[N];

void test(int i) {
    if (state[i] == HUNGRY && state[LEFT(i)] != EATING && state[RIGHT(i)] != EATING) {
        state[i] = EATING;
        sleep(1);
        printf("Philosopher %d takes forks %d and %d and starts eating\n", i, LEFT(i), i);
        printf("Philosopher %d is EATING\n", i);
        pthread_cond_signal(&cond_var[i]);
    }
}

void take_forks(int i) {
    pthread_mutex_lock(&mutex);
    state[i] = HUNGRY;
    printf("Philosopher %d is HUNGRY\n", i);
    test(i);
    while (state[i] != EATING) {
        pthread_cond_wait(&cond_var[i], &mutex);
    }
    pthread_mutex_unlock(&mutex);
}

void put_forks(int i) {
    pthread_mutex_lock(&mutex);
    state[i] = THINKING;
    printf("Philosopher %d puts down forks %d and %d and is THINKING\n", i, LEFT(i), i);
    test(LEFT(i));
    test(RIGHT(i));
    pthread_mutex_unlock(&mutex);
}

void *philosopher(void *num) {
    int i = *(int *)num;
    take_forks(i);
    eat:
    sleep(1);
    put_forks(i);
    return NULL;
}

int main() {
    pthread_t thread_id[N];
    int ids[N];

    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < N; i++) {
        pthread_cond_init(&cond_var[i], NULL);
        state[i] = THINKING;
    }

    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&thread_id[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(thread_id[i], NULL);
    }

    return 0;
}
