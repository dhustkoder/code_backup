



section .data
	BYTE_VALUE DB 150    ; a  byte value is defined
	WORD_VALUE DW 300    ; a word value is defined


section .text
	global _start


_start
	;  An immediate operand has a contant value or an expression. 
	;  When an instruction with 2 operand uses immediate addressing, the first operand
	;  may be a register or memory location, and the second is the immediate constant


	add BYTE_VALUE, 65h ; an immediate operand 65h us added
	mov ax, 45h        ; an immediate contant 45h is transfered to ax
	
	mov eax, 1
	mov ebx, 0
	int 0x80
