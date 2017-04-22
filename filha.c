#include "filha.h"
#include <stdbool.h>
#include <stdlib.h>

struct No {
    void *conteudo;
    No anterior, proximo;
};

struct Filha {
    unsigned int tamanho;
    No primeiro, ultimo;
};

Filha constroiFilha() {
    Filha f = malloc(sizeof(struct Filha));
    if(!f) return NULL;
    f->tamanho = 0;
    f->primeiro = f->ultimo = NULL;
    return f;
}

unsigned int tamanhoFilha(Filha f) {
    return f->tamanho;
}

No primeiroNo(Filha f) {
    if(f->tamanho == 0) {
        return NULL;
    }
    No n = f->primeiro;
    f->primeiro = f->primeiro->proximo;
    n->anterior = NULL;
    n->proximo = NULL;
    return n;
}

No ultimoNo(Filha f) {
    if(f->tamanho == 0) {
        return NULL;
    }
    No n = f->ultimo;
    f->ultimo = f->ultimo->anterior;
    n->anterior = NULL;
    n->proximo = NULL;
    return n;
}

No sucessorNo(No n) {
    return n->proximo;
}

No antecessorNo(No n) {
    return n->anterior;
}

void *conteudo(No n) {
    return n->conteudo;
}

No insere(void *conteudo, Filha f) {
    No novo = malloc(sizeof(struct No));

    if(!novo) return NULL;

    novo->conteudo = conteudo;
    novo->anterior = f->ultimo;
    ++f->tamanho;
    return f->ultimo = novo;
}

bool destroi(Filha f, bool destroi(void *)) {
    No n;
    bool ok=true;

    while( (n = primeiroNo(f)) ) {
        if(destroi)
            ok &= destroi(conteudo(n));
        free(n);
    }
    free(f);
    return ok;
}
