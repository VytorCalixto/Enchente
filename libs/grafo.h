#ifndef _GRAFO_
#define _GRAFO_
#include "tabuleiro.h"

struct Grafo {
    Lista vertices;
};

typedef struct Grafo *Grafo;

Grafo criaGrafo();

Vertice insereVertice(Grafo g, Vertice v);

void criaArco(Vertice v, Vertice w);

void tabuleiroParaGrafo(Tblr t, Grafo g);

int *buscaCaminho(Grafo g);

#endif
