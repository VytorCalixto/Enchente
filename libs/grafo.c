#include <stdlib.h>
#include "grafo.h"
#include "lista.h"
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
				int auxi = i;
				int auxj = j;
				printf("\nIN HERE \n");
				floodFill(t, g, v, c, auxi, auxj);
			}
		}
	}
}

void floodFill(Tblr t, Grafo g, Vertice v, Celula c, int i, int j){
	c->vert = v;
	v->peso = v->peso + 1;
	Celula cima, baixo, esq, dir;
	printf("in floodfill, a cor foi: %d, o i foi: %d e o j foi: %d \n", c->cor, i, j);
	int auxi = i;
	int auxj = j;

	//Cima
	if(i > 0) {
		cima = t->celulas[(i-1) * t->y + j];
		if((cima->cor == c->cor) && (cima->vert == NULL)) {
			printf("cima\n");
			floodFill(t, g, v, cima, (auxi-1), auxj);
		}
	}
	// Esquerda
	if(j > 0) {
		esq = t->celulas[i * t->y + (j - 1)];
		if((esq->cor == c->cor) && (esq->vert == NULL)) {
			printf("esq\n");
			floodFill(t, g, v, esq, auxi, (auxj-1));
		}
	}
	// Baixo
	if(i < t->x - 1) {
		baixo = t->celulas[(i + 1) * t->y + j];
		if((baixo->cor == c->cor) && (baixo->vert == NULL)) {
			printf("baixo\n");
			floodFill(t, g, v, baixo, (auxi+1), auxj);
		}
	}
	// Direita
	if(j < t->y - 1) {
		dir = t->celulas[i * t->y + (j + 1)];
		if((dir->cor == c->cor) && (dir->vert == NULL)) {
			printf("dir \n");
			floodFill(t, g, v, dir, auxi, (auxj+1));
		}
	}
	return;
}

/* Algoritmo inicial do vytor. 

Para cada celula do tabuleiro, indo da esquerda pra direita, de cima pra baixo.  
	verifica se a cor desta celula é a mesma da célula de cima e se a célula de cima já tem vértice
		se sim, esta célula será mapeada para o mesmo vértice.
		o vértice recebe peso +1
	verifica para o da esquerda
	" baixo
	" direita

	se esta célula nao se agrupou com nenhuma, entao cria sua própria

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
                    c->vert = cima->vert; //o vertice ao qual este vai ser agrupado sera o mesmo vertice do seu vizinho de cima
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
*/
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
        fprintf(fp, "\t\"%p\" [label=\"cor=%d,peso=%d\"];\n", pai, pai->cor, pai->peso);
        for(No m = primeiroNoLista(pai->filhos); m; m = getSucessorNo(m)) {
            Vertice filho = (Vertice) getConteudo(m);
            fprintf(fp, "\t\"%p\" [label=\"cor=%d,peso=%d\"];\n", filho, filho->cor, filho->peso);
            fprintf(fp, "\t\"%p\" -- \"%p\";\n", pai, filho);
        }
    }
    fprintf(fp, "}\n");
}
