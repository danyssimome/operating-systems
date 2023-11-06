#include <iostream>

using namespace std;

int main() {
    string str;
    cout << "Введите символы: ";
    cin >> str;

    int max = 0;
    int buf = 0;
    for (char ch: str) {
        //если нужна проверка на пробелы то: isblank
        if (isalpha(ch)) {
            buf = 0;
            continue;
        }
        buf++;
        if (buf > max)max = buf;
    }
    printf("Максимальная серия - %d", max);
}
