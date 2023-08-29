#ifndef SYSTEM_H
#define SYSTEM_H
#include "../matrix/matrix.h"

matrix_t *parcial_pivoting_system_solver(matrix_t *A, matrix_t *b, int *err);
matrix_t *total_pivoting_system_solver(matrix_t *A, matrix_t *b, int *err);
matrix_t *refinement_system_solver(matrix_t *A, matrix_t *b, matrix_t *x, int *err);

#endif // SYSTEM_H
