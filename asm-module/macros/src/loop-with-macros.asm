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
	NumberFibbonachi SWORD ? ;оставляет место для вводимой переменной (вводим вещественное число)
	
	Buffer DB 10 DUP(?)
	inbuf DB 16 DUP(?)
.CODE
Start: 
	
	Invoke StdIn,ADDR Buffer,LengthOf Buffer 
	Invoke atol,ADDR Buffer 
	mov NumberFibbonachi,AX
	
	.while NumberFibbonachi > 0
	
		mov AX,firstFibbonachi
		mov DX,secondFibbonachi
		add AX,DX
		
		mov BX,secondFibbonachi
		mov firstFibbonachi,BX
		
		mov secondFibbonachi,AX
	
     	Invoke dwtoa,secondFibbonachi,ADDR ResStr
     	invoke StdOut,ADDR ResStr
     	invoke  crt_printf, ADDR space
     	sub NumberFibbonachi,1
   	.endw
	
	Invoke StdIn,ADDR inbuf,LengthOf inbuf 
	Invoke ExitProcess,0 
	
End Start
