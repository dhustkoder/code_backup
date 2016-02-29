
section .data
	msg: db 'displaying 9 starts:', 0xa 		; a message
	msg_len: equ $ - msg 				; lenght of message
	s2: times 9 db '*' 				; the starts
	endl: db 0x0a 					; end line value ( to break the line )

section .text
	global _start 					; must be declared for linker (ld) (gcc)

_start:
	mov edx, msg_len 	;
	mov ecx, msg 		;
	mov eax, 4 		; call ( sys_write )
	mov ebx, 1 		; specify file decripter ( stdout )
	int 0x80 			; call kernel
	

	mov edx, 9 		; specify number of starts
	mov ecx, s2 		; specify the character
	mov eax, 4 		; sys_write call
	mov ebx, 1 		; stdout
	int 0x80 			; call kernel

	mov edx, 1 		; endline is 1 character
	mov ecx, endl 		; endline value
	mov eax, 4 		; sys_write
	mov ebx, 1 		; stdout
	int 0x80

	
	mov eax, 1 		; system call number ( sys_exit )
	mov ebx, 0 		; exit value. no errors
	int 0x80 			; call kernel


