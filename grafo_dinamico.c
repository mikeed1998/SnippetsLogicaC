#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define INT_MAX 9223372036

typedef struct {
    int destino;
    int peso;
} Arista;

typedef struct {
    int vertice;
    Arista* aristas;
    int numAristas;
} Vertice;

typedef struct {
    Vertice vertices[MAX_VERTICES];
    int numVertices;
} Grafo;

Grafo* crearGrafo() {
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->numVertices = 0;
    return grafo;
}

int estaVacio(Grafo* grafo) {
    return grafo->numVertices == 0;
}

int obtenerTamanio(Grafo* grafo) {
    return grafo->numVertices;
}

Vertice* obtenerVertice(Grafo* grafo, int vertice) {
    if (vertice < 0 || vertice >= grafo->numVertices) {
        return NULL;
    }
    return &(grafo->vertices[vertice]);
}

void insertarVertice(Grafo* grafo, int vertice) {
    if (grafo->numVertices >= MAX_VERTICES) {
        printf("Se ha alcanzado el máximo número de vértices.\n");
        return;
    }

    if (obtenerVertice(grafo, vertice) != NULL) {
        printf("El vértice ya existe en el grafo.\n");
        return;
    }

    grafo->vertices[grafo->numVertices].vertice = vertice;
    grafo->vertices[grafo->numVertices].aristas = NULL;
    grafo->vertices[grafo->numVertices].numAristas = 0;
    grafo->numVertices++;
}

void insertarArista(Grafo* grafo, int origen, int destino, int peso) {
    Vertice* verticeOrigen = obtenerVertice(grafo, origen);
    Vertice* verticeDestino = obtenerVertice(grafo, destino);

    if (verticeOrigen == NULL || verticeDestino == NULL) {
        printf("Los vértices no existen en el grafo.\n");
        return;
    }

    int numAristasOrigen = verticeOrigen->numAristas;
    verticeOrigen->aristas = (Arista*)realloc(verticeOrigen->aristas, (numAristasOrigen + 1) * sizeof(Arista));
    verticeOrigen->aristas[numAristasOrigen].destino = destino;
    verticeOrigen->aristas[numAristasOrigen].peso = peso;
    verticeOrigen->numAristas++;
}

void mostrarListaAdyacencia(Grafo* grafo) {
    for (int i = 0; i < grafo->numVertices; i++) {
        Vertice* vertice = &(grafo->vertices[i]);
        printf("Vértice %d: ", vertice->vertice);
        for (int j = 0; j < vertice->numAristas; j++) {
            Arista arista = vertice->aristas[j];
            printf("(%d, %d) ", arista.destino, arista.peso);
        }
        printf("\n");
    }
}

void eliminarVertice(Grafo* grafo, int vertice) {
    Vertice* verticeEliminar = obtenerVertice(grafo, vertice);

    if (verticeEliminar == NULL) {
        printf("El vértice no existe en el grafo.\n");
        return;
    }

    for (int i = 0; i < grafo->numVertices; i++) {
        Vertice* verticeActual = &(grafo->vertices[i]);

        for (int j = 0; j < verticeActual->numAristas; j++) {
            if (verticeActual->aristas[j].destino == vertice) {
                for (int k = j; k < verticeActual->numAristas - 1; k++) {
                    verticeActual->aristas[k] = verticeActual->aristas[k + 1];
                }
                verticeActual->numAristas--;
                verticeActual->aristas = (Arista*)realloc(verticeActual->aristas, verticeActual->numAristas * sizeof(Arista));
                break;
            }
        }
    }

    for (int i = vertice; i < grafo->numVertices - 1; i++) {
        grafo->vertices[i] = grafo->vertices[i + 1];
    }
    grafo->numVertices--;

    free(verticeEliminar->aristas);
}

void eliminarArista(Grafo* grafo, int origen, int destino) {
    Vertice* verticeOrigen = obtenerVertice(grafo, origen);

    if (verticeOrigen == NULL) {
        printf("El vértice de origen no existe en el grafo.\n");
        return;
    }

    int indiceArista = -1;
    for (int i = 0; i < verticeOrigen->numAristas; i++) {
        if (verticeOrigen->aristas[i].destino == destino) {
            indiceArista = i;
            break;
        }
    }

    if (indiceArista == -1) {
        printf("La arista no existe en el grafo.\n");
        return;
    }

    for (int i = indiceArista; i < verticeOrigen->numAristas - 1; i++) {
        verticeOrigen->aristas[i] = verticeOrigen->aristas[i + 1];
    }
    verticeOrigen->numAristas--;
    verticeOrigen->aristas = (Arista*)realloc(verticeOrigen->aristas, verticeOrigen->numAristas * sizeof(Arista));
}

