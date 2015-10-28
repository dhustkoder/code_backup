section .data ; initialize data
	msg: db 'Hello world, using printf', 0xa, 0 ; this is our message

section .text  	
    extern printf 	; declare printf as extern
	global main 	; for gcc

main:
    push ebp
    mov ebp, esp    
    push msg
    call printf

    mov esp, ebp
    pop ebp
	mov eax, 1
    mov ebx, 0
	int 0x80
