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
					printf("%s\n", *(aux + i));
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
	char** categorias;
	categorias = (char**)calloc(4, sizeof(char*));
	*(categorias + 0) = "Musica";
	*(categorias + 1) = "Diversion";
	*(categorias + 2) = "Shows";
	*(categorias + 3) = "Espectaculo";

	
	mostrarArreglo((void*)categorias, 's');


	for(int i = 0; i < 4; i++) {
		free(*(categorias + i));
	}
}














