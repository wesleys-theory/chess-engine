#include "definitions.h"
#include "initialise.h"
#include "bitboards.h"
#include <stdio.h>

// a comment
int main(int argc, char *argv[]) {
    initialise_all();

    U64 testBoard = 0ULL;
    printf("count = %d\n", countBits(testBoard));
    printBitBoard(testBoard);
    testBoard |= (1ULL<<big_to_small[E4]);
    printf("count = %d\n", countBits(testBoard));
    printBitBoard(testBoard);
    testBoard |= (1ULL<<big_to_small[A1]);
    printf("count = %d\n", countBits(testBoard));
    printBitBoard(testBoard);
    return 0;
}