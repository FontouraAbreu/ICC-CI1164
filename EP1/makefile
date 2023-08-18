CFLAGS = -Wall -g -O1
# regras de ligação
all: main

main: intervalar.o main.o
	gcc -o main intervalar.o main.o -lm

# regras de compilação
intervalar.o: intervalar.c intervalar.h 
	gcc -c intervalar.c -o intervalar.o
	
main.o: main.c
	gcc -c main.c -o main.o




# regra para limpar os diretórios
run: main
	./main

clean:
	rm -f *.o main

purge: clean
	rm -f main

