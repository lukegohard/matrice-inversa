#include <stdio.h>
#include "macros.h"

void printMatrix(int **matrix, int n);
void printMatrixInversa(float **matrix, int n);
void cleanConsole();

// semplice print di una matrice
void printMatrix(int **matrix, int n) {

    for (int i=0;i<n;i++) {
        printf(BLU "[ " RESET);
        for (int j=0;j<n;j++) {
            printf(CYN "%d " RESET, matrix[i][j]);
        }
        printf(BLU "]\n" RESET);
    }
}

// print della matrice inversa (differenza è che matrix_inversa[][] è un float)
void printMatrixInversa(float **matrix, int n) {

    for (int i=0;i<n;i++) {
        printf(BLU "[ " RESET);
        for (int j=0;j<n;j++) {
            printf(CYN "%.2f " RESET, matrix[i][j]);
        }
        printf(BLU "]\n" RESET);
    }
}

// pulisce la console
void cleanConsole() {
    printf("\033[H\033[J");
}