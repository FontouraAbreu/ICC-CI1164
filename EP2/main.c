#include "matrix/matrix.h"
#include "system/system.h"

int main()
{
    matrix_t matrix = read_and_create_matrix();

    print_matrix(matrix);

    return 0;
}