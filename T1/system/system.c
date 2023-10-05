#include "system.h"

Interval_t *retrossubs(IntervalMatrix_t *A)
{
    int n = A->rows;
    int m = A->cols;
    Interval_t *x = malloc(sizeof(Interval_t) * n);
    Float_t zero;
    zero.f = 0.0;
    Interval_t zero_interval = generate_single_interval(&zero);
    // for each row
    for (int i = n - 1; i >= 0; i--)
    {
        Interval_t sum = zero_interval;
        // for each column
        for (int j = i + 1; j < m; j++)
            // calculate the sum of the products
            sum = op_sum_interval(sum, op_mul_interval(A->data[i][j], x[j]));
        // calculate the value of x(the independent term)
        x[i] = op_div_interval(op_sub_interval(A->independent_terms[i], sum), A->data[i][i]);
        // printf("x_%d = %1.8e\n", i, x[i]);
    }

    return x;
}

IntervalMatrix_t *partial_pivoting_system_solver(IntervalMatrix_t *A)
{
    int n = A->rows;
    int m = A->cols;
    Float_t zero;
    zero.f = 0.0;
    Interval_t zero_interval = generate_single_interval(&zero);
    // for each row
    for (int i = 0; i < n; i++)
    {
        // find the pivot
        int pivot = find_partial_pivot(A, i, i);
        // swap rows if necessary
        if (pivot != i)
            swap_rows(A, i, pivot);

        // for each column
        for (int j = i + 1; j < m; j++)
        {
            // calculate the multiplier
            Interval_t multiplier = op_div_interval(A->data[j][i], A->data[i][i]);
            A->data[j][i].min.f = 0.0;
            A->data[j][i].max.f = 0.0;
            // for each element in the row
            for (int k = i + 1; k < n; k++)
                // calculate the new value
                A->data[j][k] = op_sub_interval(A->data[j][k], op_mul_interval(multiplier, A->data[i][k]));
            // calculate the new independent term
            A->independent_terms[j] = op_sub_interval(A->independent_terms[j], op_mul_interval(multiplier, A->independent_terms[i]));
        }
    }

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

/*
IntervalMatrix_t *partial_pivoting_system_solver_no_multiplier(IntervalMatrix_t *A)
{
    // copying the matrix A to a new matrix x
    IntervalMatrix_t *x = copy_matrix(A);
    int n = x->rows;
    // for each row
    for (int i = 0; i < n; i++)
    {
        // find the pivot
        int pivot = find_partial_pivot(x, i, i);
        // swap rows if necessary
        if (pivot != i)
            swap_rows(x, i, pivot);

        // for each column
        for (int j = i + 1; j < n; j++)
        {
            // for each element in the row
            for (int k = i + 1; k < n; k++)
                // calculate the new value
                x->data[j][k] = x->data[j][k] * x->data[i][i] - x->data[i][k] * x->data[j][i];
            // calculate the new independent term
            x->independent_terms[j] = x->independent_terms[j] * x->data[i][i] - x->independent_terms[i] * x->data[j][i];
        }
    }

    return x;
}
*/

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

Interval_t *show_residual(IntervalMatrix_t *A, IntervalPoint_t *table, int n)
{
    Interval_t *residual = malloc(sizeof(Interval_t) * n);
    Float_t zero = {0.0};
    Interval_t zero_interval = generate_single_interval(&zero);
    // for each row
    for (int i = 0; i < n; i++)
    {
        Interval_t sum = zero_interval;
        // for each column
        for (int j = 0; j < n; j++)
            // calculate the sum of the products
            sum = op_sum_interval(sum, op_mul_interval(A->data[i][j], table[j].y));
        // calculate the value of x(the independent term)
        residual[i] = op_sub_interval(table[i].y, sum);
    }

    return residual;
}
