#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_ENTRADAS 2
#define NUM_CAPAS_OCULTAS 1
#define NUM_NEURONAS_OCULTAS 2
#define NUM_SALIDAS 1
#define UMBRAL 0.5
#define TASA_APRENDIZAJE 0.1
#define NUM_ITERACIONES 10000

typedef struct {
    double* pesos;
    double* deltas;
    double valor;
} Neurona;

typedef struct {
    Neurona* neuronas;
    int numNeuronas;
} Capa;

typedef struct {
    Capa capaEntrada;
    Capa* capasOcultas;
    Capa capaSalida;
} RedNeuronal;

double funcionActivacion(double x) {
    return 1 / (1 + exp(-x));
}

double derivadaFuncionActivacion(double x) {
    return x * (1 - x);
}

void inicializarRedNeuronal(RedNeuronal* red) {
    int i, j, k;
    red->capaEntrada.numNeuronas = NUM_ENTRADAS;
    red->capaEntrada.neuronas = (Neurona*)malloc(NUM_ENTRADAS * sizeof(Neurona));

    for (i = 0; i < NUM_ENTRADAS; i++) {
        red->capaEntrada.neuronas[i].pesos = NULL;
        red->capaEntrada.neuronas[i].deltas = NULL;
        red->capaEntrada.neuronas[i].valor = 0.0;
    }

    red->capasOcultas = (Capa*)malloc(NUM_CAPAS_OCULTAS * sizeof(Capa));

    for (i = 0; i < NUM_CAPAS_OCULTAS; i++) {
        red->capasOcultas[i].numNeuronas = NUM_NEURONAS_OCULTAS;
        red->capasOcultas[i].neuronas = (Neurona*)malloc(NUM_NEURONAS_OCULTAS * sizeof(Neurona));

        for (j = 0; j < NUM_NEURONAS_OCULTAS; j++) {
            red->capasOcultas[i].neuronas[j].pesos = (double*)malloc((i == 0 ? NUM_ENTRADAS : NUM_NEURONAS_OCULTAS) * sizeof(double));
            red->capasOcultas[i].neuronas[j].deltas = (double*)malloc(NUM_NEURONAS_OCULTAS * sizeof(double));
            red->capasOcultas[i].neuronas[j].valor = 0.0;

            for (k = 0; k < (i == 0 ? NUM_ENTRADAS : NUM_NEURONAS_OCULTAS); k++) {
                red->capasOcultas[i].neuronas[j].pesos[k] = ((double)rand() / RAND_MAX) - 0.5;
                red->capasOcultas[i].neuronas[j].deltas[k] = 0.0;
            }
        }
    }

    red->capaSalida.numNeuronas = NUM_SALIDAS;
    red->capaSalida.neuronas = (Neurona*)malloc(NUM_SALIDAS * sizeof(Neurona));

    for (i = 0; i < NUM_SALIDAS; i++) {
        red->capaSalida.neuronas[i].pesos = (double*)malloc(NUM_NEURONAS_OCULTAS * sizeof(double));
        red->capaSalida.neuronas[i].deltas = (double*)malloc(NUM_NEURONAS_OCULTAS * sizeof(double));
        red->capaSalida.neuronas[i].valor = 0.0;

        for (j = 0; j < NUM_NEURONAS_OCULTAS; j++) {
            red->capaSalida.neuronas[i].pesos[j] = ((double)rand() / RAND_MAX) - 0.5;
            red->capaSalida.neuronas[i].deltas[j] = 0.0;
        }
    }
}

void liberarRedNeuronal(RedNeuronal* red) {
    int i, j;
    for (i = 0; i < NUM_ENTRADAS; i++) {
        free(red->capaEntrada.neuronas[i].pesos);
        free(red->capaEntrada.neuronas[i].deltas);
    }

    for (i = 0; i < NUM_CAPAS_OCULTAS; i++) {
        for (j = 0; j < NUM_NEURONAS_OCULTAS; j++) {
            free(red->capasOcultas[i].neuronas[j].pesos);
            free(red->capasOcultas[i].neuronas[j].deltas);
        }
        free(red->capasOcultas[i].neuronas);
    }

    for (i = 0; i < NUM_SALIDAS; i++) {
        free(red->capaSalida.neuronas[i].pesos);
        free(red->capaSalida.neuronas[i].deltas);
    }

    free(red->capaEntrada.neuronas);
    free(red->capasOcultas);
    free(red->capaSalida.neuronas);
}

