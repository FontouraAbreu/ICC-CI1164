#include "utils/utils.h"
#include "PolinomialAdjust/adjust.h"
#include "system/system.h"
#ifdef LIKWID_PERFMON
    #include "likwid.h"
#endif

int main(int argc, char *argv[])
{
    #ifdef LIKWID_PERFMON
        LIKWID_MARKER_INIT;
    #endif

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
    #ifdef LIKWID_PERFMON
        LIKWID_MARKER_START("LEAST_SQUARE_METHOD");
    #endif
    IntervalPoint_t *table = read_points(k);
    IntervalMatrix_t *coefficients_matrix = leastSquareMethod(table, k, n);
    print_matrix(coefficients_matrix);
    #ifdef LIKWID_PERFMON
        LIKWID_MARKER_STOP("LEAST_SQUARE_METHOD");
    #endif
    timeLS_non_optmized = timestamp()- timeLS_non_optmized;

    timeSS_non_optmized = timestamp();
    #ifdef LIKWID_PERFMON
        LIKWID_MARKER_START("SYSTEM_SOLVER");
    #endif
    IntervalMatrix_t *triangular_matrix = partial_pivoting_system_solver(coefficients_matrix);
    Interval_t *solution = retrossubs(triangular_matrix);
    #ifdef LIKWID_PERFMON
        LIKWID_MARKER_STOP("SYSTEM_SOLVER");
    #endif
    timeSS_non_optmized = timestamp() - timeSS_non_optmized;

    Interval_t *residual = show_residual(coefficients_matrix, solution, table, k);

    // OPTMIZED VERSION
    timeLS_optmized = timestamp();
    #ifdef LIKWID_PERFMON
        LIKWID_MARKER_START("LEAST_SQUARE_METHOD_OPTMIZED");
    #endif
    OptIntervalPoint_t optTable = optRead_points(table, k);
    OptIntervalMatrix_t *optCoefficients_matrix = optLeastSquareMethod(optTable, k, n);
    printf("\n");
    print_opt_matrix(optCoefficients_matrix);
    #ifdef LIKWID_PERFMON
        LIKWID_MARKER_STOP("LEAST_SQUARE_METHOD_OPTMIZED");
    #endif
    timeLS_optmized = timestamp() - timeLS_optmized;

    //timeSS_optmized = timestamp();
    #ifdef LIKWID_PERFMON
        LIKWID_MARKER_START("SYSTEM_SOLVER_OPTMIZED");
    #endif
    //OptIntervalMatrix_t *optTriangular_matrix = optPartial_pivoting_system_solver(optCoefficients_matrix);
    //Interval_t *optSolution = optRetrossubs(optTriangular_matrix);
    #ifdef LIKWID_PERFMON
        LIKWID_MARKER_STOP("SYSTEM_SOLVER_OPTMIZED");
    #endif
    //timeSS_optmized = timestamp() - timeSS_optmized;


    // printing the solution
    //printSolution(solution, k);
    // printing the residual
    //printResidual(residual, k);

    printf("%1.8e\n", timeLS_non_optmized);
    printf("%1.8e\n", timeSS_non_optmized);

    #ifdef LIKWID_PERFMON
        LIKWID_MARKER_CLOSE;
    #endif
    return 0;
}