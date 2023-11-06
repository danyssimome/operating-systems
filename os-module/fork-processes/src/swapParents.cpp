#include "iostream"
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main() {
    //Присваивает идентификатор группы процессов pgid тому процессу, который был определен pid.
    //Если значение pid равно нулю, то процессу присваивается идентификатор текущего процесса
    setpgrp();
    setsid();//приводит к созданию новой группы, состоящей только из процесса, который его выполнил.

    int childPid = fork();//Новый процесс(Весь код после fork() выполняется дважды в потомке и родителе)
    //system("ps >> file.txt");
    //setsid();// так как программа вызовется повторно для дочернего процесса, то сделаем его главным
    switch (childPid) {
        case -1: {
            cout << "Error";
            break;
        }
        case 0: {
            cout << "---CHILD PROCESS---" << "\n"
                 << "Child PID: " << getpid() << endl
                 << "Father PID: " << getppid() << endl;
            break;
        }
        default: {
            cout << "---FATHER PROCESS---" << endl
                 << "Father PID: " << getpid() << endl
                 << "Child PID: " << childPid << endl << endl;
            wait(nullptr);
        }
    }
    return 0;
}
