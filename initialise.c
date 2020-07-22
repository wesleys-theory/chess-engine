#include "definitions.h"
#include "initialise.h"



int big_to_small[NUM_SQUARES];
int small_to_big[64];

/** function to initialise arrays that convert positions in the 64 square array
 *  to positions in the 120 square array and vice-versa 
 **/
void initialise_conversions() {
    
    int i;
    // initialise all positions in both arrays to -1 for safety
    for (i = 0; i < NUM_SQUARES; i++) {
        big_to_small[i] = -1;
    }
    for (i = 0; i < 64; i++) {
        small_to_big[i] = -1;
    }

    int file, rank, square;
    int count = 0;
    for (rank = RANK_1; rank <= RANK_8; rank++) {
        for (file = FILE_A; file <= FILE_H; file++) {
            square = fr_to_sq(file, rank);
            small_to_big[count] = square;
            big_to_small[square] = count;
            
            count++;
        }
    }
}

// called from main
void initialise_all() {
    initialise_conversions();
}