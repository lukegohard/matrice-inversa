#include <stdbool.h>
#include "macros.h"

int calcolaDeterminante(int matrix[MAX][MAX], int n);

bool esisteRigaZeri(int matrix[MAX][MAX], int n);
bool esisteColonnaZeri(int matrix[MAX][MAX], int n);
bool esistonoRigheUguali(int matrix[MAX][MAX], int n);
bool esistonoColonneUguali(int matrix[MAX][MAX], int n);

bool sonoRigheUguali(int matrix[MAX][MAX], int n, int row1, int row2);
bool sonoColonneUguali(int matrix[MAX][MAX], int n, int col1, int col2);

int calcolaDeterminante(int matrix[MAX][MAX], int n) {
    
    // matrice 1x1
    if (n == 1) {
        return matrix[0][0];
    }
    // matrice 2x2
    if (n == 2) {
        return (matrix[0][0]*matrix[1][1]) - (matrix[0][1]*matrix[1][0]);
    }
    
    // controllo se una riga/colonna è composta da interamente 0
    if (esisteRigaZeri(matrix, n) || esisteColonnaZeri(matrix, n)) return 0;
    
    // controllo se due righe/colonne sono uguali
    if (esistonoRigheUguali(matrix,n) || esistonoColonneUguali(matrix,n)) return 0;


    // calcolo del determinante tramite Laplace
    int det = 0;
    for (int col=0;col<n;col++) {

        int sub_matrix[MAX][MAX], sub_n = n-1;

        for (int row=1; row<n;row++) {
            int sub_col = 0;

            for (int col_index=0;col_index<n;col_index++) {
                if (col_index == col) continue;
                sub_matrix[row-1][sub_col] = matrix[row][col_index];
                sub_col++;
            }
        }
        det += matrix[0][col] * (col % 2 == 0 ? 1 : -1) * calcolaDeterminante(sub_matrix,sub_n);
    }

    return det;
}

// verifica se in tutta la matrice è presente una riga composta interamente da 0
bool esisteRigaZeri(int matrix[MAX][MAX], int n) {

    for (int i=0;i<n;i++) {
    
        bool zero_row = true;
        for (int j=0;j<n;j++) {
            if (matrix[i][j] != 0) {
                zero_row = false;
                break;
            }
        }

        if (zero_row) {
            return true;
        }

    }
    return false;
}

// verifica se in tutta la matrice è presente una colonna composta interamente da 0
bool esisteColonnaZeri(int matrix[MAX][MAX], int n) {
    
    for (int i=0;i<n;i++) {
    
        bool zero_column = true;
        for (int j=0;j<n;j++) {
            if (matrix[j][i] != 0) {
                zero_column = false;
                break;
            }
        }

        if (zero_column) {
            return true;
        }
    }
    
    return false;
}

// verifica se in tutta la matrice sono presenti due righe uguali
bool esistonoRigheUguali(int matrix[MAX][MAX], int n) {

    for (int i=0;i<n-1;i++) {
        for (int j=i+1;j<n;j++) {
            if (sonoRigheUguali(matrix,n,i,j)) {
                return true;
            }
        }
    }
    return false;
}

// verifica se in tutta la matrice sono presenti due colonne uguali
bool esistonoColonneUguali(int matrix[MAX][MAX], int n) {

    for (int i=0;i<n-1;i++) {
        for (int j=i+1;j<n;j++) {
            if (sonoColonneUguali(matrix,n,i,j)) {
                return true;
            }
        }
    }
    return false;
}

// prende in input la matrice e due indici di due righe diverse e verifica se siano uguali
bool sonoRigheUguali(int matrix[MAX][MAX], int n, int row1, int row2) {

    for (int col=0;col<n;col++) {
        if (matrix[row1][col] != matrix[row2][col]) {
            return false;
        }
    }
    return true;
}

// prende in input la matrice e due indici di due colonne diverse e verifica se siano uguali
bool sonoColonneUguali(int matrix[MAX][MAX], int n, int col1, int col2) {

    for (int row=0;row<n;row++) {
        if (matrix[row][col1] != matrix[row][col2]) {
            return false;
        }
    }
    return true;
}