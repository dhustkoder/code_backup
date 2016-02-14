#include <stdio.h>

int main()
{

	static int i;
	int input;
	int evenCount = 0;
	for( i = 0; i < 5 ; ++i) {
		scanf("%i", &input);
		if((input % 2) == 0)
			++evenCount;
	}

	printf("%i valores pares\n", evenCount);


}