void eliminarTodo(Grafo* grafo) {
    for (int i = 0; i < grafo->numVertices; i++) {
        free(grafo->vertices[i].aristas);
    }
    grafo->numVertices = 0;
}

void eliminarAristasDestino(Grafo* grafo, int destino) {
    for (int i = 0; i < grafo->numVertices; i++) {
        Vertice* vertice = &(grafo->vertices[i]);

        for (int j = 0; j < vertice->numAristas; j++) {
            if (vertice->aristas[j].destino == destino) {
                eliminarArista(grafo, vertice->vertice, destino);
                j--;
            }
        }
    }
}

// Anchura
void recorridoAnchura(Grafo* grafo, int verticeInicial) {
    int visitados[MAX_VERTICES] = {0};
    int cola[MAX_COLA];
    int frente = 0;
    int final = 0;

    Vertice* vertice = obtenerVertice(grafo, verticeInicial);

    if (vertice == NULL) {
        printf("El vértice inicial no existe en el grafo.\n");
        return;
    }

    visitados[verticeInicial] = 1;
    cola[final++] = verticeInicial;

    printf("Recorrido en Anchura: ");

    while (frente < final) {
        int verticeActual = cola[frente++];
        printf("%d ", verticeActual);

        for (int i = 0; i < grafo->vertices[verticeActual].numAristas; i++) {
            int verticeAdyacente = grafo->vertices[verticeActual].aristas[i].destino;

            if (!visitados[verticeAdyacente]) {
                visitados[verticeAdyacente] = 1;
                cola[final++] = verticeAdyacente;
            }
        }
    }

    printf("\n");
}

// Profundidad
void dfsRecursivo(Grafo* grafo, int vertice, int visitados[]) {
    visitados[vertice] = 1;
    printf("%d ", vertice);

    Vertice* verticeActual = obtenerVertice(grafo, vertice);

    for (int i = 0; i < verticeActual->numAristas; i++) {
        int verticeAdyacente = verticeActual->aristas[i].destino;
        if (!visitados[verticeAdyacente]) {
            dfsRecursivo(grafo, verticeAdyacente, visitados);
        }
    }
}

void recorridoProfundidad(Grafo* grafo, int verticeInicial) {
    int visitados[MAX_VERTICES] = {0};

    Vertice* vertice = obtenerVertice(grafo, verticeInicial);

    if (vertice == NULL) {
        printf("El vértice inicial no existe en el grafo.\n");
        return;
    }

    printf("Recorrido en Profundidad: ");
    dfsRecursivo(grafo, verticeInicial, visitados);
    printf("\n");
}

void primeroEnAnchura(Grafo* grafo, int verticeInicial, int verticeDestino) {
    int visitados[MAX_VERTICES] = {0};
    int cola[MAX_COLA];
    int frente = 0;
    int final = 0;
    int encontrado = 0;

    Vertice* vertice = obtenerVertice(grafo, verticeInicial);

    if (vertice == NULL) {
        printf("El vértice inicial no existe en el grafo.\n");
        return;
    }

    visitados[verticeInicial] = 1;
    cola[final++] = verticeInicial;

    while (frente < final && !encontrado) {
        int verticeActual = cola[frente++];
        printf("%d ", verticeActual);

        if (verticeActual == verticeDestino) {
            encontrado = 1;
            break;
        }

        for (int i = 0; i < grafo->vertices[verticeActual].numAristas; i++) {
            int verticeAdyacente = grafo->vertices[verticeActual].aristas[i].destino;

            if (!visitados[verticeAdyacente]) {
                visitados[verticeAdyacente] = 1;
                cola[final++] = verticeAdyacente;
            }
        }
    }

    if (encontrado) {
        printf("\nSe encontró el vértice destino %d\n", verticeDestino);
    } else {
        printf("\nNo se encontró el vértice destino %d\n", verticeDestino);
    }
}


void dfsRecursivo2(Grafo* grafo, int vertice, int verticeDestino, int visitados[]) {
    if (vertice == verticeDestino) {
        printf("%d ", vertice);
        return;
    }

    visitados[vertice] = 1;
    printf("%d ", vertice);

    for (int i = 0; i < grafo->vertices[vertice].numAristas; i++) {
        int verticeAdyacente = grafo->vertices[vertice].aristas[i].destino;

        if (!visitados[verticeAdyacente]) {
            dfsRecursivo2(grafo, verticeAdyacente, verticeDestino, visitados);
        }
    }
}

