section .data ; initialize data

msg: db "Hello world, this is assembly",10,0 ; this is our message

section .text ; asm code
    
extern printf
global main

main:
    push ebp
    mov ebp, esp
    
    push msg
    call printf

    mov esp, ebp
    pop ebp
    ret
