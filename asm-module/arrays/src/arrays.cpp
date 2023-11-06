#include <iostream>
using namespace std;

int main()
{
	setlocale(LC_ALL, "r");
	const int len = 8;
	int mass[len];
	int massCopy[len];
	for (int i = 0; i < len; i++){
		cout << "mass[" << i << "]=";
		cin >> mass[i];
	}
	_asm
	{
		// xor ebx, ebx
		// xor ecx, ecx
		lea esi, mass //���������� ����� mass
		lea edi, massCopy // ���������� ����� massCopy
		mov ecx, len
		cycle :
		mov edx, [esi]
			test edx, 01H
			jnz NOT_EVEN_NUMBER
			mov eax, 10
			imul eax, edx
			mov[edi], eax
			jmp offsetend
			NOT_EVEN_NUMBER :
		mov[edi], edx
			offsetend :
		add esi, 4 // �������� �� ���������� �������� 4 - ������ ��� ������ �������� - 4 �����.
			add edi, 4
			loop cycle
	}
	for (int i = 0; i < len; i++) {
		cout <<  massCopy[i] << " ";
	}
}
