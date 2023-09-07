#include "matrix/matrix.h"
#include "system/system.h"
#include "utils/utils.h"

int main()
{
    matrix_t matrix = read_and_create_matrix();
    matrix_t *(*current_system_solver)(matrix_t *);
    double time;
    double time_spent = 0.0;

    // for each type of system solver
    for (int i = 0; i < 3; i++)
    {
        // select the system solver
        current_system_solver = select_solver(i);

        // solve the system and measure the time spent
        time = timestamp();
        matrix_t *x = current_system_solver(&matrix);
        time = timestamp() - time;
        time_spent += time;

        printf("resulting matrix:\n");
        print_matrix(*x);
        printf("-------------------\n");
        printf("resulting solution:\n");
        double *results = retrossubs(x);

        printf("\n");
        printf("time spent: %1.8e\n", time);
        printf("\n");

        show_residual(&matrix, results);
    }


    free_matrix(matrix);
    return 0;
}