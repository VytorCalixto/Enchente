#include <stdbool.h>
#include <stdlib.h>
#include "filha.h"
#include "no.h"

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

No primeiroNoFilha(Filha f) {
    if(f->tamanho == 0) {
        return NULL;
    }
    No n = f->primeiro;
    f->primeiro = getSucessorNo(f->primeiro);
    --f->tamanho;
    setSucessorNo(n, NULL);
    setAntecessorNo(n, NULL);
    return n;
}

No ultimoNoFilha(Filha f) {
    if(f->tamanho == 0) {
        return NULL;
    }
    No n = f->ultimo;
    f->ultimo = getAntecessorNo(f->ultimo);
    --f->tamanho;
    setSucessorNo(n, NULL);
    setAntecessorNo(n, NULL);
    return n;
}

No insereFilha(void *conteudo, Filha f) {
    No novo = criaNo();

    if(!novo) return NULL;

    setConteudo(novo, conteudo);

    if(f->tamanho == 0) {
        f->primeiro = novo;
    }

    setAntecessorNo(novo, f->ultimo);
    setSucessorNo(f->ultimo, novo);

    ++f->tamanho;
    return f->ultimo = novo;
}

bool destroiFilha(Filha f, bool destroi(void *)) {
    No n;
    bool ok=true;

    while( (n = primeiroNoFilha(f)) ) {
        if(destroi)
            ok &= destroi(getConteudo(n));
        free(n);
    }
    free(f);
    return ok;
}
