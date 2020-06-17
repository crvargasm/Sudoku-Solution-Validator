/**
 * 
 * Sudoku Solution Validator
 * Autor: Cristian Camilo Vargas Morales
 * Copyright 2020 - Cristian Camilo Vargas Morales
 * Note: The program annotations are in Spanish Language
*/

/*Libraries*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int sudoku[9][9] = {
        {6, 2, 4, 5, 3, 9, 1, 8, 7},
        {5, 1, 9, 7, 2, 8, 6, 3, 4},
        {8, 3, 7, 6, 1, 4, 2, 9, 5},
        {1, 4, 3, 8, 6, 5, 7, 2, 9},
        {9, 5, 8, 2, 4, 7, 3, 6, 1},
        {7, 6, 2, 3, 9, 1, 4, 5, 8},
        {3, 7, 1, 9, 5, 6, 8, 4, 2},
        {4, 9, 6, 1, 8, 2, 5, 7, 3},
        {2, 8, 5, 4, 7, 3, 9, 1, 6}
};

bool verificacion[11]; //Arreglo de verificacion de hilos finalizados con exito(1) o fracaso (0)
int auxCuadrados = 2; //usado para validar los hilos que recorren los cuadraditos de 3x3

typedef struct {    //Nos ayuda a pasar los datos al hilo
    int fila;
    int columna;
} parametro;

/*INICIO DECLARACION HILOS*/
pthread_t columnas, fila, primer_cuadro, segundo_cuadro, tercer_cuadro,
        cuarto_cuadro, quinto_cuadro, sexto_cuadro, septimo_cuadro, octavo_cuadro, noveno_cuadro;
/*FINAL DECLARACION HILOS*/

/*recorremos las columnas*/
void *recorrerColumna(void *parametros) {

    parametro *columna = (parametro *) parametros;
    int columnaInicial = columna->columna;
    int filaInicial = columna->fila;

    /*Ordenamos la columna */
    for (int i = columnaInicial; i < 9; i++) {
        int col[9] = {0}; //Columna ordenada
        for (int j = filaInicial; j < 9; j++) {
            int aux = sudoku[i][j];
            if (col[aux - 1] == 0 && aux > 0) { //Si la posicion esta libre y el numero del sudoku es > 0
                col[aux - 1] = aux;     //Asignamos en la posicion[a-1] el numero a // e.j. col[(5-1)]=5
            } else if (aux <= 0) {
                verificacion[0] = 0;
                printf("Lo lamento, en la columna [%d] hay un número no válido.\n", j + 1);
                pthread_exit(0);
            } else {
                verificacion[0] = 0;
                printf("Lo lamento, en la columna [%d] hay un numero repetido.\n", j + 1);
                pthread_exit(0);
            }
        }
    }
    verificacion[0] = 1;
    pthread_exit(0);    //Finalizamos la ejecución del hilo.
}

/*recorremos la filas*/
void *recorrerFilas(void *parametros) {

    parametro *fila = (parametro *) parametros;
    int columnaInicial = fila->columna;
    int filaInicial = fila->fila;

    for (int i = columnaInicial; i < 9; i++) {
        int fil[9] = {0};
        for (int j = filaInicial; j < 9; j++) {
            int aux = sudoku[i][j];
            if (fil[aux - 1] == 0 && aux > 0) {
                fil[aux - 1] = aux;
            } else if (aux <= 0) {
                verificacion[0] = 0;
                printf("Lo lamento, en la fila [%d] hay un número no válido.\n", i + 1);
                pthread_exit(0);
            } else {
                verificacion[0] = 0;
                printf("Lo lamento, en la fila [%d] hay un numero repetido.\n", i + 1);
                pthread_exit(0);
            }
        }
    }
    verificacion[1] = 1;
    pthread_exit(0);
}

/*recorremos los cuadraditos de 3x3*/
void *recorrerCuadrado(void *parametros) {

    parametro *cuadradroW = (parametro *) parametros;
    int filaInicial = cuadradroW->fila;
    int columnaInicial = cuadradroW->columna;
    int square[9] = {0};

    for (int i = filaInicial; i < filaInicial + 3; ++i) {
        for (int j = columnaInicial; j < columnaInicial + 3; ++j) {
            int aux = sudoku[i][j];
            if (square[aux - 1] == 0 && aux > 0) {
                square[aux - 1] = aux;
            }
            else {
                verificacion[auxCuadrados] = 0;
                auxCuadrados++;
                pthread_exit(0);
            }
        }
    }
    verificacion[auxCuadrados] = 1;
    auxCuadrados++;
    pthread_exit(0);
}

