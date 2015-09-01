section .data
i: dd 128

msg: db "the value of i is %d",10,0

section .text

extern fprintf ;
global main


main:
    push ebp
    mov ebp, esp
    push DWORD [i]
    push msg
    mov ebx,1
    push ebx
    call fprintf
    mov esp,ebp
    pop ebp
    ret
