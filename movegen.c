#include "movegen.h"
#include "stdio.h"
#include "definitions.h"
#include "board.h"
#include "validate.h"
#include "attack.h"

// macro to create the move integer
#define MOVE(f, t, ca, pro, fl) (f | (t << 7) | (ca << 14) | (pro << 20) | fl)

// is the square offboard?
#define ISOFFBOARD(sq) (FileOf[sq]==OFFBOARD)

// Add a "quiet" move to the movelist
void AddQuietMove(const board_t *pos, int move, movelist_t *list) {
    list->moves[list->count].move = move;
    // change this later to evaluate a specific move
    list->moves[list->count].score = 0;
    list->count++;
}

// Add a capture move to the movelist
void AddCaptureMove(const board_t *pos, int move, movelist_t *list) {
    list->moves[list->count].move = move;
    // change this later to evaluate a specific move
    list->moves[list->count].score = 0;
    list->count++;
}

// Add an EnPassant move to the movelist
void AddEnPassantMove(const board_t *pos, int move, movelist_t *list) {
    list->moves[list->count].move = move;
    // change this later to evaluate a specific move
    list->moves[list->count].score = 0;
    list->count++;
}

void AddWhitePawnCapMove(const board_t *pos, movelist_t *list, const int from,
                        const int to, const int cap) {

    assert(PieceValid(cap));
    assert(SqOnBoard(from));
    assert(SqOnBoard(to));
    
    if (RankOf[to]==RANK_8) {
        AddCaptureMove(pos, MOVE(from, to, cap, wQ, 0), list);
        AddCaptureMove(pos, MOVE(from, to, cap, wR, 0), list);
        AddCaptureMove(pos, MOVE(from, to, cap, wB, 0), list);
        AddCaptureMove(pos, MOVE(from, to, cap, wN, 0), list);
    }
    else {
        AddCaptureMove(pos, MOVE(from, to, cap, EMPTY, 0), list);
    }
}

void AddWhitePawnQuietMove(const board_t *pos, movelist_t *list, const int from,
                      const int to) {

    assert(SqOnBoard(from));
    assert(SqOnBoard(to));

    if (RankOf[to]==RANK_8) {
        AddQuietMove(pos, MOVE(from, to, EMPTY, wQ, 0), list);
        AddQuietMove(pos, MOVE(from, to, EMPTY, wR, 0), list);
        AddQuietMove(pos, MOVE(from, to, EMPTY, wB, 0), list);
        AddQuietMove(pos, MOVE(from, to, EMPTY, wN, 0), list);
    }
    else {
        AddQuietMove(pos, MOVE(from, to, 0, EMPTY, 0), list);
    }
}

void AddBlackPawnCapMove(const board_t *pos, movelist_t *list, const int from,
                        const int to, const int cap) {
    assert(PieceValid(cap));
    assert(SqOnBoard(from));
    assert(SqOnBoard(to));

    if (RankOf[to]==RANK_1) {
        AddCaptureMove(pos, MOVE(from, to, cap, bQ, 0), list);
        AddCaptureMove(pos, MOVE(from, to, cap, bR, 0), list);
        AddCaptureMove(pos, MOVE(from, to, cap, bB, 0), list);
        AddCaptureMove(pos, MOVE(from, to, cap, bN, 0), list);
    }
    else {
        AddCaptureMove(pos, MOVE(from, to, cap, EMPTY, 0), list);
    }
}

void AddBlackPawnQuietMove(const board_t *pos, movelist_t *list, const int from,
                      const int to) {
    assert(SqOnBoard(from));
    assert(SqOnBoard(to));

    if (RankOf[to]==RANK_1) {
        AddQuietMove(pos, MOVE(from, to, EMPTY, bQ, 0), list);
        AddQuietMove(pos, MOVE(from, to, EMPTY, bR, 0), list);
        AddQuietMove(pos, MOVE(from, to, EMPTY, bB, 0), list);
        AddQuietMove(pos, MOVE(from, to, EMPTY, bN, 0), list);
    }
    else {
        AddQuietMove(pos, MOVE(from, to, EMPTY, EMPTY, 0), list);
    }
}

