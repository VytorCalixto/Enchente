CFLAGS = -std=c99 -O2 -W -Wall -g

.PHONY: all clean

all: main

main: main.c tabuleiro.o filha.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) *.o
