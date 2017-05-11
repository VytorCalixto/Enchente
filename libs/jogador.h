#ifndef _PLAYER_
#define _PLAYER_
#include <stdbool.h>
#include "tabuleiro.h"

// Nodo do grafo que permitira encontrar o menor numero de jogadas
typedef struct Nodo *Nodo;

// Cria um grafo ponderado com o primeiro nodo e retorna
Nodo criaGrafo(Tblr t);

// Encontra o menor caminho no grafo de pesos (ate que a soma dos pesos bruta seja igual ao numero de casas na matriz) 
// e retorna este menor caminho em um vetor de inteiros
int * Joga(Nodo n, Tblr t);

// ------- Funcoes auxiliares --------

// Checa cor de uma posicao da matriz.
int checaCor(Tblr t, int posicao);

// Checa quais sao os quadrados adjacentes a um quadrado especifico, e retorna as posicoes dos adjacentes no vetor
// que representa a matriz do jogo. 
int * verAdjacentes(Tblr t, int posicao, int cor);

// Ve quais sao os filhos deste nodo, ou seja, os grupos de cores que estao ligados ao grupo de quadrados referentes a este nodo. 
void alocaFilhos(Nodo n);
#endif
