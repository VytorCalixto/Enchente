#ifndef _BOARD_
#define _BOARD_
#include <stdbool.h>

typedef struct Celula *Celula;

typedef struct Tblr *Tblr;

// Cria um tabuleiro vazio e retorna
Tblr criaTblr();

// Faz a leitura do jogo para o tabuleiro
bool leTblr(Tblr t);

// Imprime o tabuleiro
void imprimeTblr(Tblr t);

#endif
