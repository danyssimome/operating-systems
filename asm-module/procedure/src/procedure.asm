.586
.MODEL flat, stdcall
OPTION CASEMAP:NONE 
include masm32.inc
include msvcrt.inc
include win32k.inc
include kernel32.inc

includelib masm32.lib
includelib kernel32.lib
includelib win32k.lib
includelib msvcrt.lib

.CONST
	MsgExit DB 13,10,"Press Enter to Exit",0AH,0DH,0

.DATA
	mass DWORD 13,4,50
	ResStr DWORD 3 DUP (' '),0
	space DWORD ' '
	sizeArr DWORD 3
.DATA?
	;mass DWORD 3 DUP (?)
	Buffer DB 10 DUP (?)
	inbuf DB 100 DUP (?)
.CODE
	tenXMass proc
		mov ecx, sizeArr
		cycle :
			mov edx, [esi]
			test edx, 01H
			jnz NOT_EVEN_NUMBER
			mov eax, 10
			imul eax, edx
			mov [edi], eax
			jmp offsetend
			NOT_EVEN_NUMBER :
				mov [edi], edx
			offsetend :
				add esi, 4 
				add edi, 4
		loop cycle
		ret
	tenXMass endp

Start:
	;lea esi,mass	;ввод массива
	;mov ecx,sizeArr
	;cycleEnter:
		;push ecx
		;push esi
		;Invoke StdIn,ADDR Buffer,LengthOf Buffer
		;Invoke atol,ADDR Buffer ;?????? ? ?????
		;mov DWORD PTR [esi],EAX ;?????? ????? ?? ??????
		;pop esi
		;add esi, 4
		;pop ecx
	;loop cycleEnter

	;Записываем в регистры массивы через ссылку для передачи в функцию
	lea esi,offset mass
	lea edi,offset ResStr
	call tenXMass

	;так как предача была по ссылке, то значение менялось в функции
	;следовательно просто записываем массив в регистр для вывода
	xor esi,esi
	lea esi,ResStr
	mov ecx,sizeArr
	cycleOut:
		push ecx
		push esi
		Invoke dwtoa,[esi],ADDR ResStr
		Invoke StdOut,ADDR ResStr
		invoke crt_printf, ADDR space
		pop esi
		add esi, 4
		pop ecx
	loop cycleOut
	
	Invoke StdOut,ADDR MsgExit
	Invoke StdIn,ADDR inbuf,LengthOf inbuf
	Invoke ExitProcess,0
End Start
