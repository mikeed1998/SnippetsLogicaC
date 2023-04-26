#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void eventos(void);

int main(int argc, char const *argv[])
{
	char *imagenes[6] = {
		"******\n*    *\n*    *\n*    *\n*    *\n******",
		"******\n*    *\n*    *\n*    *\n*    *\n******",
		"******\n*    *\n*    *\n*    *\n*    *\n******",
		"******\n*    *\n*    *\n*    *\n*    *\n******",
		"******\n*    *\n*    *\n*    *\n*    *\n******",
		"******\n*    *\n*    *\n*    *\n*    *\n******"
	};

	for (int i = 0; i < 6; ++i)
	{
		printf("%s ->", *(imagenes + i));
	}


	return 0;
}

void eventos(void) {
	int tamX = 6;

	char** espectaculos = (char**)calloc(tamX, sizeof(char*)); 

	*(espectaculos + 0) = "Circo";
	*(espectaculos + 1) = "Danza";
	*(espectaculos + 2) = "Musica";
	*(espectaculos + 3) = "Titeres";
	*(espectaculos + 4) = "Intervenciones artisticas";
	*(espectaculos + 5) = "Eventos";

	for (int i = 0; i < tamX; ++i) {
		printf("%s ", *(espectaculos + i));
		(i < tamX - 1) ? printf("-> ") : printf("\n");
	}

	for (int i = 0; i < tamX; ++i) {
		free(*(espectaculos + i));
	}

	free(espectaculos);
}