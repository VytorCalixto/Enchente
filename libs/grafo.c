#include <stdlib.h>
#include "grafo.h"
#include "lista.h"
#include "filha.h"
#include "vertice.h"
#include "tabuleiro.h"
#include <stdio.h>

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
    insereUnicoLista(w, v->filhos);
    insereUnicoLista(v, w->pais);
}

/* Algoritmo recursivo
Para cada celula do tabuleiro, indo da esquerda pra direita, de cima pra baixo.
    Verifica se essa célula já foi visitada, se sim, retorna.
    Se não, cria um vertice para ela e chama o algoritmo FLoodfill(celula, vertice) recursivo para esta celula


Floodfill(celula, vertice)
    atrela o vertice a este.
    visita este
    se nenhum dos vizinhos eh da mesma cor ou se os vizinhos da mesma cor ja tiverem vertices, entao
        retorna.
    se algum dos vizinhos for da mesma cor, chama
        floodfill(vizinho de mesma cor, vertice)
    retorna
-----------------------------------------------------------
*/

void tabuleiroParaGrafo(Tblr t, Grafo g) {
    g->x = t->x;
    g->y = t->y;
    g->cores = t->cores;
    //Para cada celula do tabuleiro
    for(int i=0; i < t->x; ++i) {
        for(int j=0; j < t->y; ++j) {
            Celula c = t->celulas[i * t->y +j];
            //Verifica se essa célula já foi visitada
            if(c->vert == NULL){
                //Se não, cria um vertice para ela e chama o algoritmo FLoodfill(celula, vertice) recursivo para esta celula
                // Crio um vértice para mim
                Vertice v = criaVertice();
                v->cor = c->cor;
                v->peso = 0;
                insereVertice(g, v);
                //Chama o flood fill
                floodFill(t, v, i, j);
            }

            // A célula tendo um vértice, criamos os arcos pros vizinhos
            Celula cima, baixo, esq, dir;
            //Cima
            if(i > 0) {
                cima = t->celulas[(i-1) * t->y + j];
                if(cima->vert && cima->cor != c->cor) {
                    criaArco(cima->vert, c->vert);
                    criaArco(c->vert, cima->vert);
                }
            }
            // Esquerda
            if(j > 0) {
                esq = t->celulas[i * t->y + (j - 1)];
                if(esq->vert && esq->cor != c->cor) {
                    criaArco(esq->vert, c->vert);
                    criaArco(c->vert, esq->vert);
                }
            }
            // Baixo
            if(i < t->x - 1) {
                baixo = t->celulas[(i + 1) * t->y + j];
                if(baixo->vert && baixo->cor != c->cor) {
                    criaArco(baixo->vert, c->vert);
                    criaArco(c->vert, baixo->vert);
                }
            }
            // Direita
            if(j < t->y - 1) {
                dir = t->celulas[i * t->y + (j + 1)];
                if(dir->vert && dir->cor != c->cor) {
                    criaArco(dir->vert, c->vert);
                    criaArco(c->vert, dir->vert);
                }
            }
        }
    }
}

void floodFill(Tblr t, Vertice v, int i, int j){
    Celula c = t->celulas[i * t->y + j];

    // Se a cor da célula é diferente da do vértice retorna
    if(c->cor != v->cor) return;
    // Se a célula já tem um vértice, retorna
    if(c->vert) return;

    // Se as cores são iguais...
    c->vert = v;
    v->peso = v->peso + 1;

    //Cima
    if(i > 0) {
        floodFill(t, v, (i-1), j);
    }
    // Esquerda
    if(j > 0) {
        floodFill(t, v, i, (j-1));
    }
    // Baixo
    if(i < t->x - 1) {
        floodFill(t, v, (i+1), j);
    }
    // Direita
    if(j < t->y - 1) {
        floodFill(t, v, i, (j+1));
    }
    return;
}

int calculaAltura(Grafo g, Lista raiz) {
    int alturaMax = 0;
    for(No n = primeiroNoLista(g->vertices); n; n = getSucessorNo(n)) {
        Vertice v = (Vertice) getConteudo(n);
        v->altura = -1;
    }

    Filha fila = constroiFilha();
    for(No n = primeiroNoLista(raiz); n; n = getSucessorNo(n)) {
        Vertice v = (Vertice) getConteudo(n);
        v->altura = 0;
        insereFilha(v, fila);
    }

    while(tamanhoFilha(fila) > 0) {
        No n = primeiroNoFilha(fila);
        if(!n) {
            continue;
        };
        Vertice v = (Vertice) getConteudo(n);
        for(No m = primeiroNoLista(v->filhos); m; m = getSucessorNo(m)) {
            Vertice filho = (Vertice) getConteudo(m);
            if(filho->altura == -1) {
                filho->altura = v->altura+1;
                if(filho->altura > alturaMax) {
                    alturaMax = filho->altura;
                }
                insereFilha(filho, fila);
            }
        }
        free(n);
    }
    destroiFilha(fila, NULL);
    return alturaMax;
}

void destroiGrafo(Grafo g) {
    destroiLista(g->vertices, destroiVertice);
    free(g);
    g = NULL;
    return;
}

void grafoParaDot(Grafo g, Lista grupo, FILE* fp) {
    fprintf(fp, "strict graph g {\n");
    // Pinta os nós que estão no grupo de vermelho
    for(No n = primeiroNoLista(grupo); n; n = getSucessorNo(n)) {
        Vertice v = (Vertice) getConteudo(n);
        fprintf(fp, "\t\"%p\" [color=red];\n", v);
    }
    // Imprime o grafo
    for(No n = primeiroNoLista(g->vertices); n; n = getSucessorNo(n)) {
        Vertice pai = (Vertice) getConteudo(n);
        fprintf(fp, "\t\"%p\" [label=\"cor=%d\npeso=%d\nbonus=%d\naltura=%d\"];\n", pai, pai->cor, pai->peso, pai->bonus, pai->altura);
        for(No m = primeiroNoLista(pai->filhos); m; m = getSucessorNo(m)) {
            Vertice filho = (Vertice) getConteudo(m);
            fprintf(fp, "\t\"%p\" [label=\"cor=%d\npeso=%d\nbonus=%d\naltura=%d\"];\n", filho, filho->cor, filho->peso, filho->bonus, filho->altura);
            fprintf(fp, "\t\"%p\" -- \"%p\";\n", pai, filho);
        }
    }
    fprintf(fp, "}\n");
}
