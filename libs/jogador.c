#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "jogador.h"
#include "lista.h"
#include "grafo.h"
#include <math.h>

Lista Joga(Grafo g, Lista grupo){
    Lista jogadas = constroiLista();
    //TODO: A Logica toda do jogo vai ficar aqui
    int counter = 1;
    double max = 2*(g->x) + (sqrt(2*g->cores))*(g->x) + g->cores;
    double min = (sqrt(g->cores - 1)*g->x/2) - (g->cores/2);
    while(tamanhoLista(grupo) < tamanhoLista(g->vertices)) {
        // Calcula a altura
        int altura = calculaAltura(g, grupo);

        int naoConsumidos = tamanhoLista(g->vertices) - tamanhoLista(grupo);
        int profundidade = 32;
        if(altura > 10) {
            profundidade = sqrt(max) * (sqrt(altura) / sqrt(min)) * (altura/sqrt(naoConsumidos));
            if (profundidade <= 0) profundidade = 1;
        }

        // Pega os filhos do grupo
        Lista filhos = filhosGrupo(grupo);
        // Monta a árvore de busca:
        //      - RAIZ: grupo
        //      - FILHOS: Cores alcancáveis a partir da raiz
        //      - NETOS: Cores alcançáveis a partir dos filhos que NÃO são alcançáveis a partir da raiz
        //          Só é necessário para calcular o bônus de cada filho
        // printf("\tJOGADA %d\n", counter);
        Lista coresFilhos = agrupaCores(filhos, g, profundidade);
        // printf("\tAltura da árvore: %d\n", altura);
        // printf("\tNúmero de grupos: %d\n", tamanhoLista(g->vertices));
        // printf("\tNúmero de grupos não consumidos: %d\n", tamanhoLista(g->vertices) - tamanhoLista(grupo));
        // printf("\tTamanho coresFilhos %d\n", tamanhoLista(coresFilhos));
        // for(No n = primeiroNoLista(coresFilhos); n; n = getSucessorNo(n)) {
        //     Vertice v = (Vertice) getConteudo(n);
        //     printf("\t\tVértice - cor: %d, peso: %d, bonus: %d\n", v->cor, v->peso, v->bonus);
        // }
        // Seleciona o melhor filho baseado em peso(filho) + bônus(filho) // (filho com a maior soma de filho e peso)
        // O bônus é calculado da seguinte forma:
        //      - Soma o valor de cada neto (que não é alcançável pela raiz)
        //      - Em caso de empate da soma peso + bônus:
        //          - Escolher o filho que tem mais netos da mesma cor de um filho
        // Após escolher um filho, repete o algoritmo até não terem mais filhos fora do grupo

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
                    int maiorFilhoM = 0;
                    int maiorFilhoV = 0;
                    for(No m = primeiroNoLista(maior->filhos); m; m = getSucessorNo(m)) {
                        Vertice w = (Vertice) getConteudo(m);
                        if(w->altura > maiorFilhoM) maiorFilhoM = w->altura;
                    }
                    for(No m = primeiroNoLista(v->filhos); m; m = getSucessorNo(m)) {
                        Vertice w = (Vertice) getConteudo(m);
                        if(w->altura > maiorFilhoV) maiorFilhoV = w->altura;
                    }
                    if(maiorFilhoV > maiorFilhoM) maior = v;
                }
            }
        }
        // printf("\t\tCOR ESCOLHIDA: %d\n", maior->cor);
        insereLista(maior->cor, jogadas);
        // "Pinta o tablueiro"
        for(No n = primeiroNoLista(filhos); n; n = getSucessorNo(n)) {
            Vertice v = (Vertice) getConteudo(n);
            if(v->cor == maior->cor && !v->grupo) {
                insereUnicoLista(v, grupo);
                v->grupo = true;
            }
        }

        // Limpa as coisas
        destroiLista(filhos, NULL);
        destroiLista(coresFilhos, destroiVertice);

        calculaAltura(g, grupo);
        // PARA DEBUG!! Imprime as últimas 10 jogadas em um arquivo
        char str[32];
        sprintf(str, "./jogada%d.out", counter );
        FILE* debug = fopen(str, "w+");
        if(debug) {
            grafoParaDot(g, grupo, debug);
        }
        fclose(debug);
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

Lista agrupaCores(Lista vertices, Grafo g, int profundidade) {
    if(profundidade < 0 ) return NULL;
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

    // Depos do laço anterior, temos uma lista de vértices agrupados
    //      Então, agrupamos os filhos e calculamos os bônus
    for(No n = primeiroNoLista(agrupa); n; n = getSucessorNo(n)) {
        Vertice v = (Vertice) getConteudo(n);
        Lista filhosAgrupa = agrupaCores(v->filhos, g, profundidade-1);
        for(No m = primeiroNoLista(filhosAgrupa); m; m = getSucessorNo(m)) {
            Vertice w = (Vertice) getConteudo(m);
            // TODO: verificar se W não é sobrinho de V
            //      para não dar o bônus duas vezes
            if(!w->grupo && (w->altura > v->altura) && !w->visitado){
                v->bonus += w->peso + w->bonus;
                w->visitado = true;
            }
        }
        for(No m = primeiroNoLista(v->pais); m; m = getSucessorNo(m)) {
            Vertice w = (Vertice) getConteudo(m);
            w->bonus = v->bonus;
        }
        destroiLista(filhosAgrupa, NULL);
    }

    return agrupa;
}

int calculaBonus(Vertice v, Lista irmaos, int profundidade) {
    int bonus = 0;
    for(No n = primeiroNoLista(v->filhos); n; n = getSucessorNo(n)) {
        Vertice filho = (Vertice) getConteudo(n);
        // Se o filho não está na lista irmaos e não está no grupo de vértices já consumidos
        if(!filho->grupo && !pertenceLista(filho, irmaos)) {
            bonus += filho->peso + calculaBonusRec(filho, v, profundidade);
        }
    }
    return v->bonus = bonus;
}

int calculaBonusRec(Vertice v, Vertice pai, int profundidade) {
    if(profundidade <= 0) return 0;
    int bonus = 0;
    for(No n = primeiroNoLista(v->filhos); n; n = getSucessorNo(n)) {
        Vertice filho = (Vertice) getConteudo(n);

        if(!filho->grupo && !pertenceLista(filho, pai->filhos) && (filho->altura > v->altura)) {
            bonus += filho->peso + calculaBonusRec(filho, v, profundidade-1);
        }
    }
    return v->bonus = bonus;
}
