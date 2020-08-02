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

// Print each move in a movelist
void PrintMoveList(const movelist_t *list) {

    printf("Move list: \n");
    
    char *movestr;
    int move, score;
    for (int i = 0; i < list->count; i++) {
        move = list->moves[i].move;
        score = list->moves[i].score;
        movestr = PrMove(move);

        printf("Move: %d > %s, Score: %d\n", i + 1, movestr, score);
        
        free(movestr);
    }

    printf("Total of %d moves\n", list->count);
}