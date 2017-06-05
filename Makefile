CFLAGS = -std=c99 -O2 -W -Wall -g

.PHONY: all clean

all: main

test: main
	cd tests; \
	$(CC) -std=c99 -o test geraMapa.c; \
	chmod +x runTests.sh; \
	./runTests.sh

main: main.c libs/jogador.o libs/tabuleiro.o libs/grafo.o libs/vertice.o libs/filha.o libs/lista.o libs/no.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

clean:
	$(RM) *.o
	$(RM) libs/*.o
	$(RM) tests/*.time
