#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "libs/tabuleiro.h"
#include "libs/grafo.h"

int main() {
    Tblr t = criaTblr();
    // Aloca o tabuleiro em um único array em vez de um "array de arrays"
    if(!leTblr(t)) {
        puts("Erro na leitura do tabuleiro");
        return -1;
    }
    Grafo g = criaGrafo();
    tabuleiroParaGrafo(t, g);
    destroiTblr(t);
    destroiGrafo(g);
    return 0;
}
