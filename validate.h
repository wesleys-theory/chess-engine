#ifndef VALIDATE_H
#define VALIDATE_H

#include "definitions.h"

int SqOnBoard(const int sq);

int SideValid(const int side);

int FileRankValid(const int file_or_rank);

int PieceValid(const int pce);

int PieceNonEmpty(const int pce);

#endif