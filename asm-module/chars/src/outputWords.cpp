#include <iostream>
using namespace std;

int main2(){
	setlocale(LC_ALL, "Russian");
	char line[11] = "erg sf s g";
	//cout << "Введите текст: ";
	//cin.getline(line, 256);
	int len = strlen(line);
	char newLine[256] = "";
	int countr = 0, len2 = len;
	_asm{
		xor ebx, ebx	; обнуление регистра
		xor ecx, ecx
		lea edi, line
		mov ecx, len 
		mov eax, ' ';
		cld
		m1 :
			repne scasb
			jnz outp
			cmp countr, 2
			je ex
			inc countr;
			test ecx, ecx
			jnz m1
		ex :
			sub len2, ecx
			jmp outp
		outp :
			lea esi, line
			lea edi, newLine
			mov ecx, len2
			rep movsb
	}
	cout << "Итог: " << newLine << endl;
	return 0;
}
