#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "board.h"

struct Cell {
    // Cor da célula
    int color;
    // Se a célula já foi visitada
    bool visited;
};

struct Board {
    int x, y, colors;
    Cell *cells;
};

Board createBoard() {
    Board b = malloc(sizeof(struct Board));
    if(!b) return NULL;
    b->x = b->y = b->colors = 0;
    return b;
}

int readBoard(Board b) {
    int x, y, colors;
    scanf("%d %d %d", &x, &y, &colors);
    b->x = x;
    b->y = y;
    b->colors = colors;
    // Aloca um único array em vez de um "array de arrays"
    b->cells = malloc(sizeof(struct Cell) * x * y);
    if(b->cells == NULL) return 0;
    for(int i=0; i < x; ++i)
        for(int j=0; j < y; ++j) {
            // Para acessar uma matrix [X][Y] em um vetor fazemos i*Y + j
            Cell c = malloc(sizeof(struct Cell));
            c->visited = false;
            scanf("%d", &(c->color));
            b->cells[i * y + j] = c;
        }
    return 1;
}

void printBoard(Board b) {
    printf("%d ", b->x);
    printf("%d ", b->y);
    printf("%d\n", b->colors);
    for(int i=0; i < b->x; ++i) {
        for(int j=0; j < b->y; ++j)
            printf("%d ", b->cells[i * b->y + j]->color);
        puts("");
    }
    return;
}
