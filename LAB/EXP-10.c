/*
 * EXP-10: Inter-process communication using Message Queue.
 * Parent sends a message, child receives it.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>

#define MSG_SIZE 1024

struct message {
    long msg_type;
    char msg_text[MSG_SIZE];
};

int main() {
    key_t key = ftok("msgfile", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid < 0) {
        perror("msgget failed");
        exit(1);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid > 0) {
        /* Parent: sender */
        struct message msg;
        msg.msg_type = 1;
        printf("Enter message to send: ");
        fgets(msg.msg_text, MSG_SIZE, stdin);

        msgsnd(msgid, &msg, sizeof(msg.msg_text), 0);
        wait(NULL);

        msgctl(msgid, IPC_RMID, NULL);
    } else {
        /* Child: receiver */
        struct message msg;
        msgrcv(msgid, &msg, sizeof(msg.msg_text), 1, 0);
        printf("Child received message: %s\n", msg.msg_text);
    }

    return 0;
}
