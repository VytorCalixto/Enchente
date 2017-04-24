#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "tabuleiro.h"
// #include "jogador.h"

int main() {
    Tblr t = criaTblr();
    // Aloca o tabuleiro em um único array em vez de um "array de arrays"
    if(!leTblr(t)) {
        puts("Erro na leitura do tabuleiro");
        return -1;
    }
    imprimeTblr(t);

    // // declara o grafo ponderado e seu primeiro nodo
    // grafo = criaGrafo(t);
    // if(grafo == NULL)) {
    //     puts("Erro na criacao do grafo");
    //     return -1;
    // }
    // // faz o jogador jogar o jogo a partir do tabuleiro dado
    // // o retorno do jogador sera um vetor contendo os numeros referentes a menor jogada encontrada por ele
    // int *jogadas;
    // jogadas = Joga(grafo, t);

    return 0;
}

// pilha global
// {
//      identificador: "passo"
//      valor original
//      posição
// }

// {
//      identificador: 4
//      valor original: 2
//      posição: 0,0
// },
// {
//      identificador: 5
//      valor original: 4
//      posição: 0,0 - 0,1 - 1,0 - 2,0
// }
//