void primeroEnProfundidad(Grafo* grafo, int verticeInicial, int verticeDestino) {
    int visitados[MAX_VERTICES] = {0};

    Vertice* vertice = obtenerVertice(grafo, verticeInicial);

    if (vertice == NULL) {
        printf("El vértice inicial no existe en el grafo.\n");
        return;
    }

    dfsRecursivo2(grafo, verticeInicial, verticeDestino, visitados);
    printf("\n");
}


void primeroElMejor(Grafo* grafo, int verticeInicial, int verticeDestino) {
    int visitados[MAX_VERTICES] = {0};
    int prioridad[MAX_VERTICES];
    int padre[MAX_VERTICES];
    int cola[MAX_VERTICES];
    int frente = 0;
    int final = 0;

    for (int i = 0; i < grafo->numVertices; i++) {
        prioridad[i] = INT_MAX;
        padre[i] = -1;
    }

    prioridad[verticeInicial] = 0;
    cola[final++] = verticeInicial;

    while (frente < final) {
        int verticeActual = cola[frente++];
        printf("%d ", verticeActual);

        if (verticeActual == verticeDestino) {
            break;
        }

        visitados[verticeActual] = 1;

        for (int i = 0; i < grafo->vertices[verticeActual].numAristas; i++) {
            int verticeAdyacente = grafo->vertices[verticeActual].aristas[i].destino;
            int pesoArista = grafo->vertices[verticeActual].aristas[i].peso;
            int nuevaPrioridad = prioridad[verticeActual] + pesoArista;

            if (!visitados[verticeAdyacente] && nuevaPrioridad < prioridad[verticeAdyacente]) {
                prioridad[verticeAdyacente] = nuevaPrioridad;
                padre[verticeAdyacente] = verticeActual;
                cola[final++] = verticeAdyacente;
            }
        }
    }

    printf("\n");
    printf("Camino: ");

    int vertice = verticeDestino;
    printf("%d ", vertice);

    while (padre[vertice] != -1) {
        vertice = padre[vertice];
        printf("%d ", vertice);
    }

    printf("\n");
}

void mostrarRutaEncontrada(Grafo* grafo, int verticeInicial, int verticeDestino) {
    int padre[MAX_VERTICES] = {0};
    int vertice = verticeDestino;

    while (vertice != -1) {
        printf("%d ", vertice);
        vertice = padre[vertice];
    }

    printf("\n");
}

// Dijkstra
void dijkstra(Grafo* grafo, int verticeInicial) {
    int distancias[MAX_VERTICES];
    int visitados[MAX_VERTICES];

    // Inicializar distancias y visitados
    for (int i = 0; i < grafo->numVertices; i++) {
        distancias[i] = INT_MAX;
        visitados[i] = 0;
    }

    // La distancia al vértice inicial es 0
    distancias[verticeInicial] = 0;

    // Iterar para encontrar la ruta más corta
    for (int i = 0; i < grafo->numVertices - 1; i++) {
        // Encontrar el vértice de menor distancia no visitado
        int minDistancia = INT_MAX;
        int minVertice = -1;

        for (int j = 0; j < grafo->numVertices; j++) {
            if (visitados[j] == 0 && distancias[j] < minDistancia) {
                minDistancia = distancias[j];
                minVertice = j;
            }
        }

        // Marcar el vértice como visitado
        visitados[minVertice] = 1;

        // Actualizar las distancias de los vértices adyacentes no visitados
        for (int j = 0; j < grafo->vertices[minVertice].numAristas; j++) {
            int destino = grafo->vertices[minVertice].aristas[j].destino;
            int peso = grafo->vertices[minVertice].aristas[j].peso;

            if (visitados[destino] == 0 && distancias[minVertice] != INT_MAX &&
                distancias[minVertice] + peso < distancias[destino]) {
                distancias[destino] = distancias[minVertice] + peso;
            }
        }
    }

    // Imprimir las distancias mínimas desde el vértice inicial
    printf("Distancias mínimas desde el vértice %d:\n", verticeInicial);
    for (int i = 0; i < grafo->numVertices; i++) {
        printf("Vértice %d: %d\n", i, distancias[i]);
    }
}

// Kruskal
// Estructura para representar un conjunto disjunto
typedef struct {
    int padre[MAX_VERTICES];
    int rango[MAX_VERTICES];
} ConjuntoDisjunto;

// Inicializar el conjunto disjunto
void inicializarConjuntoDisjunto(ConjuntoDisjunto* conjuntoDisjunto) {
    for (int i = 0; i < MAX_VERTICES; i++) {
        conjuntoDisjunto->padre[i] = i;
        conjuntoDisjunto->rango[i] = 0;
    }
}

