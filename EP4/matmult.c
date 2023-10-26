#include <stdio.h>
#include <stdlib.h> /* exit, malloc, calloc, etc. */
#include <string.h>
#include <getopt.h> /* getopt */
#include <time.h>
#ifdef LIKWID_PERFMON
#include "likwid.h"
#endif
#include "utils.h"

#include "matriz.h"

/**
 * Exibe mensagem de erro indicando forma de uso do programa e termina
 * o programa.
 */

static void usage(char *progname)
{
  fprintf(stderr, "Forma de uso: %s [ <ordem> ] \n", progname);
  exit(1);
}

/**
 * Programa principal
 * Forma de uso: matmult [ -n <ordem> ]
 * -n <ordem>: ordem da matriz quadrada e dos vetores
 *
 */

int main(int argc, char *argv[])
{

#ifdef LIKWID_PERFMON
  LIKWID_MARKER_INIT;
#endif

  int n = DEF_SIZE;

  MatRow mRow_1, mRow_2, resMat, resMatOptimized;
  Vetor vet, res, resOptimized;
  double time_mxv, time_mxv_optimized, time_mxm, time_mxm_optimized;

  /* =============== TRATAMENTO DE LINHA DE COMANDO =============== */

  if (argc < 2)
    usage(argv[0]);

  n = atoi(argv[1]);

  /* ================ FIM DO TRATAMENTO DE LINHA DE COMANDO ========= */

  srandom(20232);

  res = geraVetor(n, 0); // (real_t *) malloc (n*sizeof(real_t));
  /* Optimized result var */
  resOptimized = geraVetor(n, 1);
  memcpy(resOptimized, res, n * sizeof(Vetor));
  // resOptimized = geraVetor (n, 0); // (real_t *) malloc (n*sizeof(real_t));

  resMat = geraMatRow(n, n, 1);
  /* Optimized result var */
  resMatOptimized = geraMatRow(n, n, 1);
  memcpy(resMatOptimized, resMat, n * sizeof(MatRow));

  mRow_1 = geraMatRow(n, n, 0);
  mRow_2 = geraMatRow(n, n, 0);

  vet = geraVetor(n, 0);
  // vetToOptimize = geraVetor (n, 0);
  // memcpy(vetToOptimize, vet, n*sizeof(Vetor));

  if (!res || !resMat || !mRow_1 || !mRow_2 || !vet || !resOptimized || !resMatOptimized)
  {
    fprintf(stderr, "Falha em alocação de memória !!\n");
    liberaVetor((void *)mRow_1);
    liberaVetor((void *)mRow_2);
    liberaVetor((void *)resMat);
    liberaVetor((void *)resMatOptimized);
    liberaVetor((void *)vet);
    liberaVetor((void *)res);
    liberaVetor((void *)resOptimized);
    exit(2);
  }

#ifdef _DEBUG_
  printf("não otimizado:\n");

  printf("\tMatriz 1:\n");
  prnMat(mRow_1, n, n);
  printf("\tMatriz 2:\n");
  prnMat(mRow_2, n, n);
  printf("\tVetor:\n");
  prnVetor(vet, n);

  printf("=================================\n\n");
#endif /* _DEBUG_ */

  // MATxVET
  time_mxv = timestamp();
#ifdef LIKWID_PERFMON
  LIKWID_MARKER_START("NOT_OPTIMIZED_MATxVET");
#endif
  multMatVet(mRow_1, vet, n, n, res);
#ifdef LIKWID_PERFMON
  LIKWID_MARKER_STOP("NOT_OPTIMIZED_MATxVET");
#endif
  time_mxv = timestamp() - time_mxv;

  time_mxv_optimized = timestamp();
#ifdef LIKWID_PERFMON
  LIKWID_MARKER_START("OPTIMIZED_MATxVET");
#endif
  optimizedMultMatVet_unroll_jam_blocking(mRow_1, vet, n, n, resOptimized);
#ifdef LIKWID_PERFMON
  LIKWID_MARKER_STOP("OPTIMIZED_MATxVET");
#endif
  time_mxv_optimized = timestamp() - time_mxv_optimized;

  // MATxMAT
  time_mxm = timestamp();
#ifdef LIKWID_PERFMON
  LIKWID_MARKER_START("NOT_OPTIMIZED_MATxMAT");
#endif
  multMatMat(mRow_1, mRow_2, n, resMat);
#ifdef LIKWID_PERFMON
  LIKWID_MARKER_STOP("NOT_OPTIMIZED_MATxMAT");
#endif
  time_mxm = timestamp() - time_mxm;

  time_mxm_optimized = timestamp();
#ifdef LIKWID_PERFMON
  LIKWID_MARKER_START("OPTIMIZED_MATxMAT");
#endif
  optimizedMulMatMat_blocking(mRow_1, mRow_2, n, resMatOptimized);
#ifdef LIKWID_PERFMON
  LIKWID_MARKER_STOP("OPTIMIZED_MATxMAT");
#endif
  time_mxm_optimized = timestamp() - time_mxm_optimized;

#ifdef _DEBUG_
  printf("resultado não otimizado\n");
  prnVetor(res, n);
  printf("%lf\n", time_mxv);

  printf("resultado otimizado com loop unrolling e JAM + blocking\n");
  prnVetor(resOptimized, n);
  printf("%lf\n", time_mxv_optimized);

  printf("=================================\n\n");

  printf("resultado não otimizado\n");
  prnMat(resMat, n, n);
  printf("%lf\n", time_mxm);

  printf("resultado otimizado com loop unrolling e JAM + blocking\n");
  prnMat(resMatOptimized, n, n);
  printf("%lf\n", time_mxm_optimized);
#endif /* _DEBUG_ */

  liberaVetor((void *)mRow_1);
  liberaVetor((void *)mRow_2);
  liberaVetor((void *)resMat);
  liberaVetor((void *)resMatOptimized);
  liberaVetor((void *)vet);
  liberaVetor((void *)res);
  liberaVetor((void *)resOptimized);

#ifdef LIKWID_PERFMON
  LIKWID_MARKER_CLOSE;
#endif
  return 0;
}
