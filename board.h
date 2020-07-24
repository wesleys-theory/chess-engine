#ifndef BOARD_H
#define BOARD_H

#include "definitions.h"

void ResetBoard(board_t *pos);
int ParseFEN(char *fen, board_t *pos);



#endif