int main() {

    /*Asignamos (reservamos) cada parametro en memoria y asi poder pasar más fácil la ubicacion del Struct con &a*/
    parametro *verificarFilas = (parametro *) malloc(sizeof(parametro));
    verificarFilas->fila = 0;
    verificarFilas->columna = 0;

    parametro *verificarColumnas = (parametro *) malloc(sizeof(parametro));
    verificarColumnas->fila = 0;
    verificarColumnas->columna = 0;

    parametro *cuadro1 = (parametro *) malloc(sizeof(parametro));
    cuadro1->fila = 0;
    cuadro1->columna = 0;

    parametro *cuadro2 = (parametro *) malloc(sizeof(parametro));
    cuadro2->fila = 0;
    cuadro2->columna = 3;

    parametro *cuadro3 = (parametro *) malloc(sizeof(parametro));
    cuadro3->fila = 0;
    cuadro3->columna = 6;

    parametro *cuadro4 = (parametro *) malloc(sizeof(parametro));
    cuadro4->fila = 3;
    cuadro4->columna = 0;

    parametro *cuadro5 = (parametro *) malloc(sizeof(parametro));
    cuadro5->fila = 3;
    cuadro5->columna = 3;

    parametro *cuadro6 = (parametro *) malloc(sizeof(parametro));
    cuadro6->fila = 3;
    cuadro6->columna = 6;

    parametro *cuadro7 = (parametro *) malloc(sizeof(parametro));
    cuadro7->fila = 6;
    cuadro7->columna = 0;

    parametro *cuadro8 = (parametro *) malloc(sizeof(parametro));
    cuadro8->fila = 6;
    cuadro8->columna = 3;

    parametro *cuadro9 = (parametro *) malloc(sizeof(parametro));
    cuadro9->fila = 6;
    cuadro9->columna = 6;

    //Creamos los hilos (posicion Thread_t, atributos: NULL, funcionaRealizar, (void *) argumento a pasar)
    pthread_create(&columnas, NULL, recorrerColumna, (void *) verificarColumnas);
    pthread_create(&fila, NULL, recorrerFilas, (void *) verificarFilas);
    pthread_create(&primer_cuadro, NULL, recorrerCuadrado, (void *) cuadro1);
    pthread_create(&segundo_cuadro, NULL, recorrerCuadrado, (void *) cuadro2);
    pthread_create(&tercer_cuadro, NULL, recorrerCuadrado, (void *) cuadro3);
    pthread_create(&cuarto_cuadro, NULL, recorrerCuadrado, (void *) cuadro4);
    pthread_create(&quinto_cuadro, NULL, recorrerCuadrado, (void *) cuadro5);
    pthread_create(&sexto_cuadro, NULL, recorrerCuadrado, (void *) cuadro6);
    pthread_create(&septimo_cuadro, NULL, recorrerCuadrado, (void *) cuadro7);
    pthread_create(&octavo_cuadro, NULL, recorrerCuadrado, (void *) cuadro8);
    pthread_create(&noveno_cuadro, NULL, recorrerCuadrado, (void *) cuadro9);

    /*Esta llamada hace que el hilo 'a' se "duerma" hasta que el hilo 'b' termine.
    ---- pthread_join(identificador pthread_t del hilo por el que queremos esperar, (void) returnStatement **). ----
    Si en el "returnStatemente" le ponemos algo no NULL nos devolverá lo que ha devuelto el hilo hijo.*/
    
    pthread_join(columnas, NULL);
    pthread_join(fila, NULL);
    pthread_join(primer_cuadro, NULL);
    pthread_join(segundo_cuadro, NULL);
    pthread_join(tercer_cuadro, NULL);
    pthread_join(cuarto_cuadro, NULL);
    pthread_join(quinto_cuadro, NULL);
    pthread_join(sexto_cuadro, NULL);
    pthread_join(septimo_cuadro, NULL);
    pthread_join(octavo_cuadro, NULL);
    pthread_join(noveno_cuadro, NULL);

    /*Recorremos la matriz de verificacion y comprobamos si se resolvió o no*/
    for (int k = 0; k < 11; ++k) {
        if (!verificacion[k]) {
            printf("\nUpss... El Sudoku NO fue resuelto.\n");
            exit(0);
        }
    }
    printf("\nBien!!! Felicitaciones, el Sudoku fue resuelto.\n");
    return 0;
}
