#include <stdio.h>
#include <math.h>

int bhask(float a, float b, float c, float* r1, float* r2);

int main()
{
	float a = 0, b = 0, c = 0;
	float r1 = 0, r2 = 0;
	scanf("%f %f %f", &a, &b, &c);

	
	if (bhask(a, b, c, &r1, &r2) == 0) {
		printf("R1 = %.5f\n", r1);
		printf("R2 = %.5f\n", r2);
	}
	else
		printf("Impossivel calcular\n");

	

	return 0;
}

int bhask(float a, float b, float c, float* r1, float* r2)
{
	float tosqrt = pow(b, 2) - (4 * (a * c));
	float divisor = 2 * a;

	if (tosqrt < 0)
		return 1;
	else if (divisor == 0)
		return 1;

	*r1 = (-b + sqrtf(tosqrt)) / divisor;
	*r2 = (-b - sqrtf(tosqrt)) / divisor;

	return 0;
}
