#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "jogador.h"

struct Nodo {
    // Jogada que foi tomada para chegar neste nodo (ou seja, cor do grupo de posicoes atual)
    int jogada;
    // Filhos deste nodo
    Nodo * filhos[];
    // "Quadrados pintados" ate aquele nodo(que sera um vetor contendo certas posicoes do vetor "celulas")
    int * quadradosPintados;
    // peso eh a quantidade de quadrados pintados deste grupo
    int peso;
};

int checaCor(Tblr t, int posicao){
	return t->celulas[posicao]->cor;
}

int * verAdjacentes(Tblr t, int posicao, int cor){
	//TODO: criar algoritmo que encontra quais sao os quadrados adjacentes a este dado quadrado
}

void alocaFilhos(Nodo n){
	//TODO: criar algoritmo que, dado um nodo, aloca seus filhos
}

Nodo criaGrafo(t){
	Nodo n = malloc(sizeof(struct Nodo));
	if(!n) return NULL;

	n->jogada = checaCor(t, 0);
	if(n->jogada == -1) return NULL;

	// Ver quais sao os quadrados pintados deste nodo(grupo de quadrados adjacentes da mesma cor, dada uma posicao)
	n->quadradosPintados = verAdjacentes(t, 0, n->jogada);
	if(quadradosPintados == NULL) return NULL;
	n.peso = (sizeof(n.quadradosPintados)/sizeof(int));

	// Ver qual e a quantidade de filhos deste Nodo e aloca espaco para eles
	alocaFilhos(n);
	if(n.filhos == NULL) return NULL;

	return n; 
}

int * Joga(Nodo n, Tblr t){
	//TODO: A Logica toda do jogo vai ficar aqui

      // printf("Enquanto pilha não vazia:\n");
      // printf("\tPega os adjacentes do grupo (retorna os pesos dos filhos = montar o grafo)\n");
      // printf("\tEscolhe filho de maior peso\n");
      // printf("\tEmpilha os outros filhos\n");
      // printf("\tSE tamanho do caminho atual + filhos do nodo atual >= menor caminho: VOLTA!\n");
      // printf("\tSE soma do peso total = tamanho do tabuleiro: VOLTA! Retorna o caminho encontrado\n");
      // printf("\n\n\n##BONUS##\n");
      // printf("Olhar os vizinhos dos vizinhos no estado atual e atribuir bônus:\n");
      // printf("\tSe vizinho tem vizinho que não tenho: adicionar valor do vizinho do vizinho como bônus\n");
      // printf("\tSe vizinho tem vizinho que tenho, mas em número maior: adicionar diferença\n");
}
