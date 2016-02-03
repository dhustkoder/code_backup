#include <stdio.h>

typedef struct Sides
{
	float a, b, c;
}sides_t;
int isTriangle(sides_t*);



int main()
{
	static sides_t sides;
	scanf("%f %f %f", &sides.a, &sides.b, &sides.c);

	if (isTriangle(&sides))
		printf("Perimetro = %.1f\n", sides.a + sides.b + sides.c);
	else
		printf("Area = %.1f\n", ((sides.a + sides.b) * sides.c) * 0.5f);
	
	return 0;
}


int isTriangle(sides_t* sides)
{
	return (sides->a + sides->b) > sides->c
		&& (sides->a + sides->c) > sides->b
		&& (sides->b + sides->c) > sides->a;
}



