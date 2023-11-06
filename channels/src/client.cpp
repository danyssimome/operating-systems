#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include "constants.h"

using namespace std;

int main() {
    cout << "Клиент\n";

    int client = open(CLIENT_FIFO, O_WRONLY);
    int server = open(SERVER_FIFO, O_RDONLY);
    cout << "Подключение к серверу успешно\n";

    char buf[BUFSIZ];
    while (true) {
        cout << "Введите команду: ";
        cin >> buf;

        write(client, buf, sizeof(buf));
        read(server, buf, sizeof(buf));
        printf("Ответ: %s\n", buf);
        if (strcmp(OFF, buf) == 0) {
            break;
        }
        memset(buf, 0, sizeof(buf));
    }
    close(client);
    close(server);
    return 0;
}
