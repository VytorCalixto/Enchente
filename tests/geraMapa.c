#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct {
    int nlinhas;
    int ncolunas;
    int ncores;
    int **mapa;
} tmapa;

void gera_mapa(tmapa *m, int semente) {
    int i, j;

    srand(semente);
    m->mapa = (int**) malloc(m->nlinhas * sizeof(int*));
    for(i = 0; i < m->nlinhas; i++) {
        m->mapa[i] = (int*) malloc(m->ncolunas * sizeof(int));
        for(j = 0; j < m->ncolunas; j++)
        m->mapa[i][j] = 1 + rand() % m->ncores;
    }
}


void mostra_mapa(tmapa *m) {
    int i, j;

    printf("%d %d %d\n", m->nlinhas, m->ncolunas, m->ncores);
    for(i = 0; i < m->nlinhas; i++) {
        for(j = 0; j < m->ncolunas; j++)
        if(m->ncores > 10)
        printf("%02d ", m->mapa[i][j]);
        else
        printf("%d ", m->mapa[i][j]);
        printf("\n");
    }
}

void mostra_mapa_cor(tmapa *m) {
    int i, j;
    char* cor_ansi[] = { "\x1b[0m",
    "\x1b[31m", "\x1b[32m", "\x1b[33m",
    "\x1b[34m", "\x1b[35m", "\x1b[36m",
    "\x1b[37m", "\x1b[30;1m", "\x1b[31;1m",
    "\x1b[32;1m", "\x1b[33;1m", "\x1b[34;1m",
    "\x1b[35;1m", "\x1b[36;1m", "\x1b[37;1m" };

    if(m->ncores > 15) {
        mostra_mapa(m);
        return;
    }
    printf("%d %d %d\n", m->nlinhas, m->ncolunas, m->ncores);
    for(i = 0; i < m->nlinhas; i++) {
        for(j = 0; j < m->ncolunas; j++)
        if(m->ncores > 10)
        printf("%s%02d%s ", cor_ansi[m->mapa[i][j]], m->mapa[i][j], cor_ansi[0]);
        else
        printf("%s%d%s ", cor_ansi[m->mapa[i][j]], m->mapa[i][j], cor_ansi[0]);
        printf("\n");
    }
}

int main(int argc, char **argv) {
    int cor;
    tmapa m;
    int semente;

    if(argc < 4 || argc > 5) {
        printf("uso: %s <numero_de_linhas> <numero_de_colunas> <numero_de_cores> [<semente_aleatoria>]\n", argv[0]);
        exit(1);
    }

    m.nlinhas = atoi(argv[1]);
    m.ncolunas = atoi(argv[2]);
    m.ncores = atoi(argv[3]);

    if(argc == 5) semente = atoi(argv[4]);
    else semente = time(NULL);
    gera_mapa(&m, semente);
    // mostra_mapa_cor(&m);

    FILE *fp;
    char str[30];
    sprintf(str, "/tmp/%d.in", semente);
    fp = fopen(str, "w+");
    fprintf(fp, "%d %d %d\n", m.nlinhas, m.ncolunas, m.ncores);
    for(int i = 0; i < m.nlinhas; i++) {
        for(int j = 0; j < m.ncolunas; j++)
        if(m.ncores > 10)
        fprintf(fp, "%02d ", m.mapa[i][j]);
        else
        fprintf(fp, "%d ", m.mapa[i][j]);
        fprintf(fp, "\n");
    }
    return 0;
}
