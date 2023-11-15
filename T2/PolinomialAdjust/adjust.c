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

OptIntervalPoint_t optRead_points(IntervalPoint_t *table, lli n)
{
    OptIntervalPoint_t optTable;
    optTable.x = malloc(sizeof(Interval_t) * n);
    optTable.y = malloc(sizeof(Interval_t) * n);
    for (lli i = 0; i < n; i++)
    {
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

OptIntervalMatrix_t *optLeastSquareMethod(OptIntervalPoint_t table, lli k, lli n)
{
    // optimized matrix A
    OptIntervalMatrix_t *A = optGenerate_interval_matrix(n + 1, n + 1);

    fill_first_row(A, table, k);

    fill_last_column(A, table, k);

    // REPLICATE THE NEEDED ROWS THROUGH ITS DIAGONAL
    replicate_diagonal_values(A);

    // fill in independent terms of matrix A (sum of y*x^i)
    fill_independent_terms(A, table, k);

    return A;
}

void fill_first_row(OptIntervalMatrix_t *A, OptIntervalPoint_t table, lli k)
{
    Interval_t zero_interval;
    zero_interval.min.f = 0.0;
    zero_interval.max.f = 0.0;

    // for each block
    for (lli b = 0; b < A->cols; b += BK)
    {
        // for each column within the block
        for (lli i = b; i < b + BK && i < A->cols; i++)
        {
            // fill in each first element of the column
            A->data[0 * A->cols + i] = zero_interval;
            // Unroll the loop by a factor of UF
            lli j;
            for (j = 0; j < k - UF + 1; j += UF)
            {
                for (lli u = 0; u < UF; u++) {
                    A->data[0 * A->cols + i] = op_sum_interval(A->data[0 * A->cols + i], op_pow_interval(table.x[j+u], i));
                }
            }
            // Handle the remaining elements
            for (; j < k; j++)
            {
                A->data[0 * A->cols + i] = op_sum_interval(A->data[0 * A->cols + i], op_pow_interval(table.x[j], i));
            }
        }
    }
}


void fill_last_column(OptIntervalMatrix_t *A, OptIntervalPoint_t table, lli k)
{
    // for each block
    for (lli b = 1; b < A->rows; b += BK)
    {
        // for each row within the block
        for (lli i = b; i < b + BK && i < A->rows; i++)
        {
            // fill in each last element of the row
            lli j;
            for (j = 0; j < k - UF + 1; j += UF)
            {
                for (lli u = 0; u < UF; u++) {
                    // filling last column
                    A->data[i * A->rows + (A->rows - 1)] = op_sum_interval(A->data[i * A->rows + A->rows - 1], op_pow_interval(table.x[j+u], i + A->cols - 1));
                }
            }
            // Handle the remaining elements
            for (; j < k; j++)
            {
                A->data[i * A->rows + (A->rows - 1)] = op_sum_interval(A->data[i * A->rows + A->rows - 1], op_pow_interval(table.x[j], i + A->cols - 1));
            }
        }
    }
}


void replicate_diagonal_values(OptIntervalMatrix_t *A)
{
    lli I;
    Interval_t replicate;
    // for each column from 1 to the end
    for (lli j = 1; j < A->cols; j++)
    {
        I = 1;
        replicate = A->data[0 * A->rows + j];
        // replicate the value of the first row through its diagonal
        lli l;
        for (l = j - 1; l >= UF - 1; l -= UF)
        {
            for (lli u = 0; u < UF; u++) {
                A->data[(I+u) * A->rows + l - u] = replicate;
            }
            I += UF;
        }
        // Handle the remaining elements
        for (; l >= 0; l--)
        {
            A->data[I * A->rows + l] = replicate;
            I++;
        }
    }

    // for each row from 1 to the end
    for (lli i = 1; i < A->rows; i++)
    {
        I = 1;
        replicate = A->data[i * A->rows + A->rows - 1];
        // replicate the value of the last column through its diagonal
        lli l;
        for (l = i + 1; l < A->rows - UF + 1; l += UF)
        {
            for (lli u = 0; u < UF; u++) {
                A->data[(l+u) * A->rows + (A->rows - I - 1 - u)] = replicate;
            }
            I += UF;
        }
        // Handle the remaining elements
        for (; l < A->rows; l++)
        {
            A->data[l * A->rows + (A->rows - I - 1)] = replicate;
            I++;
        }
    }
}

void fill_independent_terms(OptIntervalMatrix_t *A, OptIntervalPoint_t table, lli k)
{
    Interval_t zero_interval;
    zero_interval.min.f = 0.0;
    zero_interval.max.f = 0.0;

    // fill in independent terms of matrix A (sum of y*x^i)
    for (lli i = 0; i < A->rows; i++)
    {
        A->independent_terms[i] = zero_interval;
        for (lli j = 0; j < k; j++)
        {
            A->independent_terms[i] = op_sum_interval(A->independent_terms[i], op_mul_interval(table.y[j], op_pow_interval(table.x[j], i)));
        }
    }
}

void print_matrix(IntervalMatrix_t *matrix)
{
    for (lli i = 0; i < matrix->rows; i++)
    {
        for (lli j = 0; j < matrix->cols; j++)
        {
            printf("[%1.8e, %1.8e] ", matrix->data[i][j].min.f, matrix->data[i][j].max.f);
        }

        printf(" | [%1.8e, %1.8e]\n", matrix->independent_terms[i].min.f, matrix->independent_terms[i].max.f);

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

        printf(" | [%1.8e, %1.8e]\n", matrix->independent_terms[i].min.f, matrix->independent_terms[i].max.f);
        printf("\n");
    }
}