#include <stdio.h>


int main()
{

	int input = 0;
	while(1)
	{
		scanf("%i", &input);
		if(input != 2002)
			printf("Senha Invalida\n");
		else
		{
			printf("Acesso Permitido\n");
			break;
		}
	}

    return 0;
	

}
