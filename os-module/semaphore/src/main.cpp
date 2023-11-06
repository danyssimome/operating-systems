#include <sys/ipc.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#define memory_size 50

using namespace std;

const int STOP = 10;
char *addr;
sem_t semaphore;

void addition(const string &msg);

int main() {
    int shm = shm_open("semaphore", O_CREAT | O_RDWR, 0777);//создает и открывает объект разделяемой памяти POSIX
    ftruncate(shm, memory_size + 1);//задаем размер разделяемой памяти
    //выделяем область памяти и отображаем ее в виртуальное адресное пространство вызывающего процесса,
    //чтобы приложение могло получить доступ к памяти.
    addr = (char *) mmap(nullptr,
                         memory_size + 1,
                         PROT_WRITE | PROT_READ,
                         MAP_SHARED,
                         shm,
                         0
    );
    //инициализируем первые n байтов той области памяти, на которую указывает s
    memset(addr, 0, sizeof(int));

    //инициализация неименованного семафора
    sem_init(&semaphore, 0, 1);
    //форкаем процесс, и костылем запускаем процессы - в одном childUp, в другом fatherUp
    int pid = fork();
    if (pid == 0) {
        addition("child");
    } else addition("father");

    //удаляем семафор и закрываем доступ к памяти
    sem_destroy(&semaphore);
    munmap(addr, memory_size);
    close(shm);
    unlink(addr);
    return 0;
}

/**
 * Увеличение счетчика на единицу
 *
 * @param msg сообщение потока
 */
void addition(const string &msg) {
    int buf = 0;
    while (buf < STOP) {
        //перекрываем доступ другим потокам к этому куску кода
        sem_wait(&semaphore);

        memcpy(&buf, addr, sizeof(int));
        buf += 1;
        //копирует n байтов из области памяти src в область памяти dest.
        memcpy(addr, &buf, sizeof(int));
        cout << msg + " up to: " << buf << endl;
        sleep(1);

        //освобождаем семафор - даем доступ
        sem_post(&semaphore);
    }
}
