#include <stdio.h>
#include <stdint.h>

static uint64_t res;
static int N, M;

uint64_t fact(int x)
{
	if(x < 2) return 1;

	for(res = x; x > 1; --x)
		res *= x-1;

	return res;
}


int main(void)
{
	
	while(scanf("%d %d", &N, &M) > 0)
		printf("%llu\n", fact(N) + fact(M));
	
	return 0;
}