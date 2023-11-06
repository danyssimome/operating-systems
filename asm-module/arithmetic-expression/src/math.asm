.586	;набор операций для процессора 80586
.MODEL flat, stdcall	;набор и типы сегментов

Include kernel32.inc	;библиотеки
Include masm32.inc
IncludeLib kernel32.lib
IncludeLib masm32.lib

.CONST	;константы
	
.DATA	;инициализированные переменные
	Input DB 'Input Arguements',13,10,0 ; 13,10 - команды переноса строки
	Result DB 'Result=' 
	ResStr DB 16 DUP (' '),0 ;строка в которую конверитруют ответ из переменной
.DATA?	;неинициализированные данные
	A SWORD ? ;оставляет место для вводимой переменной 
	B SWORD ?
	D SWORD ?
	E SWORD ?
	
	Buffer DB 10 DUP(?)
	inbuf DB 16 DUP(?)
.CODE
Start: 
	Invoke StdOut,ADDR Input ;Вывод сообщения
	
	Invoke StdIn,ADDR Buffer,LengthOf Buffer ; Ввод строки
	Invoke atol,ADDR Buffer ;Строка в число 
	mov DWORD PTR A,EAX ;Запись числа по адресу А
	
	Invoke StdIn,ADDR Buffer,LengthOf Buffer
	Invoke atol,ADDR Buffer
	mov DWORD PTR B,EAX
	
	Invoke StdIn,ADDR Buffer,LengthOf Buffer
	Invoke atol,ADDR Buffer
	mov DWORD PTR D,EAX
	
	Invoke StdIn,ADDR Buffer,LengthOf Buffer
	Invoke atol,ADDR Buffer
	mov DWORD PTR E,EAX
	
	;Предостережение:
	;В зависимости от операции, которую ты проводишь(+/-/*...), используются РАЗНЫЕ регистры!!!
	;Так же очень выжен момент с разрядностью этих регистров(ax/EAX)
	;А именно ОПРЕДЕЛЕННЫЙ ТИП ДАННЫХ РАБОТАЕТ ТОЛЬКО С ОПРЕДЕЛЕННЫМ РЕГИСТРОМ (16 разряд тип данных с 16 разрядным регистром и тд)
	;---------------------------------------
	; X=a/b+2*c/d
	;	1)a/b
	mov ax,A
	mov dx,0
	mov bx,B
	div bx
	mov A,ax
	;	2)c/d
	mov ax,D
	mov dx,0
	mov bx,E
	div bx
	mov D,ax
	;	3)2*c/d
	mov dx,D
	mov ax,2
	imul ax,dx
	mov D,ax
	;	4)a/b+2*c/d
	mov ax,A
	mov dx,D
	add ax,dx
	mov A,ax
	;---------------------------------------
	Invoke dwtoa,A,ADDR ResStr ;Число в строку
	Invoke StdOut,ADDR ResStr ;Вывод строки
	
	Invoke StdIn,ADDR inbuf,LengthOf inbuf ;Ввод
	Invoke ExitProcess,0 ;Выход с кодом 0
End Start
