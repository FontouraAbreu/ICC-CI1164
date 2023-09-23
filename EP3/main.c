#include "interpolators/interpola.h"

int main(int argc, char *argv[]) {
    int n;
    if (argc != 2) {
        fprintf(stderr, "O programa precisa de 1 argumento posicional 'x' que será aproximado\n");
        return 1;
    }

    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Erro ao ler n\n");
        return 1;
    }
    
    double x = strtod(argv[1], NULL);

    point_t *table = read_points(n);

    double Lx = lagrange_method(table, n, x);

    newton_method(table, n, x);

    return 0;
}