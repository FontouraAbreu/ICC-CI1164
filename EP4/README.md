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

O trabalho foi executado no seguinte processador:

```text
CPU name:	Intel(R) Core(TM) i5-7500 CPU @ 3.40GHz
CPU type:	Intel Coffeelake processor
CPU clock:	3.41 GHz
```

Para realizar as análises através do Likwid, antes de realizar a chamada para cada função de multiplicação, é inicializado o marcador ` LIKWID_PERFORM ` e, para análise de tempo gasto, foi utilizado a função `timestamp()`.

## Conclusões e limitações do programa

-> Por considerarmos as matrizes de tamanho `n`, em que `n` não é divisível por UF, o programa funciona apenas para matrizes com um tamanho múltiplo de 4.

-> Não foi utilizado a técnica de padding, que consiste em adicionar uma estrutura de dados auxiliar para "preencher" um espaço de memória que não vai ser utilizado, buscando um "alinhamento" de memória para facilitar acesso. Tal técnica pode evitar a ocorrência de cache thrashing, quando a memória é acessada de maneira à ter elevado número de cache misses, que pode ser observado na multiplicação de matrizes em que o tamanho é uma potência de 2.

Conclui-se então, que as técnicas de otimização utilizadas são efetivas, observando principalmente o tempo gasto para realizar a multiplicação. Para matrizes maiores, fica óbvio a diminuição no tempo gasto para executar a multiplicação quando são aplicadas as técnicas de otimização. Ao utilizá-las, é possível observar também o aumento no número de `MFLOPS/s`, de acordo com o esperado.