// Encontrar el padre de un vértice en el conjunto disjunto
int encontrar(ConjuntoDisjunto* conjuntoDisjunto, int vertice) {
    if (conjuntoDisjunto->padre[vertice] != vertice) {
        conjuntoDisjunto->padre[vertice] = encontrar(conjuntoDisjunto, conjuntoDisjunto->padre[vertice]);
    }
    return conjuntoDisjunto->padre[vertice];
}

// Unir dos conjuntos en el conjunto disjunto
void unir(ConjuntoDisjunto* conjuntoDisjunto, int vertice1, int vertice2) {
    int padre1 = encontrar(conjuntoDisjunto, vertice1);
    int padre2 = encontrar(conjuntoDisjunto, vertice2);

    if (conjuntoDisjunto->rango[padre1] < conjuntoDisjunto->rango[padre2]) {
        conjuntoDisjunto->padre[padre1] = padre2;
    } else if (conjuntoDisjunto->rango[padre1] > conjuntoDisjunto->rango[padre2]) {
        conjuntoDisjunto->padre[padre2] = padre1;
    } else {
        conjuntoDisjunto->padre[padre2] = padre1;
        conjuntoDisjunto->rango[padre1]++;
    }
}

// Función de comparación para ordenar las aristas por peso
int compararAristas(const void* a, const void* b) {
    Arista* arista1 = (Arista*)a;
    Arista* arista2 = (Arista*)b;
    return arista1->peso - arista2->peso;
}

// Algoritmo de Kruskal para encontrar el árbol de expansión mínima
void kruskal(Grafo* grafo) {
    // Obtener el número de vértices en el grafo
    int numVertices = grafo->numVertices;

    // Ordenar las aristas del grafo por peso
    Arista* aristas = (Arista*)malloc(sizeof(Arista) * MAX_VERTICES * MAX_VERTICES);
    int numAristas = 0;
    for (int i = 0; i < numVertices; i++) {
        Vertice* vertice = &(grafo->vertices[i]);
        for (int j = 0; j < vertice->numAristas; j++) {
            aristas[numAristas++] = vertice->aristas[j];
        }
    }
    qsort(aristas, numAristas, sizeof(Arista), compararAristas);

    // Inicializar el conjunto disjunto
    ConjuntoDisjunto conjuntoDisjunto;
    inicializarConjuntoDisjunto(&conjuntoDisjunto);

    // Crear el árbol de expansión mínima
    printf("Árbol de Expansión Mínima (Kruskal):\n");
    for (int i = 0; i < numAristas; i++) {
        Arista arista = aristas[i];
        int padreOrigen = encontrar(&conjuntoDisjunto, arista.destino);
        int padreDestino = encontrar(&conjuntoDisjunto, arista.vertice);
        if (padreOrigen != padreDestino) {
            printf("Arista (%d-%d) Peso: %d\n", arista.vertice, arista.destino, arista.peso);
            unir(&conjuntoDisjunto, padreOrigen, padreDestino);
        }
    }

    free(aristas);
}


// Prim
// Estructura para representar un vértice en el algoritmo de Prim
typedef struct {
    int vertice;
    int clave;
    int padre;
} VerticePrim;

// Estructura para representar una cola de prioridad en el algoritmo de Prim
typedef struct {
    VerticePrim* verticesPrim[MAX_VERTICES];
    int numVertices;
} ColaPrioridad;

// Crear un nuevo vértice Prim
VerticePrim* crearVerticePrim(int vertice, int clave, int padre) {
    VerticePrim* v = (VerticePrim*)malloc(sizeof(VerticePrim));
    v->vertice = vertice;
    v->clave = clave;
    v->padre = padre;
    return v;
}

// Crear una nueva cola de prioridad
ColaPrioridad* crearColaPrioridad() {
    ColaPrioridad* cola = (ColaPrioridad*)malloc(sizeof(ColaPrioridad));
    cola->numVertices = 0;
    return cola;
}

// Intercambiar dos vértices Prim en la cola de prioridad
void intercambiarVerticesPrim(VerticePrim** v1, VerticePrim** v2) {
    VerticePrim* temp = *v1;
    *v1 = *v2;
    *v2 = temp;
}

// Función de comparación para ordenar los vértices Prim por clave
int compararVerticesPrim(const void* a, const void* b) {
    VerticePrim* v1 = *(VerticePrim**)a;
    VerticePrim* v2 = *(VerticePrim**)b;
    return v1->clave - v2->clave;
}

