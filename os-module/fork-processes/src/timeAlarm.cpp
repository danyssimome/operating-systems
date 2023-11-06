#include "iostream"
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

void writeTime();
void alarmEvent(int var);

int main() {
    int seconds = 2 + rand() % 4;
    printf("Alarm seconds = %d", seconds);
    writeTime();//первый вывод времени
    signal(SIGALRM, alarmEvent);//указывает что сделать, когда в системе возникнет сигна
    alarm(seconds);//указывает системе сгенерировать сигнал SIGALRM через время

    while (true);
}

/**Обработчик сигнала*/
void alarmEvent(int var) {
    writeTime();
}

void writeTime() {
    char buffer[80];
    time_t seconds = time(nullptr);
    tm *timeInfo = localtime(&seconds);
    strftime(buffer, 80, "%H:%M:%S", timeInfo);
    cout << buffer << endl;
}
