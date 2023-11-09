#include "utils/utils.h"
#include "PolinomialAdjust/adjust.h"
#include "system/system.h"
#include "likwid.h"

int main(int argc, char *argv[])
{
    LIKWID_MARKER_INIT;

    // reading inputs
    lli n, k;
    double timeLS_non_optmized, timeSS_non_optmized, timeLS_optmized, timeSS_optmized;
    if (scanf("%lld", &n) != 1)
    {
        fprintf(stderr, "Erro ao ler n\n");
        return 1;
    }

    if (scanf("%lld", &k) != 1)
    {
        fprintf(stderr, "Erro ao ler k\n");
        return 1;
    }


    // NON OPTMIZED VERSION
    timeLS_non_optmized = timestamp();
    //LIKWID_MARKER_START("LEAST_SQUARE_METHOD");
    IntervalPoint_t *table = read_points(k);
    IntervalMatrix_t *coefficients_matrix = leastSquareMethod(table, k, n);
    //LIKWID_MARKER_STOP("LEAST_SQUARE_METHOD");
    timeLS_non_optmized = timestamp()- timeLS_non_optmized;

    timeSS_non_optmized = timestamp();
    //LIKWID_MARKER_START("SYSTEM_SOLVER");
    IntervalMatrix_t *triangular_matrix = partial_pivoting_system_solver(coefficients_matrix);
    Interval_t *solution = retrossubs(triangular_matrix);
    //LIKWID_MARKER_STOP("SYSTEM_SOLVER");
    timeSS_non_optmized = timestamp() - timeSS_non_optmized;

    Interval_t *residual = show_residual(coefficients_matrix, solution, table, k);

    // OPTMIZED VERSION
    timeLS_optmized = timestamp();
    //LIKWID_MARKER_START("LEAST_SQUARE_METHOD_OPTMIZED");
    OptIntervalPoint_t optTable = optRead_points(table, k);
    OptIntervalMatrix_t *optCoefficients_matrix = optLeastSquareMethod(optTable, k, n);
    //LIKWID_MARKER_STOP("LEAST_SQUARE_METHOD_OPTMIZED");
    timeLS_optmized = timestamp() - timeLS_optmized;

    //timeSS_optmized = timestamp();
    //LIKWID_MARKER_START("SYSTEM_SOLVER_OPTMIZED");
    //OptIntervalMatrix_t *optTriangular_matrix = optPartial_pivoting_system_solver(optCoefficients_matrix);
    //Interval_t *optSolution = optRetrossubs(optTriangular_matrix);
    //LIKWID_MARKER_STOP("SYSTEM_SOLVER_OPTMIZED");
    //timeSS_optmized = timestamp() - timeSS_optmized;


    // printing the solution
    //printSolution(solution, k);
    // printing the residual
    //printResidual(residual, k);

    printf("%1.8e\n", timeLS_non_optmized);
    printf("%1.8e\n", timeSS_non_optmized);

    LIKWID_MARKER_CLOSE;
    return 0;
}