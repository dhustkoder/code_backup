#include <stdio.h>

void calculate(double);

int main()
{
	float value;
	scanf("%f", &value);
	calculate(value);

	return 0;
}

void calculate(double realValue) 
{
	enum {
		n100, n50, n20, n10, n5, n2,
		c1, c50, c25, c10, c5, c01
	};

	int qnt[12];
	int i = 0;
	for (; i < c01; ++i) {
		qnt[i] = 0;
	}

	qnt[n100] = (int)(realValue / 100);  realValue -= qnt[n100] * 100; if(realValue == 0.00) goto print;
	qnt[n50]  = (int)(realValue / 50);   realValue -= qnt[n50] * 50;   if(realValue == 0.00) goto print;
	qnt[n20]  = (int)(realValue / 20);   realValue -= qnt[n20] * 20;   if(realValue == 0.00) goto print;
	qnt[n10]  = (int)(realValue / 10);   realValue -= qnt[n10] * 10;   if(realValue == 0.00) goto print;
	qnt[n5]   = (int)(realValue / 5);    realValue -= qnt[n5]  * 5;    if(realValue == 0.00) goto print;
	qnt[n2]   = (int)(realValue / 2);    realValue -= qnt[n2]  * 2;    if(realValue == 0.00) goto print;
	qnt[c1]   = (int)(realValue / 1);    realValue -= qnt[c1]  * 1;    if(realValue == 0.00) goto print;
	qnt[c50]  = (int)(realValue / 0.5);  realValue -= qnt[c50] * 0.5;  if(realValue == 0.00) goto print;
	qnt[c25]  = (int)(realValue / 0.25); realValue -= qnt[c25] * 0.25; if(realValue == 0.00) goto print;
	qnt[c10]  = (int)(realValue / 0.10); realValue -= qnt[c10] * 0.10; if(realValue == 0.00) goto print;
	qnt[c5]   = (int)(realValue / 0.05); realValue -= qnt[c5]  * 0.05; if(realValue == 0.00) goto print;
	qnt[c01]  = (int)(realValue / 0.01);  realValue -= qnt[c01] * 0.01;
	if((realValue / 0.01) > 0.000010) ++qnt[c01];

	print:
	printf("NOTAS:\n");
	printf("%i nota(s) de R$ 100.00\n", qnt[n100]);
	printf("%i nota(s) de R$ 50.00\n",  qnt[n50]);
	printf("%i nota(s) de R$ 20.00\n",  qnt[n20]);
	printf("%i nota(s) de R$ 10.00\n",  qnt[n10]);
	printf("%i nota(s) de R$ 5.00\n",   qnt[n5]);
	printf("%i nota(s) de R$ 2.00\n",   qnt[n2]);
	
	printf("MOEDAS:\n");
	printf("%i moeda(s) de R$ 1.00\n", qnt[c1]);
	printf("%i moeda(s) de R$ 0.50\n", qnt[c50]);
	printf("%i moeda(s) de R$ 0.25\n", qnt[c25]);
	printf("%i moeda(s) de R$ 0.10\n", qnt[c10]);
	printf("%i moeda(s) de R$ 0.05\n", qnt[c5]);
	printf("%i moeda(s) de R$ 0.01\n", qnt[c01]);


}


