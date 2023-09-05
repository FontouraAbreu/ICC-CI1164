#include "matrix.h"

matrix_t read_and_create_matrix()
{
    matrix_t matrix;
    int n;

    scanf("%d", &n);
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
            scanf("%lf", &matrix.data[i][j]);
        }

        // filling the independent terms
        scanf("%lf", &matrix.independent_terms[i]);
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
        printf("| %1.8e\n", matrix.independent_terms[i]);
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