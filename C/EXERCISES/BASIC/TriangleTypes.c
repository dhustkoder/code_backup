#include <stdio.h>
#include <math.h>

typedef struct Sides {
	double a, b, c;
	int typesSize;
	const char* types[6];
}Sides;

void classifyTriangle(Sides*);

int main()
{
	static Sides sides;
	scanf("%lf %lf %lf", &sides.a, &sides.b, &sides.c);
	classifyTriangle(&sides);

	int i = 0;
	for (; i < sides.typesSize; ++i) {
		printf("%s\n", sides.types[i]);
	}


	return 0;
}


int isNotTriangle(Sides*);
int isRectangle(Sides*);
int isObtuse(Sides*);
int isAcutangle(Sides*);
int isEquilateral(Sides*);
int isIsosceles(Sides*);

void classifyTriangle(Sides* sides)
{
	sides->typesSize = 0;
	if (isNotTriangle(sides)) {
		sides->types[sides->typesSize++] = "NAO FORMA TRIANGULO";
		return;
	}

	if (isRectangle(sides))
		sides->types[sides->typesSize++] = "TRIANGULO RETANGULO";

	else if (isObtuse(sides))
		sides->types[sides->typesSize++] = "TRIANGULO OBTUSANGULO";

	else if (isAcutangle(sides))
		sides->types[sides->typesSize++] = "TRIANGULO ACUTANGULO";

	if(isEquilateral(sides))
		sides->types[sides->typesSize++] = "TRIANGULO EQUILATERO";
		
	else if (isIsosceles(sides)) 
		sides->types[sides->typesSize++] = "TRIANGULO ISOSCELES";
}


int isNotTriangle(Sides* sides) {
	return (sides->a >= (sides->b + sides->c))
		|| (sides->b >= (sides->a + sides->c))
		|| (sides->c >= (sides->a + sides->b));
}

int isRectangle(Sides* sides) {
	return (pow(sides->a, 2) == (pow(sides->b, 2) + pow(sides->c, 2)))
		|| (pow(sides->b, 2) == (pow(sides->a, 2) + pow(sides->c, 2)))
		|| (pow(sides->c, 2) == (pow(sides->a, 2) + pow(sides->b, 2)));
}

int isObtuse(Sides* sides) {
	return (pow(sides->a, 2) > (pow(sides->b, 2) + pow(sides->c, 2)))
		|| (pow(sides->b, 2) > (pow(sides->a, 2) + pow(sides->c, 2)))
		|| (pow(sides->c, 2) > (pow(sides->a, 2) + pow(sides->b, 2)));
}

int isAcutangle(Sides* sides) {
	return (pow(sides->a, 2) < (pow(sides->b, 2) + pow(sides->c, 2)))
		|| (pow(sides->b, 2) < (pow(sides->a, 2) + pow(sides->c, 2)))
		|| (pow(sides->c, 2) < (pow(sides->a, 2) + pow(sides->b, 2)));
}

int isEquilateral(Sides* sides) {
	return sides->a == sides->b && sides->b == sides->c;
}

int isIsosceles(Sides* sides) {
	return (sides->a == sides->b && sides->b != sides->c)
		|| (sides->b == sides->c && sides->c != sides->a)
		|| (sides->c == sides->a && sides->a != sides->b);
}