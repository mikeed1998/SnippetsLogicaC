#include <stdio.h>

#define MAX_NODOS 100

typedef struct Nodo {
    int dato;
    int altura;
    int hijoIzquierdo;
    int hijoDerecho;
} Nodo;

int obtenerAltura(Nodo arbol[], int indice) {
    if (indice == -1) {
        return 0;
    }
    return arbol[indice].altura;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int obtenerFactorBalance(Nodo arbol[], int indice) {
    if (indice == -1) {
        return 0;
    }
    return obtenerAltura(arbol, arbol[indice].hijoIzquierdo) - obtenerAltura(arbol, arbol[indice].hijoDerecho);
}

int rotacionDerecha(Nodo arbol[], int indice) {
    int hijoIzquierdo = arbol[indice].hijoIzquierdo;
    int subArbolDerecho = arbol[hijoIzquierdo].hijoDerecho;

    arbol[hijoIzquierdo].hijoDerecho = indice;
    arbol[indice].hijoIzquierdo = subArbolDerecho;

    arbol[indice].altura = max(obtenerAltura(arbol, arbol[indice].hijoIzquierdo), obtenerAltura(arbol, arbol[indice].hijoDerecho)) + 1;
    arbol[hijoIzquierdo].altura = max(obtenerAltura(arbol, arbol[hijoIzquierdo].hijoIzquierdo), obtenerAltura(arbol, arbol[hijoIzquierdo].hijoDerecho)) + 1;

    return hijoIzquierdo;
}

int rotacionIzquierda(Nodo arbol[], int indice) {
    int hijoDerecho = arbol[indice].hijoDerecho;
    int subArbolIzquierdo = arbol[hijoDerecho].hijoIzquierdo;

    arbol[hijoDerecho].hijoIzquierdo = indice;
    arbol[indice].hijoDerecho = subArbolIzquierdo;

    arbol[indice].altura = max(obtenerAltura(arbol, arbol[indice].hijoIzquierdo), obtenerAltura(arbol, arbol[indice].hijoDerecho)) + 1;
    arbol[hijoDerecho].altura = max(obtenerAltura(arbol, arbol[hijoDerecho].hijoIzquierdo), obtenerAltura(arbol, arbol[hijoDerecho].hijoDerecho)) + 1;

    return hijoDerecho;
}

int insertar(Nodo arbol[], int dato, int indice) {
    if (indice == -1) {
        int nuevoIndice = 0;
        arbol[nuevoIndice].dato = dato;
        arbol[nuevoIndice].hijoIzquierdo = -1;
        arbol[nuevoIndice].hijoDerecho = -1;
        arbol[nuevoIndice].altura = 1;
        return nuevoIndice;
    }

    if (dato < arbol[indice].dato) {
        arbol[indice].hijoIzquierdo = insertar(arbol, dato, arbol[indice].hijoIzquierdo);
    } else if (dato > arbol[indice].dato) {
        arbol[indice].hijoDerecho = insertar(arbol, dato, arbol[indice].hijoDerecho);
    } else {
        // Dato duplicado
        return indice;
    }

    arbol[indice].altura = 1 + max(obtenerAltura(arbol, arbol[indice].hijoIzquierdo), obtenerAltura(arbol, arbol[indice].hijoDerecho));

    int factorBalance = obtenerFactorBalance(arbol, indice);

    // Caso 1: Desbalance hacia la izquierda-izquierda
    if (factorBalance > 1 && dato < arbol[arbol[indice].hijoIzquierdo].dato) {
        return rotacionDerecha(arbol, indice);
    }

    // Caso 2: Desbalance hacia la derecha-derecha
    if (factorBalance < -1 && dato > arbol[arbol[indice].hijoDerecho].dato) {
        return rotacionIzquierda(arbol, indice);
    }

    // Caso 3: Desbalance hacia la izquierda-derecha
    if (factorBalance > 1 && dato > arbol[arbol[indice].hijoIzquierdo].dato) {
        arbol[indice].hijoIzquierdo = rotacionIzquierda(arbol, arbol[indice].hijoIzquierdo);
        return rotacionDerecha(arbol, indice);
    }

    // Caso 4: Desbalance hacia la derecha-izquierda
    if (factorBalance < -1 && dato < arbol[arbol[indice].hijoDerecho].dato) {
        arbol[indice].hijoDerecho = rotacionDerecha(arbol, arbol[indice].hijoDerecho);
        return rotacionIzquierda(arbol, indice);
    }

    return indice;
}

int obtenerNodoMinimo(Nodo arbol[], int indice) {
    if (arbol[indice].hijoIzquierdo == -1) {
        return indice;
    }
    return obtenerNodoMinimo(arbol, arbol[indice].hijoIzquierdo);
}

int eliminar(Nodo arbol[], int dato, int indice) {
    if (indice == -1) {
        printf("El dato no existe en el árbol.\n");
        return indice;
    }

    if (dato < arbol[indice].dato) {
        arbol[indice].hijoIzquierdo = eliminar(arbol, dato, arbol[indice].hijoIzquierdo);
    } else if (dato > arbol[indice].dato) {
        arbol[indice].hijoDerecho = eliminar(arbol, dato, arbol[indice].hijoDerecho);
    } else {
        // Nodo encontrado

        if (arbol[indice].hijoIzquierdo == -1 || arbol[indice].hijoDerecho == -1) {
            int nodoTemp = (arbol[indice].hijoIzquierdo != -1) ? arbol[indice].hijoIzquierdo : arbol[indice].hijoDerecho;

            if (nodoTemp == -1) {
                nodoTemp = indice;
                indice = -1;
            } else {
                arbol[indice] = arbol[nodoTemp];
            }

            arbol[nodoTemp].hijoIzquierdo = -1;
            arbol[nodoTemp].hijoDerecho = -1;
        } else {
            int nodoTemp = obtenerNodoMinimo(arbol, arbol[indice].hijoDerecho);
            arbol[indice].dato = arbol[nodoTemp].dato;
            arbol[indice].hijoDerecho = eliminar(arbol, arbol[nodoTemp].dato, arbol[indice].hijoDerecho);
        }
    }

    if (indice == -1) {
        return indice;
    }

    arbol[indice].altura = 1 + max(obtenerAltura(arbol, arbol[indice].hijoIzquierdo), obtenerAltura(arbol, arbol[indice].hijoDerecho));

    int factorBalance = obtenerFactorBalance(arbol, indice);

    // Caso 1: Desbalance hacia la izquierda-izquierda
    if (factorBalance > 1 && obtenerFactorBalance(arbol, arbol[indice].hijoIzquierdo) >= 0) {
        return rotacionDerecha(arbol, indice);
    }

    // Caso 2: Desbalance hacia la derecha-derecha
    if (factorBalance < -1 && obtenerFactorBalance(arbol, arbol[indice].hijoDerecho) <= 0) {
        return rotacionIzquierda(arbol, indice);
    }

    // Caso 3: Desbalance hacia la izquierda-derecha
    if (factorBalance > 1 && obtenerFactorBalance(arbol, arbol[indice].hijoIzquierdo) < 0) {
        arbol[indice].hijoIzquierdo = rotacionIzquierda(arbol, arbol[indice].hijoIzquierdo);
        return rotacionDerecha(arbol, indice);
    }

    // Caso 4: Desbalance hacia la derecha-izquierda
    if (factorBalance < -1 && obtenerFactorBalance(arbol, arbol[indice].hijoDerecho) > 0) {
        arbol[indice].hijoDerecho = rotacionDerecha(arbol, arbol[indice].hijoDerecho);
        return rotacionIzquierda(arbol, indice);
    }

    return indice;
}

int buscar(Nodo arbol[], int dato, int indice) {
    if (indice == -1 || arbol[indice].dato == dato) {
        return indice;
    }

    if (dato < arbol[indice].dato) {
        return buscar(arbol, dato, arbol[indice].hijoIzquierdo);
    } else {
        return buscar(arbol, dato, arbol[indice].hijoDerecho);
    }
}

void imprimirArbol(Nodo arbol[], int indice, int nivel) {
    if (indice == -1) {
        return;
    }

    imprimirArbol(arbol, arbol[indice].hijoDerecho, nivel + 1);

    for (int i = 0; i < nivel; i++) {
        printf("   ");
    }
    printf("%d\n", arbol[indice].dato);

    imprimirArbol(arbol, arbol[indice].hijoIzquierdo, nivel + 1);
}

void recorridoPreOrden(Nodo arbol[], int indice) {
    if (indice == -1) {
        return;
    }

    printf("%d ", arbol[indice].dato);
    recorridoPreOrden(arbol, arbol[indice].hijoIzquierdo);
    recorridoPreOrden(arbol, arbol[indice].hijoDerecho);
}

void recorridoInOrden(Nodo arbol[], int indice) {
    if (indice == -1) {
        return;
    }

    recorridoInOrden(arbol, arbol[indice].hijoIzquierdo);
    printf("%d ", arbol[indice].dato);
    recorridoInOrden(arbol, arbol[indice].hijoDerecho);
}

void recorridoPostOrden(Nodo arbol[], int indice) {
    if (indice == -1) {
        return;
    }

    recorridoPostOrden(arbol, arbol[indice].hijoIzquierdo);
    recorridoPostOrden(arbol, arbol[indice].hijoDerecho);
    printf("%d ", arbol[indice].dato);
}

int main() {
    Nodo arbol[MAX_NODOS];
    int raiz = -1;

    raiz = insertar(arbol, 10, raiz);
    raiz = insertar(arbol, 5, raiz);
    raiz = insertar(arbol, 15, raiz);
    raiz = insertar(arbol, 3, raiz);
    raiz = insertar(arbol, 7, raiz);
    raiz = insertar(arbol, 12, raiz);
    raiz = insertar(arbol, 20, raiz);

    printf("Árbol AVL:\n");
    imprimirArbol(arbol, raiz, 0);

    printf("\nRecorrido preorden: ");
    recorridoPreOrden(arbol, raiz);

    printf("\nRecorrido inorden: ");
    recorridoInOrden(arbol, raiz);

    printf("\nRecorrido postorden: ");
    recorridoPostOrden(arbol, raiz);

    printf("\n");

    raiz = eliminar(arbol, 7, raiz);

    printf("\nÁrbol AVL después de eliminar 7:\n");
    imprimirArbol(arbol, raiz, 0);

    int datoBuscado = 15;
    int indiceEncontrado = buscar(arbol, datoBuscado, raiz);
    if (indiceEncontrado != -1) {
        printf("\n%d encontrado en el árbol.\n", datoBuscado);
    } else {
        printf("\n%d no encontrado en el árbol.\n", datoBuscado);
    }

    return 0;
}
