#ifndef _PLAYER_
#define _PLAYER_
#include <stdbool.h>
#include "vertice.h"
#include "grafo.h"
#include "lista.h"

// Pega os vizinhos da lista Grupo e seleciona o melhor filho baseado no peso e no bônus
//      até consumir todos os vértices do grafo. Retorna a lista de jogadas
Lista Joga(Grafo g, Lista grupo);

// Retorna todos os filhos de uma lista de vértices
Lista filhosGrupo(Lista grupoPai);

// Retorna uma lista de vértices com as cores e pesos agrupadas a partir de l
Lista agrupaCores(Lista filhos, Grafo g);

int calculaBonus(Vertice v, Lista filhos);
#endif
