#include <stdlib.h>
#include <stdbool.h>
#include "vertice.h"
#include "lista.h"

Vertice criaVertice() {
    Vertice v = malloc(sizeof(struct Vertice));

    v->cor = -1;
    v->peso = 0;
    v->bonus = 0;
    v->altura = -1;
    v->grupo = false;
    v->pais = constroiLista();
    v->filhos = constroiLista();
    return v;
}

bool destroiVertice(void *v) {
    Vertice w = (Vertice) v;
    // Como os outros vértices também estão no grafo, deixamos isso a cargo dele
    destroiLista(w->pais, NULL);
    destroiLista(w->filhos, NULL);
    free(w);
    w = NULL;
    return true;
}
