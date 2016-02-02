#include <stdio.h>

int main()
{
	int value;
	scanf("%i", &value);

	int years = value / 365,
		months = (value % 365) / 30,
		days =  (value % 365) % 30;

	printf("%i ano(s)\n%i mes(es)\n%i dia(s)\n",
		years, months, days);
	



	return 0;
}