#include <stdio.h>





int main()
{

	int i = 0;

	for(; i < 20;++i)
	{
		if(i < 10)
			continue;
		else
			fprintf(stdout,"%i ",i);

	}


}
