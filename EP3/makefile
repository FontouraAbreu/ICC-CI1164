CFLAGS= -g -Wall -O3 -mavx -march=native
CC=gcc

all: interpola

# regras de ligacao
interpola: main.o interpola.o matrix.o
	$(CC) $(CFLAGS) main.o interpola.o matrix.o -lm -o interpola

# regras de compilacao
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

interpola.o: interpolators/interpola.c interpolators/interpola.h
	$(CC) $(CFLAGS) -c interpolators/interpola.c -o interpola.o

matrix.o: matrix/matrix.c matrix/matrix.h
	$(CC) $(CFLAGS) -c matrix/matrix.c -o matrix.o
	
run: interpola
	./interpola

clean:
	rm -f *.o interpola

purge: clean
	rm -f interpola