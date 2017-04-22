#ifndef _BOARD_
#define _BOARD_
#include <stdbool.h>

typedef struct Cell *Cell;

typedef struct Board *Board;

Board createBoard();

int readBoard(Board b);

void printBoard(Board b);

#endif
