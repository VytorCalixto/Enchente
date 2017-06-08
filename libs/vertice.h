#ifndef _VERTICE_
#define _VERTICE_
#include "lista.h"
#include <stdbool.h>

struct Vertice {
    int cor;
    int peso;
    unsigned long int bonus;
    int altura;
    bool grupo;
    bool visitado;
    Lista pais;
    Lista filhos;
};

typedef struct Vertice *Vertice;

Vertice criaVertice();

bool destroiVertice(void *v);

#endif
