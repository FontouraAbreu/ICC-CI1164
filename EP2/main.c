#include "matrix/matrix.h"
#include "system/system.h"

int main()
{
    matrix_t matrix = read_and_create_matrix();
    matrix_t *(*current_system_solver)(matrix_t *);

    // for each type of system solver   
    for (int i = 0; i < 3; i++)
    {
        current_system_solver = select_solver(i);
        matrix_t *x = current_system_solver(&matrix);
        printf("resulting matrix:\n");
        print_matrix(*x);
        printf("-------------------\n");
        printf("resulting solution:\n");
        double *results = retrossubs(x);
        printf("\n");
        show_residual(&matrix, results);
    }

    free_matrix(matrix);
    return 0;
}