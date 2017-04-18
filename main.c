#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char const *argv[]) {
    printf("Ler o tabuleiro (em matriz?)\n");
    printf("Enquanto pilha não vazia:\n");
    printf("\tPega os adjacentes do grupo (retorna os pesos dos filhos = montar o grafo)\n");
    printf("\tEscolhe filho de maior peso\n");
    printf("\tEmpilha os outros filhos\n");
    printf("\tSE tamanho do caminho atual + filhos do nodo atual >= menor caminho: VOLTA!\n");
    printf("\tSE soma do peso total = tamanho do tabuleiro: VOLTA! Retorna o caminho encontrado\n");
    printf("\n\n\n##BONUS##\n");
    printf("Olhar os vizinhos dos vizinhos no estado atual e atribuir bônus:\n");
    printf("\tSe vizinho tem vizinho que não tenho: adicionar valor do vizinho do vizinho como bônus\n");
    printf("\tSe vizinho tem vizinho que tenho, mas em número maior: adicionar diferença\n");
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
