#include "interpola/interpola.h"

int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Erro ao ler n\n");
        return 1;
    }

    point_t *points = malloc(n * sizeof(point_t));

    for (int i = 0; i < n; i++) {
        if (scanf("%lf %lf", &points[i].x, &points[i].y) != 2) {
            fprintf(stderr, "Erro ao ler ponto %d\n", i);
            return 1;
        }
    }

    return 0;
}