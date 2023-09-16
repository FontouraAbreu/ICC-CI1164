#include "interpola.h"

point_t *read_points(int n) {

    point_t *points = malloc(n * sizeof(point_t));

    for (int i = 0; i < n; i++) {
        if (scanf("%lf %lf", &points[i].x, &points[i].y) != 2) {
            fprintf(stderr, "Erro ao ler ponto %d\n", i);
            return 1;
        }
    }
}

double * lagrange_method(point_t *table, int n, float x) {
    float numerator = calculate_numerator(table, n, x);
    for (int i=0; i<n; ++i) {
        
    }
}

float calculate_numerator(point_t *table, int n, float x) {
    float numerator = 1.0;
    for (int i=0; i<n; ++i) {
        numerator *= x - table[i].x;
    }
    return numerator;
}