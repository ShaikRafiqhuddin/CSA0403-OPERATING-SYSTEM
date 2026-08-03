/*
 * EXP-20: Reader-Writer problem using Semaphores.
 * Compile with: gcc EXP-20.c -o EXP-20 -lpthread
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int shared_data = 0;
int read_count = 0;

sem_t rw_mutex;   /* controls access for writers */
pthread_mutex_t mutex; /* protects read_count */

void *reader(void *arg) {
    int id = *(int *)arg;

    pthread_mutex_lock(&mutex);
    read_count++;
    if (read_count == 1) sem_wait(&rw_mutex); /* first reader locks writers out */
    pthread_mutex_unlock(&mutex);

    printf("Reader %d: read shared_data = %d\n", id, shared_data);
    sleep(1);

    pthread_mutex_lock(&mutex);
    read_count--;
    if (read_count == 0) sem_post(&rw_mutex); /* last reader unlocks writers */
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void *writer(void *arg) {
    int id = *(int *)arg;

    sem_wait(&rw_mutex);
    shared_data++;
    printf("Writer %d: wrote shared_data = %d\n", id, shared_data);
    sleep(1);
    sem_post(&rw_mutex);

    return NULL;
}

int main() {
    pthread_t r[3], w[2];
    int rid[3] = {1, 2, 3};
    int wid[2] = {1, 2};

    sem_init(&rw_mutex, 0, 1);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&w[0], NULL, writer, &wid[0]);
    pthread_create(&r[0], NULL, reader, &rid[0]);
    pthread_create(&r[1], NULL, reader, &rid[1]);
    pthread_create(&w[1], NULL, writer, &wid[1]);
    pthread_create(&r[2], NULL, reader, &rid[2]);

    pthread_join(w[0], NULL);
    pthread_join(r[0], NULL);
    pthread_join(r[1], NULL);
    pthread_join(w[1], NULL);
    pthread_join(r[2], NULL);

    sem_destroy(&rw_mutex);
    pthread_mutex_destroy(&mutex);

    return 0;
}
