#include "system.h"

Interval_t *retrossubs(IntervalMatrix_t *A)
{
    int n = A->rows;
    int m = A->cols;
    Interval_t *x = malloc(sizeof(Interval_t) * n);

    // for each row
    for (int i = n - 1; i >= 0; i--)
    {
        x[i] = A->independent_terms[i];
        // for each column
        for (int j = i + 1; j < m; j++)
            // calculate the sum of the products
            x[i] = op_sub_interval(x[i], op_mul_interval(A->data[i][j], x[j]));
        // calculate the value of x(the independent term)
        x[i] = op_div_interval(x[i], A->data[i][i]);
    }
    return x;
}

IntervalMatrix_t *copy_matrix(IntervalMatrix_t *A)
{
    IntervalMatrix_t *x = malloc(sizeof(IntervalMatrix_t));
    x->rows = A->rows;
    x->cols = A->cols;
    x->data = malloc(sizeof(Interval_t *) * x->rows);
    x->independent_terms = malloc(sizeof(Interval_t) * x->rows);
    for (int i = 0; i < x->rows; i++)
    {
        x->data[i] = malloc(sizeof(Interval_t) * x->cols);
        for (int j = 0; j < x->cols; j++)
        {
            x->data[i][j] = A->data[i][j];
        }
        x->independent_terms[i] = A->independent_terms[i];
    }

    x->residual = A->residual;

    return x;
}

IntervalMatrix_t *partial_pivoting_system_solver(IntervalMatrix_t *A)
{
    Interval_t multiplier;

    int n = A->rows;
    // for each row
    for (int i = 0; i < n; i++)
    {
        // find the pivot
        int pivot = find_partial_pivot(A, i, i);
        // swap rows if necessary
        if (pivot != i)
            swap_rows(A, i, pivot);

        // for each column
        for (int j = i + 1; j < n; j++)
        {
            // calculate the multiplier
            multiplier = op_div_interval(A->data[j][i], A->data[i][i]);
            A->data[j][i].min.f = 0.0;
            A->data[j][i].max.f = 0.0;
            // for each element in the row
            for (int k = i + 1; k < n; k++)
            {
                // calculate the new value
                A->data[j][k] = op_sub_interval(A->data[j][k], op_mul_interval(A->data[i][k], multiplier));
            }
            // calculate the new independent term
            A->independent_terms[j] = op_sub_interval(A->independent_terms[j], op_mul_interval(A->independent_terms[i], multiplier));
        }
    }

    print_system(*A);

    return A;
}

void print_system(IntervalMatrix_t A)
{
    for (int i = 0; i < A.rows; i++)
    {
        for (int j = 0; j < A.cols; j++)
        {
            printf("[%1.8e, %1.8e] ", A.data[i][j].min.f, A.data[i][j].max.f);
        }
        printf("= [%1.8e, %1.8e]\n", A.independent_terms[i].min.f, A.independent_terms[i].max.f);
        printf("\n");
    }
}

IntervalMatrix_t *partial_pivoting_system_solver_no_multiplier(IntervalMatrix_t *A)
{
    int n = A->rows;
    int m = A->cols;
    // for each row
    for (int i = 0; i < n; i++)
    {
        // find the pivot
        // int pivot = find_partial_pivot(A, i, i);
        // // swap rows if necessary
        // if (pivot != i)
        //     swap_rows(A, i, pivot);

        // for each column
        for (int j = i + 1; j < m; j++)
        {
            // for each element in the row
            for (int k = i + 1; k < n; k++)
                // calculate the new value
                A->data[j][k] = op_sub_interval(op_mul_interval(A->data[j][k], A->data[i][i]), op_mul_interval(A->data[i][k], A->data[j][i]));
            // calculate the new independent term
            A->independent_terms[j] = op_sub_interval(op_mul_interval(A->independent_terms[j], A->data[i][i]), op_mul_interval(A->independent_terms[i], A->data[j][i]));
        }
    }

    return A;
}

int find_partial_pivot(IntervalMatrix_t *A, int row, int col)
{
    int imax = row;
    for (int i = row; i < A->rows; i++)
        if (greater_than(A->data[i][col], A->data[imax][col]))
            imax = i;
    return imax;
}

void swap_rows(IntervalMatrix_t *A, int row1, int row2)
{
    Interval_t *aux = A->data[row1];
    A->data[row1] = A->data[row2];
    A->data[row2] = aux;
    // swapping the independent terms
    Interval_t aux2 = A->independent_terms[row1];
    A->independent_terms[row1] = A->independent_terms[row2];
    A->independent_terms[row2] = aux2;
}

Interval_t *show_residual(IntervalMatrix_t *A, Interval_t *solution, IntervalPoint_t *table, int k)
{
    int m = A->cols;
    Interval_t *residual = malloc(sizeof(Interval_t) * k);
    for (int i = 0; i < k; i++)
    {
        residual[i].max.f = 0.0;
        residual[i].min.f = 0.0;

        // for each column
        for (int j = 0; j < m; j++)
        {
            residual[i] = op_sum_interval(residual[i], op_mul_interval(solution[j], op_pow_interval(table[i].x, j)));
        }
        residual[i] = op_sub_interval(residual[i], table[i].y);
    }
    return residual;
}