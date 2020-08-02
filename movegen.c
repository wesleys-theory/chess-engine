#include "movegen.h"
#include "stdio.h"
#include "definitions.h"
#include "board.h"

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

void GenerateAllMoves(const board_t *pos, movelist_t *list) {
    CheckBoard(pos);
    list->count = 0;

    int pce, side = pos->side, sq = 0, t_sq = 0, pceNum, move;
    
    // Add white pawn moves
    if (side==WHITE) {
        for (pceNum = 0; pceNum < pos->pceNum[wP]; pceNum++) {
            sq = pos->pList[wP][pceNum];
            assert(!ISOFFBOARD(sq));

            if (pos->pieces[sq + 10]==EMPTY) {
                AddWhitePawnQuietMove(pos, list, sq, sq + 10);
                if (pos->pieces[sq + 20]==EMPTY && RankOf[sq]==RANK_2) {
                    move = MOVE(sq, (sq + 20), 0, 0, MFLAGPS);
                    AddQuietMove(pos, move, list);
                }
            }

            if (!ISOFFBOARD(sq + 9) && PieceCol[pos->pieces[sq + 9]]==BLACK) {
                AddWhitePawnCapMove(pos, list, sq, sq + 9, pos->pieces[sq + 9]);
            }
            if (!ISOFFBOARD(sq + 11) && PieceCol[pos->pieces[sq + 11]]==BLACK) {
                AddWhitePawnCapMove(pos, list, sq, sq + 11, pos->pieces[sq + 11]);
            }

            if (pos->enPas==sq+9) {
                move = MOVE(sq, (sq + 9), 0, 0, MFLAGEP);
                AddCaptureMove(pos, move, list);
            }
            else if (pos->enPas==sq+11) {
                move = MOVE(sq, (sq + 11), 0, 0, MFLAGEP);
                AddCaptureMove(pos, move, list);
            } 

        }
    }
    
}