#include <stdio.h>
#include <math.h>
#include "gauss.h"

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b){
    int n = mat->r;

    for (int k = 0; k < n; k++) {
        
        if (fabs(mat->data[k][k]) < 1e-12) {
            fprintf(stderr, "Macierz jest osobliwa. Dzielenie przez zero w wierszu %d.\n", k);
            return 1;
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

