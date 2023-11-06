#include <iostream>
using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	char line[12] = "Ad s54@ df$";
	/*cout << "Введите текст: ";
	cin.getline(line, 256);*/
	int len = strlen(line);
	int countr = 0;
	_asm {
		xor eax,eax
		lea esi, line
		//cld		; строковая операция выполняется слева направо
		checknum:
			cmp [esi], '\0'	// символ конца строки
			je ex
			cmp [esi], '0';
			jb lable	//если символ меньше "0", значит это не цифра, переходим на метку
			cmp [esi], '9'
			ja cheksymb //если больше "9", возможно это буква(см ASCII)
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
			inc eax //раз мы здесь, значит символ НЕ цифра,и не буква 
			inc esi //символ строки - один байт, значет просто инкрементируем
			jmp checknum;
		ex:
			mov countr,eax
	}
	cout << "Итог: " << countr << endl;
	return 0;
}
