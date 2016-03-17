/*
	Read an integer value X and print the 6 consecutive odd numbers from X, 
	a value per line,  including X if it is the case.
*/

#include <cstdio>


int main()
{
	unsigned int X;
	std::scanf("%u", &X);

	unsigned int contimes;

	for(unsigned int n = X; contimes < 6; ++n) 
	{
		if( (n % 2) != 0 ) 
		{
			std::printf("%u\n", n);
			++contimes;
		}
	}


}