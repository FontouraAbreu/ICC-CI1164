# Relatório EP1 - Cálculo de Intervalos

## Nome dos alunos

Inaiê Moscal Zambonin - GRR20210578
Vinicius Fontoura de Abreu - GRR20206873

## Organização e Implementações

O trabalho foi divido em 3 arquivos fonte: `main.c`, `intervalar.c` e `FloatType.c`.

O arquivo fonte `intervalar.c` contém as **implementações de todas as operações** realizadas, o **cálculo do intervalo** para cada variável e as **demais funções** necessárias para o programa.

O arquivo fonte `main.c` contém a **função main** do programa, que realiza a **leitura dos dados** de entrada, a **chamada das funções** de cálculo de intervalo e a **impressão dos resultados**.

 Para **realizar o arredondamento dos valores** em `float`, foi utilizada a função `nextafterf()`, da biblioteca`math.h`, que **calcula o próximo número que pode ser representado por ponto flutuante** em direção a um segundo número. Nesse caso, utilizamos a definição`INFINITY` ou `-INFINITY` para definir as direções do arredondamento.

## Testes

 Para **realizar os testes**, criamos um arquivo com diversas expressões.

 O arquivo possue testes visando as seguintes situações:
    - números muito distantes: `6.0e+38` e `-6.0e-38`
    - números muito próximos de `zero`: `0.1e-38` e `0.1e-39`
    - divisões por `zero`
    - operações seguidas com `zero`
    - operações com `zero` e `INFINITY`

## Problemas

Não detectamos nenhum contexto em que o programa não funciona.
Tivemos dificuldades na criação dos intervalos, devido à problemas com a função `fesetround()`.
