#include "adjust.h"

IntervalPoint_t *read_points(int n)
{

    IntervalPoint_t *points = malloc(n * sizeof(IntervalPoint_t));
    if (points == NULL)
    {
        fprintf(stderr, "Erro ao alocar memória para os pontos\n");
        return NULL;
    }

    Float_t x, y;

    for (int i = 0; i < n; i++)
    {
        if (scanf("%f %f", &x.f, &y.f) != 2)
        {
            fprintf(stderr, "Erro ao ler ponto %d\n", i);
            return NULL;
        }
        points[i].x = generate_single_interval(&x);
        points[i].y = generate_single_interval(&y);
    }

    return points;
}

double leastSquareMethod(IntervalPoint_t *table, int k, int n) { 
    
}