; An assembly program can be devided into three sections - 
; 
; -  The DATA section

; - the BSS section

; - The TEXT section


; Text section is used for keeping te actual code. this section must begin with the declaration
; global _start, which tells the kernel where the program execution begins

section .text

global _start

_start:
	mov eax, 4
	mov ebx, 1
	mov ecx, string
	mov edx, length
	int 80h
	
	mov eax, 1
	mov ebx, 0
	int 80h


section .data
	string: db 'Hello Asm', 0Ah
	length: equ 8

	; The data section, is used for declaring initialized data or constants. this data
	; does not change at runtime. you can declare various constants values, file names,
	; or buffer size, etc.. , in this section is - 
