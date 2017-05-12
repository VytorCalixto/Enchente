#ifndef _LISTA_
#define _LISTA_
#include "no.h"

//-----------------------------------------------------------------------------
// (apontador para) Lista encadeada

typedef struct Lista *Lista;

//------------------------------------------------------------------------------
// devolve o número de nós da Lista l

unsigned int tamanhoLista(Lista l);

//------------------------------------------------------------------------------
// devolve o primeiro nó da Lista l,
//      ou NULL, se l é vazia

No primeiroNoLista(Lista l);

//------------------------------------------------------------------------------
// insere um Novo nó na Lista l cujo conteúdo é p
//
// devolve o No recém-criado
//      ou NULL em caso de falha

No insereLista(void *conteudo, Lista l);
//------------------------------------------------------------------------------
// cria uma Lista vazia e a devolve
//
// devolve NULL em caso de falha

Lista constroiLista(void);
//------------------------------------------------------------------------------
// desaloca a Lista l e todos os seus nós
//
// se destroi != NULL invoca
//
//     destroi(conteudo(n))
//
// para cada nó n da Lista.
//
// devolve 1 em caso de sucesso,
//      ou 0 em caso de falha

int destroiLista(Lista l, int destroi(void *));

//------------------------------------------------------------------------------
// remove o No de endereço rNo de l
// se destroi != NULL, executa destroi(conteudo(rNo))
// devolve 1, em caso de sucesso
//         0, se rNo não for um No de l

int removeNoLista(struct Lista *l, struct No *rNo, int destroi(void *));
#endif
