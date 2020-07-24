#include <stdio.h>
#include "definitions.h"
#include <ctype.h>

void ResetBoard(board_t *pos) {
    int i;
    
    for (i = 0; i < NUM_SQUARES; i++) {
        pos->pieces[i] = OFFBOARD;
    }

    for (i = 0; i < 64; i++) {
        pos->pieces[SMALL2BIG(i)] = EMPTY;
    }

    for (i = 0; i < 3; i++) {
        pos->bigPce[i] = 0;
        pos->majPce[i] = 0;
        pos->minPce[i] = 0;
        pos->pawns[i] = 0ULL;
    }

    for (i = 0; i < 13; i++) {
        pos->pceNum[i] = 0;
    }

    pos->hashKey = 0ULL;
    pos->histPly = 0;
    pos->KingSquare[WHITE] = pos->KingSquare[BLACK] = NO_SQ;
    pos->side = BOTH;
    pos->enPas = NO_SQ;
    pos->fiftyMove = 0;
    pos->ply = 0;
    pos->castlePerm = 0;
}

int ParseFEN(char *fen, board_t *pos) {
    assert(fen != NULL);
    assert(pos != NULL);
    ResetBoard(pos);

    int rank = RANK_8, file, index = 0, squareBig, squareSmall, 
        num, isBlack = 0;
    char ch;
    while (rank >= RANK_1) {
        for (file = FILE_A; file <= FILE_H; file++) {
            ch = fen[index];
            isBlack = islower(ch);
            ch = tolower(ch);
            squareBig = FR2SQ(file, rank);
            squareSmall = BIG2SMALL(squareBig);
            switch(ch) {
                case 'p': 
                    if (isBlack) {
                        SETBIT(pos->pawns[BLACK], squareSmall);
                        pos->pieces[squareBig] = bP;
                    }
                    else {
                        SETBIT(pos->pawns[WHITE], squareSmall);
                        pos->pieces[squareBig] = wP;
                    }
                    break;
                case 'n':
                    if (isBlack) {
                        pos->bigPce[BLACK]++;
                        pos->minPce[BLACK]++;
                        pos->pieces[squareBig] = bN;
                    }
                    else {
                        pos->bigPce[WHITE]++;
                        pos->minPce[WHITE]++;
                        pos->pieces[squareBig] = wN;
                    }
                    break;
                case 'b':
                    if (isBlack) {
                        pos->bigPce[BLACK]++;
                        pos->minPce[BLACK]++;
                        pos->pieces[squareBig] = bB;
                    }
                    else {
                        pos->bigPce[WHITE]++;
                        pos->minPce[WHITE]++;
                        pos->pieces[squareBig] = wB;
                    }
                    break;
                case 'r':
                    if (isBlack) {
                        pos->bigPce[BLACK]++;
                        pos->majPce[BLACK]++;
                        pos->pieces[squareBig] = bR;
                    }
                    else {
                        pos->bigPce[WHITE]++;
                        pos->majPce[WHITE]++;
                        pos->pieces[squareBig] = wR;
                    }
                    break;
                case 'q':
                    if (isBlack) {
                        pos->bigPce[BLACK]++;
                        pos->majPce[BLACK]++;
                        pos->pieces[squareBig] = bQ;
                    }
                    else {
                        pos->bigPce[WHITE]++;
                        pos->majPce[WHITE]++;
                        pos->pieces[squareBig] = wQ;
                    }
                    break;
                case 'k':
                    if (isBlack) {
                        pos->bigPce[BLACK]++;
                        pos->KingSquare[BLACK] = squareBig;
                        pos->pieces[squareBig] = bK;
                    }
                    else {
                        pos->bigPce[WHITE]++;
                        pos->KingSquare[WHITE] = squareBig;
                        pos->pieces[squareBig] = wK;
                    }
                    break;
                case '0' ... '9':
                    num = ch - '0';
                    file += num;
                    break;
                case '\\':
                    // do nothing
                    break;
                default:
                    printf("FEN Parsing error\n");
                    return -1;
            }
            index++;
        }
        rank--;
    }

    return 1;
}