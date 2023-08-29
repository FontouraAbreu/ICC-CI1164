#include "matrix.h"

matrix_t read_and_create_matrix()
{
    matrix_t matrix;
    int n;

    scanf("%d", &n);
    matrix.size = n;
    matrix.data = malloc(sizeof(double *) * n);

    for (int i = 0; i < n; i++)
    {
        // Allocating memory for each line of the matrix
        matrix.data[i] = malloc(sizeof(double) * n - 1);

        // filling a line of the matrix
        for (int j = 0; j < n; j++)
        {
            scanf("%lf", &matrix.data[i][j]);
        }

        // filling the independent terms
        scanf("%lf", &matrix.independent_terms[i]);
    }

    return matrix;
}

void print_matrix(matrix_t matrix)
{
    for (int i = 0; i < matrix.size; i++)
    {
        for (int j = 0; j < matrix.size; j++)
        {
            if (j == matrix.size - 1)
            {
                printf("| ");
            }
            printf("%1.8e ", matrix.data[i][j]);
        }
        printf("\n");
    }

    return;
}