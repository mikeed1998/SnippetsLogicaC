#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mostrarArreglo(void*, char);
void brecaEspectaculos(void);

int main(int argc, char const *argv[])
{
	brecaEspectaculos();

	return 0;
}

void mostrarArreglo(void* arreglo, char tipo_dato) {

	switch(tipo_dato) {
		case 'i':
			{

			}
			break;
		case 'd':
			{

			}
			break;
		case 's':
			{
				char** aux = (char**)arreglo;

				for(int i = 0; i < 4; i++) {
					printf("%s ", *(aux + i));
					(i < 3) ? printf("-> ") : printf("\n");
				}
			}
			break;
		case 'c':
			{
				
			}
			break;
		default:
			printf("Error, mostrarArreglo\n\n");
			break;
	}

	
}

void brecaEspectaculos(void) {
	int contador = 0;
	char** categorias;
	categorias = (char**)calloc(4, sizeof(char*));
	*(categorias + 0) = "Musica";
	*(categorias + 1) = "Diversion";
	*(categorias + 2) = "Shows";
	*(categorias + 3) = "Espectaculo";

	int eX = 4, eY = 3;
	char*** espectaculos = (char***)calloc(eX * eY, sizeof(char**));
	for (int i = 0; i < eX; ++i)
	{
		*(espectaculos + i) = (char**)calloc(eX, sizeof(char*));
		for (int j = 0; j < eY; ++j)
		{
			*(*(espectaculos + i) + j) = (char*)calloc(eY, sizeof(char));
		}
	}

	// MEJORAR
	*(*(espectaculos + 0) + 0) = "a";
	*(*(espectaculos + 1) + 0) = "b";
	*(*(espectaculos + 2) + 0) = "c";
	*(*(espectaculos + 3) + 0) = "d";
	*(*(espectaculos + 0) + 1) = "a";
	*(*(espectaculos + 1) + 1) = "b";
	*(*(espectaculos + 2) + 1) = "c";
	*(*(espectaculos + 3) + 1) = "d";
	*(*(espectaculos + 0) + 2) = "a";
	*(*(espectaculos + 1) + 2) = "b";
	*(*(espectaculos + 2) + 2) = "c";
	*(*(espectaculos + 3) + 2) = "d";

	for (int i = 0; i < eX; ++i)
	{
		printf("%s:\n", *(espectaculos + i));
		for (int j = 0; j < eY; ++j)
		{
			printf("\t%s\n", *(*(espectaculos + i) + j));	
		}
	}

	
	mostrarArreglo((void*)categorias, 's');

	for(int i = 0; i < 4; i++) {
		free(*(categorias + i));
	}

	// for(int i = 0; i < 4; i++) {
	// 	for(int j = 0; j < 3; j++) {
	// 		free(*(*(categorias + j) + i));
	// 	}
	// 	free(*(categorias + i));
	// }
}














