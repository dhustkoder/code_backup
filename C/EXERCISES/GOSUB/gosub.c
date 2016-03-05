/* original idea by Bisqwit: youtube.com/user/Bisqwit */
#include <stdio.h>

void* gosub_stack_ptr[10];
unsigned int gosub_stack_counter = 0;






int main()
{
	#define GOSUB(target) { __label__ n; gosub_stack_ptr[gosub_stack_counter++] = &&n; goto target; n:; }
	#define RETURN_FROM_LABEL() { if(gosub_stack_counter){ void*r = gosub_stack_ptr[gosub_stack_counter--]; goto *r; } }

	GOSUB(print_A);
	

	puts("SECOND LINE");
	
	return 0;	


	print_A:
		puts("FIRST LINE!");
		RETURN_FROM_LABEL();

}



