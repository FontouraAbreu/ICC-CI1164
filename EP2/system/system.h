#ifndef SYSTEM_H
#define SYSTEM_H
#include "../matrix/matrix.h"
#include <math.h>

/*
 *   retrossubs of a triangular matrix
 *   @param A: matrix_t(the triangular matrix)
 *   @brief Solve a system using retrossubs
 *   @return x: double*(the solutions of the system)
 *   @attention Keep in mind that the matrix must be triangular. Every system solver should use this function after generating a triangular matrix
 */
double *retrossubs(matrix_t *A);

/*
 *   parcial pivoting system solver
 *   @param A: matrix_t
 *   @return x: matrix_t
 *   @brief Will generate a triangular matrix using parcial pivoting method
 *   @complexity O(n^3)
 */
matrix_t *partial_pivoting_system_solver(matrix_t *A);

/*
 *   total pivoting system solver
 *   @param A: matrix_t
 *   @return x: matrix_t
 *   @brief Will generate a triangular matrix using total pivoting method
 *   @complexity O(n^3)
 */
matrix_t *partial_pivoting_system_solver_no_multiplier(matrix_t *A);

/*
 *   alternative system solver
 *   @param A: matrix_t
 *   @return x: matrix_t
 *   @brief Will use the alternate method to achieve the solution of a system
 *   @complexity O(n^2)
 */
matrix_t *alternative_system_solver(matrix_t *A);

/*
 *   select solver function
 *   @param i: int(the iteration)
 *   @return pointer to function that solves the system
 *   @brief Will return a pointer to a function that solves the system based on the iteration
 */
matrix_t *(*select_solver(int i))(matrix_t *A);

/*
 *   find pivot of a column
 *   @param A: matrix_t
 *   @param row: int
 *   @param col: int
 *   @return max: int
 *   @brief Will loop through the rows of a matrix and find the pivot
 *   @complexity O(n)
 */
int find_partial_pivot(matrix_t *A, int row, int col);

/*
 *   find pivot of a matrix
 *   @param A: matrix_t
 *   @param row: int
 *   @param col: int
 *   @return max: int
 *   @brief Will loop through the rows and columns of a matrix and find the pivot
 *   @complexity O(n^2)
 */
int find_total_pivot(matrix_t *A, int row, int col);

/*
 *   copy matrix A to a new matrix
 *   @param A: matrix_t(the matrix to be copied)
 *   @return x: matrix_t(the new matrix pointer)
 *   @brief Will copy: data, independent_terms and size from A to x.
 *   @complexity O(n^2)
 */
matrix_t *copy_matrix(matrix_t *A);

/*
 *   swap rows of a matrix
 *   @param A: matrix_t
 *   @param row1: int
 *   @param row2: int
 *   @brief Will swap two rows of a matrix, changing their pointers
 *   @complexity O(n)
 */
void swap_rows(matrix_t *A, int row1, int row2);

/*
 *   show residual of a system
 *   @param A: matrix_t(the matrix of the system)
 *   @param x: double*(the solutions of the system)
 *   @brief Will show the residual of a system
 *   @complexity O(n^2)
 */
void show_residual(matrix_t *A, double *results);

#endif // SYSTEM_H
