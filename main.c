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

int main() {
    Tblr t = criaTblr();
    // Aloca o tabuleiro em um único array em vez de um "array de arrays"
    if(!leTblr(t)) {
        puts("Erro na leitura do tabuleiro");
        return -1;
    }

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
