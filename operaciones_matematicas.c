#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	int array[1000];

	for (int i = 0; i < 1000; ++i) {
		array[i] = i;
	}

	for (int i = 0; i < 1000; ++i) {
		printf("%i -> ", array[i]);
	}

	printf("\n\n");

	for (int i = 0; i < 1000; ++i) {
		if (array[i] % 3 == 0)
			printf("%i -> ", array[i] + 1);
	}

	printf("\n\n");

	for (int i = 0; i < 1000; ++i) {
		if ((array[i]+2) % 3 == 0)
			printf("%i -> ", array[i]);
	}

	return 0;
}