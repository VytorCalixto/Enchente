#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "jogador.h"
#include "lista.h"
#include "grafo.h"

Lista Joga(Grafo g, Lista grupo){
	//TODO: A Logica toda do jogo vai ficar aqui

    // Pega os filhos do grupo
    // Monta a árvore de busca:
    //      - RAIZ: grupo
    //      - FILHOS: Cores alcancáveis a partir da raiz
    //      - NETOS: Cores alcançáveis a partir dos filhos que NÃO são alcançáveis a partir da raiz
    // Seleciona o melhor filho baseado em peso(filho) + bônus(filho) // (filho com a maior soma de filho e peso)
    // O bônus e calculado da seguinte forma:
    //      - Soma o valor de cada neto (que não é alcançável pela raiz)
    //      - Em caso de empate da soma peso + bônus:
    //          - Escolher o filho que tem mais netos da mesma cor de um filho
    // Após escolher um filho, repete o algoritmo até não terem mais filhos do grupo
    return constroiLista();
}
