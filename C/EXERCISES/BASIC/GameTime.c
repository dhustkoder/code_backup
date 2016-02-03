#include <stdio.h>


int main()
{
	int from, to, total;

	scanf("%i %i", &from, &to);

	if (from == 0)
		from = 24;
	if (to == 0)
		to = 24;

	if (to <= from)
		total = ((to + 24) - from);
	else if(to > from)
		total = (to - from);

	printf("O JOGO DUROU %i HORA(S)\n", total);

	return 0;
}