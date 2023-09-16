# EP-03 - Interpolação

 
## Objetivo

Implementar  os Métodos de Interpolação de Lagrange, e Newton e comparar performance em tempo e FLOPS.

 
## Especificação

Fazer  um programa  interpola que  lê pela  entrada padrão  uma tabela de N pontos (x, f(x)) e gera um polinômio de grau K=N-1  que possa ser usado para calcular o valor aproximado de f(x) para um valor xe (fornecida como argumento do programa) qualquer não pertencente à tabela de pontos fornecida.

O programa recebe como entrada a quantidade N de pontos da tabela (1ª linha) e a tabela com os pontos (x,f(x)) do tipo double, um par de coordenadas por linha.

O programa deverá mostrar na saída os vaores de f(xe) ≈ PK(xe) para os dois métodos de interpolação.

Deve ser também gerada na saída os tempos (em milisegundos) gastos em cada método
Entrada (via stdin):

```text
N
x1 y1
x2 y2
…
xN yN
```

Saída (via stdout):

```text
PK(xe)L
PK(xe)N
tLagrange
tNewton
```

O pacote de software a ser construído deve gerar um executável chamado interpola, que deve ser invocado da seguinte forma:

`./interpola xe < pontos.in > resultado.out`

O argumento xe é um valor real em dupla precisão do qual se deseja saber o valor f(x)  ≈  PK(x). A entrada deve ser feita pela Entrada Padrão (stdin) e a saída deve ser feita para a Saída Padrão (stdout). O programa não deve emitir mensagens de prompt na entrada e na saída. Os valores lidos e exibidos pelo programa devem ser apenas os valores indicados acima, da forma indicada acima.
Caso o valor xe não pertença ao intervalo da tabela de pontos, deve ser exibida uma mensagem de erro na SAÍDA PADRÃO DE ERROS (stderr).

 
## Execução do Programa

Faça um script (em bash ou python) que executa o programa perfEG através do LIKWID de forma a mostrar também:

A quantidade de MFLOP/s, medida através do LIKWID.

É imprescindível que sejam respeitadas as seguintes condições:

1. Os códigos devem ser compilados com GCC e as opções: `-O3 -mavx -march=native`;

2. Os códigos devem ser instrumentados com a biblioteca do LIKWID;

3. Os códigos devem ser compilados na mesma máquina utilizada para os testes. Você pode escolher um computador de sua preferência, desde que possua os contadores Likwid especificados.

4. Não utilize as servidoras de processamento do DInf que tenham uso compartilhado. Elas podem ser máquinas virtuais e o compartilhamento impede medidas de desempenho. Em caso de dúvida, consulte o professor.

## Makefile

O arquivo Makefile deve possuir as regras necessárias para compilar os módulos individualmente e gerar o programa executável. As seguintes regras devem existir OBRIGATORIAMENTE:

`all`: compila e produz um executável chamado perfEG no diretório corrente;

`purge`: remove todos os arquivos temporários e os arquivos gerados pela compilação do programa (*.o, executável, etc.).

## O que deve ser entregue

Este exercício deve ser feito em duplas (preferencialmente, a dupla deve continuar a mesma para todos os demais EPs e Trabalhos práticos da disciplina). Apenas um dos alunos deve entregar os códigos-fonte do programa (em linguagem C), makefile e arquivos de teste usados, além de um arquivo LEIAME contendo os nomes dos alunos e limitações do programa (por exemplo, casos que o programa não funciona).

O pacote deve ser arquivado e compactado com zip ou tar, em um arquivo chamado login1-login2.<ext>, onde login1 e login2 são os logins (nos sistemas do DINF) dos alunos que compõem o grupo, e <ext>  é `.tar`, ou  `.zip`, ou  `.tar.gz`, conforme o comando usado para arquivar o pacote.

O pacote deve ter a seguinte estrutura de diretório e arquivos:

```bash
./login1-login2/: diretório principal;
./login1-login2/LEIAME;
./login1-login2/Makefile.
```

Note que a extração dos arquivos de login1-login2.<ext> deve criar o diretório login1-login2 contendo todos os arquivo acima. Os arquivos fonte também devem estar contidos no diretório, ou em algum sub-diretório, desde que o Makefile funcione.
