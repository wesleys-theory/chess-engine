#include "validate.h"
#include "definitions.h"



// checks whether the given square is on the board or not
int SqOnBoard(const int sq) {
    return (FileOf[sq] != OFFBOARD);
}

int SideValid(const int side) {
    return (side == WHITE || side == BLACK);
}

int FileRankValid(const int file_or_rank) {
    return (file_or_rank >= 0 && file_or_rank <= 7);
}

int PieceValid(const int pce) {
    return (pce >= EMPTY && pce <= bK);
}

int PieceNonEmpty(const int pce) {
    return (pce >= wP && pce <= bK);
} 