#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "jogador.h"
#include "lista.h"
#include "grafo.h"
#include <math.h>

Lista Joga(Grafo g, Lista grupo){
    Lista jogadas = constroiLista();
    int counter = 1;
    double max = 2*(g->x) + (sqrt(2*g->cores))*(g->x) + g->cores;
    double min = (sqrt(g->cores - 1)*g->x/2) - (g->cores/2);
    if (min < 1) min = 1;
    int altura = calculaAltura(g, grupo);
    int naoConsumidos = tamanhoLista(g->vertices) - tamanhoLista(grupo);
    double razao = (altura/sqrt(naoConsumidos));
    int profundidade = (sqrt(max) * (sqrt(altura) / sqrt(min)) * razao);
    if(profundidade < 1) profundidade = 1;

    while(tamanhoLista(grupo) < tamanhoLista(g->vertices)) {
        // Calcula a altura
        altura = calculaAltura(g, grupo);

        Lista filhos = filhosGrupo(grupo);

        // printf("\tJOGADA %d\n", counter);
        // printf("\t\tProfundidade: %d\n", profundidade);
        Lista coresFilhos = agrupaCores(filhos);
        calculaBonus(coresFilhos, g, profundidade);

        // char prestr[32];
        // sprintf(prestr, "./prejogada%d.out", counter);
        // FILE* predebug = fopen(prestr, "w+");
        // if(predebug) {
        //     grafoParaDot(g, grupo, predebug);
        // }
        // fclose(predebug);

        Vertice maior = (Vertice) getConteudo(primeiroNoLista(coresFilhos));
        for(No n = primeiroNoLista(coresFilhos); n; n = getSucessorNo(n)) {
            Vertice v = (Vertice) getConteudo(n);
            // TODO: tratar empates!
            if((v->bonus) > (maior->bonus)) {
                maior = v;
            } else if((v->bonus) == (maior->bonus)) {
                if(v->peso > maior->peso) {
                    maior = v;
                } else if(v->peso == maior->peso) {
                    if(v->cor < maior->cor) {
                        maior = v;
                    }
                }
            }
        }
        // printf("\t\tCOR ESCOLHIDA: %d\n", maior->cor);
        insereLista((void *) maior->cor, jogadas);

        for(No n = primeiroNoLista(filhos); n; n = getSucessorNo(n)) {
            Vertice v = (Vertice) getConteudo(n);
            if(v->cor == maior->cor && !v->grupo) {
                insereUnicoLista(v, grupo);
                v->grupo = true;
            }
        }

        destroiLista(filhos, NULL);
        destroiLista(coresFilhos, destroiVertice);

        calculaAltura(g, grupo);
        // PARA DEBUG!! Imprime as últimas 10 jogadas em um arquivo
        // char str[32];
        // sprintf(str, "./jogada%d.out", counter );
        // FILE* debug = fopen(str, "w+");
        // if(debug) {
        //     grafoParaDot(g, grupo, debug);
        // }
        // fclose(debug);
        ++counter;
    }

    return jogadas;
}

Lista filhosGrupo(Lista grupoPai) {
    Lista filhos = constroiLista();
    for(No n = primeiroNoLista(grupoPai); n; n = getSucessorNo(n)) {
        Vertice pai = (Vertice) getConteudo(n);
        for(No m = primeiroNoLista(pai->filhos); m; m = getSucessorNo(m)) {
            Vertice filho = (Vertice) getConteudo(m);
            if(!filho->grupo && filho->altura > pai->altura) {
                insereUnicoLista(filho, filhos);
            }
        }
    }
    return filhos;
}

