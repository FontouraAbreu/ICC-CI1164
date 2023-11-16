CFLAGS= -g -Wall -O3 -mavx -march=native 
LFLAGS= -lm 
ifneq ($(LIKWID_HOME),)
	CFLAGS += -I$(LIKWID_HOME)/include -DLIKWID_PERFMON
	LFLAGS += -L$(LIKWID_HOME)/lib -llikwid
endif
CC=gcc

all: ajustePol gerador

# regras de ligacao
ajustePol: main.o ajustePol.o utils.o interval.o system.o
	$(CC) $(CFLAGS) main.o ajustePol.o utils.o interval.o system.o $(LFLAGS) -o ajustePol

gerador: gera_entrada.c
	$(CC) $(CFLAGS) gera_entrada.c -o gera_entrada

# regras de compilacao
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

ajustePol.o: PolinomialAdjust/adjust.c PolinomialAdjust/adjust.h
	$(CC) $(CFLAGS) -c PolinomialAdjust/adjust.c -o ajustePol.o

utils.o: utils/utils.c utils/utils.h
	$(CC) $(CFLAGS) -c utils/utils.c -o utils.o

interval.o: intervals/intervalar.c intervals/intervalar.h
	$(CC) $(CFLAGS) -c intervals/intervalar.c -o interval.o

system.o: system/system.c system/system.h
	$(CC) $(CFLAGS) -c system/system.c -o system.o
	
run: ajustePol
	./ajustePol

clean:
	rm -f *.o

purge: clean
	rm -f ajustePol gera_entrada