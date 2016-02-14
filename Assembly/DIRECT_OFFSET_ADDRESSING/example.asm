section .data
	BYTE_TABLE DB 14, 65, 22, 45 ; tables of bytes







section .text
	global _start

_start:
	mov ecx, BYTE_TABLE + 1 ; ( access BYTE_TABLE[1] )
	mov eax, 4
	mov ebx, 1
	mov edx, 1
	int 0x80

	mov eax, 1
	mov ebx, 0
	int 0x80
