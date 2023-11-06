#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
#include <iostream>

using namespace std;

const int NUM_OF_THREADS = 4;

void *randomSleep(void *args);

int main() {
    pthread_t threads[NUM_OF_THREADS];

    for (unsigned long &thread: threads) {
        //создание потока
        pthread_create(&thread, nullptr, randomSleep, nullptr);
    }
    for (unsigned long thread: threads) {
        //Ожидание завершения потока. Главный поток будет заблокирован на выполнение,
        //пока созданный в нем поток не завершит работу. Но данная функция никак не синхронизирует
        //несколько одноуровневых потоков, созданных от главного.
        pthread_join(thread, nullptr);
        cout << "PID -" << thread << endl;
    }
}

void *randomSleep(void *args) {
    sleep(2 + rand() % 10);
    return nullptr;
}
