#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>



typedef char byte;


struct Pessoa
{
	int32_t idade;
	int32_t habilidade;
};
typedef struct Pessoa Pessoa;


int main()
{
	// Pessoa na memoria :  [  int ( 4 bytes )  |   int ( 4 bytes )  ]
		
	Pessoa slash;

	void* ptr = &slash; // aponta  > [          8 bytes           ]
				       //10, 11, 12, 13, 14, 15, 16, 17
	
	*((int*)ptr) = 50;

	printf("valor dos primeiros 4 bytes : %i \n", *((int*)ptr));
	
	( *( (byte**) &ptr) ) += 4;

	*((int*)ptr) = 99;	

	printf("valor dos ultimos 4 bytes : %i \n", *((int*)ptr));

}
