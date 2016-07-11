#include <stdio.h>

extern "C" {
extern void foo1(int* p1, int* p2);
extern void foo2(int* __restrict p1, int* __restrict p2);
}

int main(void) {

	int x = 10;
	printf("foo1: \n");
	foo1(&x, &x);

	int y = 10;
	printf("foo2: \n");
	foo2(&y, &y);
}


