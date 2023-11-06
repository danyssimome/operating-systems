#include <cstdio>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <cstring>
#include <unistd.h>
#include <cerrno>
#include <iostream>
#include "constants.h"

using namespace std;

int main() {
    cout << "Сервер\n";

    //создание уникального ключа сообщения и очереди сообщений, для обмена между потоками
    key_t key = ftok(PATHNAME, PROJ_ID);//создание ключа
    int msqid = msgget(key, 0666 | IPC_CREAT);//создание очереди(если не существует), связанной со значением key

    msgBuffer message{};
    while (true) {
        //записывает сообщение из очереди (идентификатор = msqid)
        //в структуру сообщения msgBuffer(в message), удаляя сообщение из очереди.
        msgrcv(msqid, &message, sizeof(message), REQUEST_TYPE, 0);
        printf("Получено: %s\n", message.text);
        message.type = RESPONSE_TYPE;
        if (strcmp(OFF, message.text) == 0) {
            msgsnd(msqid, &message, sizeof(message), 0);
            break;
        }

        //stat проверяет cсылается ли имя пути на фактический объект(только в данном каталоге),
        //и возвращает информацию об объекте(можно проверить папка или файл и т.д.)
        struct stat info_obj{};
        stat(message.text, &info_obj);
        if (errno == ENOENT) { //если stat кинуло ошибку
            strcpy(message.text, STR_NOTFOUND);
            msgsnd(msqid, &message, sizeof(message), 0);
            errno = 0;//очищаем
            continue;
        } else {//проверяет, имеет ли процесс права на запись
            if (access(message.text, W_OK) == 0) {
                //копирует строку, на которую указывает src в массив dest
                strcpy(message.text, STR_ALLOW);
                //добавляет сообщение, указанное параметром msgp, в очередь сообщений
                msgsnd(msqid, &message, sizeof(message), 0);
                continue;
            } else {
                //изменяет права доступа указанного файла(даем права на запись)
                chmod(message.text, S_IWUSR);
                strcpy(message.text, STR_DENY);
                msgsnd(msqid, &message, sizeof(message), 0);
                continue;
            }
        }
    }
    //удаляем очередь
    msgctl(msqid, IPC_RMID, nullptr);
    return 0;
}
