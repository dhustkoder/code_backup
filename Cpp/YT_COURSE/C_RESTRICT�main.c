#include <stdio.h>


extern void foo1(int* p1, int* p2);
extern void foo2(int* restrict p1, int* restrict p2);


int main(void) {

	int x = 10;
	printf("foo1: \n");
	foo1(&x, &x);

	int y = 10;
	printf("foo2: \n");
	foo2(&y, &y);
}



