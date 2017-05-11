CFLAGS = -std=c99 -O2 -W -Wall -g

.PHONY: all clean

all: main

test: main
	cd tests; \
	$(CC) -std=c99 -o test geraMapa.c; \
	chmod +x runTests.sh; \
	./runTests.sh

main: main.c libs/jogador.o libs/tabuleiro.o libs/filha.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) *.o
	$(RM) tests/*.in
