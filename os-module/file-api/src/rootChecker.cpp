#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <dirent.h>
#include <cstring>

using namespace std;

int main() {
    char folder[BUFSIZ];
    cout << "Введите полный путь до папки: ";
    cin >> folder;

    DIR *dir;
    struct dirent *ent;
    char path[100];
    if ((dir = opendir(folder)) != nullptr) {//получаем каталог с записями
        cout << "Для каталога " << folder << " разрешено на чтение и исполнение у файлов: " << endl;
        while ((ent = readdir(dir)) != nullptr) {//возвращаем указатель на след запись каталога
            strcpy(path, folder);//копирование пути папки(с полным затиранием пред. данных)
            strcat(path, "/");
            strcat(path, ent->d_name);

            //проверяет, имеет ли процесс права на чтение или запись, или же просто проверяет, существует ли файл
            if (access(path, R_OK) == 0 && ent->d_name[0] != '.' && ent->d_name[0] != '..') {
                printf("%s\n", ent->d_name);
            }
        }
        closedir(dir);
    } else perror("Не найден каталог");
}
