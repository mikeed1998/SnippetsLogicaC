#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_ENTRADAS 2
#define NUM_NEURONAS_OCULTAS 4
#define NUM_SALIDAS 1
#define NUM_ITERACIONES 10000
#define TASA_APRENDIZAJE 0.1

typedef struct {
    double valor;
    double delta;
    double *pesos;
} Neurona;

typedef struct {
    Neurona *neuronas;
    int numNeuronas;
} Capa;

typedef struct {
    Capa capaEntrada;
    Capa *capasOcultas;
    Capa capaSalida;
    int numCapasOcultas;
} RedNeuronal;

double funcionActivacion(double x) {
    return 1 / (1 + exp(-x));
}

double derivadaFuncionActivacion(double x) {
    return x * (1 - x);
}

void inicializarRedNeuronal(RedNeuronal *red) {
    int i, j;

    // Capa de entrada
    red->capaEntrada.numNeuronas = NUM_ENTRADAS;
    red->capaEntrada.neuronas = (Neurona *)malloc(sizeof(Neurona) * NUM_ENTRADAS);
    for (i = 0; i < NUM_ENTRADAS; i++) {
        red->capaEntrada.neuronas[i].valor = 0;
    }

    // Capas ocultas
    red->numCapasOcultas = 1;  // Puedes ajustar el número de capas ocultas según tus necesidades
    red->capasOcultas = (Capa *)malloc(sizeof(Capa) * red->numCapasOcultas);

    for (i = 0; i < red->numCapasOcultas; i++) {
        red->capasOcultas[i].numNeuronas = NUM_NEURONAS_OCULTAS;
        red->capasOcultas[i].neuronas = (Neurona *)malloc(sizeof(Neurona) * NUM_NEURONAS_OCULTAS);
        for (j = 0; j < NUM_NEURONAS_OCULTAS; j++) {
            red->capasOcultas[i].neuronas[j].valor = 0;
            red->capasOcultas[i].neuronas[j].delta = 0;
            red->capasOcultas[i].neuronas[j].pesos = (double *)malloc(sizeof(double) * (i == 0 ? NUM_ENTRADAS : NUM_NEURONAS_OCULTAS));
            for (int k = 0; k < (i == 0 ? NUM_ENTRADAS : NUM_NEURONAS_OCULTAS); k++) {
                red->capasOcultas[i].neuronas[j].pesos[k] = (double)rand() / RAND_MAX;  // Inicialización aleatoria de pesos
            }
        }
    }

    // Capa de salida
    red->capaSalida.numNeuronas = NUM_SALIDAS;
    red->capaSalida.neuronas = (Neurona *)malloc(sizeof(Neurona) * NUM_SALIDAS);
    for (i = 0; i < NUM_SALIDAS; i++) {
        red->capaSalida.neuronas[i].valor = 0;
        red->capaSalida.neuronas[i].delta = 0;
        red->capaSalida.neuronas[i].pesos = (double *)malloc(sizeof(double) * NUM_NEURONAS_OCULTAS);
        for (j = 0; j < NUM_NEURONAS_OCULTAS; j++) {
            red->capaSalida.neuronas[i].pesos[j] = (double)rand() / RAND_MAX;  // Inicialización aleatoria de pesos
        }
    }
}

void liberarRedNeuronal(RedNeuronal *red) {
    int i, j, k;

    free(red->capaEntrada.neuronas);

    for (i = 0; i < red->numCapasOcultas; i++) {
        for (j = 0; j < NUM_NEURONAS_OCULTAS; j++) {
            free(red->capasOcultas[i].neuronas[j].pesos);
        }
        free(red->capasOcultas[i].neuronas);
    }
    free(red->capasOcultas);

    for (i = 0; i < NUM_SALIDAS; i++) {
        free(red->capaSalida.neuronas[i].pesos);
    }
    free(red->capaSalida.neuronas);
}

void propagarEntrada(RedNeuronal *red, double *entrada) {
    int i, j, k;

    // Asignar valores de entrada a la capa de entrada
    for (i = 0; i < red->capaEntrada.numNeuronas; i++) {
        red->capaEntrada.neuronas[i].valor = entrada[i];
    }

    // Propagación hacia adelante en las capas ocultas
    for (i = 0; i < red->numCapasOcultas; i++) {
        Capa *capaOculta = &red->capasOcultas[i];
        Capa *capaAnterior = (i == 0) ? &red->capaEntrada : &red->capasOcultas[i - 1];

        for (j = 0; j < capaOculta->numNeuronas; j++) {
            Neurona *neurona = &capaOculta->neuronas[j];
            neurona->valor = 0;

            for (k = 0; k < capaAnterior->numNeuronas; k++) {
                neurona->valor += capaAnterior->neuronas[k].valor * neurona->pesos[k];
            }

            neurona->valor = funcionActivacion(neurona->valor);
        }
    }

    // Propagación hacia adelante en la capa de salida
    Capa *capaSalida = &red->capaSalida;
    Capa *capaAnterior = &red->capasOcultas[red->numCapasOcultas - 1];

    for (i = 0; i < capaSalida->numNeuronas; i++) {
        Neurona *neurona = &capaSalida->neuronas[i];
        neurona->valor = 0;

        for (j = 0; j < capaAnterior->numNeuronas; j++) {
            neurona->valor += capaAnterior->neuronas[j].valor * neurona->pesos[j];
        }

        neurona->valor = funcionActivacion(neurona->valor);
    }
}

