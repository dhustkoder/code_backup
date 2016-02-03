#include <stdio.h>


int main()
{
	enum { hfrom, mfrom, hto, mto, htotal, mtotal };
	static int times[6];

	scanf("%i %i %i %i", &times[hfrom],
		&times[mfrom], &times[hto], &times[mto]);

	int i = 0;
	for (; i < hto + 1; ++i) {
		if (times[i] == 0 && (i == hfrom || i == hto))
			times[i] = 24;
	}


	if (times[hto] <= times[hfrom])
		times[htotal] = (times[hto] + 24) - times[hfrom];

	else
		times[htotal] = times[hto] - times[hfrom];


	if (times[mto] < times[mfrom]) {
		times[mtotal] = (times[mto] + 60) - times[mfrom];
		--times[htotal];
	}

	else if (times[mto] > times[mfrom])
		times[mtotal] = times[mto] - times[mfrom];

	else
		times[mtotal] = 0;


	printf("O JOGO DUROU %i HORA(S) E %i MINUTO(S)\n", times[htotal], times[mtotal]);

	return 0;
}