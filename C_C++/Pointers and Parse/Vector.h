//
// Created by damia on 2/25/2020.
//

#ifndef LIBS_VECTOR_H
#define LIBS_VECTOR_H

#include <stdio.h>
#include "Single.h"

struct Vector
{
    struct Single *S;
    unsigned mSize;
    size_t Size;
};

typedef struct Vector Vector;

Vector* VecInit();
void VecDel(Vector *V);
int VecInc(Vector *V);
int VecPush(Vector *V, Single *S);
char* VecGet(Vector *V, unsigned i);
int VecSet(Vector *V, Single *S, unsigned i);
void VecClear(Vector *V);


#endif //LIBS_VECTOR_H
