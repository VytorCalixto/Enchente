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
            // Primeiro, olho ao meu redor e vejo se posso me inserir em algum grupo existente
            Celula cima, baixo, esq, dir;
            // Olho no sentido anti-horário porque é mais provável que o cara acima e a esquerda de mim já tenham vértices
            // Cima
            if(i > 0) {
                cima = t->celulas[(i-1) * t->y + j];
                if(cima->vert && (cima->cor == c->cor)) {
                    c->vert = cima->vert;
                    ++(c->vert->peso);
                }
            }
            // Esquerda
            if(j > 0) {
                esq = t->celulas[i * t->y + (j - 1)];
                if(esq->vert != NULL && (esq->cor == c->cor)) {
                    c->vert = esq->vert;
                    ++(c->vert->peso);
                }
            }
            // Baixo
            if(i < t->x - 1) {
                baixo = t->celulas[(i + 1) * t->y + j];
                if(baixo->vert != NULL && (baixo->cor == c->cor)) {
                    c->vert = baixo->vert;
                    ++(c->vert->peso);
                }
            }
            // Direita
            if(j < t->y - 1) {
                dir = t->celulas[i * t->y + (j + 1)];
                if(dir->vert != NULL && (dir->cor == c->cor)) {
                    c->vert = dir->vert;
                    ++(c->vert->peso);
                }
            }

            // Se não me agrupei com ninguém
            if(c->vert == NULL) {
                // Crio um vértice para mim
                Vertice v = criaVertice();
                v->cor = c->cor;
                v->peso = 1;
                c->vert = v;
                insereVertice(g, v);
            }

            // Com um vértice meu, crio arcos para os vizinhos
            // Cima
            if(i > 0) {
                cima = t->celulas[(i-1) * t->y + j];
                if(cima->vert && (cima->cor != c->cor)) {
                    criaArco(c->vert, cima->vert);
                    criaArco(cima->vert, c->vert);
                }
            }
            // Direita
            if(j < t->y - 1) {
                dir = t->celulas[i * t->y + (j + 1)];
                if(dir->vert && (dir->cor != c->cor)) {
                    criaArco(c->vert, dir->vert);
                    criaArco(dir->vert, c->vert);
                }
            }
            // Baixo
            if(i < t->x - 1) {
                baixo = t->celulas[(i + 1) * t->y + j];
                if(baixo->vert && (baixo->cor != c->cor)) {
                    criaArco(c->vert, baixo->vert);
                    criaArco(baixo->vert, c->vert);
                }
            }
            // Esquerda
            if(j > 0) {
                esq = t->celulas[i * t->y + (j - 1)];
                if(esq->vert && (esq->cor != c->cor)) {
                    criaArco(c->vert, esq->vert);
                    criaArco(esq->vert, c->vert);
                }
            }
        }
    }
    return;
}

void destroiGrafo(Grafo g) {
    destroiLista(g->vertices, destroiVertice);
    free(g);
    g = NULL;
    return;
}
