#ifndef _VERTICE_
#define _VERTICE_
#include "lista.h"

struct Vertice {
    int cor;
    int peso;
    Lista pais;
    Lista filhos;
};

typedef struct Vertice *Vertice;

Vertice criaVertice();

int destroiVertice(void *v);

#endif
