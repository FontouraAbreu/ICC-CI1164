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

Interval_t *leastSquareMethod(IntervalPoint_t *table, int k, int n) { 
    // Allocate memory for matrices A
    IntervalMatrix_t *A = generate_interval_matrix(k+1, k+1);
    Float_t zero = {0.0};
    Interval_t zero_interval = generate_single_interval(&zero);
    Interval_t sum;
    // Fill in entries of matrices A
    for (int i = 0; i <= k; i++) {
        // fill in entries of matrix A (sum of x^(i+j))
        for (int j = 0; j <= k; j++) {
            sum = zero_interval;
            for (int l = 0; l < n; l++) {
                sum = op_sum_interval(sum, op_pow_interval(table[l].x, i+j));
            }
            A->data[i][j] = sum;
        }

        // fill in independent terms of matrix A (sum of y*x^i)
        sum = zero_interval;
        for (int j = 0; j < n; j++) {
            sum = op_sum_interval(sum, op_mul_interval(table[j].y, op_pow_interval(table[j].x, i)));
        }
        A->independent_terms[i] = sum;
    }

    // Solve system of linear equations using partial pivoting
    IntervalMatrix_t *X = partial_pivoting_system_solver(A);

    // Free memory for matrices A
    free_intervalMatrix(A);
    return X->independent_terms;
}
