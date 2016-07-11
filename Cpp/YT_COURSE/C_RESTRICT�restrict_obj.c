#include <stdio.h>


void foo1(int* volatile p1, int* p2) {
	printf("p2 before: %i\n", *p2);
	*p1 = 888;
	printf("p2 after: %i\n", *p2);
}


void foo2(int* volatile restrict p1, int* restrict p2) {
	printf("p2 before: %i\n", *p2);
	*p1 = 888;
	printf("p2 after: %i\n", *p2);
}







