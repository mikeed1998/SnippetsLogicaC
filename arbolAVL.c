#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
    int dato;
    struct Nodo *izquierdo;
    struct Nodo *derecho;
    int altura;
} Nodo;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int obtenerAltura(Nodo *nodo) {
    if (nodo == NULL) {
        return 0;
    }
    return nodo->altura;
}

int obtenerFactorBalance(Nodo *nodo) {
    if (nodo == NULL) {
        return 0;
    }
    return obtenerAltura(nodo->izquierdo) - obtenerAltura(nodo->derecho);
}

Nodo *rotacionDerecha(Nodo *nodo) {
    Nodo *nodoIzquierdo = nodo->izquierdo;
    Nodo *subArbolDerecho = nodoIzquierdo->derecho;

    nodoIzquierdo->derecho = nodo;
    nodo->izquierdo = subArbolDerecho;

    nodo->altura = max(obtenerAltura(nodo->izquierdo), obtenerAltura(nodo->derecho)) + 1;
    nodoIzquierdo->altura = max(obtenerAltura(nodoIzquierdo->izquierdo), obtenerAltura(nodoIzquierdo->derecho)) + 1;

    return nodoIzquierdo;
}

Nodo *rotacionIzquierda(Nodo *nodo) {
    Nodo *nodoDerecho = nodo->derecho;
    Nodo *subArbolIzquierdo = nodoDerecho->izquierdo;

    nodoDerecho->izquierdo = nodo;
    nodo->derecho = subArbolIzquierdo;

    nodo->altura = max(obtenerAltura(nodo->izquierdo), obtenerAltura(nodo->derecho)) + 1;
    nodoDerecho->altura = max(obtenerAltura(nodoDerecho->izquierdo), obtenerAltura(nodoDerecho->derecho)) + 1;

    return nodoDerecho;
}

Nodo *insertar(Nodo *raiz, int dato) {
    if (raiz == NULL) {
        Nodo *nuevoNodo = (Nodo *)malloc(sizeof(Nodo));
        nuevoNodo->dato = dato;
        nuevoNodo->izquierdo = NULL;
        nuevoNodo->derecho = NULL;
        nuevoNodo->altura = 1;
        return nuevoNodo;
    }

    if (dato < raiz->dato) {
        raiz->izquierdo = insertar(raiz->izquierdo, dato);
    } else if (dato > raiz->dato) {
        raiz->derecho = insertar(raiz->derecho, dato);
    } else {
        printf("El dato ya existe en el árbol.\n");
        return raiz;
    }

    raiz->altura = max(obtenerAltura(raiz->izquierdo), obtenerAltura(raiz->derecho)) + 1;

    int factorBalance = obtenerFactorBalance(raiz);

    // Caso 1: Desbalance hacia la izquierda
    if (factorBalance > 1 && dato < raiz->izquierdo->dato) {
        return rotacionDerecha(raiz);
    }

    // Caso 2: Desbalance hacia la derecha
    if (factorBalance < -1 && dato > raiz->derecho->dato) {
        return rotacionIzquierda(raiz);
    }

    // Caso 3: Desbalance hacia la izquierda-derecha
    if (factorBalance > 1 && dato > raiz->izquierdo->dato) {
        raiz->izquierdo = rotacionIzquierda(raiz->izquierdo);
        return rotacionDerecha(raiz);
    }

    // Caso 4: Desbalance hacia la derecha-izquierda
    if (factorBalance < -1 && dato < raiz->derecho->dato) {
        raiz->derecho = rotacionDerecha(raiz->derecho);
        return rotacionIzquierda(raiz);
    }

    return raiz;
}

Nodo *obtenerNodoMinimo(Nodo *raiz) {
    Nodo *nodoActual = raiz;
    while (nodoActual->izquierdo != NULL) {
        nodoActual = nodoActual->izquierdo;
    }
    return nodoActual;
}

