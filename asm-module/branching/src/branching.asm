.586
.MODEL flat, stdcall

Include kernel32.inc	
Include masm32.inc
IncludeLib kernel32.lib
IncludeLib masm32.lib

.CONST	
	
.DATA	
	Input DB 'Input Arguements',13,10,0 ; 13,10 - команды переноса строки
	ResultFalse DB 'False',13,10,0;строки
	ResultTrue DB 'True',13,10,0
.DATA?	
	A DW ? ;оставляет место для вводимой переменной (вводим вещественное число)
	
	Buffer DB 10 DUP(?) ;буфер строка принимающая введенные данные
	inbuf DB 16 DUP(?)
.CODE
Start: 
	Invoke StdOut,ADDR Input ;Вывод сообщения
	
	Invoke StdIn,ADDR Buffer,LengthOf Buffer ; Ввод строки
	Invoke atol,ADDR Buffer ;Строка в число 
	mov A,AX ;Запись числа по адресу А
	
	mov AX,A
	mov DX,0
	mov BX,3
	div BX
	
	CMP DX,0 ; сравниваем остаток с нулем
	JE WriteTrue ;прыжок с условием, если условие CMP верно, то переходим к метке
	
	CMP DX,0 
	JNE WriteFalse ;если условие не CMP верно, то переходим к метке	
	
	WriteTrue:
		Invoke StdOut,ADDR ResultTrue ;Вывод строки
		JMP Exit ;прыжок без условия на выход
	WriteFalse:
		Invoke StdOut,ADDR ResultFalse 
		JMP Exit 
	Exit:
		Invoke StdIn,ADDR inbuf,LengthOf inbuf 
		Invoke ExitProcess,0 
	
End Start
