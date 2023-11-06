#include <pthread.h>
#include <iostream>
#include <semaphore.h>
#include <fstream>

using namespace std;

const int NUM_OF_THREADS = 2;
const char FILE_NAME[] = "output.txt";

sem_t semaphore;

void *writeToFile(void *args);

int main() {
    sem_init(&semaphore, 0, 1);

    pthread_t threads[NUM_OF_THREADS];
    for (unsigned long &thread: threads) {
        pthread_create(&thread, nullptr, writeToFile, nullptr);
    }
    for (unsigned long thread: threads) {
        pthread_join(thread, nullptr);
    }

    sem_destroy(&semaphore);
    return 0;
}

void *writeToFile(void *args) {
    sem_wait(&semaphore);

    char str[100];
    cout << "Введите текст: ";
    cin >> str;

    ofstream outputFile;
    //файл ищем в папке build
    outputFile.open(FILE_NAME, std::ofstream::out | std::ofstream::app);
    outputFile << str << endl;
    outputFile.close();

    sem_post(&semaphore);
    return nullptr;
}
