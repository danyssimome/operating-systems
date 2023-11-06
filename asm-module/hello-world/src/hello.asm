.586	;набор операций для процессора 80586
.MODEL flat, stdcall	;набор и типы сегментов

Include kernel32.inc	;библиотеки
Include masm32.inc
IncludeLib kernel32.lib
IncludeLib masm32.lib

.CONST	;константы
	
.DATA	;инициализированные переменные
	Message DB 'Hello World'
	
.DATA?	;неинициализированные данные
	inbuf DB 100 DUP (?);идет резервация 100 байт данных(DB) с повтором (DUP) в неограниченное кол-во раз
	
.CODE
Start: 
	Invoke StdOut,ADDR Message ;Вывод строки,без задержки консоли(видно при отладке)
	Invoke StdIn,ADDR inbuf,LengthOf inbuf ;Ввод enter, который задерживает консоль
	Invoke ExitProcess,0 ;Выход с кодом 0
End Start
	