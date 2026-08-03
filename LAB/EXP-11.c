/*
 * EXP-11: Illustrate the concept of multithreading using
 * the POSIX threads (pthread) library.
 * Compile with: gcc EXP-11.c -o EXP-11 -lpthread
 */
#include <stdio.h>
#include <pthread.h>

void *print_evens(void *arg) {
    for (int i = 2; i <= 20; i += 2) {
        printf("Even Thread: %d\n", i);
    }
    pthread_exit(NULL);
}

void *print_odds(void *arg) {
    for (int i = 1; i <= 20; i += 2) {
        printf("Odd Thread: %d\n", i);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, print_evens, NULL);
    pthread_create(&t2, NULL, print_odds, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Both threads have finished execution.\n");

    return 0;
}