Nodo *eliminar(Nodo *raiz, int dato) {
    if (raiz == NULL) {
        printf("El dato no existe en el árbol.\n");
        return raiz;
    }

    if (dato < raiz->dato) {
        raiz->izquierdo = eliminar(raiz->izquierdo, dato);
    } else if (dato > raiz->dato) {
        raiz->derecho = eliminar(raiz->derecho, dato);
    } else {
        // Nodo encontrado

        if (raiz->izquierdo == NULL || raiz->derecho == NULL) {
            Nodo *nodoTemp = raiz->izquierdo ? raiz->izquierdo : raiz->derecho;

            if (nodoTemp == NULL) {
                nodoTemp = raiz;
                raiz = NULL;
            } else {
                *raiz = *nodoTemp;
            }

            free(nodoTemp);
        } else {
            Nodo *nodoMinimo = obtenerNodoMinimo(raiz->derecho);
            raiz->dato = nodoMinimo->dato;
            raiz->derecho = eliminar(raiz->derecho, nodoMinimo->dato);
        }
    }

    if (raiz == NULL) {
        return raiz;
    }

    raiz->altura = max(obtenerAltura(raiz->izquierdo), obtenerAltura(raiz->derecho)) + 1;

    int factorBalance = obtenerFactorBalance(raiz);

    // Caso 1: Desbalance hacia la izquierda
    if (factorBalance > 1 && obtenerFactorBalance(raiz->izquierdo) >= 0) {
        return rotacionDerecha(raiz);
    }

    // Caso 2: Desbalance hacia la derecha
    if (factorBalance < -1 && obtenerFactorBalance(raiz->derecho) <= 0) {
        return rotacionIzquierda(raiz);
    }

    // Caso 3: Desbalance hacia la izquierda-derecha
    if (factorBalance > 1 && obtenerFactorBalance(raiz->izquierdo) < 0) {
        raiz->izquierdo = rotacionIzquierda(raiz->izquierdo);
        return rotacionDerecha(raiz);
    }

    // Caso 4: Desbalance hacia la derecha-izquierda
    if (factorBalance < -1 && obtenerFactorBalance(raiz->derecho) > 0) {
        raiz->derecho = rotacionDerecha(raiz->derecho);
        return rotacionIzquierda(raiz);
    }

    return raiz;
}

Nodo *buscar(Nodo *raiz, int dato) {
    if (raiz == NULL || raiz->dato == dato) {
        return raiz;
    }

    if (dato < raiz->dato) {
        return buscar(raiz->izquierdo, dato);
    } else {
        return buscar(raiz->derecho, dato);
    }
}

void imprimirArbol(Nodo *raiz, int nivel) {
    if (raiz == NULL) {
        return;
    }

    imprimirArbol(raiz->derecho, nivel + 1);

    for (int i = 0; i < nivel; i++) {
        printf("   ");
    }
    printf("%d\n", raiz->dato);

    imprimirArbol(raiz->izquierdo, nivel + 1);
}

void recorridoPreOrden(Nodo *raiz) {
    if (raiz == NULL) {
        return;
    }

    printf("%d ", raiz->dato);
    recorridoPreOrden(raiz->izquierdo);
    recorridoPreOrden(raiz->derecho);
}

void recorridoInOrden(Nodo *raiz) {
    if (raiz == NULL) {
        return;
    }

    recorridoInOrden(raiz->izquierdo);
    printf("%d ", raiz->dato);
    recorridoInOrden(raiz->derecho);
}

void recorridoPostOrden(Nodo *raiz) {
    if (raiz == NULL) {
        return;
    }

    recorridoPostOrden(raiz->izquierdo);
    recorridoPostOrden(raiz->derecho);
    printf("%d ", raiz->dato);
}

int main() {
    Nodo *raiz = NULL;

    raiz = insertar(raiz, 50);
    raiz = insertar(raiz, 30);
    raiz = insertar(raiz, 70);
    raiz = insertar(raiz, 20);
    raiz = insertar(raiz, 40);
    raiz = insertar(raiz, 60);
    raiz = insertar(raiz, 80);

    printf("Árbol AVL:\n");
    imprimirArbol(raiz, 0);

    printf("\nRecorrido PreOrden: ");
    recorridoPreOrden(raiz);

    printf("\nRecorrido InOrden: ");
    recorridoInOrden(raiz);

    printf("\nRecorrido PostOrden: ");
    recorridoPostOrden(raiz);

    raiz = eliminar(raiz, 40);
    raiz = eliminar(raiz, 60);

    printf("\n\nÁrbol AVL después de eliminar nodos:\n");
    imprimirArbol(raiz, 0);

    Nodo *nodoBuscado = buscar(raiz, 30);
    if (nodoBuscado != NULL) {
        printf("\nEl nodo con el dato 30 existe en el árbol.\n");
    } else {
        printf("\nEl nodo con el dato 30 no existe en el árbol.\n");
    }

    return 0;
}
