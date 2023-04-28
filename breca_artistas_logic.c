#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Artistas {
	int id;
	char *nombres;
	char *apellidos;
	char *foto;
	char *descripcion;
	char *tipo_artista;
	int galeria;
};

struct GaleriaArtista {
	int id;
	int artista;
	char *foto;
};

void principal();
char* asignarMemoriaString(int);
char* reasignarMemoriaString(char*, int);
void liberarMemoriaString(char*);
char** asignarMemoriaArrayString(int, int);
char** reasignarMemoriaArrayString(char**, int, int);
void liberarMemoriaArrayString(char**, int, int);

int main(int argc, char const *argv[])
{
	srand(time(0));
	struct Artistas a;

	a.id = 1;
	a.nombres = asignarMemoriaString(50);
	a.nombres = "Michael Eduardo";
	a.apellidos = asignarMemoriaString(50);
	a.apellidos = "Sandoval Perez";
	a.foto = asignarMemoriaString(50);
	a.foto = "imagen_principal.png";
	a.descripcion = asignarMemoriaString(150);
	a.descripcion = "Neque porro quisquam est qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit...";
	a.tipo_artista = asignarMemoriaString(50);
	a.tipo_artista = "Pintor";
	a.galeria = 1;

	struct GaleriaArtista g[3];

	for (int i = 0; i < 3; ++i) {	
		int random = rand() % 9999;
		char *charAux = asignarMemoriaString(50);

		g[i].id = i;
		g[i].artista = a.id;
		g[i].foto = asignarMemoriaString(100);
		g[i].foto = "imagen_ejemplo_";

		sprintf(charAux, "%d", random);
		strcat(g[i].foto, charAux);

		liberarMemoriaString(charAux);
	}

	printf("\t..::Artista::..\n\n");
	printf("Nombre(s): %s\n", a.nombres);
	printf("Apellido(s): %s\n", a.apellidos);
	printf("Foto: %s\n", a.foto);
	printf("Tipo de artista: %s", a.tipo_artista);
	printf("Descripcion del artista: \n\t%s\n\n", a.descripcion);

	if(a.galeria != 0) {
		printf("--> Galeria del artista:\n\n");

		for(int i = 0; i < 3; ++i) {
			if(a.galeria == g[i].id) {
				printf("\t%s\n", g[i].foto);
			}
		}

	} else {
		printf("\tPor el momento no hay una galeria disponible\n\n");
	}

	for (int i = 0; i < 3; ++i) {
		liberarMemoriaString(g[i].foto);
	}

	liberarMemoriaString(a.nombres);
	liberarMemoriaString(a.apellidos);
	liberarMemoriaString(a.foto);
	liberarMemoriaString(a.descripcion);
	liberarMemoriaString(a.tipo_artista);

	return 0;
}

char* asignarMemoriaString(int len) {
	char *ptr;

	ptr = (char*)malloc(len * sizeof(char));
	
	return ptr;
}

char* reasignarMemoriaString(char* ptr, int len) {
	ptr = (char*)realloc(ptr, len * sizeof(char));
	return ptr;
}

void liberarMemoriaString(char* ptr) {
	free(ptr);
	ptr = NULL;
}

char** asignarMemoriaArrayString(int rows, int cols) {
	char **ptr;
	ptr = (char**)calloc(rows, sizeof(char*));
	
	for (int i = 0; i < rows; ++i) {
		*(ptr + i) = (char*)malloc((rows * cols) * sizeof(char));	
	}

	return ptr;
}

char** reasignarMemoriaArrayString(char** ptr, int rows, int cols) {
	ptr = (char**)realloc(ptr, rows * sizeof(char*));
	
	for (int i = 0; i < rows; ++i) {
		*(ptr + i) = (char*)realloc(*(ptr + i), (rows * cols) * sizeof(char));	
	}

	return ptr;
}

void liberarMemoriaArrayString(char** ptr, int rows, int cols) {
	for (int i = 0; i < rows; ++i) {
		free(*(ptr + i));
	}

	free(ptr);
	ptr = NULL;
}










