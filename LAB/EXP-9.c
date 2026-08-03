/*
 * EXP-9: Inter-process communication using Shared Memory.
 * Parent process writes a message into shared memory,
 * child process reads it.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define SHM_SIZE 1024

int main() {
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid < 0) {
        perror("shmget failed");
        exit(1);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid > 0) {
        /* Parent: writer */
        char *str = (char *) shmat(shmid, NULL, 0);
        printf("Enter message to write to shared memory: ");
        fgets(str, SHM_SIZE, stdin);

        shmdt(str);
        wait(NULL);

        shmctl(shmid, IPC_RMID, NULL);
    } else {
        /* Child: reader */
        sleep(1); /* ensure parent writes first */
        char *str = (char *) shmat(shmid, NULL, 0);
        printf("Child read from shared memory: %s\n", str);
        shmdt(str);
    }

    return 0;
}
