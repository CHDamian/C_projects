//
// Created by damia on 2/25/2020.
//

#ifndef LIBS_PACK_H
#define LIBS_PACK_H

#include <stdbool.h>

struct Pack
{
    int x;
};

typedef struct Pack Pack;

bool EqP(Pack *a, Pack *b);
bool LefP(Pack *a, Pack *b);
bool LefEP(Pack *a, Pack *b);
bool RigP(Pack *a, Pack *b);
bool RigEP(Pack *a, Pack *b);

#endif //LIBS_PACK_H
