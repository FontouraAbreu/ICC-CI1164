#include "interpolators/interpola.h"

int main(int argc, char *argv[]) {
    int n;
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Erro ao ler n\n");
        return 1;
    }
    
    if (argc != 2) {
        fprintf(stderr, "O programa precisa de 1 argumento posicional 'x' que será aproximado\n");
        return 1;
    }

    float x = *argv[1];

    point_t *table = read_points(n);

    lagrange_method(table, n, x);

    newton_method(table, n, x);

    return 0;
}