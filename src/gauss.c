#include <stdio.h>
#include <math.h>
#include "gauss.h"

/**
 * Zwraca 0 - eliminacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b) {
    int n = mat->r;

    for (int k = 0; k < n; k++) {
        // Wybór elementu głównego (pivoting)
        int max_row = k;
        double max_value = fabs(mat->data[k][k]);

        for (int i = k + 1; i < n; i++) {
            if (fabs(mat->data[i][k]) > max_value) {
                max_row = i;
                max_value = fabs(mat->data[i][k]);
            }
        }

        // Sprawdzenie, czy znaleziono odpowiedni element główny
        if (max_value < 1e-12) {
            fprintf(stderr, "Macierz jest osobliwa. Dzielenie przez zero w kolumnie %d.\n", k);
            return 1;
        }

        // Zamiana wierszy w macierzy głównej
        if (max_row != k) {
            for (int j = 0; j < n; j++) {
                double temp = mat->data[k][j];
                mat->data[k][j] = mat->data[max_row][j];
                mat->data[max_row][j] = temp;
            }

            // Zamiana wierszy w macierzy wynikowej
            double temp_b = b->data[k][0];
            b->data[k][0] = b->data[max_row][0];
            b->data[max_row][0] = temp_b;
        }

        // Eliminacja Gaussa
        for (int i = k + 1; i < n; i++) {
            double factor = mat->data[i][k] / mat->data[k][k];

            for (int j = k; j < n; j++) {
                mat->data[i][j] -= factor * mat->data[k][j];
            }

            b->data[i][0] -= factor * b->data[k][0];
        }
    }

    return 0;
}


