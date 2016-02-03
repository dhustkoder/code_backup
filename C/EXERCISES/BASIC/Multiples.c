#include <stdio.h>

int isMultiple(int a, int b);

int main()
{
	int a, b;
	scanf("%i %i", &a, &b);

	if (isMultiple(a, b))
		printf("Sao Multiplos\n");
	else
		printf("Nao sao Multiplos\n");
	
	return 0;
}


int isMultiple(int a, int b) {
	return (a % b == 0) || (b % a == 0);
}