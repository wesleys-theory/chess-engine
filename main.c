#include "definitions.h"
#include "initialise.h"
#include "bitboards.h"
#include <stdio.h>

// a comment
int main(int argc, char *argv[]) {
    initialise_all();

    U64 testBoard = 0ULL;
    testBoard |= (1ULL<<big_to_small[E4]);

    printBitBoard(testBoard);
    return 0;
}