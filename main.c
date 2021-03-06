#include "definitions.h"
#include "initialise.h"
#include "bitboards.h"
#include "movegen.h"
#include "validate.h"
#include "board.h"
#include "attack.h"
#include "io.h"
#include <stdio.h>
#include <stdlib.h>

#define FEN1 "8/3q1p2/8/5P2/4Q3/8/8/8 w - - 0 2 "
#define FEN2 "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1"
#define FEN3 "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2"
#define FEN4 "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"
#define PAWNMOVESW "rnbqkb1r/pp1p1pPp/8/2p1pP2/1P1P4/3P3P/P1P1P3/RNBQKBNR w KQkq e6 0 1"
#define PAWNMOVESB "rnbqkbnr/p1p1p3/3p3p/1p1p4/2P1Pp2/8/PP1P1PpP/RNBQKB1R b KQkq e3 0 1"
#define KNIGHTSKINGS "5k2/1n6/4n3/6N1/8/3N4/8/5K2 w - - 0 1"
#define LOTOFMOVES "R6R/3Q4/1Q4Q1/4Q3/2Q4Q/Q4Q2/pp1Q4/kBNN1KB1 w - - 0 1"

int main(int argc, char *argv[]) {
    initialise_all();

    board_t *board = (board_t *)malloc(sizeof(board_t));
    movelist_t *list = (movelist_t *)malloc(sizeof(movelist_t));

    ParseFEN(LOTOFMOVES, board);
    PrintBoard(board);

    GenerateAllMoves(board, list);
    PrintMoveList(list);

    return 0;
}