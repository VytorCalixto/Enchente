#include <malloc.h>
#include "lista.h"
#include "no.h"
//---------------------------------------------------------------------------
// Lista encadeada

struct Lista {

    unsigned int tamanho;
    int padding; // só pra evitar warning
    No primeiro;
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

int destroiLista(Lista l, int destroi(void *)) {

    No p;
    int ok=1;

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
    setSucessorNo(novo, primeiroNoLista(l));
    ++l->tamanho;

    return l->primeiro = novo;
}

//------------------------------------------------------------------------------
// remove o No de endereço rNo de l
// se destroi != NULL, executa destroi(getConteudo(rNo))
// devolve 1, em caso de sucesso
//         0, se rNo não for um No de l

int removeNo(struct Lista *l, struct No *rNo, int destroi(void *)) {
    int r = 1;
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
            if (destroi != NULL) {
                r = destroi(getConteudo(rNo));
            }
            free(rNo);
            l->tamanho--;
            return r;
        }
    }
    return 0;
}
