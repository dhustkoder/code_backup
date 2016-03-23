#include <stdio.h>
#include <math.h>

int raf_func(register int x, register int y)
{
	return pow(x * 3, 2) + pow(y, 2);
}

int beto_func(register int x, register int y)
{
	return ( pow(x, 2) * 2)  + pow(y * 5, 2);
}

int carl_func(register int x, register int y)
{
	return (-100 * x) + pow(y, 3);
}


static int inputsz;
static int inX, inY, r, b, c;
int main()
{
	scanf("%i", &inputsz);

	for(; inputsz; --inputsz) 
	{
		scanf("%i %i", &inX, &inY);
		r = raf_func(inX, inY);
		b = beto_func(inX, inY);
		c = carl_func(inX, inY);
		if( r > b && r > c) printf("Rafael ganhou\n");
		else if(b > r && b > c) printf("Beto ganhou\n");
		else if(c > r && c > b) printf("Carlos ganhou\n");

	}



}