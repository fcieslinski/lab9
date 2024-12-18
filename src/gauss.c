#include <stdio.h>
#include <math.h>
#include "gauss.h"

int eliminate(Matrix *mat, Matrix *b) {
    int n = mat->r;

    for (int k = 0; k < n; k++) {
        int max_row = k;
        double max_val = fabs(mat->data[k][k]);
        for (int i = k + 1; i < n; i++) {
            if (fabs(mat->data[i][k]) > max_val) {
                max_row = i;
                max_val = fabs(mat->data[i][k]);
            }
        }

        if (fabs(max_val) < 1e-12) {
            fprintf(stderr, "Macierz jest osobliwa. Dzielenie przez zero w kolumnie %d.\n", k);
            return 1;
        }

        if (max_row != k) {
            double *temp_row = mat->data[k];
            mat->data[k] = mat->data[max_row];
            mat->data[max_row] = temp_row;

            double temp_b = b->data[k][0];
            b->data[k][0] = b->data[max_row][0];
            b->data[max_row][0] = temp_b;
        }

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

