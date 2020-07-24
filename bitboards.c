#include <stdio.h>
#include "definitions.h"
#include "initialise.h"

// Function to print the board with each piece on it
void printBitBoard(U64 bitBoard) {
    U64 shift = 1ULL;

    int rank, file;

    for (rank = RANK_8; rank >= RANK_1; rank--) {
        for (file = FILE_A; file <= FILE_H; file++) {
            int indexBig = FR2SQ(file, rank);
            int index64 = BIG2SMALL(indexBig);

            if ((shift << index64) & bitBoard) {
                printf("X ");
            }
            else {
                printf("- ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

int countBits(U64 board) {
    int count = 0, n = board;
    while (n != 0) {
        if (n & 1) {
            count++;
        }
        n>>=1;
    }
    return count;
}