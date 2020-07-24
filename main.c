#include "definitions.h"
#include "initialise.h"
#include "bitboards.h"
#include "board.h"
#include <stdio.h>
#include <stdlib.h>

#define FEN1 "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
#define FEN2 "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1"
#define FEN3 "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2"
#define FEN4 "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2"

int main(int argc, char *argv[]) {
    initialise_all();

    board_t board[1];

    ResetBoard(board);

    ParseFEN(FEN1, board);
    PrintBoard(board);

    ParseFEN(FEN2, board);
    PrintBoard(board);

    ParseFEN(FEN3, board);
    PrintBoard(board);

    ParseFEN(FEN4, board);
    PrintBoard(board);
    

    return 0;
}