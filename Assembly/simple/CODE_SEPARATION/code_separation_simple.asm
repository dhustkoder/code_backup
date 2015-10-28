section .data
	msg: db 'hello', 0xa
	len: equ $ - msg

section .text

	global sys_write	; our code part that will call  sys_write 
	global _start

sys_write:
	mov eax, 4 ; sys_write number
	mov ebx, 1 ; stdout
	int 0x80   ; call kernel
	ret        ; return from this

_start:
	mov ecx, msg
	mov edx, len
	call sys_write ; more simple to call sys_write

	mov eax, 1
	mov ebx, 0
	int 0x80	
