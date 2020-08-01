#include "movegen.h"
#include "stdio.h"
#include "definitions.h"

// Add a "quiet" move to the movelist
void AddQuietMove(const board_t *pos, int move, movelist_t *list) {
    list->moves[list->count].move = move;
    // change this later to evaluate a specific move
    list->moves[list->count].score = 0;
    list->count++;
}

// Add a capture move to the movelist
void AddCaptureMove(const board_t *pos, int move, movelist_t *list) {
    list->moves[list->count].move = move;
    // change this later to evaluate a specific move
    list->moves[list->count].score = 0;
    list->count++;
}

// Add an EnPassant move to the movelist
void AddEnPassantMove(const board_t *pos, int move, movelist_t *list) {
    list->moves[list->count].move = move;
    // change this later to evaluate a specific move
    list->moves[list->count].score = 0;
    list->count++;
}

void GenerateAllMoves(const board_t *pos, movelist_t *list) {
    list->count = 0;
}