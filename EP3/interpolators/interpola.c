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

void lagrange_method(point_t *table, int n, double x) {
    double current_independent_term = 0.0;
    double *numerator = calculate_numerator(table, n, x);

    printf("\nP_%d(%1.8e)_L = ", n, x);
    for (int i=0; i<n; ++i) {
        current_independent_term =  table[i].y / calculate_denominator(table, n, i, x);
        printf("%1.8e * ", current_independent_term);
        print_numerator(numerator, n);
        printf(" + ");
    }
    printf("\n");
}

void print_numerator(double *numerator, int n) {
    for (int i=0; i<n; ++i) {
        printf("(x - %1.8e) * ", numerator[i]);
    }
}

double calculate_denominator(point_t *table, int n, int i, double x) {
    double denominator = 1.0;
    for (int j=0; j<n; ++j) {
        if (j != i) {
            denominator *= (table[i].x - table[j].x);
        }
    }
    denominator *= x - table[i].x;
    return denominator;
}

double *calculate_numerator(point_t *table, int n, double x) {
    double *numerator = malloc(n * sizeof(double));
    for (int i=0; i<n; ++i) {
        numerator[i] = table[i].x;
    }
    return numerator;
}