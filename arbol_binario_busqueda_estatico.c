#include <stdio.h>

#define MAX_SIZE 100

int arbol[MAX_SIZE];

void inicializarArbol() {
    for (int i = 0; i < MAX_SIZE; i++) {
        arbol[i] = -1; // Inicializar todos los elementos del arreglo con -1
    }
}

void insertar(int dato) {
    int i = 0;
    while (arbol[i] != -1) {
        if (dato < arbol[i]) {
            i = 2 * i + 1; // Ir al hijo izquierdo
        } else if (dato > arbol[i]) {
            i = 2 * i + 2; // Ir al hijo derecho
        } else {
            printf("El dato ya existe en el árbol.\n");
            return;
        }
    }
    arbol[i] = dato; // Insertar el dato en la posición i
}

int buscar(int dato) {
    int i = 0;
    while (arbol[i] != -1) {
        if (dato < arbol[i]) {
            i = 2 * i + 1; // Ir al hijo izquierdo
        } else if (dato > arbol[i]) {
            i = 2 * i + 2; // Ir al hijo derecho
        } else {
            return i; // El dato fue encontrado, retornar la posición
        }
    }
    return -1; // El dato no fue encontrado
}

int buscarMinimo(int indice) {
    while (arbol[2 * indice + 1] != -1) {
        indice = 2 * indice + 1; // Ir al hijo izquierdo
    }
    return indice;
}

void eliminar(int dato) {
    int indice = buscar(dato);
    if (indice == -1) {
        printf("El dato no existe en el árbol.\n");
        return;
    }

    // Caso: el nodo es una hoja
    if (arbol[2 * indice + 1] == -1 && arbol[2 * indice + 2] == -1) {
        arbol[indice] = -1;
    }
    // Caso: el nodo tiene solo un hijo izquierdo
    else if (arbol[2 * indice + 1] != -1 && arbol[2 * indice + 2] == -1) {
        arbol[indice] = arbol[2 * indice + 1];
        eliminar(arbol[2 * indice + 1]);
    }
    // Caso: el nodo tiene solo un hijo derecho
    else if (arbol[2 * indice + 1] == -1 && arbol[2 * indice + 2] != -1) {
        arbol[indice] = arbol[2 * indice + 2];
        eliminar(arbol[2 * indice + 2]);
    }
    // Caso: el nodo tiene dos hijos
    else {
        int sucesor = buscarMinimo(2 * indice + 2);
        arbol[indice] = arbol[sucesor];
        eliminar(arbol[sucesor]);
    }
}

void recorridoPreOrden(int indice, int nivel) {
    if (arbol[indice] == -1) {
        return;
    }

    printf("%*s%d\n", nivel * 4, "", arbol[indice]); // Imprimir el valor del nodo actual con el nivel de indentación
    recorridoPreOrden(2 * indice + 1, nivel + 1); // Recorrer el hijo izquierdo
    recorridoPreOrden(2 * indice + 2, nivel + 1); // Recorrer el hijo derecho
}

void recorridoInOrden(int indice, int nivel) {
    if (arbol[indice] == -1) {
        return;
    }

    recorridoInOrden(2 * indice + 1, nivel + 1); // Recorrer el hijo izquierdo
    printf("%*s%d\n", nivel * 4, "", arbol[indice]); // Imprimir el valor del nodo actual con el nivel de indentación
    recorridoInOrden(2 * indice + 2, nivel + 1); // Recorrer el hijo derecho
}

void recorridoPostOrden(int indice, int nivel) {
    if (arbol[indice] == -1) {
        return;
    }

    recorridoPostOrden(2 * indice + 1, nivel + 1); // Recorrer el hijo izquierdo
    recorridoPostOrden(2 * indice + 2, nivel + 1); // Recorrer el hijo derecho
    printf("%*s%d\n", nivel * 4, "", arbol[indice]); // Imprimir el valor del nodo actual con el nivel de indentación
}

int main() {
    inicializarArbol();

    insertar(4);
    insertar(2);
    insertar(6);
    insertar(1);
    insertar(3);
    insertar(5);
    insertar(7);

    printf("Árbol de búsqueda binaria:\n");
    printf("Recorrido PreOrden:\n");
    recorridoPreOrden(0, 0);
    printf("\n");

    printf("Recorrido InOrden:\n");
    recorridoInOrden(0, 0);
    printf("\n");

    printf("Recorrido PostOrden:\n");
    recorridoPostOrden(0, 0);
    printf("\n");

    int datoBuscado = 5;
    int indice = buscar(datoBuscado);
    if (indice != -1) {
        printf("El nodo con el valor %d fue encontrado.\n", arbol[indice]);
    } else {
        printf("El nodo no fue encontrado.\n");
    }

    eliminar(2);

    printf("Árbol después de eliminar el nodo con valor 2:\n");
    printf("Recorrido InOrden:\n");
    recorridoInOrden(0, 0);
    printf("\n");

    return 0;
}
