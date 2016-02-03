#include <stdio.h>

void msort(int* arr, int qnt);
static int i = 0;

int main()
{

	int a, b, c;
	scanf("%i %i %i", &a, &b, &c);
	int arr[3] = { a, b, c };
	msort(&arr[0], 3);

	for (i = 0; i < 3; ++i)
		printf("%i\n", arr[i]);

	printf("\n%i\n%i\n%i\n", a, b, c);


	return 0;


}


void msort(int* arr, int qnt)
{
	int j;
	for (i = 0; i < qnt; ++i)
	{
		for (j = 0; j < qnt - 1; ++j)
		if (arr[j] > arr[j + 1]) {
			int hold = arr[j];
			arr[j] = arr[j + 1];
			arr[j + 1] = hold;
		}
	}
}