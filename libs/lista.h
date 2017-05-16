#ifndef _LISTA_
#define _LISTA_
#include "no.h"
#include <stdbool.h>

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
// insere um Novo nó na Lista l cujo conteúdo é p se p não estiver na lista
//
// devolve o No recém-criado
//      ou NULL em caso de falha

No insereUnicoLista(void *conteudo, Lista l);

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
// devolve true em caso de sucesso,
//      ou false em caso de falha

bool destroiLista(Lista l, bool destroi(void *));

//------------------------------------------------------------------------------
// remove o No de endereço rNo de l
// se destroi != NULL, executa destroi(conteudo(rNo))
// devolve true, em caso de sucesso
//         false, se rNo não for um No de l

bool removeNoLista(struct Lista *l, struct No *rNo, bool destroi(void *));

//------------------------------------------------------------------------------
// retorna o nó que contém *conteudo se está na lista l,
//      NULL caso contrário
No pertenceLista(void *conteudo, Lista l);
#endif
