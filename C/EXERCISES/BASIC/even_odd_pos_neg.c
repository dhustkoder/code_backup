#include <stdio.h>
enum { evens, odds, positives, negatives };
static int results[4];
static int input[5];


int main()
{

	scanf("%i%*c%i%*c%i%*c%i%*c%i",
		&input[0], &input[1], &input[2], &input[3],
		&input[4]);

	int i = 0;
	for(; i < 5; ++i)
	{
		if(input[i] == 0) {
			++results[evens];
			continue;
		}

		if((input[i] % 2) == 0)
			++results[evens];
		else
			++results[odds];

		if(input[i] > 0)
			++results[positives];
		else if(input[i] < 0)
			++results[negatives];
	}


	printf("%i valor(es) par(es)\n%i valor(es) impar(es)\n%i valor(es) positivo(s)\n%i valor(es) negativo(s)\n",
		results[evens], results[odds], results[positives], results[negatives]);


	return 0;


}