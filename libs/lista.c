#include <malloc.h>
#include <stdbool.h>
#include "lista.h"
#include "no.h"
//---------------------------------------------------------------------------
// Lista encadeada

struct Lista {

    unsigned int tamanho;
    int padding; // só pra evitar warning
    No primeiro, ultimo;
};
//---------------------------------------------------------------------------
// devolve o número de nós da Lista l

unsigned int tamanhoLista(Lista l) { return l->tamanho; }

//---------------------------------------------------------------------------
// devolve o primeiro nó da Lista l,
//      ou NULL, se l é vazia

No primeiroNoLista(Lista l) { return l->primeiro; }

//---------------------------------------------------------------------------
// cria uma Lista vazia e a devolve
//
// devolve NULL em caso de falha

Lista constroiLista(void) {

    Lista l = malloc(sizeof(struct Lista));

    if ( ! l )
    return NULL;

    l->primeiro = NULL;
    l->ultimo = NULL;
    l->tamanho = 0;

    return l;
}
//---------------------------------------------------------------------------
// desaloca a Lista l e todos os seus nós
//
// se destroi != NULL invoca
//
//     destroi(getConteudo(n))
//
// para cada nó n da Lista.
//
// devolve 1 em caso de sucesso,
//      ou 0 em caso de falha

bool destroiLista(Lista l, bool destroi(void *)) {

    No p;
    bool ok=true;

    while ( (p = primeiroNoLista(l)) ) {

        l->primeiro = getSucessorNo(p);

        if ( destroi )
        ok &= destroi(getConteudo(p));

        free(p);
    }

    free(l);

    return ok;
}
//---------------------------------------------------------------------------
// insere um novo nó na Lista l cujo conteúdo é p
//
// devolve o No recém-criado
//      ou NULL em caso de falha

No insereLista(void *conteudo, Lista l) {
    No novo = criaNo();

    if ( ! novo )
    return NULL;

    setConteudo(novo, conteudo);
    ++l->tamanho;
    if(l->tamanho == 1) {
        l->primeiro = novo;
    }
    if(l->ultimo) {
        setSucessorNo(l->ultimo, novo);
    }
    l->ultimo = novo;

    return novo;
}

//---------------------------------------------------------------------------
// insere um novo nó na Lista l cujo conteúdo é p
//
// devolve o No recém-criado
//      ou NULL em caso de falha

No insereUnicoLista(void *conteudo, Lista l) {
    // Não insere se já estiver na lista
    for(No n = primeiroNoLista(l); n; n = getSucessorNo(n)) {
        if(getConteudo(n) == conteudo) {
            return n;
        }
    }
    No novo = criaNo();

    if ( ! novo )
    return NULL;

    setConteudo(novo, conteudo);
    ++l->tamanho;
    if(l->tamanho == 1) {
        l->primeiro = novo;
    }
    if(l->ultimo) {
        setSucessorNo(l->ultimo, novo);
    }
    l->ultimo = novo;

    return novo;
}

//------------------------------------------------------------------------------
// remove o No de endereço rNo de l
// se destroi != NULL, executa destroi(getConteudo(rNo))
// devolve 1, em caso de sucesso
//         0, se rNo não for um No de l

bool removeNo(struct Lista *l, struct No *rNo, bool destroi(void *)) {
    bool r = true;
    if (l->primeiro == rNo) {
        l->primeiro = getSucessorNo(rNo);
        if (destroi != NULL) {
            r = destroi(getConteudo(rNo));
        }
        free(rNo);
        l->tamanho--;
        return r;
    }
    for (No n = primeiroNoLista(l); getSucessorNo(n); n = getSucessorNo(n)) {
        if (getSucessorNo(n) == rNo) {
            setSucessorNo(n, getSucessorNo(rNo));
            setAntecessorNo(getSucessorNo(rNo), n);
            if (destroi != NULL) {
                r = destroi(getConteudo(rNo));
            }
            free(rNo);
            l->tamanho--;
            return r;
        }
    }
    return false;
}

No pertenceLista(void *conteudo, Lista l) {
    for(No n = primeiroNoLista(l); n; n = getSucessorNo(n)) {
        if(conteudo == getConteudo(n)) {
            return n;
        }
    }
    return NULL;
}
