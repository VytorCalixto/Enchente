#ifndef _GRAFO_
#define _GRAFO_
#include "tabuleiro.h"
#include <stdio.h>

struct Grafo {
    Lista vertices;
};

typedef struct Grafo *Grafo;

Grafo criaGrafo();

Vertice insereVertice(Grafo g, Vertice v);

void criaArco(Vertice v, Vertice w);

void tabuleiroParaGrafo(Tblr t, Grafo g);

void floodFill(Tblr t, Vertice v, int i, int j);

void destroiGrafo(Grafo g);

void grafoParaDot(Grafo g, Lista grupo, FILE* fp);

#endif
