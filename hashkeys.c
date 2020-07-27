#include "definitions.h"
#include <stdlib.h>
#include "hashkeys.h"

U64 PieceKeys[13][120];
U64 SideKey;
U64 CastleKeys[16];

/** Fill hash keys with random values. Assumes RAND64 will produce unique keys -
 *  there is a very very very tiny probability that we will get the same hash.
 * **/
void initHashKeys() {
    for (int i = 0; i < 13; i ++) {
        for (int j = 0; j < 120; j++) {
            PieceKeys[i][j] = RAND64;
        }
    }
    SideKey = RAND64;
    for (int i = 0; i < 16; i++) {
        CastleKeys[i] = RAND64;
    }
}

// Generate a hashkey based on the given board by XOR'ing everything
U64 GeneratePosKey(const board_t *pos) {
    int sq, piece;
    U64 finalKey = 0;

    /** Each square/piece combination has a unique key in PieceKeys. finalKey
     *  is XOR'd with each square/piece combination
     *  **/
    for (sq = 0; sq < NUM_SQUARES; sq++) {
        piece = pos->pieces[sq];
        if (piece!=NO_SQ && piece!=EMPTY && piece!= OFFBOARD) {
            assert(piece>=wP && piece<=bK);
            finalKey ^= PieceKeys[piece][sq];
        }
    }

    if (pos->side == WHITE) {
        finalKey ^= SideKey;
    }

    if (pos->enPas != NO_SQ) {
        assert(pos->enPas>=0 && pos->enPas<NUM_SQUARES);
        finalKey ^= PieceKeys[EMPTY][pos->enPas];
    }

    assert(pos->castlePerm >= 0 && pos->castlePerm <= 15);
    finalKey ^= CastleKeys[pos->castlePerm];

    return finalKey;
}