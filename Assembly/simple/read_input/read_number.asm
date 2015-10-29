



section .data ; data segment
	userMsg: db 'Please enter a number: '
	userMsgLen: equ $ - userMsg
	dispMsg: db 'You have entered: '
	dispMsgLen: equ $ - dispMsg



section .bss ; bss secion unitialized data
	num resb 5
	; The bss section is used for declaring variables.


section .text
	global _start
	global sys_write
	global sys_read

sys_write:
	mov eax, 4 ; sys_write
	mov ebx, 1 ; stdout
	int 0x80   ; kernel call
	ret

sys_read:
	mov eax, 3 ; sys_read
	mov ebx, 2 ; stdin
	int 0x80
	ret

_start:
	mov ecx, userMsg
	mov edx, userMsgLen
	call sys_write

	mov ecx, num
	mov edx, 5           ; 5 bytes ( numeric, 1 for sign) of that information
	call sys_read


	mov ecx, dispMsg
	mov edx, dispMsgLen
	call sys_write

	mov ecx, num
	mov edx, 5
	call sys_write


	; exit
	mov eax, 1
	mov ebx, 0
	int 0x80


