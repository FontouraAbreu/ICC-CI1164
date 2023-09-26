#include "adjust.h"

point_t *read_points(int n)
{

    point_t *points = malloc(n * sizeof(point_t));

    for (int i = 0; i < n; i++)
    {
        if (scanf("%lf %lf", &points[i].x, &points[i].y) != 2)
        {
            fprintf(stderr, "Erro ao ler ponto %d\n", i);
            return NULL;
        }
    }

    return points;
}

double leastSquareMethod(point_t *table, int k, int n) {
    
}