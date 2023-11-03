# Relatório EP4

## Alunos

Inaiê Moscal Zambonin - GRR20210578

Vinicius Fontoura de Abreu - GRR20206873

***

## Organização e implementações

A organização e estrutura do código e dos tipos usados foi entregue pelos professores nos arquivos `matriz.c` e `matriz.h`.

O programa principal se encontra no arquivo ` matmult.c ` , juntamente com o tratamento dos parâmetros para rodar o programa, e a alocação e geração dos vetores para multiplicação das matrizes.

## Otimizações feitas

## Loop unroll & jam + blocking

### Matriz x Vetor

A função ` optimizedMultMatVet_unroll_jam_blocking ` realiza a multiplicação entre matriz e vetor de forma otimizada, percorrendo a matriz em blocos de tamanho BK, considerando operações de vetorização de tamanho UF. O fator de unroll **UF** e o fator de blocking **BK** são fixados em 4, definidos em `matriz.h`

```c
void optimizedMultMatVet_unroll_jam_blocking(MatRow mat, Vetor v, int m, int n, Vetor res)
{
  /* Efetua a multiplicação */
  if (res)
  {
    for (int i = 0; i < m; i += UF)
    {
      for (int j = 0; j < n; j += BK)
      {
        for (int k = 0; k < UF; ++k)
        {
          for (int l = 0; l < BK; ++l)
          {
            res[i + k] += mat[n * (i + k) + j + l] * v[j + l];
          }
        }
      }
    }
  }
}
```

Nessa implementação, a técnica de Unroll + Jam é vista na expansão dos laços de repetição para a multiplicação, com a combinação das operações num único loop. Já a técnica de blocking está presente justamente na divisão da matriz em blocos a serem percorridos.

### Matriz x Matriz

A função `optimizedMulMatMat_blocking` realiza a multiplicação entre duas matrizes, utilizando as mesmas técnicas mencionadas acima, percorrendo a matriz em blocos de tamanho BK.

```c
void optimizedMulMatMat_blocking(MatRow A, MatRow B, int n, MatRow C)
{
  int istart, jstart, kstart, iend, jend, kend;

  for (int ii=0; ii<n/BK; ii++) 
  {
    istart = ii*BK;
    iend = istart + BK;
    for (int jj=0; jj<n/BK; jj++) 
    {
      jstart = jj*BK;
      jend = jstart + BK;
      for (int kk=0; kk<n/BK; kk++) 
      {
        kstart = kk*BK;
        kend = kstart + BK;
        for (int i=istart; i<iend; i++) 
        {
          for (int j=jstart; j<jend; j+=UF) 
          {
            for (int k=kstart; k<kend; k++) {

              for (int l=0; l<UF; l++) 
              {
                C[i*n+j+l] += A[i*n+k] * B[k*n+j+l];
              }
            }
          }
        }
      }
    }
  }
}
```

## Analise através do Likwid

Para analisar os resultados obtidos com a otimização, o programa realiza a multiplicação tanto do vetor pela matriz quanto de duas matrizes sem utilizar nenhuma técnica de otimização

O trabalho foi executado no processador com a seguinte topologia:

```text
--------------------------------------------------------------------------------
CPU name:	11th Gen Intel(R) Core(TM) i7-11700K @ 3.60GHz
CPU type:	Intel Rocketlake processor
CPU stepping:	1
********************************************************************************
Hardware Thread Topology
********************************************************************************
Sockets:		1
Cores per socket:	8
Threads per core:	2
--------------------------------------------------------------------------------
HWThread        Thread        Core        Die        Socket        Available
0               0             0           0          0             *                
1               0             1           0          0             *                
2               0             2           0          0             *                
3               0             3           0          0             *                
4               0             4           0          0             *                
5               0             5           0          0             *                
6               0             6           0          0             *                
7               0             7           0          0             *                
8               1             0           0          0             *                
9               1             1           0          0             *                
10              1             2           0          0             *                
11              1             3           0          0             *                
12              1             4           0          0             *                
13              1             5           0          0             *                
14              1             6           0          0             *                
15              1             7           0          0             *                
--------------------------------------------------------------------------------
Socket 0:		( 0 8 1 9 2 10 3 11 4 12 5 13 6 14 7 15 )
--------------------------------------------------------------------------------
********************************************************************************
Cache Topology
********************************************************************************
Level:			1
Size:			48 kB
Type:			Data cache
Associativity:		12
Number of sets:		64
Cache line size:	64
Cache type:		Non Inclusive
Shared by threads:	2
Cache groups:		( 0 8 ) ( 1 9 ) ( 2 10 ) ( 3 11 ) ( 4 12 ) ( 5 13 ) ( 6 14 ) ( 7 15 )
--------------------------------------------------------------------------------
Level:			2
Size:			512 kB
Type:			Unified cache
Associativity:		8
Number of sets:		1024
Cache line size:	64
Cache type:		Non Inclusive
Shared by threads:	2
Cache groups:		( 0 8 ) ( 1 9 ) ( 2 10 ) ( 3 11 ) ( 4 12 ) ( 5 13 ) ( 6 14 ) ( 7 15 )
--------------------------------------------------------------------------------
Level:			3
Size:			16 MB
Type:			Unified cache
Associativity:		16
Number of sets:		16384
Cache line size:	64
Cache type:		Inclusive
Shared by threads:	16
Cache groups:		( 0 8 1 9 2 10 3 11 4 12 5 13 6 14 7 15 )
--------------------------------------------------------------------------------
********************************************************************************
NUMA Topology
********************************************************************************
NUMA domains:		1
--------------------------------------------------------------------------------
Domain:			0
Processors:		( 0 8 1 9 2 10 3 11 4 12 5 13 6 14 7 15 )
Distances:		10
Free memory:		6033.35 MB
Total memory:		15851 MB
--------------------------------------------------------------------------------


********************************************************************************
Graphical Topology
********************************************************************************
Socket 0:
+-----------------------------------------------------------------------------------------+
| +--------+ +--------+ +--------+ +--------+ +--------+ +--------+ +--------+ +--------+ |
| |  0 8   | |  1 9   | |  2 10  | |  3 11  | |  4 12  | |  5 13  | |  6 14  | |  7 15  | |
| +--------+ +--------+ +--------+ +--------+ +--------+ +--------+ +--------+ +--------+ |
| +--------+ +--------+ +--------+ +--------+ +--------+ +--------+ +--------+ +--------+ |
| |  48 kB | |  48 kB | |  48 kB | |  48 kB | |  48 kB | |  48 kB | |  48 kB | |  48 kB | |
| +--------+ +--------+ +--------+ +--------+ +--------+ +--------+ +--------+ +--------+ |
| +--------+ +--------+ +--------+ +--------+ +--------+ +--------+ +--------+ +--------+ |
| | 512 kB | | 512 kB | | 512 kB | | 512 kB | | 512 kB | | 512 kB | | 512 kB | | 512 kB | |
| +--------+ +--------+ +--------+ +--------+ +--------+ +--------+ +--------+ +--------+ |
| +-------------------------------------------------------------------------------------+ |
| |                                        16 MB                                        | |
| +-------------------------------------------------------------------------------------+ |
+-----------------------------------------------------------------------------------------+

```

Para realizar as análises através do Likwid, antes de realizar a chamada para cada função de multiplicação, é inicializado o marcador ` LIKWID_PERFORM ` e, para análise de tempo gasto, foi utilizado a função `timestamp()`.

## Conclusões e limitações do programa

-> Por considerarmos as matrizes de tamanho `n`, em que `n` não é divisível por UF, o programa funciona apenas para matrizes com um tamanho múltiplo de 4.

-> Não foi utilizado a técnica de padding, que consiste em adicionar uma estrutura de dados auxiliar para "preencher" um espaço de memória que não vai ser utilizado, buscando um "alinhamento" de memória para facilitar acesso. Tal técnica pode evitar a ocorrência de cache thrashing, quando a memória é acessada de maneira à ter elevado número de cache misses, que pode ser observado na multiplicação de matrizes em que o tamanho é uma potência de 2.

Conclui-se então, que as técnicas de otimização utilizadas são efetivas, observando principalmente o tempo gasto para realizar a multiplicação. Para matrizes maiores, fica óbvio a diminuição no tempo gasto para executar a multiplicação quando são aplicadas as técnicas de otimização. Ao utilizá-las, é possível observar também o aumento no número de `MFLOPS/s`, de acordo com o esperado.
