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