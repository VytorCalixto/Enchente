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
    while(tamanhoLista(grupo) < tamanhoLista(g->vertices)) {
        int altura = calculaAltura(g, grupo);
        // Pega os filhos do grupo
        Lista filhos = filhosGrupo(grupo);
        // Monta a árvore de busca:
        //      - RAIZ: grupo
        //      - FILHOS: Cores alcancáveis a partir da raiz
        //      - NETOS: Cores alcançáveis a partir dos filhos que NÃO são alcançáveis a partir da raiz
        //          Só é necessário para calcular o bônus de cada filho
        // printf("\tJOGADA %d\n", counter);
        Lista coresFilhos = agrupaCores(filhos, g, altura, tamanhoLista(g->vertices) - tamanhoLista(grupo));
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

// TODO: primeiro agrupa, DEPOIS calcula os bônus!!!
// Para calcular o bônus, agrupa os filhos de um grupo e aí calcula o bônus
// Ou seja, 2 ou mais vértices da MESMA COR que tenham o mesmo filho (repetição)
//      só contarão UMA VEZ o bônus+peso daquele filho
Lista agrupaCores(Lista filhos, Grafo g, int altura, int naoConsumidos) {
    Lista agrupa = constroiLista();
    double max = 2*(g->x) + (sqrt(2*g->cores))*(g->x) + g->cores;
    double min = (sqrt(g->cores - 1)*g->x/2) - (g->cores/2);
    int profundidade = sqrt(max) * (sqrt(altura) / sqrt(min)) * (altura/sqrt(naoConsumidos));
    // printf("\t\tProfundidade: %d\n", profundidade);
    // printf("\t\tRazão: %f\n", (altura/sqrt(naoConsumidos)));
    for(No n = primeiroNoLista(filhos); n; n = getSucessorNo(n)) {
        Vertice v = (Vertice) getConteudo(n);
        // Verifica se a cor já está na lista
        bool estaNaLista = false;
        for(No m = primeiroNoLista(agrupa); m; m = getSucessorNo(m)) {
            Vertice w = (Vertice) getConteudo(m);
            // Se está, soma o peso do vértice
            if(w->cor == v->cor) {
                w->peso += v->peso;
                w->bonus += calculaBonus(v, filhos, profundidade);
                estaNaLista = true;
            }
        }
        // Se não está, cria um vértice para a cor
        if(!estaNaLista) {
            Vertice w = criaVertice();
            w->cor = v->cor;
            w->peso = v->peso;
            w->bonus = calculaBonus(v, filhos, profundidade);
            insereLista(w, agrupa);
        }
    }

    // Depois de agrupar, verifica se alguma cor vai chegar ao fim nesta jogada
    for(No n = primeiroNoLista(agrupa); n; n = getSucessorNo(n)) {
        Vertice v = (Vertice) getConteudo(n);
        int somaCor = 0;
        for(No m = primeiroNoLista(g->vertices); m; m = getSucessorNo(m)) {
            Vertice w = (Vertice) getConteudo(m);
            if(!w->grupo && w->cor == v->cor) {
                somaCor += w->peso;
            }
        }
        // Se a soma de todos os vértices que não pertencem ao grupo for igual
        //      ao peso do vértice agrupado, esta é a última jogada com aquela cor
        if(v->peso == somaCor) {
            v->bonus += 100; // Mais bonus para que essa cor seja a escolhida
        }
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
