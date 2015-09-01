section .text               
    global _start

_start:
    mov eax,4           ;
    mov ebx,1           ;
    mov ecx,string      ;
    mov edx,length      ;
    int 0x80h             ;
    mov eax,1           ;
    mov ebx,0           ;
    int 0x80h             ;


section .data
string: db "hello, world"       ;
length: equ 13                  ;
    
