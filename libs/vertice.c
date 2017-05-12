#include <stdlib.h>
#include "vertice.h"
#include "lista.h"

Vertice criaVertice() {
    Vertice v = malloc(sizeof(struct Vertice));

    v->cor = -1;
    v->peso = 0;
    v->pais = constroiLista();
    v->filhos = constroiLista();
    return v;
}
