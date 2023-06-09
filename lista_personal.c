#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nodo {
	int dato;
	struct Nodo *sig;
}Nodo;

void insertar(Nodo**, int);
void mostrar(Nodo*);

int main(int argc, char const *argv[])
{
	Nodo* lista = NULL;

	insertar(&lista, 1);
	insertar(&lista, 2);
	insertar(&lista, 3);

	mostrar(lista);

	return 0;
}

void insertar(Nodo **lista, int dato) {
	Nodo* aux = (Nodo*)malloc(sizeof(Nodo));

	aux->dato = dato;
	aux->sig = *lista;

	*lista = aux;
}

void mostrar(Nodo *lista) {
	Nodo* actual = lista;
	while(actual != NULL) {
		printf("%d -> ", actual->dato);
		actual = actual->sig;
	}
}