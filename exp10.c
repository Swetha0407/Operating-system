#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
struct message {
    long msg_type;
    char msg_text[100];
};
int main() {
    key_t key = ftok("msgqfile", 65);
    if (key == -1) {
        perror("ftok");
        return 1;
    }
    int msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("msgget");
        return 1;
    }
    struct message msg;
    msg.msg_type = 1;
    strcpy(msg.msg_text, "Hello, message queue!");
    if (msgsnd(msgid, &msg, sizeof(msg.msg_text), 0) == -1) {
        perror("msgsnd");
        msgctl(msgid, IPC_RMID, NULL);
        return 1;
    }
    printf("Producer: Data sent to message queue: %s\n", msg.msg_text);
    if (msgrcv(msgid, &msg, sizeof(msg.msg_text), 1, 0) == -1) {
        perror("msgrcv");
        msgctl(msgid, IPC_RMID, NULL);
        return 1;
    }
    printf("Consumer: Data received from message queue: %s\n", msg.msg_text);
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        return 1;
    }
    return 0;
}