Lista agrupaCores(Lista vertices) {
    Lista agrupa = constroiLista();
    for(No n = primeiroNoLista(vertices); n; n = getSucessorNo(n)) {
        Vertice v = (Vertice) getConteudo(n);
        // Verifica se a cor já está agrupada
        bool estaAgrupado = false;
        for(No m = primeiroNoLista(agrupa); m && !estaAgrupado; m = getSucessorNo(m)) {
            Vertice w = (Vertice) getConteudo(m);
            // Se está, soma o peso do vértice
            if(w->cor == v->cor) {
                w->peso += v->peso;
                insereUnicoLista(v, w->pais);
                for(No o = primeiroNoLista(v->filhos); o; o = getSucessorNo(o)) {
                    Vertice x = (Vertice) getConteudo(o);
                    if(x->altura > v->altura) insereUnicoLista(x, w->filhos);
                }
                estaAgrupado = true;
            }
        }

        // Se não está agrupado...
        if(!estaAgrupado) {
            Vertice w = criaVertice();
            w->cor = v->cor;
            w->peso = v->peso;
            w->altura = v->altura;
            insereUnicoLista(v, w->pais);
            for(No m = primeiroNoLista(v->filhos); m; m = getSucessorNo(m)) {
                Vertice x = (Vertice) getConteudo(m);
                if(x->altura > v->altura) insereUnicoLista(x, w->filhos);
            }
            insereLista(w, agrupa);
        }
    }

    return agrupa;
}


bool corEstaNaLista(Lista l, int cor) {
    for(No n = primeiroNoLista(l); n; n = getSucessorNo(n)) {
        Vertice v = (Vertice) getConteudo(n);
        if(v->cor == cor) {
             return true;
        }
    }
    return false;
}

int calculaBonusRec(Vertice v, Grafo g, int profundidade) {
    if(profundidade <= 0) return 0;
    int bonus = 0;
    for(No n = primeiroNoLista(v->filhos); n; n = getSucessorNo(n)) {
        Vertice filho = (Vertice) getConteudo(n);
        if((filho->altura > v->altura)) {
            bonus += filho->peso + calculaBonusRec(filho, g, profundidade-1);
        }
    }
    return v->bonus = bonus;
}

void calculaBonus(Lista grupo, Grafo g, int profundidade) {
    for(No n = primeiroNoLista(grupo); n; n = getSucessorNo(n)) {
        Vertice v = (Vertice) getConteudo(n);
        v->bonus = 0;
        for(No m = primeiroNoLista(v->filhos); m; m = getSucessorNo(m)) {
            Vertice filho = (Vertice) getConteudo(m);
            if((filho->altura > v->altura)) {
                int bonus = filho->peso + calculaBonusRec(filho, g, profundidade);
                if(corEstaNaLista(grupo, filho->cor)) bonus += 50;
                v->bonus += bonus;
            }
        }
        Lista vFilhos = agrupaCores(v->filhos);
        v->bonus += (tamanhoLista(v->filhos) - tamanhoLista(vFilhos))*2;

        for(No m = primeiroNoLista(vFilhos); m; m = getSucessorNo(m)) {
            Vertice w = (Vertice) getConteudo(m);
            int somaCor = 0;
            for(No o = primeiroNoLista(g->vertices); o; o = getSucessorNo(o)) {
                Vertice x = (Vertice) getConteudo(o);
                if(x->grupo) continue;
                if(x->altura < w->altura) continue;
                if(x->cor == w->cor) {
                    somaCor += x->peso;
                }
            }
            if(w->peso == somaCor) {
                v->bonus += 150;
            }
        }
        destroiLista(vFilhos, destroiVertice);

        int menorDistancia = v->altura;
        for(No m = primeiroNoLista(g->vertices); m; m = getSucessorNo(m)) {
            Vertice w = (Vertice) getConteudo(m);
            if(w->grupo) continue;
            if(w == v) continue;
            if(w->cor == v->cor) {
                if((w->altura < menorDistancia) || (menorDistancia == v->altura)) menorDistancia = w->altura;
            }
        }

        for(No m = primeiroNoLista(v->pais); m; m = getSucessorNo(m)) {
            Vertice pai = (Vertice) getConteudo(m);
            pai->bonus = v->bonus;
        }
    }

    for(No n = primeiroNoLista(grupo); n; n = getSucessorNo(n)) {
        Vertice v = (Vertice) getConteudo(n);
        int somaCor = 0;
        for(No m = primeiroNoLista(g->vertices); m; m = getSucessorNo(m)) {
            Vertice w = (Vertice) getConteudo(m);
            if(!w->grupo && w->cor == v->cor) {
                somaCor += w->peso;
            }
        }
        // Se a soma de todos os vértices que não pertencem ao grupo consumido
        //      for igual ao peso do vértice agrupado, esta é a
        //      última jogada com aquela cor
        if(v->peso == somaCor) {
            v->bonus += 350; // Mais bonus para que essa cor seja a escolhida
        }

    }

    return;
}
