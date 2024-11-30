#include "determinante.h"
#include "helpers-matrice.h"
#include "macros.h"


void calcolaInversa(int matrix[MAX][MAX], int n, float inversa[MAX][MAX], int det);
void calcolaMatriceComplementiAlgebrici(int matrix[MAX][MAX], int n, int compl_matrix[MAX][MAX]);
void calcolaTrasposta(int matrix[MAX][MAX], int n, int trasposta[MAX][MAX]);

// Calcola l'inversa di una matrice di interi.
// matrix -> matrice originale, det -> suo determinante
//
// B -> matrice dei complementi algebrici di matrix
// B^T -> trasposta di B
//
// inversa = (1/det)*B^T
void calcolaInversa(int matrix[MAX][MAX], int n, float inversa[MAX][MAX], int det) {

    // matrice 1x1
    if (n == 1) {
        inversa[0][0] = 1.00 / matrix[0][0];
        return;
    }

    // calcolo della matrice dei complementi algebrici di matrix
    int compl_matrix[MAX][MAX];
    calcolaMatriceComplementiAlgebrici(matrix,n,compl_matrix);

    // trasposizione della matrice dei complementi algebrici
    int trasp_compl_matrix[MAX][MAX];
    calcolaTrasposta(compl_matrix,n,trasp_compl_matrix);

    // (1/det) * trasp_compl_matrix
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) {
            inversa[i][j] = (1.0/det) * trasp_compl_matrix[i][j];
        }
    }

}

// Calcolo dei complementi algebrici di ogni elemento di matrix
void calcolaMatriceComplementiAlgebrici(int matrix[MAX][MAX], int n, int compl_matrix[MAX][MAX]) {

    int sub_matrix[MAX][MAX];

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

}

// trasposizione della matrice data in input
void calcolaTrasposta(int matrix[MAX][MAX], int n, int trasposta[MAX][MAX]) {
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) {
            trasposta[i][j] = matrix[j][i];
        }
    }
}