#ifndef _BOARD_
#define _BOARD_
#include <stdbool.h>
#include "vertice.h"

struct Celula {
    // Cor da célula
    int cor;
    // Se a célula já foi visitada
    bool visitada;
    // Vertice a qual a célula foi mapeada
    Vertice vert;
};

typedef struct Celula *Celula;

struct Tblr {
    int x, y, cores;
    Celula *celulas;
};


typedef struct Tblr *Tblr;

// Cria um tabuleiro vazio e retorna
Tblr criaTblr();

// Faz a leitura do jogo para o tabuleiro
bool leTblr(Tblr t);

// Imprime o tabuleiro
void imprimeTblr(Tblr t);

#endif
