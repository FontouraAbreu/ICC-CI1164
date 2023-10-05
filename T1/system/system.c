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
            printf("i = %d, j = %d, multiplier = [%1.8e, %1.8e]\n", i, j, multiplier.min.f, multiplier.max.f);
            A->data[j][i].min.f = 0.0;
            A->data[j][i].max.f = 0.0;
            // for each element in the row
            for (int k = i + 1; k < m; k++){
                // if (j == 2 && k == 2){
                //     printf("A[%d][%d] = [%1.8e, %1.8e]\n", j, k, A->data[j][k].min.f, A->data[j][k].max.f);
                //     printf("multiplier = [%1.8e, %1.8e]\n", multiplier.min.f, multiplier.max.f);
                //     printf("m * A[%d][%d] = [%1.8e, %1.8e]\n", i, k, op_mul_interval(multiplier, A->data[i][k]).min.f, op_mul_interval(multiplier, A->data[i][k]).max.f);
                // }
                // calculate the new value
                A->data[j][k] = op_sub_interval(A->data[j][k], op_mul_interval(A->data[i][k], multiplier));
            }
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


IntervalMatrix_t *partial_pivoting_system_solver_no_multiplier(IntervalMatrix_t *A)
{
    int n = A->rows;
    int m = A->cols;
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