void GenerateAllMoves(const board_t *pos, movelist_t *list) {
    CheckBoard(pos);
    list->count = 0;

    int pce, side = pos->side, sq = 0, temp_sq = 0, pceNum, move, i, dir;
    int otherside = (side==WHITE) ? BLACK : WHITE;
    
    // Add white pawn moves
    if (side==WHITE) {
        for (pceNum = 0; pceNum < pos->pceNum[wP]; pceNum++) {
            sq = pos->pList[wP][pceNum];
            assert(!ISOFFBOARD(sq));

            if (pos->pieces[sq + 10]==EMPTY) {
                AddWhitePawnQuietMove(pos, list, sq, sq + 10);
                if (pos->pieces[sq + 20]==EMPTY && RankOf[sq]==RANK_2) {
                    move = MOVE(sq, (sq + 20), EMPTY, 0, MFLAGPS);
                    AddQuietMove(pos, move, list);
                }
            }

            if (!ISOFFBOARD(sq + 9) && PieceCol[pos->pieces[sq + 9]]==BLACK) {
                AddWhitePawnCapMove(pos, list, sq, sq + 9, pos->pieces[sq + 9]);
            }
            if (!ISOFFBOARD(sq + 11) && PieceCol[pos->pieces[sq + 11]]==BLACK) {
                AddWhitePawnCapMove(pos, list, sq, sq + 11, pos->pieces[sq + 11]);
            }

            if (pos->enPas==sq + 9) {
                move = MOVE(sq, (sq + 9), 0, 0, MFLAGEP);
                AddCaptureMove(pos, move, list);
            }
            else if (pos->enPas==sq+11) {
                move = MOVE(sq, (sq + 11), 0, 0, MFLAGEP);
                AddCaptureMove(pos, move, list);
            } 

        }
    }
    // Add black pawns
    else {
        for (pceNum = 0; pceNum < pos->pceNum[bP]; pceNum++) {
            sq = pos->pList[bP][pceNum];
            assert(!ISOFFBOARD(sq));

            if (pos->pieces[sq - 10]==EMPTY) {
                AddBlackPawnQuietMove(pos, list, sq, sq - 10);
                if (pos->pieces[sq - 20]==EMPTY && RankOf[sq]==RANK_7) {
                    move = MOVE(sq, (sq - 20), EMPTY, 0, MFLAGPS);
                    AddQuietMove(pos, move, list);
                }
            }

            if (!ISOFFBOARD(sq - 9) && PieceCol[pos->pieces[sq - 9]]==WHITE) {
                AddBlackPawnCapMove(pos, list, sq, sq - 9, pos->pieces[sq - 9]);
            }
            if (!ISOFFBOARD(sq - 11) && PieceCol[pos->pieces[sq - 11]]==WHITE) {
                AddBlackPawnCapMove(pos, list, sq, sq - 11, pos->pieces[sq - 11]);
            }

            if (pos->enPas==sq - 9) {
                move = MOVE(sq, (sq - 9), 0, 0, MFLAGEP);
                AddCaptureMove(pos, move, list);
            }
            else if (pos->enPas==sq - 11) {
                move = MOVE(sq, (sq - 11), 0, 0, MFLAGEP);
                AddCaptureMove(pos, move, list);
            } 

        }
    }

    // Add knight move generation
    pce = (side==WHITE) ? wN : bN;
    for (pceNum = 0; pceNum < pos->pceNum[pce]; pceNum++) {
        
        sq = pos->pList[pce][pceNum];
        
        for (i = 0; i < 8; i++) {
            
            temp_sq = sq + KnDir[i];
            if (ISOFFBOARD(temp_sq)) {
                continue;
            }

            if (pos->pieces[temp_sq]==EMPTY) {
                move = MOVE(sq, temp_sq, 0, EMPTY, EMPTY);
                AddQuietMove(pos, move, list);
            }

            else if (PieceCol[pos->pieces[temp_sq]]==otherside) {
                move = MOVE(sq, temp_sq, pos->pieces[temp_sq], EMPTY, MFLAGCAP);
                AddCaptureMove(pos, move, list);
            }
        }
    }

    // Add bishop moves
    pce = (side==WHITE) ? wB : bB;
    for (pceNum = 0; pceNum < pos->pceNum[pce]; pceNum++) {

        sq = pos->pList[pce][pceNum];

        for (i = 0; i < 4; i++) {
            dir = BiDir[i];
            GenerateSlideMoves(pos, list, dir, side, sq);
        }
    }

    // Add rook moves
    pce = (side==WHITE) ? wR : bR;
    for (pceNum = 0; pceNum < pos->pceNum[pce]; pceNum++) {

        sq = pos->pList[pce][pceNum];

        for (i = 0; i < 4; i++) {
            dir = RkDir[i];
            GenerateSlideMoves(pos, list, dir, side, sq);
        }
    }

    // Add Queen moves
    pce = (side==WHITE) ? wQ : bQ;
    for (pceNum = 0; pceNum < pos->pceNum[pce]; pceNum++) {

        sq = pos->pList[pce][pceNum];

        for (i = 0; i < 8; i++) {
            dir = BiDir[i];
            GenerateSlideMoves(pos, list, dir, side, sq);
        }
    }

    // Add King moves
    pce = (side==WHITE) ? wK : bK;
        
    sq = pos->KingSquare[side];
    
    for (i = 0; i < 8; i++) {
        
        temp_sq = sq + KiDir[i];
        if (ISOFFBOARD(temp_sq) || SqAttacked(temp_sq, otherside, pos)) continue;


        if (pos->pieces[temp_sq]==EMPTY) {
            move = MOVE(sq, temp_sq, 0, EMPTY, EMPTY);
            AddQuietMove(pos, move, list);
        }

        else if (PieceCol[pos->pieces[temp_sq]]==otherside) {
            move = MOVE(sq, temp_sq, pos->pieces[temp_sq], EMPTY, MFLAGCAP);
            AddCaptureMove(pos, move, list);
        }
    }

}

// Generates possible moves in a certain direction
void GenerateSlideMoves(const board_t *pos, movelist_t *list, int dir, int side, int sq) {
    
    int temp_sq = sq + dir, move;
    int pce = pos->pieces[temp_sq];
    
    while(pce==EMPTY) {
        move = MOVE(sq, temp_sq, 0, EMPTY, 0);
        AddQuietMove(pos, move, list);
        
        temp_sq += dir;
        pce = pos->pieces[temp_sq];
    }

    // Potentially capture the piece
    if (!ISOFFBOARD(temp_sq) && (PieceCol[pce] != side)) {
        move = MOVE(sq, temp_sq, pce, 0, MFLAGCAP);
        AddCaptureMove(pos, move, list);
    }
}
