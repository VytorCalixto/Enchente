#include <stdlib.h>
#include "vertice.h"
#include "lista.h"

Vertice criaVertice() {
    Vertice v = malloc(sizeof(struct Vertice));

    v->cor = -1;
    v->peso = 0;
    Lista pais = constroiLista();
    Lista filhos = constroiLista();
    return v;
}
