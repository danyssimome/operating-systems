counting macro adress, countr
		LOCAL checknum 
		LOCAL cheksymb 
		LOCAL lable
		LOCAL ex
		lea esi, adress
		checknum:
			cmp byte ptr [esi], 0 ;конец строки (либо поставь 13 - каретак перехода на новую строку)
			je ex
			cmp byte ptr [esi], '0';при косвенной адресации надо явно конвертировать данные
			jb lable	
			cmp byte ptr [esi], '9'
			ja cheksymb 
			inc esi
			jmp checknum
			jmp ex
		cheksymb:
			cmp byte ptr [esi], 'a'
			jb lable
			cmp byte ptr [esi], 'z'
			ja lable
			inc esi
			jmp checknum
		lable :
			inc eax 
			inc esi 
			jmp checknum
		ex:	
endm

.586
.MODEL flat, stdcall
OPTION CASEMAP:NONE 
Include kernel32.inc
Include masm32.inc
IncludeLib kernel32.lib
IncludeLib masm32.lib
.CONST
MsgExit DB 13,10,"Press Enter to Exit",0AH,0DH,0
.DATA
	Result DB 'Result=' 
	ResStr DB 0,0
	countr DWORD 0,0
	countr2 DWORD 0,0
	ZaprosA DB 13,10,'Input STR',13,10,0
.DATA?
	str1 DB 256 DUP (?)

	Buffer DB 10 DUP (?)
	inbuf DB 100 DUP (?)
.CODE

START:
	Invoke StdOut, ADDR ZaprosA
	Invoke StdIn, ADDR str1, 100
	; —-----------------—
	xor eax, eax
	xor esi, esi
	
	counting str1, countr
	mov countr,eax
	; —-----------------—
	Invoke dwtoa,countr,ADDR ResStr 
	Invoke StdOut,ADDR Result
	
	XOR EAX,EAX
	Invoke StdOut,ADDR MsgExit ;??? ?????????? Enter
	Invoke StdIn,ADDR inbuf,LengthOf inbuf ;????
	Invoke ExitProcess,0 ;????? ? ????? 0
End START
