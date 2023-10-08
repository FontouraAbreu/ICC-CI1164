#include "matrix.h"

matrix_t read_and_create_matrix()
{
    matrix_t matrix;
    int n;

    if(!(scanf("%d", &n)))
    {
        printf("failed to read interer");
        exit(1);
    }
    matrix.size = n;
    matrix.data = malloc(sizeof(double *) * n);
    (matrix.data != NULL)
        ? NULL
        : exit(1);

    matrix.independent_terms = malloc(sizeof(double) * n);
    (matrix.independent_terms != NULL)
        ? NULL
        : exit(1);

    matrix.residual = malloc(sizeof(double) * n);
    (matrix.residual != NULL)
        ? NULL
        : exit(1);

    for (int i = 0; i < n; i++)
    {
        // Allocating memory for each line of the matrix
        matrix.data[i] = malloc(sizeof(double) * n);
        (matrix.data[i] != NULL)
            ? NULL
            : exit(1);

        // filling a line of the matrix
        for (int j = 0; j < n; j++)
        {
            if(!(scanf("%lf", &matrix.data[i][j])))
            {
                printf("failed to read double");
                exit(1);
            }
        }

        // filling the independent terms
        if(!(scanf("%lf", &matrix.independent_terms[i])))
        {
            printf("failed to read double");
            exit(1);
        }
        matrix.residual[i] = 0.0;
    }

    return matrix;
}

void print_matrix(matrix_t matrix)
{
    for (int i = 0; i < matrix.size; i++)
    {
        for (int j = 0; j < matrix.size; j++)
        {
            printf("%1.8e ", matrix.data[i][j]);
        }
        printf("\t| %1.8e\n", matrix.independent_terms[i]);
    }

    return;
}

void free_matrix(matrix_t matrix)
{
    for (int i = 0; i < matrix.size; i++)
    {
        free(matrix.data[i]);
    }
    free(matrix.data);
    free(matrix.independent_terms);

    return;
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