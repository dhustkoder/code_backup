#include <stdio.h>
#include <math.h>


enum { inputSz, i, j, aux };

static int buff[200];
static int vars[4];
int main()
{
	scanf("%i", &vars[inputSz]);
	for(vars[i] = 0; vars[i] < vars[inputSz]; ++vars[i])
	{
		scanf("%i", &buff[vars[i]]);
	}

	for(vars[i] = 0; vars[i] < vars[inputSz]; ++vars[i])
	{
		if(buff[vars[i]] > 1) 
		{
			vars[aux] = sqrt(buff[vars[i]]);
		
			for( vars[j] = 2; vars[j] <= vars[aux]; ++vars[j])
			{
				if((buff[vars[i]] % vars[j]) == 0)
				{
					vars[j] = 0;
					break;
				}
			}
		}
		else vars[j] = 0;

		if(vars[j] == 0)	
			printf("Not Prime\n");
		else
			printf("Prime\n");
	}


	return 0;
}