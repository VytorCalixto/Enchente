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

int destroiVertice(void *v) {
    Vertice w = (Vertice) v;
    // Como os outros vértices também estão no grafo, deixamos isso a cargo dele
    destroiLista(w->pais, NULL);
    destroiLista(w->filhos, NULL);
    free(w);
    w = NULL;
    return 1;
}
