section .data
	BYTE_TABLE db 10, 20, 30, 40, 50

	WORD_TABLE dw 300, 400, 500, 600, 700




section .text
	global _start


_start:
	mov CL, BYTE_TABLE[2]    ; Gets the 3rd element of the BYTE_TABLE, to 8bit low part of ecx
	mov CL, BYTE_TABLE + 2   ; Again, Gets the 3rd element of the BYTE_TABLE

	mov CX, WORD_TABLE[3]    ; Gets the 4rd element of the WORD_TABLE, to the half 16-bit part of ecx
	mov CX, WORD_TABLE + 3   ; Again, Gets the 4rd element of the WORD_TABLE




