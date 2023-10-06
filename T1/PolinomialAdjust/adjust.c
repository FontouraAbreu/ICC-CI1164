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

IntervalMatrix_t *leastSquareMethod(IntervalPoint_t *table, int k, int n)
{
    // Allocate memory for matrices A
    IntervalMatrix_t *A = generate_interval_matrix(n + 1, n + 1);
    Interval_t zero_interval;
    zero_interval.min.f = 0.0;
    zero_interval.max.f = 0.0; 

    // Fill in entries of matrices A
    for (int i = 0; i <= n; i++)
    {
        // fill in entries of matrix A (sum of x^(i+j))
        for (int j = 0; j <= n; j++)
        {
            Interval_t sum = zero_interval;
            // A->data[i][j] = sum of x^(i+j)
            // WE CAN OPTIMIZE THIS BY USING THE SYMMETRY OF THE MATRIX A[0][2] = A[2][0]; A[1][3] = A[3][1] ...
            for (int l = 0; l <= k; l++)
                sum = op_sum_interval(sum, op_pow_interval(table[l].x, i + j));
            A->data[i][j] = sum;
        }

        // fill in independent terms of matrix A (sum of y*x^i)
        Interval_t sum = zero_interval;
        for (int j = 0; j < k; j++)
        {
            sum = op_sum_interval(sum, op_mul_interval(table[j].y, op_pow_interval(table[j].x, i)));
        }
        A->independent_terms[i] = sum;
    }

    // Solve system of linear equations using partial pivoting
    A = partial_pivoting_system_solver(A);

    return A;
}
