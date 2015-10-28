



; Syntax Of Assembly Statements

; Assembly statements are entered one per line. each one  follows the following format:

; [label] mnemonic [operands] [; comment]

; the fields in the square brackets are optional, A basic instruction has 2 parts

; 1. Name of the instruction ( mnemonic ) 

; 2. operands or parameter of the first command


; lets see some typical assembly statements


section .bss
COUNT: dw
TOTAL: dw 
MASK1: dw 
MARKS: dw 

section .text
	global _start

_start:
	inc [COUNT],1 	; Increment the memory variable COUNT

	mov TOTAL, 48 	; transfer value 48 to memory variable TOTAL
	
	add ah, bh 	; add the content of BH register to AH register


	and MASK1, 128 	; perform AND operation on variable MASK1 and 128


	add MARKS, 10 	; add 10 to the variable MARKS



	mov al, 10 	; transfer value 10 to the al register

	mov eax, 1
	mov ebx, 0
	int 0x80
