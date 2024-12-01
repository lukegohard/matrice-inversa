#include "determinante.h"
#include "helpers-matrice.h"
#include "macros.h"


void calcolaInversa(int **matrix, int n, float **inversa, int det);
void calcolaMatriceComplementiAlgebrici(int **matrix, int n, int **compl_matrix);
void calcolaTrasposta(int **matrix, int n, int **trasposta);

// Calcola l'inversa di una matrice di interi.
// matrix -> matrice originale, det -> suo determinante
//
// B -> matrice dei complementi algebrici di matrix
// B^T -> trasposta di B
//
// inversa = (1/det)*B^T
void calcolaInversa(int **matrix, int n, float **inversa, int det) {

    // matrice 1x1
    if (n == 1) {
        inversa[0][0] = 1.00 / matrix[0][0];
        return;
    }

    // calcolo della matrice dei complementi algebrici di matrix
    int **compl_matrix = malloc(n * sizeof(int *)); // Allocazione delle righe
    if (compl_matrix == NULL) {
        printf(RED"Errore nell'allocazione di memoria.\n" RESET);
        return;
    }

    for (int i = 0; i < n; i++) {
        compl_matrix[i] = malloc(n * sizeof(int)); // Allocazione delle colonne
        if (compl_matrix[i] == NULL) {
            printf(RED"Errore nell'allocazione di memoria.\n" RESET);
            return;
        }
    }
    calcolaMatriceComplementiAlgebrici(matrix,n,compl_matrix);

    // trasposizione della matrice dei complementi algebrici
    int **trasp_compl_matrix = malloc(n * sizeof(int *)); // Allocazione delle righe
    if (trasp_compl_matrix == NULL) {
        printf(RED"Errore nell'allocazione di memoria.\n" RESET);
        return;
    }

    for (int i = 0; i < n; i++) {
        trasp_compl_matrix[i] = malloc(n * sizeof(int)); // Allocazione delle colonne
        if (trasp_compl_matrix[i] == NULL) {
            printf(RED"Errore nell'allocazione di memoria.\n" RESET);
            return;
        }
    }
    calcolaTrasposta(compl_matrix,n,trasp_compl_matrix);

    // (1/det) * trasp_compl_matrix
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) {
            inversa[i][j] = (1.0/det) * trasp_compl_matrix[i][j];
        }
    }


    for (int i = 0; i < n; i++) {
        free(compl_matrix[i]); // Libera ciascuna riga
        free(trasp_compl_matrix[i]);
    }

    free(compl_matrix);
    free(trasp_compl_matrix);
}

// Calcolo dei complementi algebrici di ogni elemento di matrix
void calcolaMatriceComplementiAlgebrici(int **matrix, int n, int **compl_matrix) {

    int **sub_matrix = malloc(n * sizeof(int *)); // Allocazione delle righe
    if (sub_matrix == NULL) {
        printf(RED"Errore nell'allocazione di memoria.\n" RESET);
        return;
    }

    for (int i = 0; i < n; i++) {
        sub_matrix[i] = malloc(n * sizeof(int)); // Allocazione delle colonne
        if (sub_matrix[i] == NULL) {
            printf(RED"Errore nell'allocazione di memoria.\n" RESET);
            return;
        }
    }

    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) {

            int subR = 0;
            for (int x=0; x<n; x++) {
                if (x==i) continue;
                int subC = 0;
                for (int y=0; y<n; y++) {
                    if (y==j) continue;

                    sub_matrix[subR][subC] = matrix[x][y];
                    subC++;
                }
                subR++;
            }

            compl_matrix[i][j] = ((i+j) % 2 == 0 ? 1 : -1) * calcolaDeterminante(sub_matrix,n-1);

        }
    }
    
    for (int i = 0; i < n; i++) {
        free(sub_matrix[i]); // Libera ciascuna riga
    }
    free(sub_matrix);
}

// trasposizione della matrice data in input
void calcolaTrasposta(int **matrix, int n, int **trasposta) {
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) {
            trasposta[i][j] = matrix[j][i];
        }
    }
}