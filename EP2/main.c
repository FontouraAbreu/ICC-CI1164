#include "matrix/matrix.h"
#include "system/system.h"

int main()
{
    matrix_t matrix = read_and_create_matrix();
    printf("\nyour matrix:\n");
    print_matrix(matrix);
    matrix_t *(*current_system_solver)(matrix_t *);
    for (int i = 0; i < 2; i++)
    {
        current_system_solver = select_solver(i);
        matrix_t *x = current_system_solver(&matrix);
        printf("resulting matrix:\n");
        print_matrix(*x);
        printf("-------------------\n");
        printf("resulting solution:\n");
        retrossubs(x);
    }

    free_matrix(matrix);
    return 0;
}