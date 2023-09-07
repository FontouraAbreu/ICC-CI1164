#include "system.h"

double *retrossubs(matrix_t *A)
{
    int n = A->size;
    double *x = malloc(sizeof(double) * n);
    // for each row
    for (int i = n - 1; i >= 0; i--)
    {
        double sum = 0.0;
        // for each column
        for (int j = i + 1; j < n; j++)
            // calculate the sum of the products
            sum += A->data[i][j] * x[j];
        // calculate the value of x(the independent term)
        x[i] = (A->independent_terms[i] - sum) / A->data[i][i];
        printf("x_%d = %1.8e\n", i, x[i]);
    }

    return x;
}

matrix_t *(*select_solver(int i))(matrix_t *A)
{
    switch (i)
    {
    case 0:
        printf("\n------PARTIAL PIVOTING------\n");
        return partial_pivoting_system_solver;
    case 1:
        printf("\n------PIVOTING WITHOUT MULTIPLIER------\n");
        return partial_pivoting_system_solver_no_multiplier;
    case 2:
        printf("\n------ALTERNATIVE------\n");
        return alternative_system_solver;
    default:
        return NULL;
    }
}

matrix_t *partial_pivoting_system_solver(matrix_t *A)
{
    // copying the matrix A to a new matrix x
    matrix_t *x = copy_matrix(A);
    int n = x->size;
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
            // calculate the multiplier
            double m = x->data[j][i] / x->data[i][i];
            x->data[j][i] = 0.0;
            // for each element in the row
            for (int k = i + 1; k < n; k++)
                // calculate the new value
                x->data[j][k] -= m * x->data[i][k];
            // calculate the new independent term
            x->independent_terms[j] -= m * x->independent_terms[i];
        }
    }

    return x;
}

matrix_t *partial_pivoting_system_solver_no_multiplier(matrix_t *A)
{
    // copying the matrix A to a new matrix x
    matrix_t *x = copy_matrix(A);
    int n = x->size;
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
            x->data[j][i] = 0.0;
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

matrix_t *alternative_system_solver(matrix_t *A)
{
    matrix_t *x = copy_matrix(A);
    int n = x->size;

    // for each row
    for (int i = 0; i < n; i++)
    {
        // for each column
        for (int j = i; j < n; j++)
        {
            // divide every element in the row by the pivot
            double divider = x->data[i][i];
            for (int k = i; k < n; k++)
                x->data[i][k] /= divider;
            x->independent_terms[i] /= divider;
        }
        // loop through the next rows
        // and use the multiplier of that row to update it
        for (int k = i + 1; k < n; k++)
        {
            double m = x->data[k][i];
            for (int l = i; l < n; l++)
                x->data[k][l] -= m * x->data[i][l];
            x->independent_terms[k] -= m * x->independent_terms[i];
        }
    }
    return x;
}

int find_partial_pivot(matrix_t *A, int row, int col)
{
    int imax = row;
    for (int i = row; i < A->size; i++)
        if (fabs(A->data[i][col]) > fabs(A->data[imax][col]))
            imax = i;
    return imax;
}

int find_total_pivot(matrix_t *A, int row, int col)
{
    int imax = row;
    int jmax = col;
    for (int i = row; i < A->size; i++)
        for (int j = col; j < A->size; j++)
            if (fabs(A->data[i][j]) > fabs(A->data[imax][jmax]))
            {
                imax = i;
                jmax = j;
            }
    return imax;
}

void swap_rows(matrix_t *A, int row1, int row2)
{
    double *aux = A->data[row1];
    A->data[row1] = A->data[row2];
    A->data[row2] = aux;
    // swapping the independent terms
    double aux2 = A->independent_terms[row1];
    A->independent_terms[row1] = A->independent_terms[row2];
    A->independent_terms[row2] = aux2;
}

matrix_t *copy_matrix(matrix_t *A)
{
    matrix_t *x = malloc(sizeof(matrix_t));
    x->size = A->size;
    x->data = malloc(sizeof(double *) * x->size);
    x->independent_terms = malloc(sizeof(double) * x->size);
    for (int i = 0; i < x->size; i++)
    {
        x->data[i] = malloc(sizeof(double) * x->size);
        for (int j = 0; j < x->size; j++)
        {
            x->data[i][j] = A->data[i][j];
        }
        x->independent_terms[i] = A->independent_terms[i];
    }

    x->residual = A->residual;

    return x;
}

void show_residual(matrix_t *A, double *results) {
    int n = A->size;
    double *b = A->independent_terms;
    // r = Ax - b
    double *r = malloc(sizeof(double) * n);
    double *Ax = malloc(sizeof(double) * n);
    double *residual = malloc(sizeof(double) * n);
    // for each row
    for (int i = 0; i < n; i++)
    {
        double sum = 0.0;
        // for each column
        for (int j = 0; j < n; j++)
            // calculate the sum of the products
            sum += A->data[i][j] * results[j];
        // calculate the value of Ax
        Ax[i] = sum;
        // calculate the value of r
        r[i] =Ax[i] - b[i];
        // calculate the value of the residual
        residual[i] = fabs(r[i] / b[i]);
    }

    printf("residual vector:\n");
    for (int i = 0; i < n; i++)
        printf("%1.8e\n", residual[i]);
}