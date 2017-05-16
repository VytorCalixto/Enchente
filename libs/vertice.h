#ifndef _VERTICE_
#define _VERTICE_
#include "lista.h"
#include <stdbool.h>

struct Vertice {
    int cor;
    int peso;
    int bonus;
    bool grupo;
    Lista pais;
    Lista filhos;
};

typedef struct Vertice *Vertice;

Vertice criaVertice();

int destroiVertice(void *v);

#endif
