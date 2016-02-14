#include <stdio.h>


int main()
{

	static int i;
	static int posCount = 0;
	float inputNumber;	
	float posTotal = 0;
	for(i = 0; i < 6; ++i)
	{
		scanf("%f", &inputNumber);
		
		if(inputNumber > 0)
		{
			posTotal += inputNumber;
			++posCount;
		}
	}

	printf("%i valores positivos\n", posCount);
	if(posCount > 0)
		printf("%.1f\n", posTotal / posCount);
	else
		printf("0\n");

}
