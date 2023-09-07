EP-02 - Sistemas Lineares

Objetivo

Implementar  3 variações  para  o  Método de  Eliminação  de Gauss  e comparar performance em tempo e FLOPS.

Especificação

Fazer  um programa  perfEG que  lê pela  entrada padrão  um sistema linear (SL) AX = B, de ordem N.

O formato de  entrada dos dados consiste da ordem  do SL na 1ª linha, e nas linhas seguintes está a matriz aumentada C = A|B, conforme exemplo abaixo:

4
4   -1   0   -1   3
-1   4   -1   0   6
0   -1    4   -1  1
-1   0   -1    4  12

Os  valores dos  coeficientes e  termos  independentes do  SL devem ser considerados do tipo real de precisão dupla.

A solução do SL deve ser calculada usando 3 (três) variações do Método de Eliminação de Gauss:

    Forma clássica com pivoteamento (visto aqui);
    Forma clássica com pivoteamento, sem o cálculo dos multiplicadores (visto aqui, no slide 114);
    Forma alternativa onde não usa pivoteamento e que consiste em:

            Para cada linha  do pivô, dividir todos os  coeficientes pelo pivô  (que fica com o valor 1)
            Proceder com  a eliminação,  zerando a coluna  do pivô,  sem fazer pivoteamento.
            Completada   a  triangularização,   calcular  as   incógnitas  por retro-substituição.

   Veja o exemplo abaixo:

```text
  -1   4  -1   0   6   -->  / -1
   2  -1   4  -1   1
   4  -1   0  -1   3
  -1   0  -1   4  12

   1. -4.   1.   0.  -6.
   2. -1.   4.  -1.   1.    m = 2
   4. -1.   0.  -1.   3.    m = 4
  -1.   0.  -1.   4.  12.   m = -1

   1. -4.    1.   0.  -6.
   0. 7.    2.  -1.  13.  -->  / 7
   0. 15.   -4.  -1.  27.
   0. -4.     0.   4.   6.

   1. -4.    1.            0.              -6.
   0. 1.    0.2857   -0.14285.  1.85714
   0. 15.   -4.           -1.            27.              m = 15
   0. -4.    0.             4.              6.             m = -4

   1. -4.   1.              0.              -6.
   0. 1.   0.28571  -0.14286   1.85714
   0. 0.  -8.28571   1.14286  -0.85714      -->  / -8.28571
   0. 0.   1.14286   3.42857   13.4286

   1. -4.   1.             0.                     -6.
   0. 1.   0.28571  -0.14285.         1.85714
   0. 0.   1.              -0.137931       0.1034483
   0. 0.   1.14286    3.4285714  13.428571         m = 1.14286

   1. -4.   1.              0.                  -6.
   0. 1.   0.28571  -0.1428571   1.85714
   0. 0.   1.              -0.137931    0.10345
   0. 0.   0.               3.58621    13.31035  
```

Aplicando a retro-substituição:

X = [ 2.23077   2.21154   0.61539   3.71154 ]

O Programa deve  gerar na saída padrão os seguintes  dados para cada uma das variações acima:

            A solução do SL (valores das incógnitas);
            O tempo médio de cálculo da solução em milisegundos;
            O resíduo.

Execução do Programa
Faça um script (em bash ou python) que executa o programa perfEG através do LIKWID de forma a mostrar também:

            A quantidade de MFLOP/s, medida através do LIKWID.

É imprescindível que sejam respeitadas as seguintes condições:

    Os códigos devem ser compilados com GCC e as opções: -O3 -mavx -march=native;

    Os códigos devem ser instrumentados com a biblioteca do LIKWID;

    Os códigos devem ser compilados na mesma máquina utilizada para os testes. Você pode escolher um computador de sua preferência, desde que possua os contadores Likwid especificados.
    Não utilize as servidoras de processamento do DInf que tenham uso compartilhado. Elas podem ser máquinas virtuais e o compartilhamento impede medidas de desempenho. Em caso de dúvida, consulte o professor.

Makefile

O arquivo Makefile deve possuir as regras necessárias para compilar os módulos individualmente e gerar o programa executável. As seguintes regras devem existir OBRIGATORIAMENTE:

all: compila e produz um executável chamado perfEG no diretório corrente;

purge: remove todos os arquivos temporários e os arquivos gerados pela compilação do programa (*.o, executável, etc.).

O que deve ser entregue

Este exercício deve ser feito em duplas (preferencialmente, a dupla deve continuar a mesma para todos os demais EPs e Trabalhos práticos da disciplina). Apenas um dos alunos deve entregar os códigos-fonte do programa (em linguagem C), makefile e arquivos de teste usados, além de um arquivo LEIAME contendo os nomes dos alunos e limitações do programa (por exemplo, casos que o programa não funciona).

O pacote deve ser arquivado e compactado com zip ou tar, em um arquivo chamado login1-login2.<ext>, onde login1 e login2 são os logins (nos sistemas do DINF) dos alunos que compõem o grupo, e <ext>  é .tar, ou  .zip, ou  .tar.gz, conforme o comando usado para arquivar o pacote.

O pacote deve ter a seguinte estrutura de diretório e arquivos:

    ./login1-login2/: diretório principal;
    ./login1-login2/LEIAME;
    ./login1-login2/Makefile.

Note que a extração dos arquivos de login1-login2.<ext> deve criar o diretório login1-login2 contendo todos os arquivo acima. Os arquivos fonte também devem estar contidos no diretório, ou em algum sub-diretório, desde que o Makefile funcione.
