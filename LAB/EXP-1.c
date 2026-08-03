/*
 * EXP-1: Create a new process using fork() system call.
 * Get the process identifier of the currently running process
 * and its parent process using getpid() and getppid().
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid;

    printf("Before fork: Process ID = %d, Parent Process ID = %d\n", getpid(), getppid());

    pid = fork();

    if (pid < 0) {
        /* fork failed */
        fprintf(stderr, "Fork failed!\n");
        return 1;
    } else if (pid == 0) {
        /* Child process */
        printf("Child Process: PID = %d, Parent PID = %d\n", getpid(), getppid());
    } else {
        /* Parent process */
        wait(NULL);
        printf("Parent Process: PID = %d, Parent PID = %d, Child PID = %d\n", getpid(), getppid(), pid);
    }

    return 0;
}
