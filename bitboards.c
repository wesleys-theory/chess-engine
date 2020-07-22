#include <stdio.h>
#include "definitions.h"
#include "initialise.h"

// Function to print the board with each piece on it
void printBitBoard(U64 bitBoard) {
    U64 shift = 1ULL;

    int rank, file;

    printf("\n");
    for (rank = RANK_8; rank >= RANK_1; rank--) {
        for (file = FILE_A; file <= FILE_H; file++) {
            int indexBig = fr_to_sq(file, rank);
            int index64 = big_to_small[indexBig];

            if ((shift << index64) & bitBoard) {
                printf("X ");
            }
            else {
                printf("- ");
            }
        }
        printf("\n");
    }
}