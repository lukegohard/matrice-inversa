#include <stdio.h>
#include <stdlib.h>

#include "src/inversa.h"
#include "src/macros.h"

int main() {

    int n; // dimensione matrice --> n x n

    cleanConsole();
    do {
        printf(BLU "Inserisci la dimensione della matrice quadrata " MAG "(-1 per uscire)" BLU ": " RESET);
        scanf("%d", &n);
        if (n == -1) {
            cleanConsole();
            printf(MAG"Ci siamo salutati troppo presto.. :(\n"RESET);
            return 0;
        } else if (n <= 0) {
            cleanConsole();
            printf(RED"Il numero inserito deve essere maggiore di 0!\n"RESET);
        }
    } while (n <= 0);
    cleanConsole();

    int **matrix = malloc(n * sizeof(int *)); // Allocazione delle righe
    if (matrix == NULL) {
        printf(RED"Errore nell'allocazione di memoria.\n" RESET);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        matrix[i] = malloc(n * sizeof(int)); // Allocazione delle colonne
        if (matrix[i] == NULL) {
            printf(RED"Errore nell'allocazione di memoria.\n" RESET);
            return 1;
        }
    }
    
    for (int i = 0; i < n; i++) {
        printf(BLU "Inserisci i numeri della riga " YEL "%d" BLU " separati da spazio " CYN "(es. 1 2 3)" BLU ": " RESET, i+1);
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    cleanConsole();

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

        float **inversa = malloc(n * sizeof(float *)); // Allocazione delle righe
        if (inversa == NULL) {
            printf(RED"Errore nell'allocazione di memoria.\n" RESET);
            return 1;
        }

        for (int i = 0; i < n; i++) {
            inversa[i] = malloc(n * sizeof(int)); // Allocazione delle colonne
            if (inversa[i] == NULL) {
                printf(RED"Errore nell'allocazione di memoria.\n" RESET);
                return 1;
            }
        }

        calcolaInversa(matrix,n,inversa,det);
        printf(BLU "Matrice Inversa " YEL "%d" BLU "x" YEL "%d" BLU ".\n" RESET, n,n);
        printMatrixInversa(inversa,n);


        for (int i = 0; i < n; i++) {
            free(inversa[i]); // Libera ciascuna riga
        }
        free(inversa);
    }
    
    for (int i = 0; i < n; i++) {
        free(matrix[i]); // Libera ciascuna riga
    }
    free(matrix);
    return 0;
}

