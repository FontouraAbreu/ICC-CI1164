#include "system.h"

Interval_t *retrossubs(IntervalMatrix_t *A)
{
    lli n = A->rows;
    lli m = A->cols;
    Interval_t *x = malloc(sizeof(Interval_t) * n);

    // for each row
    for (lli i = n - 1; i >= 0; i--)
    {
        x[i] = A->independent_terms[i];
        // for each column
        for (lli j = i + 1; j < m; j++)
            // calculate the sum of the products
            x[i] = op_sub_interval(x[i], op_mul_interval(A->data[i][j], x[j]));
        // calculate the value of x(the independent term)
        x[i] = op_div_interval(x[i], A->data[i][i]);
    }
    return x;
}

Interval_t *op_retrossubs(OptIntervalMatrix_t *A) {
    lli n = A->rows;
    lli m = A->cols;
    Interval_t *x = malloc(sizeof(Interval_t) * n);

    // for each row
    for (lli i = n - 1; i >= 0; i--)
    {
        x[i] = A->independent_terms[i];
        // for each column
        lli j;
        for (j = i + 1; j < m - 3; j += 4)
        {
            // calculate the sum of the products
            x[i] = op_sub_interval(x[i], op_mul_interval(A->data[i * m + j], x[j]));
            x[i] = op_sub_interval(x[i], op_mul_interval(A->data[i * m + j + 1], x[j + 1]));
            x[i] = op_sub_interval(x[i], op_mul_interval(A->data[i * m + j + 2], x[j + 2]));
            x[i] = op_sub_interval(x[i], op_mul_interval(A->data[i * m + j + 3], x[j + 3]));
        }
        // Handle the remaining elements
        for (; j < m; j++)
        {
            x[i] = op_sub_interval(x[i], op_mul_interval(A->data[i * m + j], x[j]));
        }
        // calculate the value of x(the independent term)
        x[i] = op_div_interval(x[i], A->data[i * m + i]);
    }
    return x;
}

IntervalMatrix_t *partial_pivoting_system_solver(IntervalMatrix_t *A)
{
    Interval_t multiplier;

    lli n = A->rows;
    // for each row
    for (lli i = 0; i < n; i++)
    {
        // find the pivot
        lli pivot = find_partial_pivot(A, i, i);
        // swap rows if necessary
        if (pivot != i)
            swap_rows(A, i, pivot);

        // for each column
        for (lli j = i + 1; j < n; j++)
        {
            // calculate the multiplier
            multiplier = op_div_interval(A->data[j][i], A->data[i][i]);
            A->data[j][i].min.f = 0.0;
            A->data[j][i].max.f = 0.0;
            // for each element in the row
            for (lli k = i + 1; k < n; k++)
            {
                // calculate the new value
                A->data[j][k] = op_sub_interval(A->data[j][k], op_mul_interval(A->data[i][k], multiplier));
            }
            // calculate the new independent term
            A->independent_terms[j] = op_sub_interval(A->independent_terms[j], op_mul_interval(A->independent_terms[i], multiplier));
        }
    }

    return A;
}

void swap_rows(IntervalMatrix_t *A, lli row1, lli row2)
{
    Interval_t *aux = A->data[row1];
    A->data[row1] = A->data[row2];
    A->data[row2] = aux;
    // swapping the independent terms
    Interval_t aux2 = A->independent_terms[row1];
    A->independent_terms[row1] = A->independent_terms[row2];
    A->independent_terms[row2] = aux2;
}


OptIntervalMatrix_t *optPartial_pivoting_system_solver(OptIntervalMatrix_t *A)
{
    Interval_t multiplier;
    lli pivot;

    lli n = A->rows;
    // for each row
    for (lli i = 0; i < n; i++)
    {
        // find the pivot
        pivot = op_find_partial_pivot(A, i, i);
        // swap rows if necessary
        if (pivot != i)
            op_swap_rows(A, i, pivot);

        // for each column
        for (lli j = i + 1; j < n; j++)
        {
            // calculate the multiplier
            multiplier = op_div_interval(A->data[j * n + i], A->data[i * n + i]);
            A->data[j * n + i].min.f = 0.0;
            A->data[j * n + i].max.f = 0.0;
            // for each element in the row
            lli k;
            for (k = i + 1; k < n - 3; k += 4)
            {
                // calculate the new value
                A->data[j * n + k] = op_sub_interval(A->data[j * n + k], op_mul_interval(A->data[i * n + k], multiplier));
                A->data[j * n + k + 1] = op_sub_interval(A->data[j * n + k + 1], op_mul_interval(A->data[i * n + k + 1], multiplier));
                A->data[j * n + k + 2] = op_sub_interval(A->data[j * n + k + 2], op_mul_interval(A->data[i * n + k + 2], multiplier));
                A->data[j * n + k + 3] = op_sub_interval(A->data[j * n + k + 3], op_mul_interval(A->data[i * n + k + 3], multiplier));
            }
            // Handle the remaining elements
            for (; k < n; k++)
            {
                A->data[j * n + k] = op_sub_interval(A->data[j * n + k], op_mul_interval(A->data[i * n + k], multiplier));
            }
            // calculate the new independent term
            A->independent_terms[j] = op_sub_interval(A->independent_terms[j], op_mul_interval(A->independent_terms[i], multiplier));
        }
    }

    return A;
}

void op_swap_rows(OptIntervalMatrix_t *A, lli row1, lli row2)
{
    Interval_t aux;

    for (lli j = 0; j < A->cols; j++)
    {
        aux = A->data[row1 * A->cols + j];
        A->data[row1 * A->cols + j] = A->data[row2 * A->cols + j];
        A->data[row2 * A->cols + j] = aux;
    }

    // swapping the independent terms
    aux = A->independent_terms[row1];
    A->independent_terms[row1] = A->independent_terms[row2];
    A->independent_terms[row2] = aux;

    return;
}

void print_system(IntervalMatrix_t A)
{
    for (lli i = 0; i < A.rows; i++)
    {
        for (lli j = 0; j < A.cols; j++)
        {
            printf("[%1.8e, %1.8e] ", A.data[i][j].min.f, A.data[i][j].max.f);
        }
        printf("= [%1.8e, %1.8e]\n", A.independent_terms[i].min.f, A.independent_terms[i].max.f);
        printf("\n");
    }
}

lli find_partial_pivot(IntervalMatrix_t *A, lli row, lli col)
{
    lli imax = row;
    for (lli i = row; i < A->rows; i++)
        if (greater_than(A->data[i][col], A->data[imax][col]))
            imax = i;
    return imax;
}

lli op_find_partial_pivot(OptIntervalMatrix_t *A, lli row, lli col)
{
    lli imax = row;
    lli n = A->rows;
    for (lli i = row; i < n; i++)
        if (greater_than(A->data[i * n + col], A->data[imax * n + col]))
            imax = i;
    return imax;
}


Interval_t *show_residual(IntervalMatrix_t *A, Interval_t *solution, IntervalPoint_t *table, lli k)
{
    lli m = A->cols;
    Interval_t *residual = malloc(sizeof(Interval_t) * k);
    for (lli i = 0; i < k; i++)
    {
        residual[i].max.f = 0.0;
        residual[i].min.f = 0.0;

        // for each column
        for (lli j = 0; j < m; j++)
        {
            residual[i] = op_sum_interval(residual[i], op_mul_interval(solution[j], op_pow_interval(table[i].x, j)));
        }
        residual[i] = op_sub_interval(residual[i], table[i].y);
    }
    return residual;
}