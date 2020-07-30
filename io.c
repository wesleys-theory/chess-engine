#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"


// Returns the algebraic string of a given square
char *PrSq(const int sq) {
    
    char *SqStr = (char *) malloc(3 * sizeof(char));

    int file = FileOf[sq], rank = RankOf[sq];

    sprintf(SqStr, "%c%c", 'a' + file, '1' + rank);


    return SqStr;
}

// Returns the algebraic string of a given move
char *PrMove(const int move) {

    char *MvStr = (char *) malloc(6*sizeof(char));

    int ff = FileOf[FROMSQ(move)];
    int rf = RankOf[FROMSQ(move)];
    int ft = FileOf[TOSQ(move)];
    int rt = RankOf[TOSQ(move)];

    int promoted = PROMOTED(move);

    if (promoted) {
        char pchar = 'q';
        if (IsKn(promoted)) pchar = 'n';
        else if (IsRQ(promoted) && !IsBQ(promoted)) pchar = 'r';
        else if (!IsRQ(promoted) && IsBQ(promoted)) pchar = 'b';
        sprintf(MvStr, "%c%c%c%c%c", 'a' + ff, '1' + rf, 'a' + ft, '1' + rt, pchar);
    }
    else {
        sprintf(MvStr, "%c%c%c%c", 'a' + ff, '1' + rf, 'a' + ft, '1' + rt);
    }

    return MvStr;
}