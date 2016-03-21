#include <stdio.h>

static int in = 0;
static int out = 0;
static int num;
static int i;

int main()
{
	scanf("%i", &i);

	for(; i; --i)
	{
		scanf("%i", &num);
		if( num < 10 || num > 20)
			++out;
		else
			++in;

	}

	printf("%i in\n%i out\n", in, out);
}
