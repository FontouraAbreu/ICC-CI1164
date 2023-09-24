#include "interpola.h"

point_t *read_points(int n) {

    point_t *points = malloc(n * sizeof(point_t));

    for (int i = 0; i < n; i++) {
        if (scanf("%lf %lf", &points[i].x, &points[i].y) != 2) {
            fprintf(stderr, "Erro ao ler ponto %d\n", i);
            return NULL;
        }
    }

    return points;
}

double lagrange_method(point_t *table, int n, double x) {
    double result = 0.0;
    for (int i = 0; i < n; i++) {
        double term = table[i].y;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                term *= (x - table[j].x) / (table[i].x - table[j].x);
            }
        }
        result += term;
    }
    printf("\nP_%d(%1.8e)_L = %1.8e\n", n, x, result);
    return result;
}

double **calculate_divided_differences(point_t *table, int n, double x){
    double **divided_differences = malloc(n * sizeof(double *));

    // Allocate memory
    for (int i = 0; i < n; i++) {
        divided_differences[i] = malloc(n * sizeof(double));
    }

    // setting the first column of the divided differences table to f(x_i)
    // for (int i = 0; i < n; i++) {
    //     divided_differences[i][0] = table[i].y;
    // }

    // Calculate the divided differences
    for (int j = 0; j < n; j++) {
        for (int i = j; i < n; i++) {
            if(j == 0){
                divided_differences[i][j] = table[i].y;
            }
            else{
            divided_differences[i][j] = (divided_differences[i][j-1] - divided_differences[i-1][j-1]) / (table[i].x - table[i-j].x);
            }
        }
    }

    return divided_differences;
}
double newton_method(point_t *table, int n, double x){
    double **divided_differences = calculate_divided_differences(table, n, x);

    // Calculate polynomial value
    double result = divided_differences[0][0];
    double term = 1.0;
    for (int j = 1; j < n; j++) {
        term *= (x - table[j-1].x);
        result += divided_differences[j][j] * term;
    }

    printf("\nP_%d(%1.8e)_N = %1.8e\n", n, x, result);

    // Free memory
    for (int i = 0; i < n; i++) {
        free(divided_differences[i]);
    }
    free(divided_differences);

    return result;
}


void print_divided_differences(double **divided_differences, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%1.8e ", divided_differences[i][j]);
        }
        printf("\n");
    }
}