section .data
	var dw 65, 66



section .text
	global _start

_start:

	mov ecx, [var] 
	mov eax, 4
	mov ebx, 1
	mov edx, 2
	
	int 0x80
	

	mov eax, 1
	mov ebx, 0
	int 0x80 
