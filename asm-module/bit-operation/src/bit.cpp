#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	int x, result = 0;
	cout << "Введите число: ";
	cin >> x;
	_asm {
		mov eax, x
		mov edx, 1
		add eax, edx
		and eax, x
		jnz notdegreetwo
		mov result, 1
		notdegreetwo:
	}
	if (result > 0) cout << "Удовлетворяет условию" << endl;
	else cout << "Не удовлетворяет условию" << endl;
	return 0;
}
