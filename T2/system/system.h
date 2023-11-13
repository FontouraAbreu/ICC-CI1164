#ifndef SYSTEM_H
#define SYSTEM_H
#include <math.h>
#include "../intervals/intervalar.h"
#include "../utils/utils.h"

typedef long long int lli;


/*
 *   retrossubs of a triangular matrix
 *   @param A: IntervalMatrix_t(the triangular matrix)
 *   @brief Solve a system using retrossubs
 *   @return x: Interval*(the solutions of the system)
 *   @attention Keep in mind that the matrix must be triangular. Every system solver should use this function after generating a triangular matrix
 */
Interval_t *retrossubs(IntervalMatrix_t *A);

/*
 *   parcial pivoting system solver
 *   @param A: IntervalMatrix_t
 *   @return x: IntervalMatrix_t
 *   @brief Will generate a triangular matrix using parcial pivoting method
 *   @complexity O(n^3)
 */
IntervalMatrix_t *partial_pivoting_system_solver(IntervalMatrix_t *A);

/*
 *   parcial pivoting system solver
 *   @param A: IntervalMatrix_t
 *   @return x: IntervalMatrix_t
 *   @brief [OPTMIZED] Will generate a triangular matrix using parcial pivoting method
 *   @complexity O(n^3)
 */
OptIntervalMatrix_t *optPartial_pivoting_system_solver(OptIntervalMatrix_t *A);

/*
 *   find pivot of a column
 *   @param A: IntervalMatrix_t
 *   @param row: int
 *   @param col: int
 *   @return max: int
 *   @brief Will loop through the rows of a matrix and find the pivot
 *   @complexity O(n)
 */
lli find_partial_pivot(IntervalMatrix_t *A, lli row, lli col);


/*
*   find pivot of a column
*   @param A: OptIntervalMatrix_t
*   @param row: int
*   @param col: int
*   @return max: int
*   @brief Will loop through the rows of a matrix and find the pivot
*   @complexity O(n)
*/
lli op_find_partial_pivot(OptIntervalMatrix_t *A, lli row, lli col);


/*
 *   swap rows of a matrix
 *   @param A: IntervalMatrix_t
 *   @param row1: int
 *   @param row2: int
 *   @brief Will swap two rows of a matrix, changing their pointers
 *   @complexity O(n)
 */
void swap_rows(IntervalMatrix_t *A, lli row1, lli row2);

/*
 *   Will calculate the residual of a system as y - f(x)
 *   where y is the real value and f(x) is the value calculated by the system
 *   @param A: the solution matrix of the system
 *   @param table: the table of points given
 *   @return array of residual: the residual of the system
 */
Interval_t *show_residual(IntervalMatrix_t *A, Interval_t *solution, IntervalPoint_t *table, lli n);

/*
 *   print a system
 *   @param A: IntervalMatrix_t
 *   @brief Will print a system
 *   @complexity O(n^2)
 */
void print_system(IntervalMatrix_t A);

/*
*   swap two rows of a matrix
*   @param A: IntervalMatrix_t
*   @param index of row1: int
*   @param index of row2: int
*   @brief Will swap two rows of a matrix, changing their pointers
*/
void swap_rows(IntervalMatrix_t *A, lli row1, lli row2);

#endif // SYSTEM_H
