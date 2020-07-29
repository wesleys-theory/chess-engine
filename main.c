#include "definitions.h"
#include "initialise.h"
#include "bitboards.h"
#include "board.h"
#include "attack.h"
#include <stdio.h>
#include <stdlib.h>

#define FEN1 "8/3q1p2/8/5P2/4Q3/8/8/8 w - - 0 2 "
#define FEN2 "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1"
#define FEN3 "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2"
#define FEN4 "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"

int main(int argc, char *argv[]) {
    initialise_all();

    board_t board[1];

    ResetBoard(board);

    ParseFEN(FEN4, board);
    PrintBoard(board);
    CheckBoard(board);

    int move = 0, from = 6, to = 12, cap = wR, prom = bR;
    move = (from) | (to >> 7) | (cap << 14) | (prom << 20);
    printf("\ndec: %d, hex: %X\n", move, move);
    PrintBin(move);


    printf("from:%d to:%d cap:%d prom:%d\n",
            FROMSQ(move), TOSQ(move), CAPTURED(move), PROMOTED(move));
    
    

    return 0;
}