#include "matrix/matrix.h"

int main()
{
    matrix_t matrix = read_and_create_matrix();

    print_matrix(matrix);

    free_matrix(matrix);

    return 0;
}