#include "attack.h"
#include "definitions.h"
#include "validate.h"
#include "board.h"

// Directions of movement for each piece - queen = rook | bishop
const int KnDir[8] = {-8, -19, -21, -12, 8, 19, 21, 12};
const int RkDir[4] = {-1, -10, 1, 10};
const int BiDir[4] = {-9, -11, 11, 9};
const int KiDir[8] = {-1, -10, 1, 10, -9, -11, 11, 9};

// Checks if the given square is attacked by the given side
int SqAttacked(const int sq, const int side, const board_t *pos) {

    assert(SqOnBoard(sq));
    assert(SideValid(side));
    CheckBoard(pos);
    
    int pce, i, temp_sq;

    // check for pawns attacking the given square
    if (side==WHITE) {
        if (pos->pieces[sq-11]==wP || pos->pieces[sq-9]==wP) {
            return TRUE;
        }
    }
    else if (pos->pieces[sq+11]==bP || pos->pieces[sq+9]==bP) {
        return TRUE;
    }

    // check for knights attacking square
    for (i = 0; i < 8; i++) {
        pce = pos->pieces[sq + KnDir[i]];
        if (IsKn(pce) && PieceCol[pce]==side) {
            return TRUE;
        }
    }

    // check for rooks/queens attacking square
    for (i = 0; i < 4; i++) {
        temp_sq = sq + RkDir[i];
        pce = pos->pieces[temp_sq];
        // find the nearest piece in the current direction
        while (pce==EMPTY) {
            temp_sq += RkDir[i];
            pce = pos->pieces[temp_sq];
        }
        // check if it's a rook or a queen
        if (IsRQ(pce) && PieceCol[pce]==side) {
            return TRUE;
        }
    }

    // check for bishops/queens attacking square
    for (i = 0; i < 4; i++) {
        temp_sq = sq + BiDir[i];
        pce = pos->pieces[temp_sq];
        // find nearest piece in current direction
        while (pce==EMPTY) {
            temp_sq += BiDir[i];
            pce = pos->pieces[temp_sq];
        }
        // check if it's a bishop or a queen
        if (IsBQ(pce) && PieceCol[pce]==side) {
            return TRUE;
        }
    }

    //check for kings attacking square
    for (i = 0; i < 8; i++) {
        pce = pos->pieces[sq + KiDir[i]];
        if (IsKi(pce) && PieceCol[pce]==side) {
            return TRUE;
        }
    }

    // no pieces attacking the square were found
    return FALSE;
}