void retropropagacion(RedNeuronal *red, double *objetivo) {
    int i, j, k;

    // Calcular el delta para la capa de salida
    for (i = 0; i < red->capaSalida.numNeuronas; i++) {
        Neurona *neurona = &red->capaSalida.neuronas[i];
        neurona->delta = (objetivo[i] - neurona->valor) * derivadaFuncionActivacion(neurona->valor);
    }

    // Calcular el delta para las capas ocultas en orden inverso
    for (i = red->numCapasOcultas - 1; i >= 0; i--) {
        Capa *capaOculta = &red->capasOcultas[i];
        Capa *capaSiguiente = (i == red->numCapasOcultas - 1) ? &red->capaSalida : &red->capasOcultas[i + 1];

        for (j = 0; j < capaOculta->numNeuronas; j++) {
            Neurona *neurona = &capaOculta->neuronas[j];
            neurona->delta = 0;

            for (k = 0; k < capaSiguiente->numNeuronas; k++) {
                neurona->delta += capaSiguiente->neuronas[k].delta * capaSiguiente->neuronas[k].pesos[j];
            }

            neurona->delta *= derivadaFuncionActivacion(neurona->valor);
        }
    }

    // Actualizar pesos en las capas ocultas en orden directo
    for (i = 0; i < red->numCapasOcultas; i++) {
        Capa *capaOculta = &red->capasOcultas[i];
        Capa *capaAnterior = (i == 0) ? &red->capaEntrada : &red->capasOcultas[i - 1];

        for (j = 0; j < capaOculta->numNeuronas; j++) {
            Neurona *neurona = &capaOculta->neuronas[j];

            for (k = 0; k < capaAnterior->numNeuronas; k++) {
                neurona->pesos[k] += TASA_APRENDIZAJE * capaAnterior->neuronas[k].valor * neurona->delta;
            }
        }
    }

    // Actualizar pesos en la capa de salida
    Capa *capaSalida = &red->capaSalida;
    Capa *capaAnterior = &red->capasOcultas[red->numCapasOcultas - 1];

    for (i = 0; i < capaSalida->numNeuronas; i++) {
        Neurona *neurona = &capaSalida->neuronas[i];

        for (j = 0; j < capaAnterior->numNeuronas; j++) {
            neurona->pesos[j] += TASA_APRENDIZAJE * capaAnterior->neuronas[j].valor * neurona->delta;
        }
    }
}

void entrenarRedNeuronal(RedNeuronal *red, double entradas[][NUM_ENTRADAS], double objetivos[][NUM_SALIDAS], int numPatrones) {
    int i, j;

    for (i = 0; i < NUM_ITERACIONES; i++) {
        double errorTotal = 0;

        for (j = 0; j < numPatrones; j++) {
            double *entrada = entradas[j];
            double *objetivo = objetivos[j];

            propagarEntrada(red, entrada);
            retropropagacion(red, objetivo);

            for (int k = 0; k < NUM_SALIDAS; k++) {
                errorTotal += fabs(objetivo[k] - red->capaSalida.neuronas[k].valor);
            }
        }

        printf("Iteración %d, Error: %lf\n", i + 1, errorTotal);
    }
}

void ejecutarRedNeuronal(RedNeuronal *red, double entrada[]) {
    propagarEntrada(red, entrada);

    for (int i = 0; i < NUM_SALIDAS; i++) {
        printf("Salida %d: %lf\n", i + 1, red->capaSalida.neuronas[i].valor);
    }
}

int main() {
    // Definir los datos de entrenamiento
    double entradas[][NUM_ENTRADAS] = {
        {0, 0},
        {0, 1},
        {1, 0},
        {1, 1}
    };

    double objetivos[][NUM_SALIDAS] = {
        {0},
        {1},
        {1},
        {0}
    };

    // Crear la red neuronal
    RedNeuronal red;
    inicializarRedNeuronal(&red);

    // Entrenar la red neuronal
    entrenarRedNeuronal(&red, entradas, objetivos, 4);

    // Ejecutar la red neuronal con nuevas entradas
    double nuevaEntrada[] = {1, 0};
    ejecutarRedNeuronal(&red, nuevaEntrada);

    // Liberar la memoria utilizada por la red neuronal
    liberarRedNeuronal(&red);

    return 0;
}
