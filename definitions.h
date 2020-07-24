#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define NUM_SQUARES 120
#define MAX_MOVES 2048

#include <stdlib.h>
#include <assert.h>

typedef unsigned long long U64;

enum {EMPTY, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK};
enum {FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NONE};
enum {RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NONE};
enum {WHITE, BLACK, BOTH};
enum {
    A1 = 21, B1, C1, D1, E1, F1, G1, H1,
    A2 = 31, B2, C2, D2, E2, F2, G2, H2,
    A3 = 41, B3, C3, D3, E3, F3, G3, H3,
    A4 = 51, B4, C4, D4, E4, F4, G4, H4,
    A5 = 61, B5, C5, D5, E5, F5, G5, H5,
    A6 = 71, B6, C6, D6, E6, F6, G6, H6,
    A7 = 81, B7, C7, D7, E7, F7, G7, H7,
    A8 = 91, B8, C8, D8, E8, F8, G8, H8, NO_SQ, OFFBOARD
};

enum {FALSE, TRUE};

// Castling permissions represented by a 4 bit int
enum {WKCA = 1, WQCA = 2, BKCA = 4, BQCA = 8};

typedef struct {
    int move;
    int castlePerm;
    int enPas;
    int fiftyMove;
    U64 posKey;
} undo_t;

typedef struct {
    int pieces[NUM_SQUARES];
    
    /** For a given 64 bit int, each bit represents a square - a '1' means a 
     * pawn is on this square. Need 1 int for the white pawns, 1 int for black 
     * pawns, and 1 int for both.
     **/
    U64 pawns[3];
    
    // Squares to store location of white and black kings
    int KingSquare[2];

    // Current side to move
    int side;

    // Active en passant square, if there is one. Otherwise set to NO_SQ
    int enPas;

    // Counter for drawn games after 50 moves.
    int fiftyMove;

    // Current half moves in the search
    int ply;

    // Total number of half moves that have been made
    int histPly;

    // Unique key generated for each position (used for determining repetitions)
    U64 hashKey;

    // Arrays for the total number of pieces on the board
    int pceNum[13];
    // 3 : white, black, and both
    int bigPce[3]; // Anything that isn't a pawn
    int majPce[3]; // Rooks and queens
    int minPce[3]; // Bishops and knights

    int castlePerm;

    // Stores history of moves, used for reversing moves
    undo_t history[MAX_MOVES];

    // piece list to speed up searching
    int pList[13][10];

} board_t;

/* MACROS */

// Convert file,rank to index on big board
#define FR2SQ(f,r) (f + 21 + r*10)

// Convert index on big board to index on small board
#define BIG2SMALL(bigIndex) (big_to_small[bigIndex])

// Convert index on small board to index on big board
#define SMALL2BIG(smallIndex) (small_to_big[smallIndex])

// Set a given bit on a bitboard
#define SETBIT(bb, i) ((bb) |= SetMask[i])

// Clear a given bit on a bitboard
#define CLEARBIT(bb, i) ((bb) &= ClearMask[i])

/* GLOBALS */
extern int big_to_small[NUM_SQUARES];
extern int small_to_big[64];
extern U64 SetMask[64];
extern U64 ClearMask[64];
extern U64 PieceKeys[13][120];
extern U64 SideKey;
extern U64 CastleKeys[16];
extern char PceChar[];
extern char SideChar[];
extern char RankChar[];
extern char FileChar[];

void test();

#endif