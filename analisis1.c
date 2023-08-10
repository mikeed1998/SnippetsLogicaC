#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	int valor = 10;								// 	O(1)

	for (int i = 0; i < valor; ++i)				//	O(n)
	{
		printf("\n");							//	O(n)
		for (int j = 0; j < valor; ++j)			//	O(n^2)
		{
			printf("%d -> ");					//	O(n^2)
		}
	}

	printf("Fin");								//	O(1)

	return 0;
}

// 2n^2 + 2n + 2 = O(n^2) -> n = valor