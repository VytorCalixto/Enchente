#include <stdlib.h>
#include "no.h"

struct No {
    void *conteudo;
    No anterior, proximo;
};

No criaNo() {
    No n = malloc(sizeof(struct No));

    n->anterior = NULL;
    n->proximo = NULL;
    return n;
}

No getSucessorNo(No n) {
    return n->proximo;
}

void setSucessorNo(No n, No p) {
    n->proximo = p;
}

No getAntecessorNo(No n) {
    return n->anterior;
}

void setAntecessorNo(No n, No p) {
    n->anterior = p;
}

void *getConteudo(No n) {
    return n->conteudo;
}

void setConteudo(No n, void *conteudo) {
    n->conteudo = conteudo;
}
