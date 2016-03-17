
/*
	Read an integer value X (1 <= X <= 1000).  
	Then print the odd numbers from 1 to X, 
	each one in a line, including X if is the case.
*/

#include <cstdio>



int main(int argc, char** argv)
{
	unsigned int X;
	scanf("%u", &X);

	std::printf("1\n");
	
	for(unsigned int n = 2; n <= X ; ++n)
		if( ( n % 2 ) != 0 )
			std::printf("%u\n", n);





};
