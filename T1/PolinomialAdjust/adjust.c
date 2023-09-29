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

IntervalMatrix_t *leastSquareMethod(IntervalPoint_t *table, int k, int n) { 
    // Allocate memory for matrices A and B
    IntervalMatrix_t *A = generate_interval_matrix(k+1, k+1);
    IntervalMatrix_t *B = generate_interval_matrix(k+1, 1);

    // Fill in entries of matrices A and B
    for (int i = 0; i <= k; i++) {
        for (int j = 0; j <= k; j++) {
            // Compute sum of x^(i+j) for all data points
            Interval_t sum = {0.0, 0.0};
            for (int l = 0; l < n; l++) {
                sum = op_sum_interval(sum, op_pow_interval(table[l].x, i+j));
            }
            A->data[i][j] = sum;
        }
        // Compute sum of y*x^i for all data points
        Interval_t sum = {0.0, 0.0};
        for (int l = 0; l < n; l++) {
            sum = op_sum_interval(sum, op_mul_interval(table[l].y, op_pow_interval(table[l].x, i)));
        }
        B->data[i][0] = sum;
    }

    // Solve system of linear equations using partial pivoting
    IntervalMatrix_t X = partial_pivoting_system_solver(A, B);

    // Free memory for matrices A and B
    interval_matrix_free(A);
    interval_matrix_free(B);
    return &X;
}