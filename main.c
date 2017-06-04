#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include "libs/tabuleiro.h"
#include "libs/no.h"
#include "libs/lista.h"
#include "libs/grafo.h"
#include "libs/jogador.h"

int main(int argc, char *argv[]) {
    Tblr t = criaTblr();
    // Aloca o tabuleiro em um único array em vez de um "array de arrays"
    if(!leTblr(t)) {
        puts("Erro na leitura do tabuleiro");
        return -1;
    }

    // Se colocar UMA e APENAS UMA coisa depois do main
    if(argc == 2) {
        // Calcula e imprime o número mínimo e máximo de jogadas
        if(t->x != t->y) {
            puts("Apenas funciona para tabuleiros quadrados");
        } else {
            // Max é 2n + sqrt(2k)n + k
            double max = 2*(t->x) + (sqrt(2*t->cores))*(t->x) + t->cores;
            printf("\tNúmero máximo de jogadas: %f\n", max);
            // Min é válido para 2 <= k <= n²
            // Min é sqrt(k - 1)n/2 - k/2
            if(t->cores >= 2 && t->cores <= (t->x*t->x)) {
                double n2 = t->x/2;
                double min = (sqrt(t->cores - 1)*t->x/2) - (t->cores/2);
                printf("\tNúmero mínimo de jogadas: %f\n", min);
            }
        }
    }

    //TODO imprimindo o tabuleiro
//    imprimeTblr(t);

    Grafo g = criaGrafo();
    // Transforma o tabuleiro para um grafo
    tabuleiroParaGrafo(t, g);
    // Lista com o grupo inicial
    Lista grupo = constroiLista();
    insereLista(t->celulas[0]->vert, grupo); // A célula na posição 0 do array é a célula no canto superior esquerdo
    t->celulas[0]->vert->grupo = true;

    // Desaloca tabuleiro
    destroiTblr(t);

    Lista jogadas = Joga(g, grupo);

    printf("%d\n", tamanhoLista(jogadas));
    for(No n = primeiroNoLista(jogadas); n; n = getSucessorNo(n)) {
        int cor = (int) getConteudo(n);
        printf("%d ", cor);
    }
    puts("");

    destroiLista(jogadas, NULL);
    // Desaloca lista do grupo
    destroiLista(grupo, NULL);
    // Desaloca grafo
    destroiGrafo(g);
    return 0;
}
