#include <stdio.h>

int main()
{
	
	static int input;
	static int total = 0;
	static int nOfInputs;
	while(1)
	{
		scanf("%i", &input);
		if(input > 0)
			total+= input, ++nOfInputs;
		else
			break;
	
	}


	printf("%.2f\n", ((float)total / nOfInputs));
}
