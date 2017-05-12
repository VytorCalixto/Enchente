#ifndef _NO_
#define _NO_

// Nó cujo conteúdo é um void *
typedef struct No *No;

// Cria um nó vazio e devolve
No criaNo();

// Devolve o nó sucessor de n ou NULL se n é o último nó da filha
No getSucessorNo(No n);

// Define o nó sucessor de n
void setSucessorNo(No n, No p);

// Devolve o nó antecessor de n ou NULL se n é o primeiro nó da filha
No getAntecessorNo(No n);

// Define o nó antecessor de n
void setAntecessorNo(No n, No p);

// Devolve o conteúdo de n
void *getConteudo(No n);

void setConteudo(No n, void *conteudo);

#endif
