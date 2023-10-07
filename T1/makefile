CFLAGS= -g --debug -Wall -O3 -mavx -march=native -I$(LIKWID_HOME)/include -DLIKWID_PERFMON
LFLAGS= -lm -L$(LIKWID_HOME)/lib -llikwid
CC=gcc

all: ajustePol

# regras de ligacao
ajustePol: main.o ajustePol.o utils.o interval.o system.o
	$(CC) $(CFLAGS) main.o ajustePol.o utils.o interval.o system.o $(LFLAGS) -o ajustePol

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
	rm -f *.o ajustePol

purge: clean
	rm -f ajustePol