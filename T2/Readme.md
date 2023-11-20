# Relatório T2

Trabalho sobre a implementação do método dos mínimos quadrados utilizando representação intervalar.

## Alunos

Inaiê Moscal Zambonin - GRR20210578

Vinicius Fontoura de Abreu - GRR20206873

***

## Sumário

- [Relatório T2](#relatório-t2)
  - [Alunos](#alunos)
  - [Sumário](#sumário)
  - [Introdução](#introdução)
  - [Otimizações realizadas](#otimizações-realizadas)
    - [Estruturas de dados](#estruturas-de-dados)
    - [Acesso à matriz](#acesso-à-matriz)
    - [Loop unrolling + JAM](#loop-unrolling--jam)
    - [Blocking](#blocking)
  - [Execução](#execução)
    - [Compilação](#compilação)
    - [Scripts de execução e geração de gráficos](#scripts-de-execução-e-geração-de-gráficos)
  - [Resultados](#resultados)
  - [Conclusão](#conclusão)

## Introdução

Para atender aos requisitos do trabalho, reimplementamos as funções usadas no T1 buscando otimizar o código e acesso à memória. Para isso, utilizamos as técnicas de loop unrolling + JAM, blocking e mudamos algumas estruturas de dados utilizadas anteriormente.

## Otimizações realizadas

Alteramos as funções utilizadas no T1 para que elas utilizassem as otimizações propostas e as estruturas de dados modificadas. As principais modificações foram:

### Estruturas de dados

As principais modificações em estruturas de dados anteriores foram:

1. Utilizar uma `Struct of Arrays` para representar os pontos, ao invés de um `Array of Structs`. Isso foi feito para melhorar o acesso aos dados, já que agora os dados de um ponto estão contíguos na memória, o que melhora o acesso aos dados de um ponto em um loop.

```c
/*
 *   Point structure:
 *   x: interval_t of x coordinate
 *   y: interval_t of y coordinate
 *   BETTER OF AS TWO ARRAYS OF INTERVALS
 */
typedef struct
{
    Interval_t x;
    Interval_t y;
} IntervalPoint_t;

/*
* Optimized version of IntervalPoint_t
* An array of x and y coordinates
* where x[i] is the x Interval_t of the i-th point
* and y[i] is the y Interval_t of the i-th point
*/
typedef struct {
    Interval_t *x;
    Interval_t *y;
} OptIntervalPoint_t;
```

2. Utilizar um vetor para representar uma matriz, ao invés de um vetor de vetores. Isso foi feito para melhorar o acesso aos dados, já que agora os dados de uma matriz estão contíguos na memória, o que melhora o acesso aos dados de uma matriz em um loop.

```c
/*
    *   Interval Matrix structure:
    *   rows: number of rows
    *   cols: number of columns
    *   data: matrix of intervals
    *   independent_terms: independent terms of the system
    *   residual: residual of the system
*/
typedef struct
{
    lli rows;
    lli cols;
    Interval_t **data;
    Interval_t *independent_terms;
    Interval_t *residual;
} IntervalMatrix_t;

/*
* Optmized version of IntervalMatrix_t
* access the matrix as a single array
* data[i][j] = data[i * cols + j]
*/
typedef struct
{
    /* data */
    lli rows;
    lli cols;
    Interval_t *data;
    Interval_t *independent_terms;
    Interval_t *residual;
} OptIntervalMatrix_t;
```

### Loop unrolling + JAM e Blocking

Nas funções que calculam a matriz de coeficientes, utilização pivoteamento parcial e fazem a restrossubstituição, utilizamos a técnica de loop unrolling + JAM para melhorar o acesso à memória e diminuir o número de instruções de desvio. Além disso, utilizamos blocking para melhorar o acesso à memória.

## Execução

### Compilação

### Scripts de execução e geração de gráficos

## Resultados

## Conclusão