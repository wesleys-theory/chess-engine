#include <stdio.h>
#include "definitions.h"

void ResetBoard(board_t *pos) {
    int i;
    
    for (i = 0; i < NUM_SQUARES; i++) {
        pos->pieces[i] = OFFBOARD;
    }

    for (i = 0; i < 64; i++) {
        pos->pieces[SMALL2BIG(i)] = EMPTY;
    }

    for (i = 0; i < 3; i++) {
        pos->bigPce[i] = 0;
        pos->majPce[i] = 0;
        pos->minPce[i] = 0;
        pos->pawns[i] = 0ULL;
    }

    for (i = 0; i < 13; i++) {
        pos->pceNum[i] = 0;
    }

    pos->hashKey = 0ULL;
    pos->histPly = 0;
    pos->KingSquare[WHITE] = pos->KingSquare[BLACK] = NO_SQ;
    pos->side = BOTH;
    pos->enPas = NO_SQ;
    pos->fiftyMove = 0;
    pos->ply = 0;
    pos->castlePerm = 0;
}