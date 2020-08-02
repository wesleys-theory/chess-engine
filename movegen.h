#ifndef MOVEGEN_H
#define MOVEGEN_H

#include "definitions.h"

void AddMove(const board_t *pos, int move, movelist_t *list);
void AddCaptureMove(const board_t *pos, int move, movelist_t *list);
void AddEnPassantMove(const board_t *pos, int move, movelist_t *list);
void GenerateAllMoves(const board_t *pos, movelist_t *list);
void AddWhitePawnCapMove(const board_t *pos, movelist_t *list, const int from,
                        const int to, const int cap);
void AddWhitePawnQuietMove(const board_t *pos, movelist_t *list, const int from,
                      const int to);


#endif