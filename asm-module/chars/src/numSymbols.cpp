#include <iostream>
using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	char line[12] = "Ad s54@ df$";
	/*cout << "������� �����: ";
	cin.getline(line, 256);*/
	int len = strlen(line);
	int countr = 0;
	_asm {
		xor eax,eax
		lea esi, line
		//cld		; ��������� �������� ����������� ����� �������
		checknum:
			cmp [esi], '\0'	// ������ ����� ������
			je ex
			cmp [esi], '0';
			jb lable	//���� ������ ������ "0", ������ ��� �� �����, ��������� �� �����
			cmp [esi], '9'
			ja cheksymb //���� ������ "9", �������� ��� �����(�� ASCII)
			inc esi
			jmp checknum
		jmp ex
		cheksymb:
			cmp[esi], 'a';
			jb lable; 
			cmp[esi], 'z'
			ja lable; 
			inc esi
			jmp checknum
		lable :
			inc eax //��� �� �����, ������ ������ �� �����,� �� ����� 
			inc esi //������ ������ - ���� ����, ������ ������ ��������������
			jmp checknum;
		ex:
			mov countr,eax
	}
	cout << "����: " << countr << endl;
	return 0;
}
