#include "adjust.h"

IntervalPoint_t *read_points(lli n)
{

    IntervalPoint_t *points = malloc(n * sizeof(IntervalPoint_t));
    if (points == NULL)
    {
        fprintf(stderr, "Erro ao alocar memória para os pontos\n");
        return NULL;
    }

    Float_t x, y;

    for (lli i = 0; i < n; i++)
    {
        if (scanf("%lf %lf", &x.f, &y.f) != 2)
        {
            fprintf(stderr, "Erro ao ler ponto %lld\n", i);
            return NULL;
        }
        points[i].x = generate_single_interval(&x);
        points[i].y = generate_single_interval(&y);
    }

    return points;
}

OptIntervalPoint_t optRead_points(IntervalPoint_t *table, lli n) {
    OptIntervalPoint_t optTable;
    optTable.x = malloc(sizeof(Interval_t) * n);
    optTable.y = malloc(sizeof(Interval_t) * n);
    for (lli i = 0; i < n; i++) {
        optTable.x[i] = table[i].x;
        optTable.y[i] = table[i].y;
    }

    return optTable;
}

IntervalMatrix_t *leastSquareMethod(IntervalPoint_t *table, lli k, lli n)
{
    // Allocate memory for matrices A
    IntervalMatrix_t *A = generate_interval_matrix(n + 1, n + 1);
    Interval_t zero_interval, sum;
    zero_interval.min.f = 0.0;
    zero_interval.max.f = 0.0;

    // Fill in entries of matrices A
    for (lli i = 0; i <= n; i++)
    {
        // fill in entries of matrix A (sum of x^(i+j))
        for (lli j = 0; j <= n; j++)
        {
            sum = zero_interval;
            // A->data[i][j] = sum of x^(i+j)
            // WE CAN OPTIMIZE THIS BY USING THE SYMMETRY OF THE MATRIX A[0][2] = A[2][0]; A[1][3] = A[3][1] ...
            for (lli l = 0; l < k; l++)
                sum = op_sum_interval(sum, op_pow_interval(table[l].x, i + j));
            A->data[i][j] = sum;
        }

        // fill in independent terms of matrix A (sum of y*x^i)
        sum = zero_interval;
        for (lli j = 0; j < k; j++)
        {
            sum = op_sum_interval(sum, op_mul_interval(table[j].y, op_pow_interval(table[j].x, i)));
        }
        A->independent_terms[i] = sum;
    }

    return A;
}

OptIntervalMatrix_t *optLeastSquareMethod(OptIntervalPoint_t table, lli k, lli n) {
    // optimized matrix A
    OptIntervalMatrix_t *A = optGenerate_interval_matrix(n + 1, n + 1);
    Interval_t zero_interval, sum;
    zero_interval.min.f = 0.0;
    zero_interval.max.f = 0.0;


    // for each column
    for (lli i = 0; i <= n; i++) {
        sum = zero_interval;
        // fill in each first element of the column
        A->data[0 * n + i] = zero_interval;
        for (lli j = 0; j < k; j++) {
                // filling line 0
                A->data[0 * n + i] = op_sum_interval(A->data[0 * n + i], op_pow_interval(table.x[j], i));                
        }
    }

    // NEED TO FILL THE LAST COLUMN WITH THEIR RESPECTIVE VALUE



    return A;
}


void print_matrix(IntervalMatrix_t *matrix)
{
    for (lli i = 0; i < matrix->rows; i++)
    {
        for (lli j = 0; j < matrix->cols; j++)
        {
            printf("[%1.8e, %1.8e] ", matrix->data[i][j].min.f, matrix->data[i][j].max.f);
        }
        printf("\n");
    }
}

void print_opt_matrix(OptIntervalMatrix_t *matrix)
{
    for (lli i = 0; i < matrix->rows; i++)
    {
        for (lli j = 0; j < matrix->cols; j++)
        {
            printf("[%1.8e, %1.8e] ", matrix->data[i * matrix->cols + j].min.f, matrix->data[i * matrix->cols + j].max.f);
        }
        printf("\n");
    }
}