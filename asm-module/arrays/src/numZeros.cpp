#include <iostream>
using namespace std;

int main()
{
	setlocale(LC_ALL, "");
	const int length = 8;
	int mass[length], n;
	for (int i = 0; i < length; i++){
		cout << "mass[" << i << "]="; 
		cin >> mass[i];
	}
	_asm
	{
		mov ebx, 0; ������� �����
		lea esi, mass
		mov cx, 8; ������� ������ �� 8
		cycle: 
			cmp[esi], 0
			jnz nxt
			inc ebx
			nxt : 
				add esi, 4; �������� �� ���������� ��������
		loop cycle
		mov n, ebx
	}
	cout << "n=" << n;
}
