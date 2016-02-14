
section .data
	value_1 db 65
	value_2 db 4
section .bss
	COUNT resb 4


section .text
	global _start


_start:
	; Register Addressing.
	; in this addressing mode, a register contains the operand. Depending upon the instruction,
	; the register may be in first operand, second, or both


	mov eax, value_1    ; register in first operand
	mov ebx, eax        ; register in both
	mov [COUNT], ebx    ; register in second
	add ecx, [COUNT]


	mov eax, 1
	mov ebx, 0
	int 0x80 

