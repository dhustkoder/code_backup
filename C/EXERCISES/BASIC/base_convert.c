#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_bin(int number)
{
	
	if(number != 0)
	{
		int i = 0;
		unsigned char zero_on = 0;
		for(; i < 32; ++i)
		{
			if(number & 0x80000000) 
			{ 
				printf("1");
				zero_on = 1;
			}
			else if(zero_on) printf("0");
			number <<= 1;
		}
	}

	else
		printf("0");


	printf(" bin\n");
	return;
}


static int inputSize;
static int input;
static char inputLine[64];

int main()
{
	scanf("%i\n", &inputSize);
	static int i = 0;
	for( ; inputSize; --inputSize)
	{
		fgets(inputLine, sizeof(inputLine), stdin);
		sscanf(inputLine, "%i", &input);
		printf("case %d:\n", ++i);

		switch(inputLine[strlen(inputLine) - 2])
		{
			case 'c': printf("%x hex\n", input); print_bin(input); break;
			case 'x': printf("%d dec\n", input); print_bin(input); break;
			case 'n': printf("%d dec\n%x hex\n", input); break;
		}
	}




	return 0;
}