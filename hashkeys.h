#ifndef HASHKEYS_H
#define HASHKEYS_H

#include "definitions.h"


// A random 64 bit number generator
#define RAND64 (\
    (U64)rand() + \
    ((U64)rand() << 15) + \
    ((U64)rand() << 30) + \
    ((U64)rand() << 45) + \
    (((U64)rand() & 0xf) << 60))

void initHashKeys();
U64 GeneratePosKey(const board_t *pos);

#endif