#include <stdio.h>

static int vars[3];
enum { N, i, j };
int main()
{
	scanf("%i", &vars[N]);
	for( vars[i] = 0, vars[j] = 1; vars[i] < vars[N]; ++vars[i])
	{
		printf("%i %i %i PUM\n", vars[j], vars[j]+1, vars[j]+2);
		vars[j]+=4;
	}
}
