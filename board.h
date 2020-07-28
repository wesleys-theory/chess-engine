#ifndef BOARD_H
#define BOARD_H

#include "definitions.h"

void ResetBoard(board_t *pos);
int ParseFEN(char *fen, board_t *pos);
void PrintBoard(const board_t *pos);
void UpdateListsMaterial(board_t *pos);
int CheckBoard(const board_t *pos);
void ShowSqAtBySide(const int side, const board_t *pos);


#endif