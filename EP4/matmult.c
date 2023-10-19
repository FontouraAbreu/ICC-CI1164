#include <stdio.h>
#include <stdlib.h>    /* exit, malloc, calloc, etc. */
#include <string.h>
#include <getopt.h>    /* getopt */
#include <time.h>

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

int main (int argc, char *argv[]) 
{
  int n=DEF_SIZE;
  
  MatRow mRow_1, mRow_2, resMat, resMatOptimized;
  Vetor vet, vetToOptimize, res, resOptimized;
  
  /* =============== TRATAMENTO DE LINHA DE COMANDO =============== */

  if (argc < 2)
    usage(argv[0]);

  n = atoi(argv[1]);
  
  /* ================ FIM DO TRATAMENTO DE LINHA DE COMANDO ========= */
 
  srandom(20232);
      
  res = geraVetor (n, 0); // (real_t *) malloc (n*sizeof(real_t));
  /* Optimized result var */
  //resOptimized = res;
  resOptimized = geraVetor (n,1);
  memcpy(resOptimized, res, n*sizeof(Vetor));
  //resOptimized = geraVetor (n, 0); // (real_t *) malloc (n*sizeof(real_t));


  resMat = geraMatRow(n, n, 1);
  /* Optimized result var */
  //resMatOptimized = resMat;
  resMatOptimized = geraMatRow(n, n, 1);
  memcpy(resMatOptimized, resMat, n*sizeof(MatRow));

    
  mRow_1 = geraMatRow (n, n, 0);
  mRow_2 = geraMatRow (n, n, 0);

  vet = geraVetor (n, 0);
  vetToOptimize = geraVetor (n, 0);


  if (!res || !resMat || !mRow_1 || !mRow_2 || !vet || !resOptimized || !resMatOptimized) {
    fprintf(stderr, "Falha em alocação de memória !!\n");
    liberaVetor ((void*) mRow_1);
    liberaVetor ((void*) mRow_2);
    liberaVetor ((void*) resMat);
    liberaVetor ((void*) resMatOptimized);
    liberaVetor ((void*) vet);
    liberaVetor ((void*) res);
    liberaVetor ((void*) resOptimized);
    exit(2);
  }
    
#ifdef _DEBUG_
    printf("não otimizado:\n");

    printf("\tMatriz:\n");
    prnMat (mRow_1, n, n);
    // prnMat (mRow_2, n, n);
    printf("\t*\n\tVetor:\n");
    prnVetor (vet, n);

    printf("\t*\n\tVetor p/ otimizar:\n");
    prnVetor (vetToOptimize, n);
    printf ("=================================\n\n");
#endif /* _DEBUG_ */

  multMatVet (mRow_1, vet, n, n, res);
  optimezedMultMatVet_unroll (mRow_1, vet, n, n, resOptimized);
    
  // multMatMat (mRow_1, mRow_2, n, resMat);
  // multMatMat (mRow_1, mRow_2, n, resMatOptimized);

    
#ifdef _DEBUG_
    printf("resultado não otimizado\n");
    prnVetor (res, n);

    printf("resultado otimizado com loop unrolling(fator 4)\n");
    prnVetor (resOptimized, n);

    // prnMat (resMat, n, n);
    // prnMat (resMatOptimized, n, n);
#endif /* _DEBUG_ */

  liberaVetor ((void*) mRow_1);
  liberaVetor ((void*) mRow_2);
  liberaVetor ((void*) resMat);
  liberaVetor ((void*) resMatOptimized);

  liberaVetor ((void*) vet);
  liberaVetor ((void*) res);
  liberaVetor ((void*) resOptimized);

  return 0;
}

