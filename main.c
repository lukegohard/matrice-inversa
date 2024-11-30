#include <stdio.h>
#include "src/inversa.h"
#include "src/macros.h"

int main() {

    int matrix[MAX][MAX];
    int n; // dimensione matrice --> n x n

    cleanConsole();
    printf(BLU "Inserisci la dimensione della matrice quadrata (max: " YEL "%d" BLU "): " RESET, MAX);
    scanf("%d", &n);
    cleanConsole();

    // Input di ciascun elemento della matrice
    for (int i=0;i<n;i++) {
        printf(BLU "Inserisci i numeri della riga " YEL "%d" BLU ".\n" RESET, i+1);
        for (int j=0;j<n;j++) {
            printf(CYN "Elemento " YEL "%d" CYN "x" YEL "%d" CYN ": " RESET, i+1,j+1);
            scanf("%d", &matrix[i][j]);
        }
        cleanConsole();
    }
    
    // calcolo e print del determinante della matrice
    int det = calcolaDeterminante(matrix,n);
    printf(BLU "Matrice " YEL "%d" BLU "x" YEL "%d" BLU ".\n" RESET, n,n);
    printMatrix(matrix, n);
    printf(BLU "\nIl determinante della matrice che hai inserito è: " MAG "%d" BLU ".\n\n" RESET , det);
    
    // se il determinante è 0, la matrice non è invertibile
    if (det == 0) {
        printf(RED "Il determinante della matrice che hai inserito è pari a 0,\nper cui non è possibile calcolare l'inversa.\n" RESET);
        return 1;
    } else { // calcolo e print della matrice inversa
        float inversa[MAX][MAX];
        calcolaInversa(matrix,n,inversa,det);
        printf(BLU "Matrice Inversa " YEL "%d" BLU "x" YEL "%d" BLU ".\n" RESET, n,n);
        printMatrixInversa(inversa,n);
    }

    return 0;
}

