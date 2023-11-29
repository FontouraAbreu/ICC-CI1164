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
    - [Loop unrolling + JAM e blocking](#loop-unrolling--jam-e-blocking)
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

Nas funções que calculam a matriz de coeficientes, triangularizam o sistema e fazem a restrossubstituição, utilizamos a técnica de loop unrolling + JAM para melhorar o acesso à memória e diminuir o número de instruções de desvio. Além disso, utilizamos blocking para melhorar o acesso à memória nestas mesmas funções.

É possível alterar o tamanho do bloco utilizado para o blocking e o fator de unrrolling através de macros no arquivo `utils/utils.h`.

```c
#define UF 4
#define BK 2
```

## Execução

Temos 4 arquivos executáveis onde 2 deles são scripts em bash:

- gera_entrada: arquivo dos professores que gera uma entrada para o programa
- ajustePol: programa que realiza o ajuste polinomial
- likwid.sh: script que executa `ajustePol` utilizando entradas geradas pelo `gera_entrada` com os tamanhos especificados, e gera os arquivos `.csv` com os resultados
- plot.sh: script que consome os arquivos `.csv` indicados em seu código e gera os gráficos

### Compilação

Para compilar o programa, basta executar o comando `make` na pasta raiz do projeto. Isso irá gerar os arquivos executáveis `gera_entrada` e `ajustePol`.

### Scripts de execução e geração de gráficos

Para executar o programa utilizando o likwid, basta executar o comando `./likwid.sh` na pasta raiz do projeto. Isso irá gerar os arquivos `.csv` com os resultados da execução do programa.

Para gerar os gráficos, basta executar o comando `./generate_plot.sh` na pasta raiz do projeto. Isso irá gerar os gráficos com os resultados da execução do programa.

## Resultados

Vamos analisar os resultados obtidos com o likwid para cada uma das metricas indicadas no enunciado do trabalho:

- FLOPS DP: A quantidade de FLOPS/s no geral aumentou, o que indica que o programa está utilizando melhor os recursos da CPU. Entretanto, é difícil de analisar essa métrica se não for acompanha do tempo que o evento(Least Square Method, System Solver ou Residual) levou. Visto que o tempo de execução do programa diminuiu, mas o número de FLOPS continuou o mesmo, ainda sim isso é bom, pois indica que o programa está utilizando melhor os recursos da CPU.

- FLOPS AVX DP: A metrica de FLPOS AVX DP segue a mesma lógica da métrica de FLOPS DP, onde o número de FLOPS aumentou, mas o tempo de execução diminuiu. Então mesmo que o número de FLOPS AVX DP não tenha aumentado, o programa está mais eficiente. **OBS.:** Na minha máquina os valores de FLOPS AVX DP são sempre 0, só pude analisá-los nas máquinas do dinf

- TEMPO: O tempo de execução do programa diminuiu em todas os eventos, o que indica que o programa está mais eficiente.

- ENERGY: Visto que o tempo diminuiu e a quantidade de FLOPS aumentou, o consumo de energia do programa diminuiu. **OBS.:** Na minha máquina os valores de ENERGY são sempre 0, só pude analisá-los nas máquinas do dinf

- L2CACHE MISS RATIO: O número de cache misses diminuiu, o que indica que o programa está utilizando melhor a memória cache, principalmente devido a blocagem nas funções. **OBS.:** Na minha máquina não existe o evento L2CACHE, só pude analisá-lo nas máquinas do dinf

- L3 BANDWIDTH: O número de bytes lidos e escritos na memória diminuiu, o que indica que o programa está utilizando melhor a memória cache, também devido a blocagem nas funções. **OBS.:** Na minha máquina não existe o evento L3, só pude analisá-lo nas máquinas do dinf

## Problemas

- Calculo do residuo: Não foi possível otimizar a função que calcula o residual, pois usar técnicas de loop unrroll ou blocking não melhorou o desempenho da função.

- Versões diferentes do likwid: Nos trabalhos não foi especificada uma versão do likwid para ser utilizada, isso gera problemas de compatibilidade entre os scripts feitos e as máquinas. Além de atrapalhar o aluno que: hora vê seus scripts funcionando e hora não. Isso também atrapalha a correção do trabalho, pois o professor pode não conseguir executar os scripts e gerar os gráficos corretamente, além de gerar diversos casos em que: o aluno perde nota por mais que tenha feito corretamente o trabalho ou o professor precisa corrigir o trabalho manualmente.

## Conclusão

Com a implementação das otimizações propostas, conseguimos melhorar o desempenho do programa em relação ao T1. Isso pode ser visto nos gráficos gerados, onde o tempo de execução do programa diminuiu consideravelmente. Além disso, o número de FLOPS aumentou, o que indica que o programa está utilizando melhor os recursos da CPU. Por fim, o número de cache misses também diminuiu, o que indica que o programa está utilizando melhor a memória cache.