void propagarEntrada(RedNeuronal* red, double* entrada) {
    int i, j, k;
    double sumatoria;

    for (i = 0; i < NUM_ENTRADAS; i++) {
        red->capaEntrada.neuronas[i].valor = entrada[i];
    }

    for (i = 0; i < NUM_CAPAS_OCULTAS; i++) {
        for (j = 0; j < NUM_NEURONAS_OCULTAS; j++) {
            sumatoria = 0.0;

            for (k = 0; k < (i == 0 ? NUM_ENTRADAS : NUM_NEURONAS_OCULTAS); k++) {
                sumatoria += red->capasOcultas[i].neuronas[j].pesos[k] * (i == 0 ? red->capaEntrada.neuronas[k].valor : red->capasOcultas[i - 1].neuronas[k].valor);
            }

            red->capasOcultas[i].neuronas[j].valor = funcionActivacion(sumatoria);
        }
    }

    for (i = 0; i < NUM_SALIDAS; i++) {
        sumatoria = 0.0;

        for (j = 0; j < NUM_NEURONAS_OCULTAS; j++) {
            sumatoria += red->capaSalida.neuronas[i].pesos[j] * red->capasOcultas[NUM_CAPAS_OCULTAS - 1].neuronas[j].valor;
        }

        red->capaSalida.neuronas[i].valor = funcionActivacion(sumatoria);
    }
}

void retropropagarError(RedNeuronal* red, double* objetivo) {
    int i, j, k;
    double error;

    for (i = 0; i < NUM_SALIDAS; i++) {
        error = objetivo[i] - red->capaSalida.neuronas[i].valor;

        for (j = 0; j < NUM_NEURONAS_OCULTAS; j++) {
            red->capaSalida.neuronas[i].deltas[j] = error * derivadaFuncionActivacion(red->capaSalida.neuronas[i].valor) * red->capasOcultas[NUM_CAPAS_OCULTAS - 1].neuronas[j].valor;
        }
    }

    for (i = NUM_CAPAS_OCULTAS - 1; i >= 0; i--) {
        for (j = 0; j < NUM_NEURONAS_OCULTAS; j++) {
            error = 0.0;

            for (k = 0; k < NUM_SALIDAS; k++) {
                error += red->capaSalida.neuronas[k].pesos[j] * red->capaSalida.neuronas[k].deltas[j];
            }

            red->capasOcultas[i].neuronas[j].deltas[j] = derivadaFuncionActivacion(red->capasOcultas[i].neuronas[j].valor) * error;
        }
    }

    for (i = NUM_CAPAS_OCULTAS - 1; i >= 0; i--) {
        for (j = 0; j < NUM_NEURONAS_OCULTAS; j++) {
            for (k = 0; k < (i == 0 ? NUM_ENTRADAS : NUM_NEURONAS_OCULTAS); k++) {
                red->capasOcultas[i].neuronas[j].pesos[k] += TASA_APRENDIZAJE * red->capasOcultas[i].neuronas[j].deltas[k] * (i == 0 ? red->capaEntrada.neuronas[k].valor : red->capasOcultas[i - 1].neuronas[k].valor);
            }
        }
    }

    for (i = 0; i < NUM_SALIDAS; i++) {
        for (j = 0; j < NUM_NEURONAS_OCULTAS; j++) {
            red->capaSalida.neuronas[i].pesos[j] += TASA_APRENDIZAJE * red->capaSalida.neuronas[i].deltas[j] * red->capasOcultas[NUM_CAPAS_OCULTAS - 1].neuronas[j].valor;
        }
    }
}

void entrenarRedNeuronal(RedNeuronal* red) {
    double entrada[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    double objetivo[4][1] = {{0}, {1}, {1}, {0}};
    int i, j, iteracion;
    double errorPromedio;

    for (iteracion = 0; iteracion < NUM_ITERACIONES; iteracion++) {
        errorPromedio = 0.0;

        for (i = 0; i < 4; i++) {
            propagarEntrada(red, entrada[i]);
            retropropagarError(red, objetivo[i]);

            double error = 0.0;
            for (j = 0; j < NUM_SALIDAS; j++) {
                error += pow(objetivo[i][j] - red->capaSalida.neuronas[j].valor, 2);
            }
            errorPromedio += error;
        }

        errorPromedio /= 4;
        printf("Iteracion: %d, Error Promedio: %f\n", iteracion, errorPromedio);

        if (errorPromedio < 0.01) {
            break;
        }
    }
}

void probarRedNeuronal(RedNeuronal* red) {
    double entrada[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    int i, j;

    printf("Resultados:\n");
    for (i = 0; i < 4; i++) {
        propagarEntrada(red, entrada[i]);
        for (j = 0; j < NUM_SALIDAS; j++) {
            printf("Entrada: %d %d, Salida: %f\n", (int)entrada[i][0], (int)entrada[i][1], red->capaSalida.neuronas[j].valor);
        }
    }
}

int main() {
    RedNeuronal red;
    inicializarRedNeuronal(&red);
    entrenarRedNeuronal(&red);
    probarRedNeuronal(&red);
    liberarRedNeuronal(&red);
    return 0;
}



