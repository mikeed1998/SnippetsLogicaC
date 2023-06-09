#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
    int dato;
    struct Nodo* izquierdo;
    struct Nodo* derecho;
} Nodo;

Nodo* crearNodo(int dato) {
    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo)); // Crear un nuevo nodo
    nuevoNodo->dato = dato;
    nuevoNodo->izquierdo = NULL;
    nuevoNodo->derecho = NULL;
    return nuevoNodo;
}

Nodo* insertar(Nodo* raiz, int dato) {
    if (raiz == NULL) { // Si la raíz es NULL, crear un nuevo nodo y establecerlo como raíz
        return crearNodo(dato);
    }

    if (dato < raiz->dato) { // Si el dato es menor que el valor en la raíz, insertarlo en el subárbol izquierdo
        raiz->izquierdo = insertar(raiz->izquierdo, dato);
    } else if (dato > raiz->dato) { // Si el dato es mayor que el valor en la raíz, insertarlo en el subárbol derecho
        raiz->derecho = insertar(raiz->derecho, dato);
    }

    return raiz;
}

Nodo* buscar(Nodo* raiz, int dato) {
    if (raiz == NULL || raiz->dato == dato) {
        return raiz;
    }

    if (dato < raiz->dato) { // Si el dato es menor que el valor en la raíz, buscar en el subárbol izquierdo
        return buscar(raiz->izquierdo, dato);
    } else { // Si el dato es mayor que el valor en la raíz, buscar en el subárbol derecho
        return buscar(raiz->derecho, dato);
    }
}

Nodo* buscarMinimo(Nodo* raiz) {
    Nodo* actual = raiz;
    while (actual->izquierdo != NULL) {
        actual = actual->izquierdo;
    }
    return actual;
}

Nodo* eliminar(Nodo* raiz, int dato) {
    if (raiz == NULL) {
        return raiz;
    }

    if (dato < raiz->dato) { // Si el dato es menor que el valor en la raíz, eliminarlo del subárbol izquierdo
        raiz->izquierdo = eliminar(raiz->izquierdo, dato);
    } else if (dato > raiz->dato) { // Si el dato es mayor que el valor en la raíz, eliminarlo del subárbol derecho
        raiz->derecho = eliminar(raiz->derecho, dato);
    } else { // Si el dato es igual al valor en la raíz, eliminar el nodo actual
        if (raiz->izquierdo == NULL) { // Caso: el nodo tiene solo un hijo derecho o no tiene hijos
            Nodo* temp = raiz->derecho;
            free(raiz);
            return temp;
        } else if (raiz->derecho == NULL) { // Caso: el nodo tiene solo un hijo izquierdo
            Nodo* temp = raiz->izquierdo;
            free(raiz);
            return temp;
        }

        // Caso: el nodo tiene dos hijos, buscar el sucesor inorden (mínimo en el subárbol derecho)
        Nodo* temp = buscarMinimo(raiz->derecho);

        // Copiar el dato del sucesor inorden al nodo actual
        raiz->dato = temp->dato;

        // Eliminar el sucesor inorden
        raiz->derecho = eliminar(raiz->derecho, temp->dato);
    }

    return raiz;
}

void recorridoPreOrden(Nodo* raiz, int nivel) {
    if (raiz == NULL) {
        return;
    }

    printf("%*s%d\n", nivel * 4, "", raiz->dato); // Imprimir el valor del nodo actual con el nivel de indentación
    recorridoPreOrden(raiz->izquierdo, nivel + 1); // Recorrer el subárbol izquierdo
    recorridoPreOrden(raiz->derecho, nivel + 1); // Recorrer el subárbol derecho
}

void recorridoInOrden(Nodo* raiz, int nivel) {
    if (raiz == NULL) {
        return;
    }

    recorridoInOrden(raiz->izquierdo, nivel + 1); // Recorrer el subárbol izquierdo
    printf("%*s%d\n", nivel * 4, "", raiz->dato); // Imprimir el valor del nodo actual con el nivel de indentación
    recorridoInOrden(raiz->derecho, nivel + 1); // Recorrer el subárbol derecho
}

void recorridoPostOrden(Nodo* raiz, int nivel) {
    if (raiz == NULL) {
        return;
    }

    recorridoPostOrden(raiz->izquierdo, nivel + 1); // Recorrer el subárbol izquierdo
    recorridoPostOrden(raiz->derecho, nivel + 1); // Recorrer el subárbol derecho
    printf("%*s%d\n", nivel * 4, "", raiz->dato); // Imprimir el valor del nodo actual con el nivel de indentación
}

int main() {
    Nodo* raiz = NULL; // Inicializar la raíz del árbol como NULL

    raiz = insertar(raiz, 4);
    raiz = insertar(raiz, 2);
    raiz = insertar(raiz, 6);
    raiz = insertar(raiz, 1);
    raiz = insertar(raiz, 3);
    raiz = insertar(raiz, 5);
    raiz = insertar(raiz, 7);

    printf("Árbol de búsqueda binaria:\n");
    printf("Recorrido PreOrden:\n");
    recorridoPreOrden(raiz, 0);
    printf("\n");

    printf("Recorrido InOrden:\n");
    recorridoInOrden(raiz, 0);
    printf("\n");

    printf("Recorrido PostOrden:\n");
    recorridoPostOrden(raiz, 0);
    printf("\n");

    Nodo* nodoBuscado = buscar(raiz, 5);
    if (nodoBuscado != NULL) {
        printf("El nodo con el valor %d fue encontrado.\n", nodoBuscado->dato);
    } else {
        printf("El nodo no fue encontrado.\n");
    }

    raiz = eliminar(raiz, 2);

    printf("Árbol después de eliminar el nodo con valor 2:\n");
    printf("Recorrido InOrden:\n");
    recorridoInOrden(raiz, 0);
    printf("\n");

    return 0;
}
