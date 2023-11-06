#include <cstdio>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <iostream>
#include "constants.h"

using namespace std;

int main() {
    cout << "Клиент\n";

    key_t key = ftok(PATHNAME, PROJ_ID);
    int msqid = msgget(key, 0666 | IPC_CREAT);

    msgBuffer message{};
    while (true) {
        cout << "Введите путь либо команду: ";
        cin >> message.text;

        message.type = REQUEST_TYPE;
        msgsnd(msqid, &message, sizeof(message), 0);
        msgrcv(msqid, &message, sizeof(message), RESPONSE_TYPE, 0);
        printf("Ответ: %s\n", message.text);

        if (strcmp(OFF, message.text) == 0) {
            break;
        }
    }
    return 0;
}
