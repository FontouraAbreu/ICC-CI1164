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
    double numerator = calculate_numerator(table, n, x);
    double denominator = 1.0;
    double Px = 0.0;
    double Li;
    for (int i=0; i<n; ++i) {
        denominator = calculate_denominator(table, n, i, x);
        Li = numerator / denominator;
        Px += Li * table[2*i+1].y;
    }
    printf("\nP_%d(%1.8e)_L = %1.8e\n", n, x, Px);
    return Px;
}

void print_numerator(double *numerator, int n) {
    for (int i=0; i<n; ++i) {
        printf("(x - %1.8e) * ", numerator[i]);
    }
}

double calculate_denominator(point_t *table, int n, int i, double x) {
    double denominator = 1.0;
    double xi = table[2*i].x;
    for (int j=0; j<n; ++j) {
        if (j != i) {
            denominator *= (xi - table[2*j].x);
        }
    }
    denominator *= (x - xi);
    return denominator;
}

double calculate_numerator(point_t *table, int n, double x) {
    double numerator = 1.0;
    for (int i=0; i<n; ++i) {
        numerator *= (x - table[2*i].x);
    }
    return numerator;
}

void newton_method(point_t *table, int n, double x){

}

void calculate_divided_differences(point_t *table, int n, double x){
    double **divided_differences = malloc(n * sizeof(double *));

    //j caminha nas colunas
    for(int j = 0; j < n; j++){
        //i caminha nas linhas
        for(int i = j; i < n*2; i++){
            if(j == 0){
                divided_differences[i][j] = table[j].y;
                i++;
            } 
            else {
                divided_differences[i][j] = (divided_differences[i+1][j-1] - divided_differences[i-1][j-1]) / (divided_differences[0][i+j]- divided_differences[0][i-j]);
                i++;
            }
        }
    }
}

void print_divided_differences(double **divided_differences, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%1.8e ", divided_differences[i][j]);
        }
        printf("\n");
    }
}