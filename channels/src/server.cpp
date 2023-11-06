#include <fcntl.h>
#include <cstdio>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <iostream>
#include "constants.h"

using namespace std;

int main() {
    cout << "Сервер\n";

    //Функция mkfifo создает специальный FIFO файл с именем pathname, а параметр mode задает права доступа к файлу.
    //Как только файл создан, любой процесс может открыть этот файл для чтения или записи также,
    //как открывает обычный файл. Однако, для корректного использования файла, необходимо открыть его одновременно
    //двумя процессами/потоками, одним для получение данных (чтение файла), другим на передачу (запись в файл).
    mkfifo(CLIENT_FIFO, 0666);
    mkfifo(SERVER_FIFO, 0666);

    //открытие файлов для двух процессов
    int client = open(CLIENT_FIFO, O_RDONLY);
    int server = open(SERVER_FIFO, O_WRONLY);
    cout << "Клиент подключен\n";

    char buf[BUFSIZ];
    while (true) {
        read(client, buf, BUFSIZ);//читаем из файла
        printf("Получено: %s\n", buf);
        if (strcmp(OFF, buf) == 0) {
            write(server, OFF, sizeof(OFF));
            break;
        }

        //открываем канал и передаем команду оболочке linux
        FILE *fp;
        fp = popen(buf, "r");
        if (fp == nullptr) {
            printf("Ошибка %s", buf);
        }
        //записываем в строку результат команды
        string strBuf;
        char path[BUFSIZ];
        while (fgets(path, sizeof(path), fp) != nullptr) {
            strBuf.append(path);
        }
        pclose(fp);

        //передаем данные, выполненные командой, обратно в канал
        write(server, strBuf.c_str(), BUFSIZ);
        memset(buf, 0, sizeof(buf));//обнуляем сообщение
    }
    close(client);
    close(server);
    unlink(CLIENT_FIFO);
    unlink(SERVER_FIFO);
    return 0;
}
