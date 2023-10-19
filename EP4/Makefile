# PROGRAMA
PROG = matmult
OBJS = $(PROG).o matriz.o

# Compilador
CC = gcc -Wall 
CFLAGS = -O3 -mavx2 -march=native
LFLAGS = -lm
OPTIMIZINGFLAGS = -fopt-info-vec -fopt-info-vec-missed

# Lista de arquivos para distribuição
DISTFILES = *.c *.h README.md Makefile perfctr
DISTDIR = `basename ${PWD}`

.PHONY: all debug clean purge dist

%.o: %.c %.h
	$(CC) $(CFLAGS) $(OPTIMIZINGFLAGS) -c $<

all: $(PROG)

debug:CFLAGS += -g -D_DEBUG_
debug:$(PROG)

$(PROG): $(OBJS) 
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

clean:
	@rm -f *~ *.bak *.tmp core 

purge: clean
	@rm -f  $(PROG) *.o a.out $(DISTDIR) $(DISTDIR).tar
	@rm -f *.png marker.out

dist: purge
	@ln -s . $(DISTDIR)
	@tar -cvf $(DISTDIR).tar $(addprefix ./$(DISTDIR)/, $(DISTFILES))
	@rm -f $(DISTDIR)