// Insertar un vértice Prim en la cola de prioridad
void insertarColaPrioridad(ColaPrioridad* cola, VerticePrim* verticePrim) {
    cola->verticesPrim[cola->numVertices] = verticePrim;
    cola->numVertices++;
    qsort(cola->verticesPrim, cola->numVertices, sizeof(VerticePrim*), compararVerticesPrim);
}

// Extraer el vértice Prim con la menor clave de la cola de prioridad
VerticePrim* extraerMinimoColaPrioridad(ColaPrioridad* cola) {
    if (cola->numVertices == 0) {
        return NULL;
    }
    VerticePrim* minimo = cola->verticesPrim[0];
    cola->verticesPrim[0] = cola->verticesPrim[cola->numVertices - 1];
    cola->numVertices--;
    qsort(cola->verticesPrim, cola->numVertices, sizeof(VerticePrim*), compararVerticesPrim);
    return minimo;
}

// Función para el algoritmo de Prim
void prim(Grafo* grafo, int verticeInicial) {
    int numVertices = grafo->numVertices;
    int clave[MAX_VERTICES];  // Almacena las claves (pesos mínimos) de los vértices
    int padre[MAX_VERTICES];  // Almacena los padres de los vértices en el árbol de expansión mínima
    int visitado[MAX_VERTICES];  // Marca los vértices visitados

    for (int i = 0; i < numVertices; i++) {
        clave[i] = INT_MAX;  // Inicializar las claves con un valor infinito
        padre[i] = -1;  // Inicializar los padres como no definidos
        visitado[i] = 0;  // Inicializar los vértices como no visitados
    }

    // La clave del vértice inicial es 0
    clave[verticeInicial] = 0;

    ColaPrioridad* cola = crearColaPrioridad();

    // Insertar todos los vértices en la cola de prioridad
    for (int i = 0; i < numVertices; i++) {
        VerticePrim* v = crearVerticePrim(i, clave[i], padre[i]);
        insertarColaPrioridad(cola, v);
    }

    while (cola->numVertices > 0) {
        // Extraer el vértice con la menor clave
        VerticePrim* verticePrim = extraerMinimoColaPrioridad(cola);
        int verticeActual = verticePrim->vertice;
        visitado[verticeActual] = 1;  // Marcar el vértice como visitado

        // Recorrer las aristas del vértice actual
        Vertice* vertice = obtenerVertice(grafo, verticeActual);
        for (int i = 0; i < vertice->numAristas; i++) {
            Arista arista = vertice->aristas[i];
            int verticeDestino = arista.destino;

            // Si el vértice destino no ha sido visitado y el peso de la arista es menor que su clave actual,
            // actualizar su clave y su padre en el árbol de expansión mínima
            if (!visitado[verticeDestino] && arista.peso < clave[verticeDestino]) {
                clave[verticeDestino] = arista.peso;
                padre[verticeDestino] = verticeActual;

                // Actualizar la cola de prioridad con la nueva clave
                for (int j = 0; j < cola->numVertices; j++) {
                    if (cola->verticesPrim[j]->vertice == verticeDestino) {
                        cola->verticesPrim[j]->clave = arista.peso;
                        cola->verticesPrim[j]->padre = verticeActual;
                        break;
                    }
                }
            }
        }
    }

    // Mostrar el árbol de expansión mínima
    printf("Árbol de expansión mínima:\n");
    for (int i = 0; i < numVertices; i++) {
        if (padre[i] != -1) {
            printf("Arista: %d - %d, Peso: %d\n", padre[i], i, clave[i]);
        }
    }
}

int main() {
    Grafo* grafo = crearGrafo();

    insertarVertice(grafo, 0);
    insertarVertice(grafo, 1);
    insertarVertice(grafo, 2);

    insertarArista(grafo, 0, 1, 5);
    insertarArista(grafo, 0, 2, 10);

    mostrarListaAdyacencia(grafo);

    // recorridoAnchura(grafo, 0);
    // recorridoProfundidad(grafo, 0);
    // primeroEnAnchura(grafo, 0, 5);
    // primeroEnProfundidad(grafo, 0, 5);
    // primeroElMejor(grafo, 0, 5);
    // mostrarRutaEncontrada(grafo, 0, 5);
    // dijkstra(grafo, 0);
    // kruskal(grafo);
    
    // int verticeInicial = 0;  // Vértice inicial para el algoritmo de Prim
    //prim(grafo, verticeInicial);

    eliminarVertice(grafo, 1);
    eliminarArista(grafo, 0, 2);

    mostrarListaAdyacencia(grafo);

    eliminarTodo(grafo);

    return 0;
}
