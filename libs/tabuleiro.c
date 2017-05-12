#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tabuleiro.h"
#include "vertice.h"
#include "grafo.h"

Tblr criaTblr() {
    Tblr t = malloc(sizeof(struct Tblr));
    if(!t) return NULL;
    t->x = t->y = t->cores = 0;
    return t;
}

bool leTblr(Tblr t) {
    int x, y, cores;
    scanf("%d %d %d", &x, &y, &cores);
    t->x = x;
    t->y = y;
    t->cores = cores;
    // Aloca um único array em vez de um "array de arrays"
    t->celulas = malloc(sizeof(struct Celula) * x * y);
    if(t->celulas == NULL) return false;
    for(int i=0; i < x; ++i)
        for(int j=0; j < y; ++j) {
            // Para acessar uma matrix [X][Y] em um vetor fazemos i*Y + j
            Celula c = malloc(sizeof(struct Celula));
            c->visitada = false;
            c->vert = NULL;
            scanf("%d", &(c->cor));
            t->celulas[i * y + j] = c;
        }
    return true;
}

void imprimeTblr(Tblr t) {
    printf("%d ", t->x);
    printf("%d ", t->y);
    printf("%d\n", t->cores);
    for(int i=0; i < t->x; ++i) {
        for(int j=0; j < t->y; ++j)
            printf("%d ", t->celulas[i * t->y + j]->cor);
        puts("");
    }
    return;
}

bool destroiTblr(Tblr t) {
    for(int i=0; i < t->x; ++i) {
        for(int j=0; j < t->y; ++j) {
            free(t->celulas[i*t->y + j]);
        }
    }
    free(t->celulas);
    free(t);
    t = NULL;
    return true;
}
