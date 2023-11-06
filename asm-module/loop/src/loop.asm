.586
.MODEL flat, stdcall

include masm32.inc
include msvcrt.inc
include win32k.inc
include kernel32.inc

includelib masm32.lib
includelib kernel32.lib
includelib win32k.lib
includelib msvcrt.lib

.CONST	
	
.DATA	
	ResStr DB 16 DUP (' '),0 ;строка в которую конверитруют ответ из переменной
	firstFibbonachi SWORD 0
	secondFibbonachi SWORD 1
	space SWORD ' '
.DATA?	
	NumberFibbonachi DW ? ;оставляет место для вводимой переменной (вводим вещественное число)
	
	Buffer DB 10 DUP(?)
	inbuf DB 16 DUP(?)
.CODE
Start: 
	
	Invoke StdIn,ADDR Buffer,LengthOf Buffer 
	Invoke atol,ADDR Buffer 
	mov NumberFibbonachi,AX
	;Где label — это метка, которая идентифицирует целевую инструкцию. 
	;Инструкция LOOP предполагает, что регистр ECX содержит в себе счетчик циклов. 
	;Когда инструкция цикла выполняется, регистр ECX уменьшается, 
	; точка выполнения программы переходит к метке до тех пор, пока значение регистра ECX  не достигнет нуля
	;---------------------------------------
	; Ввести с клавиатуры число N и вывести первые N чисел Фибоначчи
	
	mov CX,NumberFibbonachi ;записали введенные данные в счетчик ECX	
	cycle:
		mov AX,firstFibbonachi
		mov DX,secondFibbonachi
		add AX,DX
		
		mov BX,secondFibbonachi
		mov firstFibbonachi,BX
		
		mov secondFibbonachi,AX
		push ecx
		Invoke dwtoa,secondFibbonachi,ADDR ResStr 
		Invoke StdOut,ADDR ResStr 
		invoke  crt_printf, ADDR space
		pop ecx
	loop cycle
	
	
	;Важный момент - Invoke вызывает метод с помощью соглашения о вызове __stdcall. 
	;Частью этого соглашения является то, что EAX, ECX и EDX не сохраняются во время этого вызова.
	;Вот почему регистры eax не уменьшаются и не приводят к остановке цикла
	;Invoke dwtoa,secondFibbonachi,ADDR ResStr 
	;Invoke StdOut,ADDR ResStr 
	
	Invoke StdIn,ADDR inbuf,LengthOf inbuf 
	Invoke ExitProcess,0 
	
End Start
