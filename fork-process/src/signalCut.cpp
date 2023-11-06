#include <unistd.h>
#include <csignal>
#include <iostream>

using namespace std;

void sigInt(int sig) {
    //получаем сигнал и игнорируем его
    signal(SIGINT, SIG_IGN);
    cout << "Получен сигнал SIGINT\n";
}

void sigUsr1(int sig) {
    signal(SIGUSR1, SIG_IGN);
    cout << "Получен сигнал SIGUSR1\n";
}

void sigKill(int sig) {
    //SIGKILL нельзя игнорировать
    signal(SIGKILL, SIG_IGN);
    cout << "Получен сигнал SIGKILL\n";
}

int main() {
    std::cout << getpid() << endl;
    signal(SIGINT, sigInt);
    signal(SIGUSR1, sigUsr1);
    signal(SIGKILL, sigKill);

    while (true);
}
