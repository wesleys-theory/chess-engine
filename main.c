#include "definitions.h"
#include "initialise.h"
#include "bitboards.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    initialise_all();

    U64 testBoard = 0ULL;
    printBitBoard(testBoard);
    
    SETBIT(testBoard, BIG2SMALL(E4));
    printBitBoard(testBoard);
    
    SETBIT(testBoard, BIG2SMALL(D2));
    printBitBoard(testBoard);

    SETBIT(testBoard, BIG2SMALL(A1));
    printBitBoard(testBoard);

    CLEARBIT(testBoard,BIG2SMALL(E4));
    printBitBoard(testBoard);
    return 0;
}