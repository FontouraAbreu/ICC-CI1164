CFLAGS= -g -Wall -O3 -mavx -march=native
CC=gcc

all: perfEG

# regras de ligacao
perfEG: main.o matrix.o
	$(CC) $(CFLAGS) matrix.o main.o -lm -o perfEG

# regras de compilacao
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

system.o: system/system.c system/system.h
	$(CC) $(CFLAGS) -c system/system.c -o system.o

matrix.o: matrix/matrix.c matrix/matrix.h
	$(CC) $(CFLAGS) -c matrix/matrix.c -o matrix.o


run: perfEG
	./perfEG

clean:
	rm -f *.o perfEG

purge: clean
	rm -f perfEG