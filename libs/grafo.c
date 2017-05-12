#include <stdlib.h>
#include "grafo.h"
#include "lista.h"
#include "vertice.h"
#include "tabuleiro.h"

Grafo criaGrafo() {
    Grafo g = malloc(sizeof(struct Grafo));

    g->vertices = constroiLista();
    return g;
}

Vertice insereVertice(Grafo g, Vertice v) {
    if(insereLista(v, g->vertices)) {
        return v;
    }
    return NULL;
}

void criaArco(Vertice v, Vertice w) {
    insereLista(w, v->filhos);
    insereLista(v, w->pais);
}

void tabuleiroParaGrafo(Tblr t, Grafo g) {
    for(int i=0; i < t->x; ++i) {
        for(int j=0; j < t->y; ++j) {
            Celula c = t->celulas[i * t->y + j];
            Vertice v = NULL;
            if(c->vert == NULL) {
                v = criaVertice();
                v->cor = c->cor;
                v->peso = 1;
                c->vert = v;
                insereVertice(g, v);
            } else {
                v = c->vert;
            }
            //------Vizinhos
            Celula cima, baixo, esq, dir;
            // Cima
            if(i > 0) {
                cima = t->celulas[(i-1) * t->y + j];
                if(cima->vert == NULL) {
                    Vertice w = criaVertice();
                    w->cor = cima->cor;
                    w->peso = 1;
                    c->vert = w;
                    insereVertice(g, w);
                    criaArco(v, w);
                    criaArco(w, v);
                }
            }
            // Direita
            if(j < t->y - 1) {
                dir = t->celulas[i * t->y + (j + 1)];
                if(dir->vert == NULL) {
                    Vertice w = criaVertice();
                    w->cor = dir->cor;
                    w->peso = 1;
                    c->vert = w;
                    insereVertice(g, w);
                    criaArco(v, w);
                    criaArco(w, v);
                }
            }
            // Baixo
            if(i < t->x - 1) {
                baixo = t->celulas[(i + 1) * t->y + j];
                if(baixo->vert == NULL) {
                    Vertice w = criaVertice();
                    w->cor = baixo->cor;
                    w->peso = 1;
                    c->vert = w;
                    insereVertice(g, w);
                    criaArco(v, w);
                    criaArco(w, v);
                }
            }
            // Esquerda
            if(j > 0) {
                esq = t->celulas[i * t->y + (j - 1)];
                if(esq->vert == NULL) {
                    Vertice w = criaVertice();
                    w->cor = esq->cor;
                    w->peso = 1;
                    c->vert = w;
                    insereVertice(g, w);
                    criaArco(v, w);
                    criaArco(w, v);
                }
            }
        }
    }
    return;
}

int *buscaCaminho(Grafo g) {
    int *caminho = malloc(sizeof(int));
    return caminho;
}
