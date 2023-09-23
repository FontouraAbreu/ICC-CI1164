#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>

typedef struct matrix
{
    int size;                  // matrix size
    double **data;             // pointer to an array of *double
    double *independent_terms; // pointer to an array of double
    double *residual;           // residual of the matrix
} matrix_t;

/*
 * Will read from stdin a size n
 * and then a matrix of size n x n
 * @return a pointer to a matrix_t
 */
matrix_t read_and_create_matrix();

/*
* Will only create a matrix of size n x n
* initializing the each element, independent terms and residual to 0.0
* @param n: int
* @return a pointer to a matrix_t
*/
matrix_t create_matrix(int n);

/*
 * Will print a matrix and its independent terms to stdout
 * @param matrix the matrix to be printed
 */
void print_matrix(matrix_t matrix);

/*
 * Will free the memory allocated for a matrix
 * @param matrix the matrix to be freed
 */
void free_matrix(matrix_t matrix);

#endif // MATRIX_H