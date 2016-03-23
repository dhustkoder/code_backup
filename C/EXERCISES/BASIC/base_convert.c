#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char* get_bin_str(int number)
{
	static char binary_str_zero[2] = {'0', '\0'};
	static char binary_str[32];
	if(number == 0) return binary_str_zero;
	
	static int i, j;
	unsigned char zero_on = 0;
	for( i = j = 0; i < 32; ++i)
	{
		if(number & 0x80000000) 
		{ 
			binary_str[j++] = '1';
			zero_on = 1;
		}
		else if(zero_on) binary_str[j++] = '0';
		
		number <<= 1;
	}
	
	binary_str[j] = '\0';
	return binary_str;
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
		printf("Case %d:\n", ++i);
		switch(inputLine[strlen(inputLine) - 2])
		{
			case 'c': 
				sscanf(inputLine, "%d", &input); 
				printf("%x hex\n%s bin\n", input, get_bin_str(input));  
				break;

			case 'x': 
				input = strtol(inputLine, NULL, 16);
				printf("%d dec\n%s bin\n", input, get_bin_str(input));
				break;
			
			case 'n': 
				input = strtol(inputLine, NULL, 2);
				printf("%d dec\n%x hex\n", input, input); 
				break;
		}
		printf("\n");
	}




	return 0;
}